#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

struct PasswordEntry
{
    int first_index = 0;
    int second_index = 0;
    char letter = ' ';
    std::string passwd;
};

bool is_valid_entry(const PasswordEntry& entry)
{
    const auto chara_first = entry.passwd[entry.first_index - 1u];
    const auto chara_second = entry.passwd[entry.second_index - 1u];
    if ((chara_first == entry.letter && chara_second != entry.letter) ||
        (chara_first != entry.letter && chara_second == entry.letter))
    {
        return true;
    }
    return false;
}

int main(int arg, char** argv)
{
    std::ifstream input("data/day02_input.txt");
    if (!input.is_open())
    {
        return EXIT_FAILURE;
    }

    std::cout << "Valid: " << is_valid_entry({ 1,3, 'a', "abcde" })<<'\n';
    std::cout << "Valid: " << is_valid_entry({ 1,3, 'c', "abcde" })<<'\n';
    std::cout << "Invalid: " << is_valid_entry({ 1,3, 'b', "cdefg" })<<'\n';
    std::cout << "Invalid: " << is_valid_entry({ 2,9, 'c', "ccccccccc" })<<'\n';

    std::vector<PasswordEntry> entries;
    for (std::string line; std::getline(input, line); )
    {
        if(line.empty())
            continue;
        PasswordEntry entry;
        const size_t separator_pos = line.find('-');
        entry.first_index = std::stoi(line.substr(0, separator_pos));
        const size_t first_space = line.find(' ', separator_pos);
        entry.second_index = std::stoi(line.substr(separator_pos + 1, first_space));
        const size_t double_point_pos = line.find(':', first_space);
        entry.letter = line[double_point_pos - 1];
        const size_t last_space = line.find(' ', double_point_pos);
        entry.passwd = line.substr(last_space+1);
        entries.push_back(entry);
    }
    size_t count = 0;
    for (const auto& entry : entries)
    {
        if (is_valid_entry(entry))
        {
            count++;
        }
    }
    std::cout << "Correct count: " << count << '\n';
    return EXIT_SUCCESS;
}
