#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

class Application
{

	std::mutex mutexDataAvailable;
	std::condition_variable condDataAvailable;
	bool isDataAvailable;

public:

	Application()
	{
		isDataAvailable = false;
	}

	bool isDataLoaded()
	{
		return isDataAvailable;
	}

	void loadData()
	{
		std::cout << "Loading data" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		std::lock_guard<std::mutex> guard(mutexDataAvailable);
		isDataAvailable = true;
		condDataAvailable.notify_all();
	}

	void processingData()
	{
		std::unique_lock<std::mutex> lock(mutexDataAvailable);
		condDataAvailable.wait(lock, std::bind(&Application::isDataLoaded, this));
		std::cout << "Processing loaded data" << std::endl;
	}
};

int main()
{
	Application app;

	std::thread thread_1(&Application::processingData, &app);
	std::thread thread_2(&Application::loadData, &app);

	thread_1.join();
	thread_2.join();

	system("pause");
	return 0;
}