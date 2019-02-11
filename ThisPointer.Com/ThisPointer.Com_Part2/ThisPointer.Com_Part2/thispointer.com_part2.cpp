#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>

using namespace std;

class ThreadRAII
{
public:

	std::thread &threadObj;

	ThreadRAII(std::thread &obj)
		: threadObj(obj)
	{

	}

	~ThreadRAII()
	{
		if (threadObj.joinable())
		{
			std::cout << "Detach thread " << threadObj.get_id() << std::endl;
			threadObj.detach();
		}
	}
};

class WorkerThread
{
public:

	void operator()()
	{
		for (int i = 0; i < 100; i++)
			std::cout << "Worker Thread " << std::this_thread::get_id() << " is Executing" << std::endl;
	}
};

int main()
{
	std::vector<std::thread> threadList;

	for (int i = 0; i < 10; i++)
	{
		threadList.push_back(std::thread((WorkerThread())));
	}

	std::for_each(threadList.begin(), threadList.end(), [=](std::thread &obj) { ThreadRAII wrapper(obj); });

	std::cout << "Exiting from Main Thread" << std::endl;
	system("pause");
	return 0;
}