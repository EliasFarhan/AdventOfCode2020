

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>


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

    std::size_t difference1 = 0;
    std::size_t difference3 = 0;

    int previousValue = 0;
    for (const auto n : numbers)
    {
        std::cout << n << '\n';
        if (previousValue + 3 < n)
        {
            assert(false && "Should not happen?");
            break;
        }
        if (previousValue + 1 == n)
        {
            difference1++;
        }
        else if (previousValue + 3 == n)
        {
            difference3++;
        }
        previousValue = n;
    }
    std::cout << "1-jolt: " << difference1 << ", 3-jolt: " << difference3
        << ", Product: " << difference1 * (difference3+1) << '\n';
    return EXIT_SUCCESS;
}
