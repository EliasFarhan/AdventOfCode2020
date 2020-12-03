//
// Created by efarhan on 12/3/20.
//
#include <fstream>
#include <iostream>
#include <vector>

int main(int arg, char** argv)
{
    std::ifstream input("data/day03_input.txt");
    if (!input.is_open())
    {
        return EXIT_FAILURE;
    }
    size_t width = 0;
    std::vector<std::uint64_t> toboggan{};
    for (std::string line; std::getline(input, line); )
    {
        if(line.empty())
            continue;
        std::uint64_t value = 0;
        for(std::uint64_t i = 0; i < line.size(); i++)
        {
            if(line[i] == '#')
            {
                value = value | (1u << i);
            }

        }
        if(width < line.size())
        {
            width = line.size();
        }
        toboggan.push_back(value);
    }
    const size_t height = toboggan.size();
    size_t count = 0;
    std::uint64_t x = 0;
    std::uint64_t y = 0;
    while(y < height)
    {
        if(toboggan[y] & (1u << x))
        {
            count++;
        }
        x += 3;
        if(x >= width)
        {
            x = x % width;
        }
        y += 1;
    }
    std::cout << "Count: "<<count<<'\n';
    return EXIT_SUCCESS;
}