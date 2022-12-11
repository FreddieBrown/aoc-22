#include "shared.hpp"
#include "day6.hpp"

int lineChecker(std::string line, int size)
{
    std::set<char> container;

    for (auto i = 0; i + size - 1 < line.length(); i++)
    {
        for (auto j = i; j < i + size; j++)
        {
            if (container.count(line[j]) == 0)
            {
                container.insert(line[j]);
            }
        }
        if (container.size() == size)
        {
            return i + size;
        }
        else
        {
            container.clear();
        }
    }
    return 0;
}

int day6::solver(std::string filename, bool part1)
{
    int total(0);
    std::string line;
    std::ifstream file(filename);

    while (std::getline(file, line))
    {
        if (part1)
            return lineChecker(line, 4);
        else
            return lineChecker(line, 14);
    }

    return 0;
}

void day6::part1()
{
    std::cout << "Part 1: " << solver("data/day6", true) << std::endl;
}

void day6::part2()
{
    std::cout << "Part 2: " << solver("data/day6", false) << std::endl;
}