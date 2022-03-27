#include<iostream>
#include<thread>
#include<conio.h>
#include<Windows.h>
using namespace std;
using namespace std::chrono_literals;

#define Escape	27
#define Enter	13

#define MIN_TANK_VOLUME	20
#define MAX_TANK_VOLUME	80

#define MIN_ENGIN_CONSUMPTION	3
#define MAX_ENGIN_CONSUMPTION	25
#define DEFAULT_ENGINE_CONSUMPTION	10

#define MAX_SPEED_LOW_LIMIT		150
#define MAX_SPEED_HIGH_LIMIT	300
#define DEFAULT_MAX_SPEED		250

#define MIN_ACCELLERATION		5
#define MAX_ACCELLERATION		25
#define DEFAULT_ACCELLERATION	12

class Tank
{
	const unsigned int VOLUME;	//Характеристика бака - его объем
	double fuel_level;
public:
	unsigned int get_VOLUME()const
	{
		return this->VOLUME;
	}
	double get_fuel_level()const
	{
		return fuel_level;
	}
	void fill(double fuel_level)
	{
		if (fuel_level <= 0)return;
		if (this->fuel_level + fuel_level <= VOLUME)this->fuel_level += fuel_level;
		else this->fuel_level = VOLUME;
	}
	double give_fuel(double amount)
	{
		if (fuel_level - amount > 0)fuel_level -= amount;
		else fuel_level = 0;
		return fuel_level;
	}
	Tank(const unsigned int volume) :
		VOLUME(volume >= MIN_TANK_VOLUME && volume <= MAX_TANK_VOLUME ? volume : 60)
	{
		//Константный член класса можно проинициализировать только в списке инициализации конструктора
		//(только в заголовке)
		/*if (volume >= MIN_TANK_VOLUME && volume <= MAX_TANK_VOLUME)this->VOLUME = volume;
		else this->VOLUME = 60;*/
		this->fuel_level = 0;
		cout << "Tank is ready" << endl;
	}
	~Tank()
	{
		cout << "Tank is over" << endl;
	}

	void info()const
	{
		cout << "Tank volume: " << VOLUME << " liters\n";
		cout << "Fuel level:  " << fuel_level << " liters\n";
	}
};

class Engine
{
	double consumption;	//расход на 100 км
	double consumption_per_second;	//расход за одну секунду
	bool is_started;	//двигатель заведен или заглушен
public:
	double get_consumption()const
	{
		return consumption;
	}
	double get_consumption_per_second()const
	{
		return consumption_per_second;
	}
	void set_consumption(double consumption)
	{
		if (consumption >= MIN_ENGIN_CONSUMPTION && consumption <= MAX_ENGIN_CONSUMPTION)
			this->consumption = consumption;
		else
			this->consumption = DEFAULT_ENGINE_CONSUMPTION;
		this->consumption_per_second = this->consumption*3e-5;
	}
	void start()
	{
		is_started = true;
	}
	void stop()
	{
		is_started = false;
	}
	bool started()const
	{
		return is_started;
	}
	void info()const
	{
		cout << "Consumption per 100 km: " << consumption << " liters\n";
		cout << "Consumption per second: " << consumption_per_second << " liters\n";
	}

	Engine(double consumption)
	{
		set_consumption(consumption);
		is_started = false;
		cout << "Engine is ready" << endl;
	}
	~Engine()
	{
		cout << "Engine is over" << endl;
	}
};

