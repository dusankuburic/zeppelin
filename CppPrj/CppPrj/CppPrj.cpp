#include <iostream>
#include <iomanip>
#include <vector>
#include <map>

#include <string>

int main()
{


	{
		int age;
		std::cout << "Please type in your age: " << std::endl;
		std::cin >> age;

		std::cin.clear();
		std::cin.ignore('\n');

		std::string name;
		std::cout << "what is your name: " << std::endl;
		std::getline(std::cin, name);
		std::cout << "hello" << age << " years old" << name << std::endl;
	}

	{
		std::map<std::string, int> IDs{
			{"Steve", 1234},
			{"Adam", 1334},
			{"Ada", 1434}
		};

		std::cout << IDs["Adam"] << std::endl;

		IDs["Adam"] = 1544;
		std::cout << IDs["Adam"] << std::endl;

		IDs.insert({ "Leon",  1644 });

		std::cout << IDs["Leon"] << std::endl;

		std::cout << "the size of IDs is: " << IDs.size() << std::endl;

		IDs.erase("Leon");

		std::cout << "the size of IDs is: " << IDs.size() << std::endl;

		std::cout << IDs["Leon"] << std::endl;

	
	}


	{
		std::string employeeOne = "steve";
		std::string employeeTwo = "bob";

		std::string employees[] = { "steve", "bob", "allen" };

		std::cout << employees[0] << std::endl;

		employees[1] = "Adam";

		std::cout << employees[1] << std::endl;
		std::cout << sizeof(employees) / sizeof(std::string) << std::endl;
	}

	{
		int IDs[] = { 123, 1334, 1434 };

		std::vector<int> IDVec = { 1234, 1334, 1434 };

		std::cout << "the first one ID is: " << IDs[0] << std::endl;
		std::cout << "the firs t of id vec is: " << IDVec[0] << std::endl;

		std::cout << "the last one of IDs is: " << IDs[sizeof(IDs) / sizeof(int) - 1] << std::endl;;
		std::cout << "this last of IDVEC IS: " << IDVec.back() << std::endl;

		std::cout << "this izes of IDs is: " << sizeof(IDs) / sizeof(int) << std::endl;
		std::cout << "thie size oF IDVec is: " << IDVec.size() << std::endl;
	}

}

