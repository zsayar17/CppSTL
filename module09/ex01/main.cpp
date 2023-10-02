#include "RPN.hpp"

int main(int argc, char **argv)
{
	try
	{
		if (argc != 2)
			throw Error();
		RPN rpn(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}

}
