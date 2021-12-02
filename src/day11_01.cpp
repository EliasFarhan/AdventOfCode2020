//
// Created by efarhan on 12/3/20.
//
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int arg, char** argv)
{
    std::ifstream input("data/day11_input.txt");
    if (!input.is_open())
    {
        return EXIT_FAILURE;
    }
    std::vector<std::string> grid{};
    for (std::string line; std::getline(input, line); )
    {
        if (line.empty())
            continue;
        grid.push_back(line);
    }

    constexpr char EMPTY_SEAT = 'L';
    constexpr char OCCUPIED_SEAT = '#';
    constexpr char FLOOR = '.';

    std::size_t count = 0;
    std::size_t change_count = 0;
    do
    {
        change_count = 0;
        const auto read_grid = grid;
        for (int row = 0; row < grid.size(); row++)
        {
            auto& gridRow = read_grid[row];
            for (int column = 0; column < gridRow.size(); column++)
            {
                const auto currentElement = read_grid[row][column];
                if (currentElement == FLOOR)
                    continue;
                int occupied = 0;
                for (int dx = -1; dx <= 1; dx++)
                {
                    for (int dy = -1; dy <= 1; dy++)
                    {
                        if (dx == 0 && dy == 0)
                            continue;
                        const int x = row + dx;
                        if (x < 0 || x >= grid.size())
                            continue;
                        const int y = column + dy;
                        if (y < 0 || y >= gridRow.size())
                            continue;
                        if (read_grid[x][y] == OCCUPIED_SEAT)
                            occupied++;
                    }
                }
                if (currentElement == EMPTY_SEAT && occupied == 0)
                {
                    grid[row][column] = OCCUPIED_SEAT;
                    change_count++;
                }
                else if (currentElement == OCCUPIED_SEAT && occupied >= 4)
                {
                    grid[row][column] = EMPTY_SEAT;
                    change_count++;
                }
            }
        }
        count++;
    } while (change_count != 0);
    std::size_t occupied = 0;
    for (auto& row : grid)
    {
        for (const char element : row)
        {
            if (element == OCCUPIED_SEAT)
                occupied++;
        }
    }
    std::cout << "Occupied: " << occupied << ", Round Count: " << count << '\n';
    return EXIT_SUCCESS;
}
