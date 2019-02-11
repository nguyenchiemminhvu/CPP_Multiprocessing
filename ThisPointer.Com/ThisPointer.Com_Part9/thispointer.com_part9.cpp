#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <future>


std::string fetchFromDB()
{
	std::cout << "Start new thread to load data from DB: " << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	return "Data from DB";
}

std::string fetchFromFile()
{
	std::cout << "Start new thread to load data from File: " << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	return "Data from File";
}

int main()
{
	std::future<std::string> resultFromDB = std::async(std::launch::async, fetchFromDB);
	std::future<std::string> resultFromFile = std::async(std::launch::async, fetchFromFile);
	std::future<void> mergeThread = std::async(
		std::launch::async,
		[&]() {
			std::cout << "Merge thread: " << std::this_thread::get_id() << std::endl;
			std::string result = resultFromDB.get() + "_____" + resultFromFile.get();
			std::cout << "Final Result: " << result << std::endl;
		}
	);

	for (int i = 0; i < 10; i++)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "Do something else" << std::endl;
	}

	std::cout << "Exit main thread: " << std::this_thread::get_id() << std::endl;
	system("pause");
	return 0;
}