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
        Instruction newInstruction{};
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
            assert(false);
        }

        std::string number = line.substr(spaceIndex+1+(line[spaceIndex+1] == '+' ? 1 : 0));
        newInstruction.argument = std::stoi(number);

        instructions.push_back(newInstruction);
    }

    size_t currentLine = 0;
    int accumulator = 0;
    std::vector<size_t> previousInstructions;
    while(currentLine < instructions.size())
    {
        const auto it = std::ranges::find(previousInstructions, currentLine);
        if(it != previousInstructions.end())
        {
            break;
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

    size_t currentChangedIndex = 0;
    size_t nextChangedIndex = 0;
    while(currentChangedIndex <= previousInstructions.size())
    {
        currentLine = 0;
        accumulator = 0;
        auto tmpInstructions = instructions;
        auto changedInstructionIt = std::find_if(previousInstructions.begin() + nextChangedIndex,
                                                 previousInstructions.end(),
                                                 [&instructions](const auto index)
            {
                return instructions[index].type == InstructionType::NOP ||
                instructions[index].type == InstructionType::JMP;
            });
        //We are at the end of the previous instructions and no result...
        assert(changedInstructionIt != previousInstructions.end());

        currentChangedIndex = std::distance(previousInstructions.begin(), changedInstructionIt);
        nextChangedIndex = currentChangedIndex + 1;
        auto& changedInstruction = tmpInstructions[previousInstructions[currentChangedIndex]];
        assert(changedInstruction.type == InstructionType::NOP ||
            changedInstruction.type == InstructionType::JMP);

        changedInstruction.type =
                changedInstruction.type == InstructionType::NOP ?
                InstructionType::JMP :
                InstructionType::NOP;
        std::vector<size_t> tmpPreviousInstructions;
        while(currentLine < tmpInstructions.size())
        {
            const auto it = std::ranges::find(tmpPreviousInstructions, currentLine);
            if(it != tmpPreviousInstructions.end())
            {
                break;
            }
            tmpPreviousInstructions.push_back(currentLine);
            const auto& instruction = tmpInstructions[currentLine];
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
        std::cout << "Current line: "<<currentLine<<" Accumulator: "<<accumulator<<'\n';
        if(currentLine >= tmpInstructions.size())
        {
            std::cout << "The accumulator value is "<< accumulator <<'\n';
            return EXIT_SUCCESS;
        }
    }
    return EXIT_SUCCESS;
}