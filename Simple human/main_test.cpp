#include "Header files/HUMAN_DEQUE_MANIPULATION.h"


int main() {
	std::deque<Human> humans;


	AddMoreHumans(humans, 2);
	PrintHumans(humans);

	if (humans.size() >= 2) {
		humans.at(0).AddMoreElemToInventory(4);
		humans.at(1).AddMoreElemToInventory(2);

		PrintHumansInventory(humans);

		humans.at(0).Trade(humans.at(1), "brick");

		PrintHumansInventory(humans);
	} else {
		std::cout << "\nNot enough humans added. Program terminated.\n";
	}

	getchar();
	getchar();

	return 0;
}
