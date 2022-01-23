#include <iostream>
#include <string>
#include <fstream>


using std::string;
using std::cout;
using std::cin;
using std::endl;

//                                               ACADEMY                             //

// DEFINITIONS:

// Human:
#define HUMAN_TAKE_PARAMETERS const string& first_name, const string& last_name, unsigned int age
#define HUMAN_GIVE_PARAMETERS first_name, last_name, age
//Student:
#define STUDENT_TAKE_PARAMETERS const string& speciality, const string& group, unsigned int rating, unsigned int attending
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attending
//Teacher:
#define TEACHER_TAKE_PARAMETERS const string& speciality, unsigned int experience, unsigned int salary
#define TEACHER_GIVE_PARAMETERS speciality, experience, salary
//Employee:
#define EMPLOYEE_TAKE_PARAMETERS const string& position, unsigned int experience, unsigned int salary
#define EMPLOYEE_GIVE_PARAMETERS position, experience, salary

// ClASSES:

class Human {
	string first_name;
	string last_name;
	unsigned int age;
public:

	// Get - , Set - methods:

	const string& get_first_name()const
	{
		return first_name;
	}
	const string& get_last_name()const
	{
		return last_name;
	}
	unsigned int get_age()const
	{
		return age;
	}

	void set_first_name(const string& first_name)
	{
		this->first_name = first_name;
	}
	void set_last_name(const string& last_name)
	{
		this->last_name = last_name;
	}
	void set_age(unsigned int age)
	{
		this->age = age;
	}
	// Constructors:

	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_first_name(first_name);
		set_last_name(last_name);
		set_age(age);
		// cout << "\nHuman Constructor: \t" << this << endl;
	}
	virtual ~Human()
	{
		//cout << "Human Destructor: \t" << this << endl;
	}
	// Methods:
	virtual std::ostream& print(std::ostream& os) const
	{
		os << "Name: ";
		os.width(5);
		os << std::left;
		os << last_name << " ";
		os.width(5);
		os << first_name << " ";
		os << "Age: ";
		os.width(3);
		os << age << "years ";
		return os;
	}
	virtual std::ofstream& print(std::ofstream& os)const
	{
		os.width(5);
		os << std::left;
		os << last_name;
		os.width(10);
		os << first_name;
		os.width(10);
		os << age;
		return os;
	}
	virtual std::istream& input(std::istream& is)
	{
		cout << "Last name:  ";
		is >> last_name;
		cout << "First name: ";
		is >> first_name;
		cout << "Age:        ";
		is >> age;
		return is;
	}
	virtual std::ifstream& scan(std::ifstream& is)
	{
		is >> last_name >> first_name >> age;
		return is;
	}
};

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.print(os);
}
std::istream& operator>>(std::istream& is, Human& obj)
{
	return obj.input(is);
}
std::ofstream& operator<<(std::ofstream& os, const Human& obj)
{
	return obj.print(os);
}
std::ifstream& operator>>(std::ifstream& is, Human& obj)
{
	return obj.scan(is);
}

class Student : public Human {
	string speciality;
	string group;
	unsigned int rating;
	unsigned int attending;
public:

	// Get - , Set - methods:

	const string& get_speciality() const
	{
		return speciality;
	}
	const string& get_group()const
	{
		return group;
	}
	unsigned int get_rating()
	{
		return rating;
	}
	unsigned int get_attending()
	{
		return attending;
	}

	void set_speciality(const string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const string& group)
	{
		this->group = group;
	}
	void set_rating(unsigned int rating)
	{
		this->rating = rating;
	}
	void set_attending(unsigned int attending)
	{
		this->attending = attending;
	}
	// Constructors:

	Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS) : Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attending(attending);
		//  cout << "Student Constructor: \t" << this << endl;
	}
	~Student()
	{
		//  cout << "Student Destructor: \t" << this << endl;
	}
	//    void print()const
	//    {
	//        Human::print();
	//        cout << "\nSpeciality: " << speciality << endl;
	//        cout << "\nFaculty: " << group << endl;
	//        cout << "\nRating: " << rating << endl;
	//        cout << "\nAttending: " << attending << endl;
	//    }

	std::ostream& print(std::ostream& os)const
	{
		Human::print(os);
		os.width(8);
		os << std::left;
		os << "\nSpeciality: " << speciality;
		os.width(3);
		os << "\nFaculty:    " << group;
		os.width(3);
		os << "\nRating:     " << rating;
		os.width(3);
		os << "\nAttending:  " << attending;
		return os;
	}
	std::ofstream& print(std::ofstream& os)const
	{
		Human::print(os);
		os.width(10);
		os << std::left;
		os << speciality;
		os.width(10);
		os << group;
		os.width(10);
		os << rating;
		os.width(10);
		os << attending;
		return os;
	}
	std::istream& input(std::istream& is)
	{
		Human::input(is);
		cout << "\nSpeciality: ";
		is >> speciality;
		cout << "\nFaculty:    ";
		is >> group;
		cout << "\nRating:     ";
		is >> rating;
		cout << "\nAttending:  ";
		is >> attending;
		return is;
	}
	std::ifstream& scan(std::ifstream& is)
	{
		Human::scan(is);
		is >> speciality;
		is >> group;
		is >> rating;
		is >> attending;
		return is;
	}
};

