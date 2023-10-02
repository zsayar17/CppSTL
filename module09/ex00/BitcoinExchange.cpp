#include "BitcoinExchange.hpp"


// BİTCOIN_BEGIN
BitcoinExchange::BitcoinExchange()
{
	readDB();
}

BitcoinExchange::BitcoinExchange(std::string filename)
{
	readDB();
	try {
		exchange(filename);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	*this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this == &other) return (*this);

	map = other.map;
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
	map.clear();
}

void BitcoinExchange::readDB() {
	std::ifstream file;
	std::string line;
	std::string date;
	std::string price;
	Date date_obj;

	tryOpenFile(file, std::string("data.csv"));
	std::getline(file, line);
	while (std::getline(file, line))
	{
		try
		{
			std::stringstream ss(line);
			std::getline(ss, date, ',');
			date_obj.setDate(date);
			ss >> price;
			map[date_obj] = setDouble(price);
		}
		catch(const std::exception& e)
		{
			std::cout << "error: " << e.what() << '\n';
		}
	}
	file.close();
}

Iterator BitcoinExchange::findIterator(Date& date) {
	std::map<Date, double>::iterator it = map.begin();
	std::map<Date, double>::iterator end = map.end();

	if (date < it->first) throw(InvalidDateException());
	while (it != end)
	{
		if (it->first == date)
			return (it);
		else if (it->first > date)
			return (--it);
		it++;
	}
	return (--end);
}

bool BitcoinExchange::tryValidLine(std::string& delimeter, std::string& end) {
	try
	{
		if (delimeter.compare("|") || end.size()) throw(std::exception());
		return (true);
	}
	catch(const std::exception& e)
	{
		std::cout << "Error: Invalid line\n";
	}
	return (false);
}

bool BitcoinExchange::tryValidDate(std::string& date, Date& date_obj, double& total) {
	Iterator it;

	try
	{
		date_obj.setDate(date);
		it = findIterator(date_obj);
		total = it->second;
		return (true);
	}
	catch(const std::exception& e)
	{
		std::cout << "Error: bad input => " << date << std::endl;
	}
	return (false);
}

bool BitcoinExchange::tryValidAmount(std::string& amount_s, double& amount_f) {
	try
	{
		amount_f = setDouble(amount_s);
		if (amount_f < 0) throw(NotPositiveNumberException());
		else if (amount_f > 1000) throw(TooLargeNumberException());
		return (true);
	}
	catch(const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	return (false);
}

void BitcoinExchange::tryOpenFile(std::ifstream& file, std::string filename) {
	try
	{
		file.open(filename.c_str());
		if (!file.is_open()) throw(FailureFileException());
	}
	catch(const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		exit(1);
	}
}

void BitcoinExchange::exchange(std::string& filename)
{
	std::string line;
	std::string date;
	std::string delimeter;
	std::string end;
	std::string amount_s;
	Date date_obj;
	double amount_f;
	double total;
	std::ifstream file;

	tryOpenFile(file, filename);
	std::getline(file, line);
	if (line.compare("date | value")) throw (FailureFormatException()); // dene
	while (std::getline(file, line))
	{
		std::stringstream ss(line);

		date.clear();
		delimeter.clear();
		amount_s.clear();
		end.clear();
		ss >> date >> delimeter >> amount_s >> end;
		if (date.empty() && !tryValidLine(delimeter, end)) continue;
		if (!tryValidDate(date, date_obj, total) || !tryValidLine(delimeter, end)
			|| !tryValidAmount(amount_s, amount_f)) continue;
		total *= amount_f;
		std::cout << date << " => " << amount_f << " = " << total << std::endl;
	}
}

void BitcoinExchange::printCurrentExchanges() {
	Iterator it = map.begin();
	Iterator end = map.end();

	while (it != end) std::cout << it->first << " " << (it++)->second << std::endl;
}

const char *BitcoinExchange::FailureFileException::what() const throw() {
	return ("could not open file");
}

const char *BitcoinExchange::InvalidDateException::what() const throw() {
	return ("Invalid date");
}

//BITCOIN_END

//DATE_BEGIN
Date::Date()
{

}

Date::Date(const Date& other)
{
	*this = other;
}

Date &Date::operator=(const Date& other)
{
	if (this == &other) return (*this);

	day = other.day;
	month = other.month;
	year = other.year;
	return (*this);
}

Date::~Date()
{

}

const std::string& Date::getYear() const
{
	return (year);
}

const std::string& Date::getMonth() const
{
	return (month);
}

const std::string& Date::getDay() const
{
	return (day);
}

bool Date::operator<(const Date& other) const
{
	if (year != other.year) return year < other.year;
	if (month != other.month) return month < other.month;
	return day < other.day;
}

bool Date::operator>(const Date& other) const
{
	if (year != other.year) return year > other.year;
	if (month != other.month) return month > other.month;
	return day > other.day;
}

bool Date::operator==(const Date& other) const
{
	return year == other.year && month == other.month && day == other.day;
}

bool Date::operator!=(const Date& other) const
{
	return !(*this == other);
}


void Date::setDate(std::string date) {
	std::stringstream ss(date);

	year.clear();
	std::getline(ss, year, '-');
	month.clear();
	std::getline(ss, month, '-');
	day.clear();
	std::getline(ss, day, '-');
	checkValidDate();
}

void Date::checkValidDate() {
	char *endptr1, *endptr2, *endptr3;

	if (!day.length()) throw(FailureDateException());
	if (this->day.find('.') != std::string::npos || this->month.find('.') != std::string::npos
		|| this->year.find('.') != std::string::npos)
			throw(FailureDateException());

	errno = 0;
	double day = std::strtod(this->day.c_str(), &endptr1);
	double month = std::strtod(this->month.c_str(), &endptr2);
	double year = std::strtod(this->year.c_str(), &endptr3);

	if (*endptr1 || *endptr2 || *endptr3) throw(FailureDateException());
	if (errno || year < 0 || year > 2023 || month < 1 || month > 12 || day < 1 || day > 31)
		throw(FailureDateException());
	if ((month == 2 && ((day > 28 && (int)year % 4 != 0) || (day > 29 && (int)year % 4 == 0)))
		|| ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30))
		throw(FailureDateException());

	if (this->day.length() == 1) this->day = '0' + this->day;
	if (this->month.length() == 1) this->month = '0' + this->month;
}

const char* Date::FailureDateException::what() const throw() {
	return "Bad Input Date";
};
//DATE_END


std::ostream& operator<<(std::ostream& ofs, const Date& date) {
	ofs << date.getYear() << "-" << date.getMonth() << "-" << date.getDay();
	return ofs;
}

double setDouble(std::string str) {
	double price;
	char *endptr;

	errno = 0;
	price = std::strtod(str.c_str(), &endptr);
	if (errno != 0 || *endptr) throw(InvalidNumberException());
	return price;
}

const char* InvalidNumberException::what() const throw() {
	return "Invalid Number";
};

const char* NotPositiveNumberException::what() const throw() {
	return "not a positive number";
};
const char* TooLargeNumberException::what() const throw() {
	return "too large a number";
};

const char* FailureFormatException::what() const throw() {
	return "Failure format";
};
