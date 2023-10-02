#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {

}

PmergeMe::~PmergeMe() {

}

PmergeMe::PmergeMe(int argc, char **argv) {
	if (argc < 2) throw std::exception();
	for (int i = 1; i < argc; i++) fillValues(argv[i]);
}

PmergeMe::PmergeMe(PmergeMe const &other) {
	*this = other;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &other) {
	if (this == &other) return (*this);
	_vector = other._vector;
	_list = other._list;
	return *this;
}

void PmergeMe::fillValues(std::string str) {
	double value;
	char *endptr;

	errno = 0;
	value = std::strtod(str.c_str(), &endptr);
	if (str.empty() || errno || *endptr || value > INT_MAX || value < 0
		|| str.find('.') != std::string::npos || str[0] == ' ')
		throw std::exception();
	_vector.add(value);
	_list.add(value);
}


void PmergeMe::mergeSort() {
	double vector_work_duration;
	double list_work_duration;

	std::cout << "Before: ";
	_vector.print();
	vector_work_duration = _vector.mergeInsertSort();
	list_work_duration = _list.mergeInsertSort();
	std::cout << "After: ";
	_list.print();
	std::cout << std::fixed;
	std::cout << "Time to process a range of " << _vector.getSize() << " elements with std::vector : " << vector_work_duration << " s\n";
	std::cout << "Time to process a range of " << _list.getSize() << " elements with std::list : " << list_work_duration << " s\n";
}
