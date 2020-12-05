//
// Created by efarhan on 12/5/20.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <cassert>

struct BoardingPass
{
    std::uint32_t row = 0;
    std::uint32_t column = 0;
    std::uint32_t passId = 0;
};

int main(int arg, char** argv)
{
    std::ifstream input("data/day05_input.txt");
    if (!input.is_open())
    {
        return EXIT_FAILURE;
    }
    std::uint32_t maxSeatId = 0;
    for (std::string line; std::getline(input, line); )
    {
        if(line == "\n" || line.empty())
        {
            continue;
        }
        BoardingPass pass;
        std::uint8_t minRow = 0;
        std::uint8_t maxRow = 127;
        for(int i = 0; i < 7; i++)
        {
            const auto diff = maxRow-minRow;
            if(line[i] == 'F')
            {
                maxRow = diff / 2u + minRow;
            }
            else if(line[i] == 'B')
            {
                minRow = minRow + diff / 2u + 1;
            }
        }

        assert(maxRow == minRow);
        pass.row = maxRow;
        std::uint8_t minColumn = 0;
        std::uint8_t maxColumn = 7;
        for(int i = 7; i < 10; i++)
        {
            const auto diff = maxColumn - minColumn;
            if(line[i] == 'L')
            {
                maxColumn = diff / 2u + minColumn;
            }
            else if(line[i] == 'R')
            {
                minColumn = minColumn + diff / 2u + 1;
            }
        }
        assert(maxColumn == minColumn);
        pass.column = maxColumn;

        pass.passId = pass.row * 8u + pass.column;
        if(pass.passId > maxSeatId)
            maxSeatId = pass.passId;
    }
    std::cout<< "Max Seat Id: "<<maxSeatId<<'\n';
    return EXIT_SUCCESS;
}