#pragma once

#include <string>
#include <ctime>

using namespace std;

// colors
#define LIGHT_ORANGE "\e[38;5;216m"
#define TURQUOISE "\e[38;5;43m"
#define PALE_BLUE "\e[38;5;159m"
#define RED "\e[38;5;196m"
#define NO_COLOR "\e[0m"
#define GREY "\e[38;5;8m"
#define SILVER "\e[38;5;7m"
#define LIGHT_BLUE "\e[38;5;32m"

#define BOLD "\e[1m"
#define UNDERLINE "\e[4m"

// debug mag
#ifdef MAP
#define debug(text) (std::cout << LIGHT_ORANGE << "[debug]: " << text << " (" << __FILE__ << ":" << __LINE__ << ")" << NO_COLOR << std::endl)
#define debugtv(text, value) (std::cout << LIGHT_ORANGE << "[debug]: " << text << " = " << value << " (" << __FILE__ << ":" << __LINE__ << ")" << NO_COLOR << std::endl)
#else
#define debug(expression) ((void)0)
#define debugtv(exp, var) ((void)0)
#endif


string timestampToString(time_t &time);
