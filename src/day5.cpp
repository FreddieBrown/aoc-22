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
        if (crate.find("[") != std::string::npos && crate.find("]") != std::string::npos) {
            std::cout << "Crate: " << crate << "; Len: "<< crate.length() << "; Crate: " << crateCounter << std::endl;
            crateStack.push(std::tuple<int, std::string>{crateCounter, crate});
        }  
    }
}

void performInstruction(int cratesToMove, int initialStack, int finalStack, std::map<int, std::stack<std::string>> &crates) {
    std::cout<<"Crates to move: "<<cratesToMove<<"; Initial Stack: "<<initialStack<<"; Final Stack: "<<finalStack<<std::endl;
    for (int i = cratesToMove; i > 0; i--) {
        std::cout<<"Moving from "<<initialStack<<" to "<<finalStack<<"; Crates Left To Move: "<<i<<std::endl;
    }
}

void decodeInstruction(std::string instruction, std::map<int, std::stack<std::string>> &crates) {
    std::cout<<instruction<<std::endl;
    std::regex word_regex("(\\d+)");
    auto words_begin = 
        std::sregex_iterator(instruction.begin(), instruction.end(), word_regex);
    auto words_end = std::sregex_iterator();

    std::cout << "Found "
              << std::distance(words_begin, words_end)
              << " numbers\n";
    auto counter(0);
    int number(0);
    int initialStack(0);
    int finalStack(0);
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        auto match_value = std::stoi(match.str());
        std::cout << "  " << match_value << '\n';
        switch(counter) {
            case 0:
                number=match_value;
                break;
            case 1:
                initialStack=match_value;
                break;
            case 2:
                finalStack=match_value;
                break;
        }
        counter++;
    }

    performInstruction(number, initialStack, finalStack, crates);
    
}

int day5::solver(std::string filename, bool part1)
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
        std::cout << "Size of string: " << lineSize << std::endl;
        if (initialDrawing) {
            if (lineSize == 0) {
                initialDrawing = false;
                // After this point, need to set things up to be moved around
                while(!initialStack.empty()) {
                    auto next = initialStack.top();
                    initialStack.pop();
                    auto key = std::get<0>(next);
                    auto value = std::get<1>(next);
                    std::cout << "Next Item: "<< key << "; " << value  << std::endl;
                    if (auto search = crates.find(key); search != crates.end()) {
                        // Add the element to the stack
                        search->second.push(value);
                    } else {
                        // Create a new stack
                        std::stack<std::string> newStack; 
                        newStack.push(value);
                        crates.insert({key, newStack});
                    }
                }
            } else {
                getCrates(line, initialStack);
            }
        }
         else {
            // This will be moving instructions, so need to perform actions based on this
            decodeInstruction(line, crates);
        }
        
    }

    return total;
}

void day5::part1()
{
    std::cout << "Part 1: " << solver("data/test", true) << std::endl;
}

void day5::part2()
{
    // std::cout << "Part 2: " << solver("data/day5", false) << std::endl;
}