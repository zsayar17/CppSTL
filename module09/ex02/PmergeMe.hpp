#ifndef __PMERGEME_HPP__
#define __PMERGEME_HPP__

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include <climits>
#include <sys/time.h>
#include <cerrno>
#include <iterator>



template <typename DataType>
class MergeInsert
{
	private:
		typedef typename DataType::iterator iterator;
		DataType _data;
		int _size;
		int _threshold;

		iterator getMid(iterator begin, iterator end) {
			size_t dist = std::distance(begin, end) / 2;

			if (!dist) return begin;
			std::advance(begin, dist);
			return begin;
		};

		void merge(iterator begin, iterator mid, iterator end) {
			DataType new_vec;
			iterator left = begin;
			iterator right = mid;

			while (left != mid && right != end) {
				if (*right < *left) new_vec.push_back(*(right++));
				else new_vec.push_back(*(left++));
			}
			while (left != mid) new_vec.push_back(*(left++));
			while (right != end) new_vec.push_back(*(right++));

			for (iterator it = new_vec.begin(); it != new_vec.end(); it++) *(begin++) = *(it);
		};

		void insertionSort(iterator begin, iterator end) {
			iterator iter = begin;
			iterator current_iter;
			iterator temp_iter;

			current_iter = iter;
			current_iter++;
			while (current_iter != end)
			{

				while (current_iter != begin)
				{
					temp_iter = current_iter;
					if (*current_iter > *(--temp_iter)) break;
					*current_iter ^= *temp_iter;
					*temp_iter ^= *current_iter;
					*current_iter ^= *temp_iter;
					current_iter--;
				}
				iter++;
				current_iter = iter;
				current_iter++;
			}
		}

		void sort(iterator begin, iterator end) {
			iterator mid;

			if (_threshold > 1 && std::distance(begin, end) <= _threshold) {
				insertionSort(begin, end);
				return ;
			}
			mid = getMid(begin, end);
			if (begin == mid) return;
			sort(begin, mid); //left
			sort(mid, end); //right
			merge(begin, mid, end); //merge
		};

		void setThreshold() {
			_threshold = _size  / 10;

			if (_threshold > 100) _threshold = 100;
		}

	public:
		MergeInsert() {_size = 0; _threshold = 0;}
		MergeInsert(const MergeInsert& other) {*this = other;};
		MergeInsert& operator=(const MergeInsert& other) {
			if (this == &other) return *this;
			_data = other._data;
			_size = other._size;
			_threshold = other._threshold;
			return *this;
		};
		~MergeInsert() {_data.clear();}

		void add(int new_value) {
			_data.push_back(new_value);
			_size++;
		};

		double mergeInsertSort() {
			iterator begin = _data.begin();
			iterator end = _data.end();
			timeval start, finish;

			setThreshold();
			gettimeofday(&start, NULL);
			sort(begin, end);
			gettimeofday(&finish, NULL);
			return ((finish.tv_sec - start.tv_sec) + (finish.tv_usec - start.tv_usec) / 1000000.0);
		};

		void print() {
			iterator begin = _data.begin();
			iterator end = _data.end();

			while (begin != end) std::cout << *(begin++) << " ";
			std::cout << std::endl;
		}

		int getSize() {return _size;};
};


class PmergeMe {
	private:
		MergeInsert< std::vector<int> > _vector;
		MergeInsert< std::list<int> > _list;

		void fillValues(std::string str);
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(int argc, char **argv);
		PmergeMe(PmergeMe const& other);
		PmergeMe & operator=(PmergeMe const& other);

		void mergeSort();
};

#endif

