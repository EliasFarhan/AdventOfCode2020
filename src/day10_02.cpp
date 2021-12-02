

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <functional>


int main(int argc, char** argv)
{
    std::ifstream input("data/day10_input.txt");
    if (!input.is_open())
    {
        return EXIT_FAILURE;
    }
    std::vector<int> numbers;
    for (std::string line; std::getline(input, line); )
    {
        numbers.push_back(std::stoi(line));
    }
    std::ranges::sort(numbers);

    std::vector subPossibilities(numbers.size(), 0ull);
    subPossibilities.back() = 1ull;

    const std::function<unsigned long long(std::size_t)> calculateSubPossibility = [&numbers, &calculateSubPossibility](std::size_t index)
    {
        if (index == numbers.size() - 1)
            return 1ull;
        const auto currentNumber = numbers[index];
        unsigned long long possibility = 0;
        for (std::size_t di = 1; di <= 3; di++)
        {
            const std::size_t nextIndex = index + di;
            if (nextIndex >= numbers.size())
                break;
            const auto nextNumber = numbers[nextIndex];
            if (nextNumber - currentNumber <= 3)
            {
                possibility += calculateSubPossibility(nextIndex);
            }
        }
        return possibility;
    };

    unsigned long long possibility = 0;
    for (std::size_t i = 2; i <= numbers.size(); i++)
    {
        const std::size_t index = numbers.size() - i;
        const auto currentNumber = numbers[index];
        auto subPossibility = 0ull;
        for (std::size_t di = 1; di <= 3; di++)
        {
            const std::size_t nextIndex = index + di;
            if (nextIndex >= numbers.size())
                break;
            const auto nextNumber = numbers[nextIndex];
            if (nextNumber - currentNumber <= 3)
            {
                subPossibility += subPossibilities[nextIndex];
            }
        }
        subPossibilities[index] = subPossibility;
    }
    for(std::size_t i = 0; i <= 3; i++)
    {
        if(numbers[i] <= 3)
        {
            possibility += subPossibilities[i];
        }
    }
    std::cout << "Possibility: " << possibility << '\n';
    return EXIT_SUCCESS;
}