class Car
{
	Engine engine;
	Tank tank;
	bool driver_inside;
	int speed;			//скорость
	const int MAX_SPEED;//максимальная скорость
	int accelleration;	//ускорение
	struct Control
	{
		std::thread panel_thread;		//отображение панели приборов
		std::thread engine_idle_thread;	//холостой ход двигателя
		std::thread free_wheeling_thread;//замедляет скорость автомобиля
	}control;
public:
	Car(double engine_consumption, unsigned int tank_volume, int max_speed = DEFAULT_MAX_SPEED, int accelleration = 10)
		:engine(engine_consumption), tank(tank_volume),
		MAX_SPEED(max_speed >= MAX_SPEED_LOW_LIMIT && max_speed <= MAX_SPEED_HIGH_LIMIT ? max_speed : DEFAULT_MAX_SPEED)
	{
		driver_inside = false;
		speed = 0;
		//MAX_SPEED = max_speed;
		this->accelleration = accelleration >= MIN_ACCELLERATION && accelleration <= MAX_ACCELLERATION ? accelleration : DEFAULT_ACCELLERATION;

		cout << "Your car is ready" << endl;
	}
	~Car()
	{
		cout << "Car is over" << endl;
	}
	void get_in()
	{
		driver_inside = true;
		//panel();
		control.panel_thread = std::thread(&Car::panel, this);
	}
	void get_out()
	{
		driver_inside = false;
		if (control.panel_thread.joinable())control.panel_thread.join();
		system("CLS");
		cout << "You are out of your car" << endl;
	}
	void start_engine()
	{
		if (driver_inside && tank.get_fuel_level())
		{
			engine.start();
			control.engine_idle_thread = std::thread(&Car::engine_idle, this);
		}
	}
	void stop_engine()
	{
		engine.stop();
		if (control.engine_idle_thread.joinable())control.engine_idle_thread.join();
	}
	void control_car()
	{
		cout << "Press Enter to get in" << endl;
		char key;
		do
		{
			key = _getch();
			switch (key)
			{
			case Enter:
				if (driver_inside)get_out();
				else get_in();
				break;	//Вход/Выход из машины
			case 'I':	
			case 'i':	//ignition - зажигание
				if (engine.started())stop_engine();
				else start_engine();
				break;
			case 'F':
			case 'f':	//fill - заправка
				if (driver_inside)
				{
					cout << "Для того, чтобы заправиться, нужно выйти из машины" << endl;
				}
				else
				{
					double amount;	//количество заправляемого топлива
					cout << "Введите литраж: "; cin >> amount;
					tank.fill(amount);
					cout << "Заправка успешно завершина" << endl;
				}
				break;
			case 'W':case 'w':	//Газ
				if (driver_inside && engine.started())
				{
					if (speed < MAX_SPEED)speed += accelleration;
					if (speed > MAX_SPEED)speed = MAX_SPEED;
					if (!control.free_wheeling_thread.joinable())
						control.free_wheeling_thread = std::thread(&Car::free_wheeling, this);
					std::this_thread::sleep_for(1s);
				}
				break;
			case 'S':case 's'://тормоз	
				//slow_down();	break;
				if (driver_inside && speed > 0)
				{
					speed -= accelleration;
					if (speed < 0)speed = 0;
					std::this_thread::sleep_for(1s);
				}
				break;
			case Escape:
				stop_engine();
				get_out();
				break;
			}
			if (speed == 0 && control.free_wheeling_thread.joinable())
				control.free_wheeling_thread.join();
		} while (key != Escape);
	}
	void panel()const
	{
		while (driver_inside)
		{
			system("CLS");
			cout << "Speed:\t" << speed << "km/h\n";
			cout << "Fuel level: " << tank.get_fuel_level() << " liters\t";
			if (tank.get_fuel_level() < 5)
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 0xCF);
				cout << "LOW FUEL";
				SetConsoleTextAttribute(hConsole, 0x07);
			}
			cout << endl;
			cout << "Engine is " << (engine.started() ? "started" : "stopped") << endl;
			std::this_thread::sleep_for(1s);
		}
	}
	void engine_idle()
	{
		while (engine.started() && tank.give_fuel(engine.get_consumption_per_second()))
		{
			std::this_thread::sleep_for(1s);
		}
	}
	void free_wheeling()
	{
		while (speed > 0)
		{
			speed--;
			if (speed < 0)speed = 0;
			std::this_thread::sleep_for(1s);
		}
	}

	void info()const
	{
		engine.info();
		tank.info();
	}
};

//#define TANK_CHECK
//#define ENGINE_CHECK

void main()
{
	//throw std::exception();
	setlocale(LC_ALL, "");
#ifdef TANK_CHECK
	Tank tank(40);
	tank.info();
	int fuel;
	while (true)
	{
		cout << "Введите объем топлива: "; cin >> fuel;
		tank.fill(fuel);
		tank.info();
	}
#endif // TANK_CHECK

#ifdef ENGINE_CHECK
	Engine engine(10);
	engine.info();
#endif // ENGINE_CHECK

	Car bmw(12, 60);
	//bmw.info();
	bmw.control_car();
}