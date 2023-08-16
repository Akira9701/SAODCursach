#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

struct Deposit
{
	std::string depositorName;
	std::string depositAmount;
	std::string depositDate;
	std::string lawyerName;
};

int main()
{
	std::ifstream file("file.dat");

	if (file.is_open())
	{
		std::vector<Deposit> deposits;
		std::string line;

		while (std::getline(file, line))
		{
			Deposit deposit;
			deposit.depositorName = line.substr(0, 30);
			deposit.depositAmount = line.substr(30, 5);
			deposit.depositDate = line.substr(36, 10);
			deposit.lawyerName = line.substr(46, 22);
			deposits.push_back(deposit);
		}

		file.close();

		for (const Deposit &deposit : deposits)
		{
			std::cout << "fio vklad: " << deposit.depositorName
								<< ", Sum: " << deposit.depositAmount
								<< ", Date: " << deposit.depositDate
								<< ", Fio loyer: " << deposit.lawyerName << std::endl;
		}
	}
	else
	{
		std::cout << "Не удалось открыть файл." << std::endl;
	}

	return 0;
}
