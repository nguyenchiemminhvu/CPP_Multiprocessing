
#include <iostream>
#include <thread>
#include <future>


int main()
{
	std::promise<int> thePromise;
	std::future<int> theFuture = thePromise.get_future();
	
	std::thread computingThread(
		[](std::promise<int> *aPromise) { 
			for (int i = 0; i < 1000; i++) 
				std::cout << "Computing in thread " << std::this_thread::get_id() << std::endl;
			aPromise->set_value(9999); 
		}, 
		&thePromise
	);

	for (int i = 0; i < 1000; i++)
		std::cout << "Do something else" << std::endl;

	std::thread gettingThread(
		[](std::future<int> * aFuture) {
		std::cout << "Get result in thread " << std::this_thread::get_id() << ": " << aFuture->get() << std::endl;
	},
		&theFuture
		);
	gettingThread.join();

	std::cout << "Exit main thread: " << std::this_thread::get_id() << std::endl;
	system("pause");
	return 0;
}