class Teacher : public Human {
	string speciality;
	unsigned int experience;
	unsigned int salary;
public:
	// Get - , Set - methods:

	const string& get_speciality()const
	{
		return speciality;
	}
	unsigned int get_experience()
	{
		return experience;
	}
	unsigned int get_salary()
	{
		return salary;
	}
	void set_speciality(const string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experience(unsigned int experience)
	{
		this->experience = experience;
	}
	void set_salary(unsigned int salary)
	{
		this->salary = salary;
	}
	// Constructors:

	Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS) : Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_experience(experience);
		set_salary(salary);
		//  cout << "Teacher constructor: \t" << this << endl;
	}
	~Teacher()
	{
		//  cout << "Teacher Destructor: \t" << this << endl;
	}
	// Methods:

//    void print() const
//    {
//        Human::print();
//        cout << "Speciality: " << speciality << endl;
//        cout << "Working experience: " << experience << endl;
//        cout << "Salary: " << salary << endl;
//    }

	std::ostream& print(std::ostream& os)const
	{
		Human::print(os);
		os.width(8);
		os << std::left;
		os << "\nSpeciality:            " << speciality;
		os.width(3);
		os << "\nWorking experience:    " << experience;
		os.width(3);
		os << "\nSalary:                " << salary;
		return os;
	}

	std::ofstream& print(std::ofstream& os)const
	{
		Human::print(os);
		os.width(8);
		os << std::left;
		os << speciality;
		os.width(3);
		os << experience;
		os.width(3);
		os << salary;
		return os;
	}
	std::istream& input(std::istream& is)
	{
		Human::input(is);
		cout << "\nSpeciality:          ";
		is >> speciality;
		cout << "\nWorking experience:  ";
		is >> experience;
		cout << "\nSalary:              ";
		is >> salary;
		return is;
	}
	std::ifstream& scan(std::ifstream& is)
	{
		Human::scan(is);
		is >> speciality;
		is >> experience;
		is >> salary;
		return is;
	}

};

class Employee : public Human {
	string position;
	unsigned int experience;
	unsigned int salary;
public:

	// Get -, Set - Methods:

	const string& get_position()const
	{
		return position;
	}
	unsigned int get_experience()
	{
		return experience;
	}
	unsigned int get_salary()
	{
		return salary;
	}
	void set_position(const string& position)
	{
		this->position = position;
	}
	void set_experience(unsigned int experience)
	{
		this->experience = experience;
	}
	void set_salary(unsigned int salary)
	{
		this->salary = salary;
	}
	// Constructors:

	Employee(HUMAN_TAKE_PARAMETERS, EMPLOYEE_TAKE_PARAMETERS) : Human(HUMAN_GIVE_PARAMETERS)
	{
		set_position(position);
		set_experience(experience);
		set_salary(salary);
		//  cout << "Employee constructor: \t" << this << endl;
	}
	~Employee()
	{
		//  cout << "Employee Destructor: \t" << this << endl;
	}
	// Methods:

//    void print() const
//    {
//        Human::print();
//        cout << "Position: " << position << endl;
//        cout << "Working experience: " << experience << endl;
//        cout << "Salary: " << salary << endl;
//    }
	std::ostream& print(std::ostream& os)const
	{
		Human::print(os);
		os.width(8);
		os << std::left;
		os << "\nPosition:            " << position;
		os.width(3);
		os << "\nWorking experience:    " << experience;
		os.width(3);
		os << "\nSalary:                " << salary;
		return os;
	}
	std::ofstream& print(std::ofstream& os)const
	{
		Human::print(os);
		os.width(8);
		os << std::left;
		os << position;
		os.width(3);
		os << experience;
		os.width(3);
		os << salary;
		return os;
	}
	std::istream& input(std::istream& is)
	{
		Human::input(is);
		cout << "\nPosition:          ";
		is >> position;
		cout << "\nWorking experience:  ";
		is >> experience;
		cout << "\nSalary:              ";
		is >> salary;
		return is;
	}
	std::ifstream& scan(std::ifstream& is)
	{
		Human::scan(is);
		is >> position;
		is >> experience;
		is >> salary;
		return is;
	}
};

