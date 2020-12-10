#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int arg, char** argv)
{
    std::ifstream input("data/day09_input.txt");
    if (!input.is_open())
    {
        return EXIT_FAILURE;
    }

    const size_t preambleSize = 25;
    std::vector<int> numbers;
    std::vector<int> preambleNumbers;
    preambleNumbers.reserve(preambleSize);

    for (std::string line; std::getline(input, line); )
    {
        if (line == "\n" || line.empty())
        {
            continue;
        }
        int number = std::atoi(line.data());
        if (preambleNumbers.size() >= preambleSize)
        {
            bool valid = false;
            for (size_t i = 0; i < preambleSize; i++)
            {
                for (size_t j = i + 1; j < preambleSize; j++)
                {
                    if (preambleNumbers[i] + preambleNumbers[j] == number)
                    {
                        valid = true;
                        break;
                    }
                }
                if (valid)
                    break;
            }
            if (!valid)
            {
                std::cout << "First invalid number: " << number << '\n';

                for(size_t i = 0; i < numbers.size(); i++)
                {
                    int sum = 0;
                    int maxValue = std::numeric_limits<int>::min();
                    int minValue = std::numeric_limits<int>::max();
                    for(size_t j = i; j < numbers.size(); j++)
                    {
                        sum += numbers[j];
                        if (sum > number)
                        {
                            break;
                        }
                        if(numbers[j] > maxValue)
                        {
                            maxValue = numbers[j];
                        }
                        if(numbers[j] < minValue)
                        {
                            minValue = numbers[j];
                        }
                        if(j > i + 1 && sum == number)
                        {
                            std::cout << "Min: " << minValue << " Max: " << maxValue << " Sum:" <<
                                minValue + maxValue << '\n';
                            return EXIT_SUCCESS;
                        }
                    }
                }
            }
            preambleNumbers.erase(preambleNumbers.begin());
        }
        preambleNumbers.push_back(number);
        numbers.push_back(number);
    }
    return EXIT_FAILURE;

}
