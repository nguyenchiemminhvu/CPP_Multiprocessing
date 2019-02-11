#include <iostream>
#include <string>
#include <thread>
#include <mutex>

void func_1()
{
	for (int i = 0; i < 10000; i++)
	{
		std::cout << "Func_1 in thread " << std::this_thread::get_id() << std::endl;
	}
}

void func_2()
{
	for (int i = 0; i < 10000; i++)
	{
		std::cout << "Func_2 in thread " << std::this_thread::get_id() << std::endl;
	}
}

void func_3()
{
	for (int i = 0; i < 10000; i++)
	{
		std::cout << "Func_3 in thread " << std::this_thread::get_id() << std::endl;
	}
}

void func_4()
{
	for (int i = 0; i < 10000; i++)
	{
		std::cout << "Func_4 in thread " << std::this_thread::get_id() << std::endl;
	}
}

int main()
{
	std::thread t1(func_1);
	std::thread	t2(func_2);
	std::thread t3(func_3);

	while (true)
	{
		std::cout << "Main thread " << std::this_thread::get_id() << std::endl;
	}

	return 0;
}