#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

void print(const size_t column1, const std::thread::id thread_id, const std::string column3, const std::string column4);

double worker(const size_t thread_count, const int length)
{
	char square = (char)254u;
	const std::thread::id thread_id = std::this_thread::get_id();


	std::string progress = "";//"                      ";//22 spaces
	progress = square;
	


	auto start = std::chrono::steady_clock::now();
	for (size_t i = 0; i < length; i++)
	{
		print(thread_count, thread_id, progress, "");
	}

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<long, std::nano> time = end - start;

	double d_time = static_cast<double>(time.count()) / 1000000000;
	return d_time;
}

void print(const size_t column1, const std::thread::id thread_id, const std::string column3, const std::string column4)
{
	std::cout << column1 << "\t" << "\t" << thread_id << " " << column3 << "\t" << "\t" << column4 << "\t" << std::endl;
}


int main(int argc, char** argv)
{
	const int THREADS_QUANTITY = 2;
	const int COMPUTING_LENGTH = 1;

	std::cout << "#" << "\t" << "\t" << "id" << "\t" << "\t" << "Progress Bar" << "\t" << "\t" << "Elapsed time" << "\t" << std::endl;

	std::thread threads[THREADS_QUANTITY];
	for (size_t i = 0; i < THREADS_QUANTITY; i++)
	{
		threads[i] = std::thread(worker, i, COMPUTING_LENGTH);
		threads[i].join();
	}
	











	return 0;
}