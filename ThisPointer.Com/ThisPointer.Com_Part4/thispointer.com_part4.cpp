
#include <iostream>
#include <thread>
#include <vector>

class Wallet
{
	int m_money;

public:

	Wallet()
		: m_money(0)
	{
		
	}

	int getMoney() { return m_money; }
	void addMoney(int money) { for (int i = 0; i < money; i++) m_money++; }
};


int testRaceConditionProblem()
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
		val = testRaceConditionProblem();
		std::cout << val << std::endl;
		if (val != 5000)
		{
			std::cout << "Something wrong with my wallet: " << i + 1 << std::endl;
		}
	}

	system("pause");
	return 0;
}