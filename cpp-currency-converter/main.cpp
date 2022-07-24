#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <sstream>
#include <vector>

#include "currency.h"

// this code is made by Yash Rathore
std::ostream& operator<<(std::ostream &strm, const Currency &c) {
    return strm << "Currency{name: " << c.name
                << ", symbol: " << c.symbol
                << ", value: " << std::fixed
                            << std::setprecision(std::numeric_limits<long double>::max_digits10)
                            << std::to_string(c.value)
                << "}";
}

std::vector<Currency> currencies;
std::map<std::string, Currency> cMap;

void loadCurrencyData(std::string filePath);


int main() {
    loadCurrencyData("../data.csv");

    std::string symbolFrom;
    do {
        std::cout << "Please enter a currency symbol: ";
        std::cin >> symbolFrom;
        transform(symbolFrom.begin(), symbolFrom.end(), symbolFrom.begin(), ::toupper); // ensure symbol is uppercase
    } while (cMap.count(symbolFrom) != 1);

    std::string amount;
    std::cout << "Please enter an amount: ";
    std::cin >> amount;

    std::string symbolTo;
    do {
        std::cout << "Please enter a currency symbol to convert to: ";
        std::cin >> symbolTo;
        transform(symbolTo.begin(), symbolTo.end(), symbolTo.begin(), ::toupper); // ensure symbol is uppercase
    } while (cMap.count(symbolTo) != 1);

    char* end;
    long double amnt = std::strtold(amount.c_str(), &end);

    long double result = convert(amnt, cMap.at(symbolFrom), cMap.at(symbolTo));
    std::cout << amount << " (" << symbolFrom << ") is worth " << result << " (" << symbolTo << ")";

    std::exit(EXIT_SUCCESS);
}

void loadCurrencyData(std::string filePath) {
    std::cout << "Opening csv file..." << std::endl;
    std::ifstream in;
    in.open(filePath);

    if(!in.is_open()) {
        std::cerr << "failed to open file.";
        std::exit(EXIT_FAILURE);
    }

    std::string line;

    std::getline(in, line); // skip 1st line

    while (std::getline(in, line)) {

        std::istringstream lineStream(line);
        std::vector<std::string> tokens;
        std::string token;

        while (std::getline(lineStream, token, ',')) {
            tokens.push_back(std::move(token));
        }

        if(tokens.size() != 3) {
            std::cerr << "malformed CSV data.";
            std::exit(EXIT_FAILURE);
        }

        char* end;
        long double value = std::strtold(tokens[2].c_str(), &end);
        transform(tokens[1].begin(), tokens[1].end(), tokens[1].begin(), ::toupper); // ensure symbol is uppercase
        Currency currency = Currency(tokens[0], tokens[1], value);
        currencies.push_back(std::move(currency));

        cMap.insert(std::make_pair(tokens[1], currency));
    }

    std::cout << "The following currencies are available:" << std::endl;

    std::for_each(currencies.begin(), currencies.end(), [](Currency& cur) { std::cout << cur << std::endl; });
}

