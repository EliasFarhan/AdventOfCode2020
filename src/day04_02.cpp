//
// Created by efarhan on 12/5/20.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <string>

enum class KeyType
{
    BirthYear,
    IssueYear,
    ExpirationYear,
    Height,
    HairColor,
    EyeColor,
    PassportId,
    CountryId,
    Length
};

const std::array<std::string, static_cast<size_t>(KeyType::Length)> keys
        {
                "byr",
                "iyr",
                "eyr",
                "hgt",
                "hcl",
                "ecl",
                "pid",
                "cid"
        };

struct Entry
{
    std::string key;
    std::string value;
};

struct Passport
{
    std::array<Entry, static_cast<size_t>(KeyType::Length)> entries;
};

bool isValueValid(KeyType keyType, const std::string& value)
{
    switch (keyType)
    {
        case KeyType::BirthYear:
        {
            if(value.size() != 4)
                break;
            int birthYear = std::atoi(value.data());
            return birthYear >= 1920 && birthYear <= 2002;
        }
        case KeyType::IssueYear:
        {
            if(value.size() != 4)
                break;
            int issueYear = std::atoi(value.data());
            return issueYear >= 2010 && issueYear <= 2020;
        }
        case KeyType::ExpirationYear:
        {
            if(value.size() != 4)
                break;
            int expirationYear = std::atoi(value.data());
            return expirationYear >= 2020 && expirationYear <= 2030;
        }
        case KeyType::Height:
            if(auto cmPos = value.find("cm"); cmPos != std::string::npos)
            {
                std::string heightNumber = value.substr(0, cmPos);
                int height = std::atoi(heightNumber.data());
                return height >= 150 && height <= 193;
            }
            else if(auto inPos = value.find("in"); inPos != std::string::npos)
            {
                std::string heightNumber = value.substr(0, inPos);
                int height = std::atoi(heightNumber.data());
                return height >= 59 && height <= 76;
            }
            break;
        case KeyType::HairColor:
        {
            if(value[0] != '#' || value.size() != 7)
                break;
            for(int i = 1; i < value.size(); i++)
            {
                if(!((value[i] >= '0' && value[i] <= '9') ||
                     (value[i] >= 'a' && value[i] <= 'f')))
                {
                    return false;
                }
            }
            return true;
        }
        case KeyType::EyeColor:
        {
            static const std::array<std::string, 7> eyeColorKeys =
                    {
                            "amb",
                            "blu",
                            "brn",
                            "gry",
                            "grn",
                            "hzl",
                            "oth"
                    };
            if(value.size() != 3)
            {
                break;
            }
            for(const auto& eyeColor : eyeColorKeys)
            {
                if(value == eyeColor)
                    return true;
            }
            break;
        }
        case KeyType::PassportId:
        {
            if(value.size() != 9)
                break;
            return std::all_of(value.begin(), value.end(), [](char c){return c >= '0' && c <= '9';});
        }
        default:
            break;
    }
    return false;
}

// Checking keys from BYR to PID
bool isPassportValid(const Passport& passport)
{
    for(size_t i = 0; i < static_cast<size_t>(KeyType::CountryId); i++)
    {
        if(passport.entries[i].value.empty() ||
           !isValueValid(static_cast<KeyType>(i), passport.entries[i].value))
            return false;
    }
    return true;
}

int main(int arg, char** argv)
{

    const size_t keyLength = 3;
    std::ifstream input("data/day04_input.txt");
    if (!input.is_open())
    {
        return EXIT_FAILURE;
    }
    size_t count = 0;
    Passport currentPassport;
    for (std::string line; std::getline(input, line); )
    {
        if(line == "\n" || line.empty())
        {
            if(isPassportValid(currentPassport))
                count++;
            currentPassport = {};
        }
        else
        {
            size_t first_index = 0;
            auto next_space = line.find(' ');
            while(first_index != std::string::npos)
            {
                std::string token = line.substr(first_index, next_space-first_index);
                const auto separatorPos = token.find(':');
                std::string key = token.substr(0, separatorPos);

                if(key.length() == keyLength)
                {
                    for(size_t i = 0; i < keys.size(); i++)
                    {
                        if(key == keys[i])
                        {
                            currentPassport.entries[i].key = key;
                            std::string value = token.substr(separatorPos+1);
                            value.erase(std::remove(value.begin(), value.end(), '\n'), value.end());
                            currentPassport.entries[i].value = value;
                            break;
                        }
                    }
                }
                first_index = next_space == std::string::npos ? std::string::npos : next_space + 1;
                next_space = line.find(' ', next_space+1);
            }
        }
    }
    if(isPassportValid(currentPassport))
        count++;
    currentPassport = {};
    std::cout <<"Valid passports: "<<count<<'\n';
    return EXIT_SUCCESS;
}