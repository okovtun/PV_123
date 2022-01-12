#include<iostream>
#include<string>
using namespace std;

//#define DEBUG

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
#ifdef DEBUG
		cout << "HConstructor:\t" << this << endl;
#endif // DEBUG

	}
	virtual ~Human()
	{
#ifdef DEBUG
		cout << "HDestructor:\t" << this << endl;
#endif // DEBUG

	}

	//				Methods:
	virtual void print()const
	{
		cout << last_name << " " << first_name << " " << age << " лет" << endl;
	}
};

ostream& operator<<(ostream& os, const Human& obj)
{
	return os << obj.get_last_name() << " " << obj.get_first_name() << " " << obj.get_age() << " лет.";
}

#define EMPLOYEE_TAKE_PARAMETERS	const std::string& position
#define EMPLOYEE_GIVE_PARAMETERS	position


//АБСТРАКТНЫЙ КЛАСС
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

	Employee(HUMAN_TAKE_PARAMETERS, EMPLOYEE_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)//Делегирование
	{
		set_position(position);
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Employee()
	{
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}

	void print()const
	{
		Human::print();
		cout << position;
		cout << endl;
	}
};

ostream& operator<<(ostream& os, const Employee& obj)
{
	//os << (Human)obj;
	return os << (Human)obj << obj.get_position();
}

#define PERMANENT_EMPLOYEE_TAKE_PARAMETERS double salary
#define PERMANENT_EMPLOYEE_GIVE_PARAMETERS salary

//КОНКРЕТНЫЙ КЛАСС
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
		HUMAN_TAKE_PARAMETERS, EMPLOYEE_TAKE_PARAMETERS, PERMANENT_EMPLOYEE_TAKE_PARAMETERS
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

ostream& operator<<(ostream& os, const PermanentEmployee& obj)
{
	return os << (Employee&)obj << " " << obj.get_salary();
}

#define HOURLY_EMPLOYEE_TAKE_PARAMETERS double rate, int hours
#define HOURLY_EMPLOYEE_GIVE_PARAMETERS rate, hours

//КОНКРЕТНЫЙ КЛАСС
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

ostream& operator<<(ostream& os, const HourlyEmployee& obj)
{
	return os
		<< (Employee&)obj
		<< "rate: " << obj.get_rate() << "hours:" << obj.get_hours()
		<< "total: " << obj.get_salary();
}

void main()
{
	std::string str = "Hello";
	cout << str.c_str()[1] << endl;;
	cout << typeid(str.c_str()).name() << endl;

	setlocale(LC_ALL, "");
	//Generalisation(UPCAST):
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
		//department[i]->print();
		cout << typeid(*department[i]).name() << endl;
		//Specialisation(DOWNCAST):

		//int - int
		//int* - Указатель на int

		if(typeid(*department[i]) == typeid(PermanentEmployee))	
			cout << *dynamic_cast<PermanentEmployee*>(department[i]) << endl;
		if(typeid(*department[i]) == typeid(HourlyEmployee))
			cout << *dynamic_cast<HourlyEmployee*>(department[i]) << endl;
		//dynamic_cast<DerivedClass*>(BaseClass*);
		//dynamic_cast<ЦелевойТип>(ПреобразуемоеЗначение)
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