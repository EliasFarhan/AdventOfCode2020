
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <string>
#include <algorithm>
#include <map>

static std::map<size_t, std::vector<size_t>> bagRules;

const size_t shinyGoldHash = std::hash<std::string>{}("shiny gold");

bool check_bag(size_t key, size_t originKey)
{
    const auto it = bagRules.find(key);
    if(it == bagRules.end())
    {
        return false;
    }
    const auto& values = it->second;
    for(auto v : values)
    {
        if (v == shinyGoldHash)
        {
            return true;
        }
        const auto result = check_bag(v, originKey);
        if (result)
            return true;
    }
    return false;
}

int main(int arg, char** argv)
{
    std::ifstream input("data/day07_input.txt");
    if (!input.is_open())
    {
        return EXIT_FAILURE;
    }

    std::vector<size_t> keys;
    for (std::string line; std::getline(input, line); )
    {
        if (line == "\n" || line.empty())
        {
            continue;
        }
        const auto middleIndex = line.find("contain");

        std::string key = line.substr(0, line.find("bag", 0)-1u);
        std::vector<size_t> values;

        size_t index = middleIndex;
        while (index < line.size())
        {
            if (std::isdigit(line[index]))
            {
                const auto bagIndex = line.find("bag", index);
                std::string value = line.substr(index + 2, bagIndex - (index + 3));
                values.push_back(std::hash<std::string>{}(value));
                index = bagIndex;
            }
            else
            {
                index++;
            }
        }
        const auto hashKey = std::hash<std::string>{}(key);
        keys.push_back(hashKey);
        bagRules[hashKey] = values;
    }
    size_t count = 0;
    for(auto key : keys)
    {
        if(check_bag(key, key))
        {
            count++;
        }
    }
    std::cout << "Bags that contain at least one shiny gold: " << count << '\n';
    return EXIT_SUCCESS;
}