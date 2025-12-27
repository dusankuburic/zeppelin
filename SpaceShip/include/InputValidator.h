#pragma once

#include <iostream>
#include <limits>
#include <string>

class InputValidator {
public:

	static bool readInt(const std::string& prompt, int& value,
		int min, int max, int max_attempts = 3) {

		for (int attempt = 0; attempt < max_attempts; ++attempt) {
			std::cout << prompt;

			if (!(std::cin >> value)) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input. Please enter a number.\n";
				continue;
			}

			if (value < min || value > max) {
				std::cout << "Out of range. Enter between " << min
					<< " and " << max << ".\n";
					continue;
			}

			return true;
		}

		std::cout << "Too many invalid attempts. Exiting.\n";
		return false;
	}

	static bool confirm(const std::string& message) {
		char choice;
		std::cout << message << " (y/n): ";
		std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return (choice == 'y' || choice == 'Y');
	}
};
