#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>


void client_worker(std::atomic<int>& count, const int count_max)
{
	while (true)
	{
		if (count < count_max)
		{
			std::cout << ++count << " ";
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	}
}

void operator_worker(std::atomic<int>& count)
{
	while (true)
	{
		if (count > 0)
		{
			std::cout << --count << " ";
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		}
	}
}

int main(int argc, char** argv)
{
	int count_max = 10;
	std::atomic<int> count = 0;
	std::thread t1(client_worker, std::ref(count), count_max);
	std::thread t2(operator_worker, std::ref(count));
	if (t1.joinable())
	{
		t1.join();
	}
	if (t2.joinable())
	{
		t2.join();
	}
	return 0;
}