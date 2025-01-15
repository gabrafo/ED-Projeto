#include "trade.hpp"

Trade::Trade(long timeref, std::string account, std::string code, std::string countryCode, std::string productType, std::string value, char status)
: timeref(timeref), account(account), code(code), countryCode(countryCode), productType(productType), value(std::stof(value)), status(status) {}

long Trade::getTimeref() const 
{
    return timeref;
}

void Trade::setTimeref(long value) 
{
    timeref = value;
}

const std::string& Trade::getAccount() const 
{
    return account;
}

void Trade::setAccount(const std::string& value) 
{
    account = value;
}

const std::string& Trade::getCode() const 
{
    return code;
}

void Trade::setCode(const std::string& value) 
{
    code = value;
}

const std::string& Trade::getCountryCode() const 
{
    return countryCode;
}

void Trade::setCountryCode(const std::string& value) 
{
    countryCode = value;
}

const std::string& Trade::getProductType() const 
{
    return productType;
}

void Trade::setProductType(const std::string& value) 
{
    productType = value;
}

float Trade::getValue() const 
{
    return value;
}

void Trade::setValue(float newValue) 
{
    value = newValue;
}

char Trade::getStatus() const 
{
    return status;
}

void Trade::setStatus(char newStatus) 
{
    status = newStatus;
}

// Sobrecarga do operador < para comparar por 'code'
bool operator<(const Trade& other) const 
{
    return code < other.code;  // Compara o campo 'code' lexicograficamente
}

// Sobrecarga do operador >, baseado no operador <
bool operator>(const Trade& other) const 
{
    return other < *this;
}

// Sobrecarga do operador <=, usando < e ==
bool operator<=(const Trade& other) const 
{
    return !(other < *this);
}

// Sobrecarga do operador >=, usando < e ==
bool operator>=(const Trade& other) const 
{
    return !(*this < other);
}

// Sobrecarga do operador ==, para permitir comparação de igualdade
bool operator==(const Trade& other) const 
{
    return code == other.code;
}

// Sobrecarga do operador !=, para permitir comparação de desigualdade
bool operator!=(const Trade& other) const 
{
    return !(*this == other);
}