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

// Checking keys from BYR to PID
bool isPassportValid(const Passport& passport)
{
    for(size_t i = 0; i < static_cast<size_t>(KeyType::CountryId); i++)
    {
        if(passport.entries[i].value.empty())
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