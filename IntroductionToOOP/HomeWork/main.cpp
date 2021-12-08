#include<iostream>
using std::cin;
using std::cout;
using std::endl;

class Fraction;
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(Fraction left, Fraction right);
Fraction operator+(Fraction left, Fraction right);
Fraction operator-(Fraction left, Fraction right);

class Fraction
{
	int integer; //öåëàÿ ÷àñòü
	int numerator;//×èñëèòåëü
	int denominator;//Çíàìåíàòåëü
public:

	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}

	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;	//Îòôèëüòðîâûâàåì 0
		this->denominator = denominator;
	}
	//         Constructor:

	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << " DefaultConstruct:\t" << this << endl;
	}
	Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "lagrConstructor:\t" << this << endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);// ×òîáû íå îáîéòè ôèëüòðàöèþ äàííûõ
		cout << "Constructor:\t" << this << endl;
	}

	Fraction(int integer, int numerator, int denomenator)
	{
		this->integer = integer;
		this->numerator = numerator;
		this->denominator = denomenator;
		cout << "Constructor;\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t" << endl;
	}
	//     Operators:


	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this * other;
	}//          A    =    A   *  B
	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}
	Fraction& operator+=(const Fraction& other)
	{
		return *this = *this + other;
	}
	Fraction& operator-=(const Fraction& other)
	{
		return *this = *this - other;
	}


	//        Methods:
	Fraction& to_improper()//ïåðåâîäèò äðîáü â íåïðàâèëüíóþ
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& to_proper()//Ïåðåâîäèò äðîáü â ïðàâèëüíóþ
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}

	void print()const
	{
		if (integer)cout << integer;//Åñëè åñòü öåëàÿ ÷àñòü, âûâîäèì åå íà ýêðàí
		if (numerator)
		{
			if (integer)cout << "(";
			cout << numerator << "/" << denominator;
			if (integer)cout << ")";
		}
		else if (integer == 0)cout << 0;
		cout << endl;
	}
	Fraction inverted()
	{
		to_improper();
		return Fraction(this->denominator, this->numerator);
	}
	Fraction& reduce()
	{
		int more, less;
		int rest;
		if (numerator > denominator)
		{
			more = numerator;
			less = denominator;
		}
		else
		{
			less = numerator;
			more = denominator;
		}
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int gcd = more;
		numerator /= gcd;
		denominator /= gcd;
		return *this;
	}

};

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	//Fraction result
	//(
	//	left.get_numerator() * right.get_numerator(),
	//	left.get_denominator() * right.get_denominator()
	//	);
	//result.set_numerator(left.get_numerator() * right.get_numerator());
	//result.set_denominator(left.get_denominator() * right. get_denominator());
	//result.to_proper();
	//return result;
	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();
}
Fraction operator/(Fraction left, Fraction right)
{
	return left * right.inverted();
}

Fraction operator+(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(left.get_numerator() * right.get_denominator()
		+ right.get_numerator() * left.get_denominator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();
}
Fraction operator-(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(left.get_numerator() * right.get_denominator()
		- right.get_numerator() * left.get_denominator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();

}

bool operator==(Fraction left, Fraction right)
{
	return left.get_numerator() == right.get_numerator() &&
		left.get_denominator() == right.get_denominator();
}
bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(left == right);

}
bool operator>(Fraction left, Fraction right)
{
	return	left.to_improper().get_numerator() * right.get_denominator() >
		right.to_improper().get_numerator() * left.get_denominator();
}
bool operator<(Fraction left, Fraction right)
{

	return	left.to_improper().get_numerator() * right.get_denominator() <
		right.to_improper().get_numerator() * left.get_denominator();
}
bool operator<=(const Fraction& left, const Fraction& right)
{
	return !(left < right);
}
bool operator>=(const Fraction& left, const Fraction& right)
{
	return !(left > right);
}
//#define CONCTRUCTOR_CHEK

void main()
{
	setlocale(LC_ALL, "");
#ifdef CONCTRUKTOR_CHEK

	Fraction A;
	A.print();
	double b = 5;
	Fraction B = 5;
	B.print();
	Fraction C(3, 4);
	C.print();
	Fraction D(2, 3, 4);
	D.print();
#endif // CONCTRUKTOR_CHEK

	/*double a = 2.5;
	double b = 3.4;
	double c = a * b;
	cout << c << endl;*/
	//Fraction A(2, 1, 2);
	//Fraction B(3, 2, 5);
	//Fraction C = A * B;
	//C.print();

	/*Fraction D(840, 3600);
	D.reduce();
	D.print();*/
	//C = A / B;
	//C.print();

	Fraction A(2, 1, 2);
	Fraction B(3, 2, 5);
	cout << "\n------------------------------------------------------\n";
	A *= B;
	A.print();
	A /= B;
	A.print();
	A += B;
	A.print();
	A -= B;
	A.print();
	cout << "\n------------------------------------------------------\n";
	cout << (A == B) << endl;
	cout << (A != B) << endl;
	cout << (A > B) << endl;
	cout << (A < B) << endl;
	cout << (A >= B) << endl;
	cout << (A <= B) << endl;

}