//
// Created by efarhan on 12/3/20.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <array>

struct Point
{
    std::uint32_t x = 0;
    std::uint32_t y = 0;

    Point operator+(Point p) const
    {
        return {p.x+x, p.y+y};
    }
    Point& operator+=(Point p)
    {
        x += p.x;
        y += p.y;
        return *this;
    }
};
struct Slope
{
    size_t count = 0;
    Point currentPos {};
    Point slope;
};

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
    const size_t slopeCount = 5;
    std::array<Slope, slopeCount> slopeResults =
            {{
                    {0,{0,0},{1,1}},
                    {0,{0,0},{3,1}},
                    {0,{0,0},{5,1}},
                    {0,{0,0},{7,1}},
                    {0,{0,0},{1,2}},
            }};
    while(std::any_of(slopeResults.begin(), slopeResults.end(), [&height](const Slope& result){
        return result.currentPos.y < height;
    }))
    {
        for(auto& result : slopeResults)
        {
            if(toboggan[result.currentPos.y] & (1u << result.currentPos.x))
            {
                result.count++;
            }
            result.currentPos += result.slope;
            if(result.currentPos.x >= width)
            {
                result.currentPos.x = result.currentPos.x  % width;
            }
        }

    }
    size_t count = 1;
    for(auto& result : slopeResults)
    {
        count *= result.count;
    }
    std::cout << "Count: "<<count<<'\n';
    return EXIT_SUCCESS;
}