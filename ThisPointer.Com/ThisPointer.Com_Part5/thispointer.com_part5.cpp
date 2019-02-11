
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

class LockGuard
{
	std::mutex mutex;

public:

	LockGuard() { mutex.lock(); }
	~LockGuard() { mutex.unlock(); }
};

class Wallet
{
	int m_money;
	std::mutex mutex;

public:

	Wallet()
		: m_money(0)
	{

	}

	int getMoney() 
	{ 
		return m_money; 
	}

	void addMoney(int money) 
	{ 
		LockGuard lock;

		for (int i = 0; i < money; i++)
			m_money++;
	}
};


int fixRaceConditionProblem()
{
	Wallet wallet;

	std::vector<std::thread> threads;
	for (int i = 0; i < 5; ++i)
	{
		threads.push_back(std::thread(&Wallet::addMoney, &wallet, 1000));
	}

	for (int i = 0; i < threads.size(); i++)
	{
		threads[i].join();
	}

	return wallet.getMoney();
}

int main()
{
	int val = 0;

	for (int i = 0; i < 1000; i++)
	{
		val = fixRaceConditionProblem();
		std::cout << val << std::endl;
		if (val != 5000)
		{
			std::cout << "Something wrong with my wallet: " << i + 1 << std::endl;
		}
	}

	system("pause");
	return 0;
}