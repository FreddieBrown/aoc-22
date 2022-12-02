#include "shared.hpp"
#include "day2.hpp"

std::vector<std::string> string_split(const std::string &str)
{
    std::vector<std::string> result;
    std::istringstream iss(str);
    for (std::string s; iss >> s;)
        result.push_back(s);
    return result;
}

int part1Rules(std::string oppo, std::string you)
{
    // A, X -> Rock
    // B, Y -> Paper
    // C, Z -> Scissors
    int score(0);
    if (you == "X")
    {
        if (oppo == "A")
        {
            return 4;
        }
        else if (oppo == "C")
        {
            return 7;
        }
        else
        {
            return 1;
        }
    }
    else if (you == "Y")
    {
        if (oppo == "A")
        {
            return 8;
        }
        else if (oppo == "B")
        {
            return 5;
        }
        else
        {
            return 2;
        }
    }
    else
    {
        if (oppo == "B")
        {
            return 9;
        }
        else if (oppo == "C")
        {
            return 6;
        }
        else
        {
            return 3;
        }
    }
}

int part2Rules(std::string oppo, std::string res)
{
    // X -> Lose
    // Y -> Draw
    // Z -> Win

    if (oppo == "A")
    {
        if (res == "Z")
        {
            return 8;
        }
        else if (res == "Y")
        {
            return 4;
        }
        return 3;
    }
    else if (oppo == "B")
    {
        if (res == "Z")
        {
            return 9;
        }
        else if (res == "Y")
        {
            return 5;
        }

        return 1;
    }
    else
    {
        if (res == "Z")
        {
            return 7;
        }
        else if (res == "Y")
        {
            return 6;
        }
        return 2;
    }
}

int rockPaperScissors(std::string filename, int (*rules)(std::string, std::string))
{
    int total(0);
    std::string str;
    std::ifstream file(filename);

    while (std::getline(file, str))
    {
        std::vector<std::string> match = string_split(str);
        total += rules(match.at(0), match.at(1));
    }

    return total;
}

void day2::part1()
{
    std::cout << "Part 1: " << rockPaperScissors("data/day2", &part1Rules) << std::endl;
}

void day2::part2()
{
    std::cout << "Part 2: " << rockPaperScissors("data/day2", &part2Rules) << std::endl;
}
