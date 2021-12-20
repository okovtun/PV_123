#include"String.h"
#define delimiter "\n-------------------------------------------------\n"


///--------------------------------------------------------------------------------------------///



//char str[] = { 'S', 't', 'r', 'o', 'k', 'a' };

//#define CONSTRUCTORS_CHECK
#define OPERATORS_CHECK
//#define INPUT_CHECK

void main()
{
	//char test[1024 * 1024]{};
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	String str1;		//Default constructor
	str1.print();
	cout << str1 << endl;

	String str2(25);	//Single-argument constructor
	str2.print();

	String str3 = "Hello";
	str3 = str3;
	cout << str3 << endl;

	String str4 = str3;	//CopyConstructor
	//Deep copy
	//Shallow copy
	//Debug Assertion Failed
	cout << str4 << endl;

	String str5;
	str5 = str3;	//CopyAssignment (operator=)
	cout << str5 << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef OPERATORS_CHECK
	int a = 2;
	int b = 3;
	int c = a + b;

	String str1 = "Hello";
	String str2 = "World";
	cout << delimiter << endl;
	String str3 = str1 + str2;
	cout << delimiter << endl;
	cout << str3 << endl;
	cout << delimiter << endl;
	str1 += str2;
	cout << delimiter << endl;
	cout << str1 << endl;
	cout << delimiter << endl;
#endif // OPERATORS_CHECK


#ifdef INPUT_CHECK
	String str;
	cout << "Введите строку: ";
	//cin >> str;
	getline(cin, str);
	cout << str << endl;
	str.print();
#endif // INPUT_CHECK

}