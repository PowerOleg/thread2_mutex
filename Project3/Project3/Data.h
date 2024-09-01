#pragma once
#include <iostream>
#include <mutex>
class Data
{
public:
	std::mutex m1;
	Data(int var_);
	~Data();
	Data(const Data& other_data);//copy
	Data& operator=(const Data& other_data);//copy

	Data& operator=(Data&& other_data) noexcept;//move
	Data(Data&& other_data);//move
	friend std::ostream& operator<<(std::ostream& os, Data& data);
private:
	int var;
};

