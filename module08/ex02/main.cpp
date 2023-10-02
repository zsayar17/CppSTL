#include "MutantStack.hpp"

int main()
{
	std::cout << "\t\tMUTANT STACK\n";
	{
		MutantStack<int> mstack;

		mstack.push(1);
		mstack.push(2);
		mstack.push(3);
		mstack.pop();
		std::cout << "Current Top: " << mstack.top() << std::endl;
		mstack.push(4);
		mstack.push(5);
		mstack.push(6);

		std::cout << "Current Top: " << mstack.top() << ", Current begin value: " << *mstack.begin() << std::endl;
		*mstack.begin() = 11;
		std::cout << "Current Top: " << mstack.top() << ", Current begin value: " << *mstack.begin() << std::endl;


		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}
		std::stack<int> s(mstack);
		std::cout << "copy upcasted object top count: " << s.top() << std::endl;
		MutantStack<int> s1(mstack);
		std::cout << "copy (constructure) object top count: " << s1.top() << std::endl;
		MutantStack<int> s2;
		s2 = s1;
		std::cout << "copy (assignment) object top count: " << s1.top() << std::endl;
	}
	std::cout << "\t\tLIST\n";
	{
		std::list<int> list;

		list.push_back(1);
		list.push_back(2);
		list.push_back(3);
		list.erase(--list.end());
		list.push_back(4);
		list.push_back(5);
		list.push_back(6);

		std::cout << "Current begin value: " << *list.begin() << std::endl;
		*list.begin() = 11;
		std::cout << "Current begin value: " << *list.begin() << std::endl;


		std::list<int>::iterator it = list.begin();
		std::list<int>::iterator ite = list.end();
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}
	}
	return (0);
}
