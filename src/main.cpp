#include "shared.hpp"
#include "day1.hpp"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cout << "Need to provide an argument" << std::endl;
        return 0;
    }

    std::string day(argv[1]);

    if (day == "day1")
    {

        // do part 1
        day1::part1();
        // do part 2
        day1::part2();
    }
    else
    {
        std::cout << "Input doesn't match any days" << std::endl;
    }

    return 0;
}
