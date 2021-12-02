//
// Created by efarhan on 12/8/20.
//

#include <fstream>
#include <cassert>
#include <vector>
#include <iostream>
#include <string>

enum class InstructionType : std::uint8_t
{
    NONE = 0u,
    ACC,
    JMP,
    NOP
};

struct Instruction
{
    InstructionType type = InstructionType::NONE;
    std::int16_t argument = 0;
};


int main(int arg, char** argv)
{
    std::ifstream input("data/day08_input.txt");
    if (!input.is_open())
    {
        return EXIT_FAILURE;
    }
    std::vector<Instruction> instructions;
    for (std::string line; std::getline(input, line); )
    {
        if (line == "\n" || line.empty())
        {
            continue;
        }
        Instruction newInstruction;
        const auto spaceIndex = line.find(' ');
        std::string instruction = line.substr(0, spaceIndex);
        if(instruction == "acc")
        {
            newInstruction.type = InstructionType::ACC;
        }
        else if (instruction == "jmp")
        {
            newInstruction.type = InstructionType::JMP;
        }
        else if(instruction == "nop")
        {
            newInstruction.type = InstructionType::NOP;
        }
        else
        {
            //Invalid instruction type
            assert(false && "Invalid instruction type");
        }

        std::string number = line.substr(spaceIndex+1+(line[spaceIndex+1] == '+' ? 1 : 0));
        newInstruction.argument = std::stoi(number);

        instructions.push_back(newInstruction);
    }
    //instructions[61].type = InstructionType::NOP;
    size_t currentLine = 0;
    int accumulator = 0;
    std::vector<size_t> previousInstructions;
    while(currentLine < instructions.size())
    {
        const auto it = std::ranges::find(previousInstructions, currentLine);
        if(it != previousInstructions.end())
        {
            std::cout << "Before executing instruction "<<currentLine<<" the accumulator value is: "<<accumulator<<'\n';
            return EXIT_SUCCESS;
        }
        previousInstructions.push_back(currentLine);
        const auto& instruction = instructions[currentLine];
        switch(instruction.type)
        {
            case InstructionType::ACC:
                accumulator += instruction.argument;
                break;
            case InstructionType::JMP:
                currentLine += instruction.argument;
                continue;
            case InstructionType::NOP:
                break;
            default:
                break;
        }
        currentLine++;
    }
    return EXIT_SUCCESS;
}