#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>

class BitcoinExchange
{
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

        void processFile(const std::string &path) const;

    private:
        std::map<std::string, double> _rates;

        void loadDatabase(const std::string &path);
        double getRate(const std::string &date) const;
        static bool isValidDate(const std::string &date);
        static bool isValidValue(const std::string &value, double &out);
        static std::string trim(const std::string &s);
};

#endif
