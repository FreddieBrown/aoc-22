#include "shared.hpp"
#include "day4.hpp"

std::tuple<int, int> highLow(std::string pair)
{
    int low = std::stoi(pair.substr(0, pair.find("-")));
    int high = std::stoi(pair.substr(pair.find("-") + 1, pair.length()));
    return std::tuple<int, int>{low, high};
}

int day4::solver(std::string filename, bool part1)
{
    int contains(0);
    int overlap(0);
    std::string line;
    std::ifstream file(filename);
    std::vector<std::string> itemCollections;

    while (std::getline(file, line))
    {
        // Split the pairs into different strings
        std::string elf1 = line.substr(0, line.find(","));
        std::string elf2 = line.substr(line.find(",") + 1, line.length());
        // Get the high and low of each elf
        auto elf1HL = highLow(elf1);
        auto elf2HL = highLow(elf2);
        // find diff between both lows and both highs
        int lowDiff = std::get<0>(elf1HL) - std::get<0>(elf2HL);
        int highDiff = std::get<1>(elf1HL) - std::get<1>(elf2HL);
        int lowHighDiffE1E2 = std::get<0>(elf1HL) - std::get<1>(elf2HL);
        int lowHighDiffE2E1 = std::get<0>(elf2HL) - std::get<1>(elf1HL);
        // Using this, easy to find contained ranges
        if ((lowDiff <= 0 && highDiff >= 0) || (lowDiff >= 0 && highDiff <= 0))
        {
            contains += 1;
        }
        else if ((lowDiff <= 0 && highDiff <= 0 && lowHighDiffE2E1 <= 0) || (lowDiff >= 0 && highDiff >= 0 && lowHighDiffE1E2 <= 0))
        {
            overlap += 1;
        }
    }

    if (part1)
        return contains;

    return contains + overlap;
}

void day4::part1()
{
    std::cout << "Part 1: " << solver("data/day4", true) << std::endl;
}

void day4::part2()
{
    std::cout << "Part 2: " << solver("data/day4", false) << std::endl;
}