#include<iostream>
#include<string>
using namespace std;

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, unsigned int age	//Принимаемые переметры конструктора Human
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

class Human
{
	std::string last_name;
	std::string first_name;
	unsigned int age;
public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	unsigned int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(unsigned int age)
	{
		this->age = age;
	}

	//					Constructors:
	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	//				Methods:
	virtual void print()const
	{
		cout << last_name << " " << first_name << " " << age << " лет" << endl;
	}
};

#define EMPLOYEE_TAKE_PARAMETERS	const std::string& position
#define EMPLOYEE_GIVE_PARAMETERS	position

class Employee :public Human	//Наследование
{
	std::string position;	//Должность
public:
	const std::string& get_position()const
	{
		return position;
	}
	void set_position(const std::string& position)
	{
		this->position = position;
	}
	virtual double get_salary()const = 0;

	Employee(HUMAN_TAKE_PARAMETERS, EMPLOYEE_TAKE_PARAMETERS):Human(HUMAN_GIVE_PARAMETERS)//Делегирование
	{
		set_position(position);
		cout << "EConstructor:\t" << this << endl;
	}
	~Employee()
	{
		cout << "EDestructor:\t" << this << endl;
	}

	void print()const
	{
		Human::print();
		cout << position;
		cout << endl;
	}
};

#define PERMANENT_EMPLOYEE_TAKE_PARAMETERS double salary
#define PERMANENT_EMPLOYEE_GIVE_PARAMETERS salary

class PermanentEmployee : public Employee
{
	double salary;	//Зарплата
public:
	double get_salary()const
	{
		return salary;
	}
	void set_salary(double salary)
	{
		this->salary = salary;
	}

	PermanentEmployee
	(
		HUMAN_TAKE_PARAMETERS,	EMPLOYEE_TAKE_PARAMETERS, PERMANENT_EMPLOYEE_TAKE_PARAMETERS
	) :Employee(HUMAN_GIVE_PARAMETERS, EMPLOYEE_GIVE_PARAMETERS)
	{
		set_salary(salary);
		cout << "PEConstructor:\t" << this << endl;
	}
	~PermanentEmployee()
	{
		cout << "PEDestructor:\t" << this << endl;
	}

	void print()const
	{
		Employee::print();
		cout << salary;
		cout << endl;
	}
};

#define HOURLY_EMPLOYEE_TAKE_PARAMETERS double rate, int hours
#define HOURLY_EMPLOYEE_GIVE_PARAMETERS rate, hours

class HourlyEmployee :public Employee
{
	double rate;	//Тариф (ставка за 1 час)
	int hours;		//Количество отработанных часов
public:
	double get_rate()const
	{
		return rate;
	}
	int get_hours()const
	{
		return hours;
	}
	double get_salary()const
	{
		return rate * hours;
	}
	void set_rate(double rate)
	{
		this->rate = rate;
	}
	void set_hours(int hours)
	{
		this->hours = hours;
	}

	HourlyEmployee
	(
		HUMAN_TAKE_PARAMETERS, EMPLOYEE_TAKE_PARAMETERS, HOURLY_EMPLOYEE_TAKE_PARAMETERS
	) :Employee(HUMAN_GIVE_PARAMETERS, EMPLOYEE_GIVE_PARAMETERS)
	{
		set_rate(rate);
		set_hours(hours);
		cout << "HEConstructor:\t" << this << endl;
	}
	~HourlyEmployee()
	{
		cout << "HEDestructor:\t" << this << endl;
	}
	void print()const
	{
		Employee::print();
		cout << " тариф:" << rate << ",отработано:" << hours << " итого:" << get_salary();
		cout << endl;
	}
};

void main()
{
	std::string str = "Hello";
	cout << str.c_str()[1] << endl;;
	cout << typeid(str.c_str()).name() << endl;

	setlocale(LC_ALL, "");
	Employee* department[] =
	{
		new PermanentEmployee("Rosenberg", "Ken", 30, "Lawyer", 2000),
		new PermanentEmployee("Diaz", "Ricardo", 50, "Boss", 50000),
		new HourlyEmployee("Vercetty", "Tomas", 30, "Security", 500, 8)
	};

	double total_salary = 0;	//Общая зарплата
	//sizeof(department) / sizeof(Employee*) - Делим размер массива в Байтах на размер одного указателя,
	//и таким образом получаем размер массива в элементах.
	for (int i = 0; i < sizeof(department) / sizeof(Employee*); i++)
	{
		cout << "\n--------------------------------------\n";
		department[i]->print();
		total_salary += department[i]->get_salary();
	}
	cout << "\n--------------------------------------\n";
	cout << "Общая зарплата всего отдела: " << total_salary << endl;
	cout << "\n--------------------------------------\n";

	for (int i = 0; i < sizeof(department) / sizeof(Employee*); i++)
	{
		delete department[i];
	}
}