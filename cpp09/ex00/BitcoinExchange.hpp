#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>

class BitcoinExchange
{
    public:
        BitcoinExchange(); // loads data.csv into _rates
        BitcoinExchange(const BitcoinExchange &other); // copy constructor
        BitcoinExchange &operator=(const BitcoinExchange &other); // copy assignment
        ~BitcoinExchange(); // nothing to release, std::map cleans itself up

        void processFile(const std::string &path) const; // reads the input file, prints one converted value per line

    private:
        std::map<std::string, double> _rates;

        void loadDatabase(const std::string &path); // parses data.csv into _rates
        double getRate(const std::string &date) const; // exact match, or the closest earlier date
        static bool isValidDate(const std::string &date); // checks YYYY-MM-DD format and real calendar bounds
        static bool isValidValue(const std::string &value, double &out); // checks the value is a plain number, parses it into out
        static std::string trim(const std::string &s); // strips leading/trailing whitespace
};

#endif
