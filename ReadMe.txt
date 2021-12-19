https://github.com/okovtun/PV_123
https://www.youtube.com/watch?v=AL5ArbG1fy8&list=PLeqyOOqxeiINhkggE6tzeBd_wUr9XEaBJ

Book:
https://drive.google.com/drive/folders/1mIhAKMp5-Jpy6s5X8u924tRCXFEdHE_z?usp=sharing

TOREAD:
https://www.softelectro.ru/ieee754.html

TODO:
1. В операторе + вместо выражения DONE
	result.get_str()[i] = left.get_str()[i];
   использовать выражение:
    result[i] = left[i];
2. Для класса String перегрузить оператор +=
	String str1 = "Hello";
	String str2 = "World";
	str1 += str2;
	cout << str1 << endl;	//HelloWorld
3. Перегрузить оператор ввода
	String str;
	cout << "Введите строку: "; cin >> str;
	cout << str;

DONE:
В отдельном проекте реализовать класс String, описывающий строку.
Класс должен обеспечивать создание объектов следующим образом:
	String str;	//Пустая строка размером 80 Байт	DONE
	String str1 = "Hello";			DONE
	String str2 = "World";			DONE
**	String str3 = str1 + str2;		DONE
**	cout << str3 << endl;			DONE

	String str4(25);	//Создает пустую строку размером 25 Байт

DONE:
Перегрузить оператор ввода:
	Fraction A;
	cout << "Введите простую дробь: "; cin >> A;
	cout << A << endl;
cin является объектом класса istream.

DONE:
Проверочный код в секции HOME_WORK должен заработать:
	Fraction A(2, 3, 4);
	double a = A;
	cout << a << endl;

	double b = 2.75;
	Fraction B = b;
	B.print();

DONE:
1. Перегрузить все недостающие операторы: +, -, +=, -=, /=;
2. Для класса Fraction перегрузить операторы сравнения:
	==
	!=
	>
	<
	>=
	<=

DONE:
В классе Fraction написать метод reduce(), который сокращает протую дробь.
https://www.webmath.ru/poleznoe/formules_12_7.php

DONE:
В Solution IntroductionToOOP добавить проект Fraction, и в нем реализовать класс Fraction,
описывающий простую дробь. В классе должны быть все необходимые методы и операторы.

Fraction A;	//Default onstructor
A.print();
Fraction B=5;
B.print();
Fraction C(1,2);
C.print();
Fraction D(2,3,4);
D.print()
Fraction E = C*D;
E.print();

DONE:
0. Выучить теорию!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
1. Проанализировать еще раз DISTANCE_CHECK;
2. Проверочный код в секции ASSIGNMENT_CHECK должен заработать:
	Point A, B, C;
	A = B = C = Point(2,3);
	A.print();
	B.print();
	C.print();
   

DONE:
0. Выучить теорию!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
1. Написать метод ??? distance(???), который возвращает расстояние до указанной точки;	DONE
2. Написать функцию ??? distance(???), которая возвращает расстояние между двумя точками;