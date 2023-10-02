#include "Span.hpp"

Span::Span() {
	setSize(0);
}

Span::~Span() {

}

Span::Span(unsigned int size) {
	setSize(size);
}

Span::Span(const Span& other) {
	*this = other;
}

Span& Span::operator=(const Span& other) {
	if (this == &other) return (*this);

	setSize(other.getSize());
	m_set.clear();
	m_set = other.m_set;
	return (*this);
}

unsigned int Span::getSize() const{
	return (this->size);
}

void Span::setSize(unsigned int size) {
	this->size = size;
}

void Span::addNumber(int new_number) {
	if (m_set.size() == getSize()) throw (std::out_of_range("Max capacity! Can not add new element"));
	m_set.insert(new_number);
}

void Span::addNumbers(m_it begin, m_it end) {
	while (begin != end) addNumber(*(begin++));
}

long int Span::shortestSpan() {
	m_it begin;
	m_it end;
	long int dist;
	long int local_dist;

	if (m_set.size() <= 1) throw(std::length_error("Not enough numbers stored"));

	begin = m_set.begin();
	end = --m_set.end();
	dist = std::abs(*begin - *(++begin));
	while (begin != end && dist != 0)
	{
		local_dist = std::abs(*begin - *(++begin));
		if (local_dist < dist) dist = local_dist;
	}
	return (dist);
}

long int Span::longestSpan() {
	if (m_set.size() <= 1) throw(std::length_error("Not enough numbers stored"));
	return ((long int)*(--m_set.end()) - *(m_set.begin()));
}

void Span::printStoredNumbers() const {
	m_it begin;
	m_it end;

	begin = m_set.begin();
	end = m_set.end();
	while (begin != end) std::cout << *(begin++) << std::endl;
}

