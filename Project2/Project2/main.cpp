#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <mutex>
#include <random>

std::mutex m1;
char SQUARE = (char)254u;


static void getRandom(int& num, const int range_start, const int range_end)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(range_start, range_end); // distribution in range [1, 6]
	num = dist6(rng);
}

void move_cursor_in_console(const int x, const int y)
{
	printf("\033[%d;%dH", y, x);
}

void print_square()
{
	std::cout << SQUARE;
}

void print_title(const size_t THREADS_QUANTITY, const std::thread::id* thread_ids/*, const int* progress, const std::string* elapsed_time, const size_t line_number*/)
{
	std::cout << "#" << "\t" << "\t" << "ID" << "\t" << "\t" << "Progress Bar" << "\t" << "\t" << "Elapsed Time" << "\t" << std::endl;
	for (size_t i = 0; i < THREADS_QUANTITY; i++)
	{
		std::cout << i << "\t" << "\t" << thread_ids[i] << std::endl;
	}
}

void draw(const size_t line_number, std::thread::id* thread_ids, std::string* elapsed_time, const int iteration_quantity)
{
	int x = 33;
	int y = line_number + 2;
	int random_num = 1000;
	auto start = std::chrono::steady_clock::now();
	for (size_t i = 0; i < iteration_quantity; i++)//work simulating
	{
		getRandom(random_num, 0, 3000);
		std::this_thread::sleep_for(std::chrono::milliseconds(random_num));
		std::unique_lock<std::mutex> lk1(m1);
		move_cursor_in_console(x++, y);
		print_square();
		lk1.unlock();
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<long, std::nano> time = end - start;
	double d_time = static_cast<double>(time.count()) / 1000000000;
	if (d_time < 0)
	{
		d_time * -1;
	}
	elapsed_time[line_number] = std::to_string(d_time);

	std::unique_lock<std::mutex> lk1(m1);
	move_cursor_in_console(x+12, y);
	std::cout << std::to_string(d_time);
	lk1.unlock();
}

int main(int argc, char** argv)
{
	const size_t THREADS_QUANTITY = 4;
	const int ITERATION_QUANTITY = 12;
	std::thread::id* thread_ids = new std::thread::id[THREADS_QUANTITY];
	std::string* elapsed_time = new std::string[THREADS_QUANTITY];
	for (size_t i = 0; i < THREADS_QUANTITY; i++)
	{
		elapsed_time[i] = "";
	}

	std::thread threads[THREADS_QUANTITY];
	for (size_t i = 0; i < THREADS_QUANTITY; i++)
	{
		threads[i] = std::thread(draw, i, std::ref(thread_ids), std::ref(elapsed_time), ITERATION_QUANTITY);
		const std::thread::id thread_id = threads[i] .get_id();
		thread_ids[i] = thread_id; 
		threads[i].detach();
	}
	print_title(THREADS_QUANTITY, thread_ids);

	while(elapsed_time[0] == "" || elapsed_time[1] == "" || elapsed_time[2] == "" || elapsed_time[3] == "")
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}

	move_cursor_in_console(1, 7);
	std::cout << "THE END";
	delete[] thread_ids;
	delete[] elapsed_time;
	delete[] threads;
	return 0;
}