
#include <iostream>
#include <thread>

using namespace std;

void thread_function()
{
	for (int i = 0; i < 100; i++);
		std::cout << "Thread Function Executing " << std::this_thread::get_id() << std::endl;
}

class DisplayThread
{
public:

	void operator()()
	{
		for (int i = 0; i < 100; i++)
			std::cout << "Thread Object Executing " << std::this_thread::get_id() << std::endl;
	}
};

int main()
{
	std::cout << "Display From MainThread" << std::endl;

	std::thread threadObj1(thread_function);

	std::thread threadObj2((DisplayThread()));

	std::thread threadObj3(
		[]() {
			for (int i = 0; i < 100; i++)
				std::cout << "Lambda Function executing " << std::this_thread::get_id() << std::endl;
		}
	);

	threadObj1.join();
	threadObj2.join();
	threadObj3.join();

	std::cout << "Exit of Main function" << std::endl;

	system("pause");
	return 0;
}