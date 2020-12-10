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
    numbers.reserve(preambleSize);

    for (std::string line; std::getline(input, line); )
    {
        if (line == "\n" || line.empty())
        {
            continue;
        }
        int number = std::atoi(line.data());
        if(numbers.size() >= preambleSize)
        {
            bool valid = false;
            for(size_t i = 0; i < preambleSize; i++)
            {
                for(size_t j = i + 1; j < preambleSize; j++)
                {
                    if(numbers[i]+numbers[j] == number)
                    {
                        valid = true;
                        break;
                    }
                }
                if (valid)
                    break;
            }
            if(!valid)
            {
                std::cout << "First invalid number: " << number << '\n';
                return EXIT_SUCCESS;
            }
            numbers.erase(numbers.begin());
            numbers.push_back(number);
        }
        else
        {
            numbers.push_back(number);
        }
    }
    return EXIT_FAILURE;

}
