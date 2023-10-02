#ifndef __SPAN_HPP__
# define __SPAN_HPP__

#include <iostream>
#include <set>
#include <iostream>
#include <iterator>
#include <exception>
#include <algorithm>
#include <ctime>
#include <climits>

typedef std::multiset<int>::iterator m_it;

class Span
{
	private:
		unsigned int size;
		std::multiset<int> m_set;
	public:
		Span();
		Span(unsigned int size);
		Span(const Span& other);

		~Span();
		Span& operator=(const Span& other);

		unsigned int getSize() const;
		void setSize(unsigned int size);

		void addNumber(int new_number);
		void addNumbers(m_it begin, m_it end);
		long int shortestSpan();
		long int longestSpan();
		void printStoredNumbers() const;
};

#endif
