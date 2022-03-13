#pragma once
#include<iostream>
#include<string>
#include<map>

const std::map<size_t, std::string> crimes =
{
	{1, "������ �� �������"},
	{2, "���������� ��������"},
	{3, "���� �� ��������� ������"},
	{4, "����� �� �����������"},
	{5, "�������� � ������������ �����"},
	{6, "����������� �������"},
};

class Crime
{
	size_t id;
	std::string place;
public:
	size_t get_id()const
	{
		return id;
	}
	const std::string& get_place()const
	{
		return place;
	}
	Crime(size_t id, const std::string& place):id(id), place(place){}
	~Crime() {}
};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return os << crimes.at(obj.get_id()) << ", " << obj.get_place();
	//return os << crimes[obj.get_id()] << ", " << obj.get_place();
	//out_of_range exception
}