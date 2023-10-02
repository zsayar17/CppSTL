#ifndef __BITCOINEXCHANGE_HPP__
#define __BITCOINEXCHANGE_HPP__

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <cstdlib>

//DATE_BEGIN
class Date
{
	private:
		std::string day;
		std::string month;
		std::string year;

		void checkValidDate();

		class FailureDateException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
	public:
		Date();
		Date(const Date& other);
		Date &operator=(const Date& other);
		~Date();

		bool operator<(const Date& other) const;
		bool operator>(const Date& other) const;
		bool operator==(const Date& other) const;
		bool operator!=(const Date& other) const;

		void setDate(std::string date);

		const std::string& getYear() const;
		const std::string& getMonth() const;
		const std::string& getDay() const;
};

std::ostream& operator<<(std::ostream& ofs, const Date& date);
//DATE_END

//BITCOIN_BEGIN
typedef std::map<Date, double>::iterator Iterator;
class BitcoinExchange
{
	private:
		std::map<Date, double> map;

		Iterator findIterator(Date& date);
		void readDB();
		void exchange(std::string& filename);
		bool tryValidLine(std::string& delimeter, std::string& end);
		bool tryValidDate(std::string& date, Date& date_obj, double& total);
		bool tryValidAmount(std::string& amount_s, double& amount_f);
		void tryOpenFile(std::ifstream& file, std::string filename);

		class FailureFileException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class InvalidDateException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
	public:
		BitcoinExchange();
		BitcoinExchange(std::string filename);
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange &operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		void printCurrentExchanges();
};
//BITCOIN_END

double setDouble(std::string str);

class InvalidNumberException : public std::exception
{
	public:
	virtual const char* what() const throw();
};

class NotPositiveNumberException : public std::exception
{
	public:
	virtual const char* what() const throw();
};

class TooLargeNumberException : public std::exception
{
	public:
	virtual const char* what() const throw();
};

class FailureFormatException : public std::exception
{
	public:
		virtual const char* what() const throw();
};

#endif
