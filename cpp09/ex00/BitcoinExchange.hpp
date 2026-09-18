#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>


class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const std::string& databasePath);
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		void processFile(const std::string& inputPath) const;

	private:
		std::map<std::string, double> _rates;

		void loadDatabase(const std::string& path);
		double getRate(const std::string& date) const;

		static bool isValidDate(const std::string& date);
		static bool isLeapYear(int year);
		static bool splitDateValue(const std::string& line, std::string& date, std::string& valueStr);
		static bool parseValue(const std::string& valueStr, double& value);
};

#endif
