#pragma once

#include <string>

class Trade
{
    private:
        long timeref;
        std::string account;
        std::string code; // Para não desconsiderar zeros à esquerda
        std::string countryCode;
        std::string productType;
        float value;
        char status;

    public:
        long getTimeref() const;
        void setTimeref(long value);
        const std::string& getAccount() const;
        void setAccount(const std::string& value);
        const std::string& getCode() const;
        void setCode(const std::string& value);
        const std::string& getCountryCode() const;
        void setCountryCode(const std::string& value);
        const std::string& getProductType() const;
        void setProductType(const std::string& value);
        float getValue() const;
        void setValue(float newValue);
        char getStatus() const;
        void setStatus(char newStatus);
}