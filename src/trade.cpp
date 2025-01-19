#include "trade.hpp"

Trade::Trade() : timeref(0), account(""), code(""), countryCode(""), productType(""), value(0.0), status(" ") {}

Trade::Trade(long int timeref, std::string account, std::string code, std::string countryCode,
        std::string productType, float value, std::string status)
    : timeref(timeref), account(account), code(code), countryCode(countryCode),
        productType(productType), value(value), status(status) {}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n"); 
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n"); 
    return str.substr(first, (last - first + 1));
}

bool Trade::equals(const Trade& other) const {

    if(timeref != other.timeref){
        std::cout << "Timeref diferente: " << timeref << " != " << other.timeref << std::endl;
    }

    if(account != other.account){
        std::cout << "Account diferente: " << account << " != " << other.account << std::endl;
    }

    if(code != other.code){
        std::cout << "Code diferente: " << code << " != " << other.code << std::endl;
    }

    if(countryCode != other.countryCode){
        std::cout << "CountryCode diferente: " << countryCode << " != " << other.countryCode << std::endl;
    }

    if(productType != other.productType){
        std::cout << "ProductType diferente: " << productType << " != " << other.productType << std::endl;
    }

    if(fabs(value - other.value) > 1e-6){
        std::cout << "Value diferente: " << value << " != " << other.value << std::endl;
    }

    if(status != other.status){
        std::cout << "Status diferente: " << status << " != " << other.status << std::endl;
    }

    return timeref == other.timeref and
           trim(account) == trim(other.account) and
           trim(code) == trim(other.code) and
           trim(countryCode) == trim(other.countryCode) and
           trim(productType) == trim(other.productType) and
           fabs(value - other.value) < 1e-6 and // Comparação de ponto flutuante
           trim(status) == trim(other.status);
}

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

std::string Trade::getStatus() const 
{
    return status;
}

void Trade::setStatus(std::string newStatus) 
{
    status = newStatus;
}

// Sobrecarga do operador < para comparar por 'code'
bool Trade::operator<(const Trade& other) const 
{
    return countryCode < other.countryCode;
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
bool Trade::operator==(const Trade& other) const {
    return countryCode == other.countryCode;
}

// Sobrecarga do operador !=, para permitir comparação de desigualdade
bool Trade::operator!=(const Trade& other) const {
    return !(*this == other);
}

void Trade::serialize(std::ofstream& out) const {
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
    size = status.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(status.c_str(), size);
}


void Trade::deserialize(std::ifstream& in) {
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
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    status.resize(size);
    in.read(&status[0], size);
}

std::string Trade::toString() const {
    std::string str = "Trade: ";
    str += "timeref: " + std::to_string(timeref) + ", ";
    str += "account: " + account + ", ";
    str += "code: " + code + ", ";
    str += "countryCode: " + countryCode + ", ";
    str += "productType: " + productType + ", ";
    str += "value: " + std::to_string(value) + ", ";
    str += "status: " + status;
    return str;
}
