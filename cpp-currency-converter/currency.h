
// this code is made by Yash Rathore
#ifndef CRYPTO_CURRENCY_CONVERTER_CURRENCY_H
#define CRYPTO_CURRENCY_CONVERTER_CURRENCY_H

#include<ostream>

class Currency {
public:
    std::string name;
    std::string symbol;
    long double value;

public:
    Currency(std::string name, std::string symbol, long double value) {
        this->name = name;
        this->symbol = symbol;
        this->value = value;
    }
private:
    friend std::ostream& operator<<(std::ostream&, const Currency&);
};

long double convert(long double amount, Currency from, Currency to) {
    return (amount * from.value) / to.value;
}
#endif
