#include <iostream>
#include <vector>

// ANSI escape codes for color (greenish Game Boy style)
const std::string reset = "\033[0m";
const std::string colors[] = {
    "\033[38;5;232m", // Black
    "\033[38;5;22m",  // Dark green
    "\033[38;5;28m",  // Medium green
    "\033[38;5;34m",  // Light green
};

// Pixels mapped to unicode characters
const char *tiles[] = {"▖", "▗", "▘", "▝", "▀", "▛", "▌", "▙", "▄", "▟", "▐", "▜", "▚", "▞", " ", "█"};
//.......................0.....1.....2.....3....4....5....6.....7....8.....9...10...11....12....13...14...15
const char *graphic_tiles[] = {"█", "▒", "░", " "};

std::vector<std::vector<int>> pkmntr = {
    {5, 6, 14, 14, 5, 13, 6, 14},
    {5, 2, 14, 14, 6, 14, 6, 14},
    {2, 14, 7, 2, 2, 10, 0, 6},
    {14, 14, 6, 6, 14, 10, 3, 6},
};

std::vector<std::vector<int>> pkmntr2 = {
    {15, 15, 15, 14, 14, 14, 14, 14, 15, 15, 14, 15, 15, 14, 14, 14},

    {15, 14, 15, 14, 14, 14, 14, 14, 15, 14, 15, 14, 15, 14, 14, 14},

    {15, 15, 15, 14, 14, 14, 14, 14, 15, 14, 14, 14, 15, 14, 14, 14},

    {15, 14, 14, 14, 15, 14, 15, 14, 15, 14, 14, 14, 15, 14, 14, 14},

    {15, 14, 14, 14, 15, 14, 15, 14, 15, 14, 14, 15, 14, 14, 15, 14},

    {14, 14, 14, 14, 15, 15, 14, 14, 14, 14, 14, 15, 15, 14, 15, 14},

    {14, 14, 14, 14, 15, 14, 15, 14, 14, 14, 14, 15, 14, 15, 15, 14},

    {14, 14, 14, 14, 15, 14, 15, 14, 14, 14, 14, 15, 14, 14, 15, 14}};

void render_screen()
{
    for (const auto &row : pkmntr2)
    {
        for (int shade : row)
        {
            std::cout << tiles[shade] << tiles[shade] << reset;
        }
        std::cout << '\n';
    }
}

int main()
{
    std::cout << "\033[2J\033[H"; // Clear screen
    render_screen();
    std::cout << reset << std::endl;
    return 0;
}