//#define SAVE_TO_FILE
#define RECORD_TO_FILE

Human* humanFactory(const string& type)
{
	Human* human = nullptr;

	if (type.find("Student") != std::string::npos)
	{
		human = new Student("", "", 0, "", "", 0, 0);
	}
	if (type.find("Teacher") != std::string::npos)
	{
		human = new Teacher("", "", 0, "", 0, 0);
	}
	if (type.find("Employee") != std::string::npos)
	{
		human = new Employee("", "", 0, "", 0, 0);
	}

	return human;
}


//Student* humanFaculty(const string& type)
//{
//    Student* student = nullptr;
//    if(type.find("faculty") != std::string::npos)
//    {
//        student = new Student("", "", 0, "", "", 0, 0);
//    }
//    return student;
//}
//Teacher* teacherDepartment(const string& type)
//{
//    Teacher* teacher = nullptr;
//    if(type.find("department") != std::string::npos)
//    {
//        teacher = new Teacher("", "", 0, "", 0, 0);
//    }
//    return teacher;
//}
//Employee* staffDepartment(const string& type)
//{
//    Employee* staff = nullptr;
//    if(type.find("staff") != std::string::npos)
//    {
//        staff = new Employee("", "", 0, "", 0, 0);
//    }
//    return staff;
//}

