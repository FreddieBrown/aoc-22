#include "shared.hpp"
#include "day5.hpp"

void getCrates(std::string crates, std::stack<std::tuple<int, std::string>> &crateStack)
{

    auto crateCounter(0);
    for (auto i = 0; i < crates.length(); i++)
    {
        crateCounter += 1;
        // Grab each crate
        auto crate = crates.substr(i, 3);
        i += 3;
        if (crate.find("[") != std::string::npos && crate.find("]") != std::string::npos)
        {
            crateStack.push(std::tuple<int, std::string>{crateCounter, crate});
        }
    }
}

void performInstructionP1(int cratesToMove, int initialStack, int finalStack, std::map<int, std::stack<std::string>> &crates)
{
    for (int i = cratesToMove; i > 0; i--)
    {
        if (auto search = crates.find(initialStack); search != crates.end())
        {
            // Add the element to the stack
            auto element = search->second.top();
            search->second.pop();
            if (auto search2 = crates.find(finalStack); search2 != crates.end())
            {
                // Add the element to the stack
                search2->second.push(element);
            }
            else
            {
                std::cout << "Final Stack Doesn't Exist " << finalStack << std::endl;
            }
        }
        else
        {
            std::cout << "Initial Stack Doesn't Exist " << initialStack << std::endl;
        }
    }
}

void performInstructionP2(int cratesToMove, int initialStack, int finalStack, std::map<int, std::stack<std::string>> &crates)
{
    if (cratesToMove == 0)
    {
        return;
    }
    if (auto search = crates.find(initialStack); search != crates.end())
    {
        // Add the element to the stack
        auto element = search->second.top();
        search->second.pop();

        performInstructionP2(cratesToMove - 1, initialStack, finalStack, crates);

        if (auto search2 = crates.find(finalStack); search2 != crates.end())
        {
            // Add the element to the stack
            search2->second.push(element);
        }
        else
        {
            std::cout << "Final Stack Doesn't Exist " << finalStack << std::endl;
        }
    }
    else
    {
        std::cout << "Initial Stack Doesn't Exist " << initialStack << std::endl;
    }
}

void decodeInstruction(std::string instruction, std::map<int, std::stack<std::string>> &crates, void (*mover)(int, int, int, std::map<int, std::stack<std::string>> &))
{
    std::regex word_regex("(\\d+)");
    auto words_begin =
        std::sregex_iterator(instruction.begin(), instruction.end(), word_regex);
    auto words_end = std::sregex_iterator();

    auto counter(0);
    int number(0);
    int initialStack(0);
    int finalStack(0);
    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
    {
        std::smatch match = *i;
        auto match_value = std::stoi(match.str());
        switch (counter)
        {
        case 0:
            number = match_value;
            break;
        case 1:
            initialStack = match_value;
            break;
        case 2:
            finalStack = match_value;
            break;
        }
        counter++;
    }

    mover(number, initialStack, finalStack, crates);
}

std::string printCrates(std::map<int, std::stack<std::string>> &crates)
{
    std::string result;
    for (auto pair : crates)
    {
        result.append(pair.second.top());
    }

    return result;
}

std::string day5::solver(std::string filename, bool part1)
{
    int total(0);
    std::string line;
    std::ifstream file(filename);
    std::stack<std::tuple<int, std::string>> initialStack;
    std::map<int, std::stack<std::string>> crates;

    bool initialDrawing = true;

    while (std::getline(file, line))
    {
        // If this is the first line, find out how many stacks of crates there are
        auto lineSize = line.length();
        if (initialDrawing)
        {
            if (lineSize == 0)
            {
                initialDrawing = false;
                // After this point, need to set things up to be moved around
                while (!initialStack.empty())
                {
                    auto next = initialStack.top();
                    initialStack.pop();
                    auto key = std::get<0>(next);
                    auto value = std::get<1>(next);
                    if (auto search = crates.find(key); search != crates.end())
                    {
                        // Add the element to the stack
                        search->second.push(value);
                    }
                    else
                    {
                        // Create a new stack
                        std::stack<std::string> newStack;
                        newStack.push(value);
                        crates.insert({key, newStack});
                    }
                }
            }
            else
            {
                getCrates(line, initialStack);
            }
        }
        else
        {
            // This will be moving instructions, so need to perform actions based on this
            if (part1)
                decodeInstruction(line, crates, *performInstructionP1);
            else
                decodeInstruction(line, crates, *performInstructionP2);
        }
    }

    return printCrates(crates);
}

void day5::part1()
{
    std::cout << "Part 1: " << solver("data/day5", true) << std::endl;
}

void day5::part2()
{
    std::cout << "Part 2: " << solver("data/day5", false) << std::endl;
}