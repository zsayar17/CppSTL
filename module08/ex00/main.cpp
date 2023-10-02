#include "easyfind.hpp"



int main()
{
	int container_count = 10;
	int test_count = 15;
	int test_begin = -5;

	std::vector<int> my_intvector;
	std::list<int> my_intlist;
	std::deque<int> my_intdeque;


	for (int i = 0; i < container_count; i++)
	{
		my_intvector.push_back(i);
		my_intlist.push_back(i);
		my_intdeque.push_back(i);
	}

	for (int i = test_begin; i < test_count; i++)
	{
		std::cout << "\n~~~~~~~~" << i << "~~~~~~~~\n";
		std::cout << "Int vector: ";
		tryFind(my_intvector, i);
		std::cout << "Int list: ";
		tryFind(my_intlist, i);
		std::cout << "Int deque: ";
		tryFind(my_intdeque, i);
	}
}