int main(int argc, const char * argv[])
{
#ifdef SAVE_TO_FILE

	Student* faculty[] =
	{
		new Student("Harry", "Potter", 15, "wizard", "Griffindor", 5, 100),
		//new Student("Ronald", "Weaseley", 15, "wizard", "Griffindor", 5, 100),
		//new Student("Hermione", "Granger", 15, "wizard", "Griffindor", 5, 100),
	};

	Teacher* department[] =
	{
		new Teacher("Severus", "Snape", 37, "potion-making", 14, 1587),
		//new Teacher("Alastor", "Moody", 56, "defence-against-art-Dark", 1, 2600),
		//new Teacher("Minerva", "McGonagall", 54, "transfiguration", 30, 3500),
	};

	Employee* staff[] =
	{
		new Employee("Argus", "Filch", 69, "caretaker", 32, 900),
	};

	unsigned int total_salary = 0;
	unsigned int total_experience = 0;

	// INPUT

	for (int i = 0; i < sizeof(faculty) / sizeof(Student*); ++i)
	{
		cout << "\n _________________________ \n";
		//cout << *faculty[i];
		cin >> *faculty[i];
	}

	for (int i = 0; i < sizeof(department) / sizeof(Teacher*); ++i)
	{
		cout << "\n _________________________ \n";
		//cout << *department[i];
		cin >> *department[i];
		//total_salary += department[i] -> get_salary();
	}

	for (int i = 0; i < sizeof(staff) / sizeof(Employee*); ++i)
	{
		cout << "\n _________________________ \n";
		//cout << *staff[i];
		cin >> *staff[i];
	}

	// OUTPUT
	for (int i = 0; i < sizeof(faculty) / sizeof(Student*); ++i)
	{
		cout << "\n _________________________ \n";
		cout << *faculty[i];
	}

	for (int i = 0; i < sizeof(department) / sizeof(Teacher*); ++i)
	{
		cout << "\n _________________________ \n";
		cout << *department[i];
		total_salary += department[i]->get_salary();
	}

	for (int i = 0; i < sizeof(staff) / sizeof(Employee*); ++i)
	{
		cout << "\n _________________________ \n";
		cout << *staff[i];
	}

	total_salary += staff[0]->get_salary();
	total_experience += staff[0]->get_experience();

	cout << "\n _________________________ \n";
	cout << "Total salary: " << total_salary << endl;
	cout << "Total experience: " << total_experience << endl;
	cout << "\n _________________________ \n";

	// OUTPUT IN FILE

	std::ofstream fout("/Users/antonkurin/Documents/Cplusplus/InheritanceCplusplus/file.txt");

	for (int i = 0; i < sizeof(faculty) / sizeof(Student*); ++i)
	{
		fout.width(10);
		fout << std::left;
		fout << string(typeid(*faculty[i]).name()) + ":";
		fout << *faculty[i];
	}

	for (int i = 0; i < sizeof(department) / sizeof(Teacher*); ++i)
	{
		fout.width(10);
		fout << std::left;
		fout << string(typeid(*department[i]).name()) + ":";
		fout << *department[i];
		total_salary += department[i]->get_salary();
	}

	for (int i = 0; i < sizeof(staff) / sizeof(Employee*); ++i)
	{
		fout.width(10);
		fout << std::left;
		fout << string(typeid(*staff[i]).name()) + ":";
		fout << *staff[i];
	}
	fout.close();

	system("more /Users/antonkurin/Documents/Cplusplus/InheritanceCplusplus/file.txt");


	// CLEAR MEMORY

	for (int i = 0; i < sizeof(faculty) / sizeof(Student*); ++i)
	{
		delete faculty[i];
	}

	for (int i = 0; i < sizeof(department) / sizeof(Teacher*); ++i)
	{
		delete department[i];
	}

	for (int i = 0; i < sizeof(staff) / sizeof(Employee*); ++i)
	{
		delete staff[i];
	}

#endif // SAVE_TO_FILE

#ifdef RECORD_TO_FILE

	//Student** faculty = nullptr;
	//Teacher** department = nullptr;
	//Employee** staff = nullptr;

	Human** group = nullptr;    //Здесь мы НЕ знаем сколько памяти нужно для массива

	int n = 0;
	std::ifstream fin("file.txt");

	if (fin.is_open())
	{
		//string student_type;
		//string teacher_type;
		//string staff_type;

		string type;
		//Вычисляем объем необходимой памяти для массива:
		for (; !fin.eof(); n++)
		{
			getline(fin, type); // необходимо просто посчитать количество строк в файле
		}
		//n--;

		//Выделяем память:
		group = new Human*[n] {};
		//faculty = new Student*[n] {};
		//department = new Teacher*[n] {};
		//staff = new Employee*[n] {};

		fin.clear();
		fin.seekg(0);
		/*
			  for(int i = 0; i < n; ++i)
			  {
				  getline(fin, student_type, ':');
				  faculty[i] = studentFaculty(student_type);
				  fin >> *faculty[i];
			  }

			  for(int i = 0; i < n; ++i)
			  {
				  getline(fin, teacher_type, ':');
				  department[i] = teacherDepartment(teacher_type);
				  fin >> *department[i];
			  }
			  for(int i = 0; i < n; ++i)
			  {
				  getline(fin, staff_type, ':');
				  staff[i] = staffDepartment(staff_type);
				  fin >> *staff[i];
			  }
		 */

		for (int j = 0; j < n; j++)
		{
			std::getline(fin, type, ':');
			group[j] = humanFactory(type);
			fin >> *group[j];
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: file is not found" << endl;
	}

	//    for(int i = 0; i < n; ++i)
	//    {
	//        cout << *faculty[i] << endl;
	//    }
	//    for(int i = 0; i < n; ++i)
	//    {
	//        cout << *department[i] << endl;
	//    }
	//    for(int i = 0; i < n; ++i)
	//    {
	//        cout << *staff[i] << endl;
	//    }

		// CLEAR MEMORY
		/*
		for (int i = 0; i < n; ++i)
		{
			delete faculty[i];
		}
		for (int i = 0; i < n; ++i)
		{
			delete department[i];
		}
		for (int i = 0; i < n; ++i)
		{
			delete staff[i];
		}

		delete [] faculty;
		delete [] department;
		delete [] staff;
		 */
	for (int i = 0; i < n; ++i)
	{
		cout << *group[i] << endl;
	}
	for (int i = 0; i < n; ++i)
	{
		delete group[i];
	}
	delete[] group;

	

#endif // RECORD_TO_FILE

	return 0;
}



//	virtual type name(parameters) const = 0;
//	virtual type name(parameters) = 0;
//	= 0; показывает, что у метода нет определения.