#include "Span.hpp"

template <typename T>
void createRandomNumbers(T& container, int size)
{
	for (int i = 0; i < size; i++)
		container.insert(std::rand() * (1 - ((i & 1) << 1)));
}

void tryAddNumbers(Span span, std::multiset<int>& ms) //copy
{
	try
	{
		span.addNumbers(ms.begin(), ms.end());
		std::cout << "longest: " << span.longestSpan() << " shortest: " << span.shortestSpan() << std::endl;
	} catch(std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

int main() {
	const int test_count = 20000;
	std::srand(std::time(NULL));


	std::cout << "~~~~COPY TEST~~~~\n";
	{
		Span span;
		Span span2(20);

		try
		{
			span.addNumber(10);//error
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		span = span2;
		span.addNumber(10); //success
		span.addNumber(20); //success
		span.addNumber(30); //success
		span.addNumber(40); //success
		span.printStoredNumbers(); //Display Shallow copy
		span2.printStoredNumbers(); //Display Shallow copy

		Span span3(span); //Copy constructure
		span3.printStoredNumbers();
	}

	std::cout << "\n~~~~ADD NUMBER TEST~~~~\n";
	{
		Span span(test_count);
		std::multiset<int> ms_1;
		std::multiset<int> ms_2;
		std::multiset<int> ms_3;

		createRandomNumbers(ms_2, test_count - 1);
		createRandomNumbers(ms_1, test_count);
		createRandomNumbers(ms_3, test_count + 1);

		tryAddNumbers(span, ms_1); //success
		tryAddNumbers(span, ms_2); //success
		tryAddNumbers(span, ms_3); //error
	}
}
