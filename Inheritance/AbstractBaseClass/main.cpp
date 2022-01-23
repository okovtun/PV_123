#include<iostream>
using namespace std;

class Vehicle
{
	int speed;
public:
	virtual void move() = 0;//Чисто виртуальный метод.
	//Именно этот метод и делает класс абстрактным.
};

class GroundVehicle : public Vehicle {};

class Car :public GroundVehicle
{
public:
	void move()
	{
		cout << "Машина едит на 4-х колесах" << endl;
	}
};

class Bike :public GroundVehicle
{
public:
	void move()
	{
		cout << "Мотоцикл едит на 2-х колесах" << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	//Vehicle v;		//Abstract
	//GroundVehicle gv;	//Abstract

	Car bmw;	//Неявный конструктор по умолчанию.
	bmw.move();
	Bike harley_devidson;
}