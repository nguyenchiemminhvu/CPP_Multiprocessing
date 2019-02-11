#include <iostream>
#include <string>
#include <thread>


class DummyClass 
{
public:

	void sampleMemberFunction(int x)
	{
		std::cout << "Inside sampleMemberFunction " << x << std::endl;
	}
};


void threadCallback(const int &x)
{
	std::cout << "Inside thread x = " << x << std::endl;
	int &xx = const_cast<int &>(x);
	xx++;
}

int main()
{
	int x = 9;
	std::thread threadObj(threadCallback, std::ref(x));
	threadObj.join();

	std::cout << "Outside thread x = " << x << std::endl;

	DummyClass dummyObj;
	std::thread threadObj2(&DummyClass::sampleMemberFunction, dummyObj, x);
	threadObj2.join();

	system("pause");
	return 0;
}