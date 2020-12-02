#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

struct PasswordEntry
{
    int min_value = 0;
    int max_value = 0;
    char letter = ' ';
    std::string passwd;
};

int main(int arg, char** argv)
{
    std::ifstream input("data/day02_input.txt");
    if (!input.is_open())
    {
        return EXIT_FAILURE;
    }
    std::vector<PasswordEntry> entries;
    for (std::string line; std::getline(input, line); )
    {
        PasswordEntry entry;
        const size_t separator_pos = line.find('-');
        entry.min_value = std::stoi(line.substr(0, separator_pos));
        const size_t first_space = line.find(' ', separator_pos);
        entry.max_value = std::stoi(line.substr(separator_pos + 1, first_space));
        const size_t doube_point_pos = line.find(':', first_space);
        entry.letter = line[doube_point_pos - 1];
        const size_t last_space = line.find(' ', doube_point_pos);
        entry.passwd = line.substr(last_space);
        entries.push_back(entry);
    }
    size_t count = 0;
    for(auto& entry : entries)
    {
        const auto chara_count = std::count(entry.passwd.begin(), entry.passwd.end(), entry.letter);
        if(chara_count >= entry.min_value && chara_count <= entry.max_value)
        {
            count++;
        }
    }
    std::cout << "Correct count: " << count << '\n';
    return EXIT_SUCCESS;
}
