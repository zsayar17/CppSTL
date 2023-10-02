#include "RPN.hpp"

void (*RPN::functions[RPN::functionsCount])(std::stack<float>&) = {
	add, remove, multiple, divide
};

const std::string RPN::operators = "+-*/";

RPN::RPN() {

}

RPN::RPN(std::string str) {
	if (str.empty()) throw (Error());
	handleArg(str);
}

RPN::RPN(RPN const &other) {
	*this = other;
}

void RPN::handleArg(std::string str) {
	std::stringstream ss(str);
	std::string token;
	size_t	pos;

	ss >> token;
	while (!token.empty())
	{
		for (size_t i = 0; i < token.size(); i++) {
			if (std::isdigit(token[i])) stack.push(token[i] - '0');
			else {
				pos = operators.find(token[i]);
				if (pos != std::string::npos) functions[pos](stack);
				else throw(Error());
			}
		}
		token.clear();
		ss >> token;
	}
	while (!stack.empty())
	{
		std::cout << (int)stack.top() << std::endl;
		stack.pop();
	}
}

RPN::~RPN() {

}

RPN &RPN::operator=(RPN const &other) {
	if (this == &other) return (*this);
	this->stack = other.stack;
	return *this;
}

void add(std::stack<float> &stack) {
	if (stack.size() < 2) throw (InvalidStackCount());
	float value1 = stack.top();
	stack.pop();
	float value2 = stack.top();
	stack.pop();
	value2 += value1;
	stack.push(value2);
}

void remove(std::stack<float> &stack) {
	if (stack.size() < 2) throw (InvalidStackCount());
	float value1 = stack.top();
	stack.pop();
	float value2 = stack.top();
	stack.pop();
	value2 -= value1;
	stack.push(value2);
}

void multiple(std::stack<float> &stack) {
	if(stack.size() < 2) throw (InvalidStackCount());
	float value1 = stack.top();
	stack.pop();
	float value2 = stack.top();
	stack.pop();
	value2 *= value1;
	stack.push(value2);
}

void divide(std::stack<float> &stack){
	if(stack.size() < 2) throw (InvalidStackCount());
	float value1 = stack.top();
	stack.pop();
	float value2 = stack.top();
	stack.pop();
	if (!value1) throw DevideByZero();
	value2 /= value1;
	stack.push(value2);
}

const char *Error::what() const throw() {
	return "Error";
}

const char* DevideByZero::what() const throw() {
	return "Devide by zero";
}

const char* InvalidStackCount::what() const throw() {
	return "Invalid stack count";
}


