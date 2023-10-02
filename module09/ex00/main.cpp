#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
	if (argc == 1) {
		std::cout << "could not open file" << std::endl;
		return (1);
	}
	BitcoinExchange exchange(argv[1]);
	return (0);
}
