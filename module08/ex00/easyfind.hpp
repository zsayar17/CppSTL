#ifndef __EASYFIND_HPP__
# define __EASYFIND_HPP__

#include <iostream>
#include <vector>
#include <iostream>
#include <iterator>
#include <list>
#include <deque>
#include <sstream>
#include <exception>
#include <algorithm>

template <typename T>
void easyfind(T t, int value)
{
	typename T::iterator it;

	it = std::find(t.begin(), t.end(), value);
	if (it == t.end()) throw(std::out_of_range("This value not in range"));
	std::cout << *it << std::endl;
}

template <typename T> void tryFind(T t, int index)
{
	try {
		easyfind(t, index);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}


#endif
