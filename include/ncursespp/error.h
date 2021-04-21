#ifndef NCURSESPP_ERROR_H_
#define NCURSESPP_ERROR_H_

#include <stdexcept>
#include <string>

namespace ncurses
{
class Error: public std::runtime_error
{
public:
	Error(std::string const& message) noexcept: std::runtime_error{message} {}
};
}

#endif // NCURSESPP_ERROR_H_
