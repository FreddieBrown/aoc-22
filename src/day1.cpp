#include "shared.hpp"
#include "day1.hpp"

bool comp(int i, int j) { return (i > j); }

int mostCalories(int numOfElves, std::string filename)
{
    // Maintain a list of the numOfElves carrying the most calories
    // Add this together at the end

    int calorieCount(0);

    std::vector<int> calorieList;

    std::string myText;
    std::ifstream file(filename);
    while (std::getline(file, myText))
    {
        if (myText == "")
        {
            calorieList.push_back(calorieCount);
            calorieCount = 0;
        }
        else
        {
            calorieCount += std::stoi(myText);
        }
    }

    file.close();

    std::sort(calorieList.begin(), calorieList.end(), comp);

    return std::reduce(calorieList.begin(), calorieList.begin() + numOfElves);
}

void day1::part1()
{
    std::cout << "Part 1: " << mostCalories(1, "data/day1part1") << std::endl;
}

void day1::part2()
{
    std::cout << "Part 2: " << mostCalories(3, "data/day1part2") << std::endl;
}
