#include "PmergeMe.hpp"


//./PmergeMe `shuf -i 1-100000 -n 30000 | tr "\n" " "`
int main(int argc, char **argv) {
	try {
		PmergeMe pmergeMe(argc, argv);
		pmergeMe.mergeSort();
	}
	catch (std::exception &e) {
		std::cout << "Error" << std::endl;
	}
}
