#include "shared.hpp"
#include "day3.hpp"

int scorer(const char &letter)
{
    if (std::isupper(letter))
    {
        return ((int)letter) - ((int)'A') + 27;
    }
    else
    {
        return ((int)letter) - ((int)'a') + 1;
    }
}

int common(std::vector<std::string> &collectionOfItems)
{
    int total(0);
    std::set<char> items;
    for (auto group : collectionOfItems)
    {
        std::set<char> commonItems;

        for (const auto ch : group)
        {
            if ((items.count(ch) > 0 || items.size() == 0) && commonItems.count(ch) == 0)
            {
                commonItems.insert(ch);
            }
        }
        items = commonItems;
    }

    std::set<char>::iterator it;
    for (it = items.begin(); it != items.end(); ++it)
    {
        total += scorer(*it);
    }

    return total;
}

int solver(std::string filename, bool part1)
{
    int total(0);
    std::string rucksack;
    std::ifstream file(filename);
    std::vector<std::string> itemCollections;

    while (std::getline(file, rucksack))
    {
        int len(rucksack.length());
        if (part1)
        {
            itemCollections = {rucksack.substr(0, len / 2), rucksack.substr(len / 2, len)};
            total += common(itemCollections);
        }
        else
        {
            itemCollections.push_back(rucksack);
            if (itemCollections.size() == 3)
            {
                total += common(itemCollections);
                itemCollections.clear();
            }
        }
    }

    return total;
}

void day3::part1()
{
    std::cout << "Part 1: " << solver("data/day3", true) << std::endl;
}

void day3::part2()
{
    std::cout << "Part 2: " << solver("data/day3", false) << std::endl;
}