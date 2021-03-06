

#include <fstream>
#include <iostream>
#include <string>
#include <vector>



int main(int argc, char** argv)
{
    const int sum = 2020;
    std::ifstream input("data/day01_input.txt");
    if(!input.is_open())
    {
        return EXIT_FAILURE;
    }
    std::vector<int> numbers;
    for (std::string line; std::getline(input, line); )
    {
        numbers.push_back(std::stoi(line));
    }
    size_t sumCount = 0;
    for(size_t i = 0; i < numbers.size(); i++)
    {
        for(size_t j = i+1; j < numbers.size(); j++)
        {
            if(numbers[i]+numbers[j] == sum)
            {
                std::cout << "The pair of number is " << numbers[i] << " and " <<
                    numbers[j] << " with product: " << numbers[i] * numbers[j] << '\n';
                return EXIT_SUCCESS;
            }
        }
    }
    
    return EXIT_SUCCESS;
}
