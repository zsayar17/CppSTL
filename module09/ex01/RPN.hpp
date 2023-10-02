#ifndef __RPN_HPP__
# define __RPN_HPP__

# include <iostream>
# include <sstream>
# include <stack>
# include <cstdlib>

class RPN {
	public:
		RPN(void);
		RPN(std::string arg);
		RPN(RPN const &other);
		~RPN(void);

		RPN& operator=(RPN const &other);

	private:
		static const int functionsCount = 4;
		static void (*functions[functionsCount])(std::stack<float> &stack);
		static const std::string operators;

		std::stack<float> stack;


		void handleArg(std::string str);
};

void add(std::stack<float> &stack);
void remove(std::stack<float> &stack);
void multiple(std::stack<float> &stack);
void divide(std::stack<float> &stack);

class Error : public std::exception {
	public:
		const char *what() const throw();
};

class DevideByZero : public std::exception {
	public:
		const char *what() const throw();
};

class InvalidStackCount : public std::exception {
	public:
		const char *what() const throw();
};

#endif
