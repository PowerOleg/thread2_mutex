#include "Data.h"
#include <iostream>
#include <mutex>
#include <thread>
#include <functional>

#include <chrono>
#include <functional>
#include <vector>

void swap_lock_guard(Data& d1, Data& d2)
{
	std::lock_guard<std::mutex> lk1(d1.m1);
	std::lock_guard<std::mutex> lk2(d2.m1);
	//std::scoped_lock lock(d1.m1, d2.m1);
	Data temp = std::move(d1);
	d1 = std::move(d2);
	d2 = std::move(temp);
}

void swap_unique_lock(Data& d1, Data& d2)
{
	//std::lock_guard<std::mutex> lk1(d1.m1);
	//std::lock_guard<std::mutex> lk2(d2.m1);

	Data temp = std::move(d1);
	d1 = std::move(d2);
	d2 = std::move(temp);
}

std::ostream& operator<<(std::ostream& os, Data& data)
{
	return os << data.var;
}

int main(int argc, char** argv)
{
	Data d1(1);
	Data d2(2);
	std::cout << "Data1:" << d1 << std::endl;
	std::cout << "Data2:" << d2 << std::endl;
	std::cout << &d1 << std::endl;
	swap_lock_guard(d1, d2);//task: take the mutex of the Data1, take the mutex of The Data2, then swap()
	std::cout << "Data1:" << d1 << std::endl;
	std::cout << "Data2:" << d2 << std::endl << std::endl;
	std::cout << &d1 << std::endl;
	/*
	swap_unique_lock(d1, d2);
	std::cout << "Data1:" << d1 << std::endl;
	std::cout << "Data2:" << d2 << std::endl << std::endl;
	swap_lock(d1, d2);
	std::cout << "Data1:" << d1 << std::endl;
	std::cout << "Data2:" << d2 << std::endl << std::endl;*/

	return 0;
}