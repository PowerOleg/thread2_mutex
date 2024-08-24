#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>

std::mutex m1;

void client_worker(int& count, const int count_max)
{
	std::unique_lock<std::mutex> lk_client(m1, std::defer_lock);
	
	while (true)
	{
		if (count < count_max)
		{
			lk_client.lock();
			std::cout << ++count << " ";
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			lk_client.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
	
}

void operator_worker(int& count)
{
	std::unique_lock<std::mutex> lk_operator(m1, std::defer_lock);
	
	while (true)
	{
		if (count > 0)
		{
			lk_operator.lock();
			std::cout << --count << " ";
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			lk_operator.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
	
}

int main(int argc, char** argv)
{
	unsigned int cores_quantity = std::thread::hardware_concurrency();
	std::cout << "Quantity of processor cores - " << cores_quantity << std::endl;
	int count_max = 10;
	//std::atomic<int> count = 0;
	int count = 0;
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