#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>

void refresh_console(const size_t column1, const std::thread::id* thread_ids, const int* progress, const std::string* elapsed_time);


void worker(const size_t line_number, std::thread::id* thread_ids, int* progress_line, std::string* elapsed_time, const int iteration_quantity)
{
	double ratio = 20.0 / static_cast<double>(iteration_quantity);//a ratio to transform iteration_quantity into 20 units

	const std::thread::id thread_id = std::this_thread::get_id();
	thread_ids[line_number] = thread_id;

	auto start = std::chrono::steady_clock::now();
	size_t i = 0;
	int result = 0;
	while (result < iteration_quantity)//work simulating
	{
		result = ++i / (line_number + 1);
		progress_line[line_number] = result * ratio;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<long, std::nano> time = end - start;

	double d_time = static_cast<double>(time.count()) / 1000000000;	
	elapsed_time[line_number] = std::to_string(d_time);
}

void refresh_console(const size_t size, const std::thread::id* thread_ids, const int* progress, const std::string* elapsed_time)
{
	char square = (char)254u;
	std::vector<std::string> progress_string(size, "");
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < progress[i]; j++)
		{
			progress_string[i] += square;
		}
	}


	std::system("cls");
	std::cout << "#" << "\t" << "\t" << "ID" << "\t" << "\t" << "Progress Bar" << "\t" << "\t" << "Elapsed Time" << "\t" << std::endl;
	for (size_t i = 0; i < size; i++)
	{
		std::cout << i << "\t" << "\t" << thread_ids[i] << "\t" << progress_string[i] << "\t" << "\t" << elapsed_time[i] << "\t" << std::endl;
	}
}


int main(int argc, char** argv)
{
	const size_t THREADS_QUANTITY = 4;
	const int ITERATION_QUANTITY = 10;
	const size_t PROGRESS_BAR_LENGTH = 20;

	std::thread::id* thread_ids = new std::thread::id[THREADS_QUANTITY];
	int* progress_line = new int[THREADS_QUANTITY];
	std::string* elapsed_time = new std::string[THREADS_QUANTITY];
	for (size_t i = 0; i < THREADS_QUANTITY; i++)
	{
		progress_line[i] = 0;
		elapsed_time[i] = "";
	}

	
	std::thread threads[THREADS_QUANTITY];
	for (size_t i = 0; i < THREADS_QUANTITY; i++)
	{
		threads[i] = std::thread(worker, i, std::ref(thread_ids), std::ref(progress_line), std::ref(elapsed_time), ITERATION_QUANTITY);
		threads[i].detach();
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	int count_end = 0;
	while(elapsed_time[0] == "" || elapsed_time[1] == "" || elapsed_time[2] == "" || elapsed_time[3] == "")
	{
		refresh_console(THREADS_QUANTITY, thread_ids, progress_line, elapsed_time);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	refresh_console(THREADS_QUANTITY, thread_ids, progress_line, elapsed_time);
	delete[] thread_ids;
	delete[] progress_line;
	delete[] elapsed_time;
	return 0;
}