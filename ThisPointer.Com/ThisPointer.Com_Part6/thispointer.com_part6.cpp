#include<iostream>
#include<thread>
#include<mutex>


class Application
{
	std::mutex mutex;
	bool isDataAvailable;

public:

	Application()
	{
		isDataAvailable = false;
	}

	void loadData()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		std::cout << "Loading data" << std::endl;

		std::lock_guard<std::mutex> guard(mutex);
		isDataAvailable = true;
	}

	void processingData()
	{
		mutex.lock();
		while (!isDataAvailable)
		{
			mutex.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			mutex.lock();
		}
		mutex.unlock();

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