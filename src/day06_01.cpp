
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <string>

struct Form
{
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
            for(auto c : line)
            {
                if(std::isalpha(c))
                {
                    currentForm.characters.insert(c);
                }
            }
        }
    }
    count += currentForm.characters.size();
    currentForm = {};
    std::cout << "Count: " << count << '\n';
}