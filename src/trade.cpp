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
bool Trade::operator<(const Trade& other) const 
{
    return code < other.code;  // Compara o campo 'code' lexicograficamente
}

// Sobrecarga do operador >, baseado no operador <
bool Trade::operator>(const Trade& other) const 
{
    return other < *this;
}

// Sobrecarga do operador <=, usando < e ==
bool Trade::operator<=(const Trade& other) const 
{
    return !(other < *this);
}

// Sobrecarga do operador >=, usando < e ==
bool Trade::operator>=(const Trade& other) const 
{
    return !(*this < other);
}

// Sobrecarga do operador ==, para permitir comparação de igualdade
bool Trade::operator==(const Trade& other) const 
{
    return code == other.code;
}

// Sobrecarga do operador !=, para permitir comparação de desigualdade
bool Trade::operator!=(const Trade& other) const 
{
    return !(*this == other);
}

void Trade::serialize(std::ofstream& out) const 
{
    out.write(reinterpret_cast<const char*>(&timeref), sizeof(timeref));
    size_t size = account.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(account.c_str(), size);
    size = code.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(code.c_str(), size);
    size = countryCode.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(countryCode.c_str(), size);
    size = productType.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(productType.c_str(), size);
    out.write(reinterpret_cast<const char*>(&value), sizeof(value));
    out.write(reinterpret_cast<const char*>(&status), sizeof(status));
}

void Trade::deserialize(std::ifstream& in) 
{
    in.read(reinterpret_cast<char*>(&timeref), sizeof(timeref));
    size_t size;
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    account.resize(size);
    in.read(&account[0], size);
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    code.resize(size);
    in.read(&code[0], size);
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    countryCode.resize(size);
    in.read(&countryCode[0], size);
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    productType.resize(size);
    in.read(&productType[0], size);
    in.read(reinterpret_cast<char*>(&value), sizeof(value));
    in.read(reinterpret_cast<char*>(&status), sizeof(status));
}