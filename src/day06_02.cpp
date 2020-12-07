
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <string>
#include <algorithm>

struct Form
{
    size_t index = 0;
    std::set<char> characters;
};

int main(int arg, char** argv)
{
    std::ifstream input("data/day06_input.txt");
    if (!input.is_open())
    {
        return EXIT_FAILURE;
    }

    size_t count = 0;
    Form currentForm{};
    for (std::string line; std::getline(input, line); )
    {
        if (line == "\n" || line.empty())
        {
            count += currentForm.characters.size();
            currentForm = {};
        }
        else
        {
            std::set<char> currentLineCharacters;
            for(auto c : line)
            {
                if(std::isalpha(c))
                {
                    currentLineCharacters.insert(c);
                }
            }
            if(currentForm.index > 0)
            {
                std::set<char> intersectSet;
                std::set_intersection(
                    currentLineCharacters.begin(), currentLineCharacters.end(),
                    currentForm.characters.begin(), currentForm.characters.end(),
                    std::inserter(intersectSet, intersectSet.begin()));
                currentForm.characters = intersectSet;
            }
            else
            {
                currentForm.characters = currentLineCharacters;
            }
            currentForm.index++;
        }
    }
    count += currentForm.characters.size();
    currentForm = {};
    std::cout << "Count: " << count << '\n';
}