
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <string>
#include <algorithm>
#include <map>

struct Bag
{
    size_t bagHash = 0;
    size_t count = 0;
};

static std::map<size_t, std::vector<Bag>> bagRules;

const size_t shinyGoldHash = std::hash<std::string>{}("shiny gold");

size_t count_bag(size_t key)
{
    const auto it = bagRules.find(key);
    if(it == bagRules.end())
    {
        return 0;
    }
    const auto& values = it->second;
    size_t count = 0;
    for(const auto& v : values)
    {
        count += v.count * (1u + count_bag(v.bagHash));
    }
    return count;
}

int main(int arg, char** argv)
{
    std::ifstream input("data/day07_input.txt");
    if (!input.is_open())
    {
        return EXIT_FAILURE;
    }

    for (std::string line; std::getline(input, line); )
    {
        if (line == "\n" || line.empty())
        {
            continue;
        }
        const auto middleIndex = line.find("contain");

        std::string key = line.substr(0, line.find("bag", 0) - 1u);
        std::vector<Bag> values;

        size_t index = middleIndex;
        while (index < line.size())
        {
            if (std::isdigit(line[index]))
            {
                const auto bagIndex = line.find("bag", index);
                std::string value = line.substr(index + 2, bagIndex - (index + 3));
                const auto bagCount = static_cast<size_t>(line[index] - '0');
                values.push_back({ std::hash<std::string>{}(value), bagCount});
                index = bagIndex;
            }
            else
            {
                index++;
            }
        }
        const auto hashKey = std::hash<std::string>{}(key);
       
        bagRules[hashKey] = values;
    }
    const size_t count = count_bag(shinyGoldHash);

    std::cout << "Individual bags in shiny gold " << count << '\n';
    return EXIT_SUCCESS;
}