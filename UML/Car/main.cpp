#include<iostream>
#include<conio.h>
using namespace std;

#define Escape	27
#define Enter	13

#define MIN_TANK_VOLUME	20
#define MAX_TANK_VOLUME	80

#define MIN_ENGIN_CONSUMPTION	3
#define MAX_ENGIN_CONSUMPTION	25

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
	Tank(const unsigned int volume):
		VOLUME(volume>=MIN_TANK_VOLUME&&volume<=MAX_TANK_VOLUME?volume:60)
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
			this->consumption = 10;
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
public:
	Car(double engine_consumption, unsigned int tank_volume)
		:engine(engine_consumption), tank(tank_volume)
	{
		driver_inside = false;
		cout << "Your car is ready" << endl;
	}
	~Car()
	{
		cout << "Car is over" << endl;
	}
	void get_in()
	{
		driver_inside = true;
		panel();
	}
	void get_out()
	{
		driver_inside = false;
		system("CLS");
		cout << "You are out of your car" << endl;
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
			}
		} while (key != Escape);
	}
	void panel()const
	{
		system("CLS");
		cout << "Fuel level: " << tank.get_fuel_level() << " liters\n";
		cout << "Engine is " << (engine.started() ? "started" : "stopped") << endl;
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