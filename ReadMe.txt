https://github.com/okovtun/PV_123
https://www.youtube.com/watch?v=AL5ArbG1fy8&list=PLeqyOOqxeiINhkggE6tzeBd_wUr9XEaBJ

Венгерская нотация:
https://ru.wikipedia.org/wiki/%D0%92%D0%B5%D0%BD%D0%B3%D0%B5%D1%80%D1%81%D0%BA%D0%B0%D1%8F_%D0%BD%D0%BE%D1%82%D0%B0%D1%86%D0%B8%D1%8F

Book:
https://drive.google.com/drive/folders/1mIhAKMp5-Jpy6s5X8u924tRCXFEdHE_z?usp=sharing

//////////////////////////////////////////////////////////////////////////////////
////////////////				  DATA CONTAINERS				//////////////////
//////////////////////////////////////////////////////////////////////////////////

TODO:
Вынести за пределы класса List методы итерторов и класса Element;

DONE:
1. Оптимизировать методы добавления элементов;
2. Создать ветку master->IteratorsInheritanceInList, и в этой ветке
   оптимизировать все итераторы двусвязного списка используя наследование,
   а так же добавить ConstIterator и ConstReverseIterator 
   (Константные итераторы, которые НЕ позволяют изменять значение по адресу);

DONE:
1. void erase(int index);
2. Оптимизировать методы добавления элементов, так как мы это делали в односвязном списке;
3. Проверочный код должен заработать:
	List list = { 3, 5, 8, 13, 21 };
	for(int i:list)cout << i << tab; cout << endl;

DONE:
Добавить в список следующие методы:
void push_back(int Data);			DONE
void pop_front();					DONE
void pop_back();					DONE
void insert(int index, int Data);	DONE

Destructor;
CopyMethods;
MoveMethods;
ILconstructor;
List list = {3,5,8,13,21};
for(int i: list) cout << i << tab; cout << endl;

DONE:
Проверочный код должен заработать: https://github.com/okovtun/PV_123/blob/2d536b048781e479ebd222d296871243b169e062/DataContainers/ForwardList/main.cpp#L388

DONE:
1. Оптимизировать код в методах push_back() и insert();	DONE
2. Оптимизировать код метода print();			DONE
3. Выражение Temp = Temp->pNext заменить выражением Temp++; Hardcore!

DONE:
0. Написать метод unique(), который находит и удаляет повторяющиеся значения в списке,
   и таким образом, делает список уникальным;
1. Написать метод reverse(), который изменяет порядок следования элементов в списке на противоположный;
2. Проверочный код в секции HOME_WORK_1 должен заработать;
3. Проверрочный код в секции HOME_WORK_2 должен заработать;
	https://github.com/okovtun/PV_123/blob/dc734a6dd077ae062d7edf32f1d2c58a328c7ac9/DataContainers/ForwardList/main.cpp#L217

DONE:
В класс ForwardList добавить методы:
void push_back(int Data);	//добавляет значение в конец списка	DONE
void pop_front();			//удаляет значение с начала списка	DONE
void pop_back();			//удаляет значение с конца списка	DONE
void insert(int index, int value);	//вставляет значение в список по заданному индексу	DONE

void erase(int index);		//удаляет значение из списка по заданному индексу	DONE

Деструктор должен очищать список перед удалением (удалять все элементы из списка).	DONE
CopyMethods;
MoveMethods;
Перегрузить оператор +, который выполняет конкатенацию двух списков.

UML:
https://www.visual-paradigm.com/download/community.jsp
https://app.creately.com/diagram/start/dashboard

//////////////////////////////////////////////////////////////////////////////////
////////////////					INHERITANCE					//////////////////
//////////////////////////////////////////////////////////////////////////////////

https://www.youtube.com/watch?v=UluSI1P4Ijg&list=PLBOPkQsFLCR2H7_0Ss0W6y703J_ySRGi_

TODO:
В нашу иерархию фигур добавить иерархтю треугольников:
	EquilateralTriangle - Равносторонний треугольник;
	IsoscalesTriangle	- Равнобедренный треугольник;
	RightTriangle		- Прямоугольный треугольник;


DONE:
Разработать иерархию геометрических фигур: 
	Квадрат - DONE 
	прямоугольник - Rectangle()	https://docs.microsoft.com/en-us/windows/win32/gdi/about-rectangles
	круг - Ellipce()			https://docs.microsoft.com/en-us/windows/win32/gdi/about-ellipses
	треугольник - Polygon().	https://docs.microsoft.com/en-us/windows/win32/gdi/about-ellipses

https://docs.microsoft.com/en-us/windows/win32/gdi/windows-gdi
https://docs.microsoft.com/en-us/windows/win32/gdi/filled-shapes
https://docs.microsoft.com/en-us/windows/win32/gdi/about-filled-shapes

Для каждой фигуры вывести ее особые свойства (первичные параметры), такие как 
длина стороны, радиус и т.д. (у каждой фигуры они свои) и вторичные параметры: площадь, периметр.
Так же каждую фигуру нужно нарисовать.

http://www.winprog.org/tutorial/
https://www.youtube.com/watch?v=kQ2TTgfvR94&list=PL0_nf9F9pvZNQsdlmE6s0UyixTnT4778Y

DONE:
В иерархию транспортных средств добавить Катер, Яхту, Самолет и вертолет,
и построить диаграмму классов;

DONE:
1. Почитать про *.csv-файлы;
2. В проекте Academy сохранить группу в файл;
3. В проекте Academy загрузить группу из файла;

DONE:
1. При помощи width() и left/right выровнять вывод во всех дочерних классах;
2. Обеспечить ввод объектов PermanentEmployee и HourlyEmployee с клавиатуры;
	PermanentEmployee pe;
	cout << "Введите информацию о сотруднике: ";
	cin >> pe;

http://cplusplus.com/reference/string/string/
http://cplusplus.com/reference/string/string/find_first_not_of/
http://cplusplus.com/reference/string/string/find_last_not_of/

https://www.boost.org/doc/libs/1_78_0/?view=categorized
https://www.boost.org/doc/libs/1_78_0/doc/html/string_algo.html

Base:https://www.youtube.com/watch?v=htkSiXnrqHQ&list=PLeqyOOqxeiIMc8VmOKgzH2KDPzAhl5Gc3

TODO:
1.*Сохранить группу в файл;
2.***Загрузить группу из файла;
http://cplusplus.com/doc/tutorial/files/
3.Есть 2 типа сотрудников - с постоянной оплатой и с почасовой оплатой.
  Нужно создать массив разнотипных сотрудников, 
  и вычислить зарплату для каждого отдельного струдника, и для всего отдела.
  Можно сохранить сотдуников в файл и загрузить их из файла.
  Реализовать в отдельном проекте.

DONE:
В проект Academy добавить классы Teacher и Graduate (Дипломник).


//////////////////////////////////////////////////////////////////////////////////
////////////////						BASE					//////////////////
//////////////////////////////////////////////////////////////////////////////////

TOREAD:
https://www.softelectro.ru/ieee754.html

TODO:
В классе Binary перегрузить операторы 
	& - AND;
	^ - XOR;

DONE:
Релизовать класс Binary, описывающий двоичное число.
Обеспечить выполнение всех арифметических и поитовых операций над двоичными числами.

DONE:
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