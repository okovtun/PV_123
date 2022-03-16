#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<map>

const std::map<size_t, std::string> crimes =
{
	{1, "проезд на красный"},
	{2, "привышение скорости"},
	{3, "езда по встречной полосе"},
	{4, "дрифт на перекрестке"},
	{5, "парковка в неположенном месте"},
	{6, "оскорбление офицера"},
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
	Crime(size_t id, const std::string& place) :id(id), place(place) {}
	~Crime() {}

	bool operator==(const Crime& other)const
	{
		return this->id == other.id && this->place == other.place;
	}
	bool operator!=(const Crime& other)const
	{
		return this->id != other.id && this->place != other.place;
	}

};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return os << crimes.at(obj.get_id()) << ", " << obj.get_place();
	//return os << crimes[obj.get_id()] << ", " << obj.get_place();
	//out_of_range exception
}

std::ofstream& operator<<(std::ofstream& ofs, const Crime& obj)
{
	ofs << obj.get_id() << " " << obj.get_place();
	return ofs;
}