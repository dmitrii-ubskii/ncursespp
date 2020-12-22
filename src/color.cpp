#include "ncursespp/color.h"

#include <ncurses.h>

void ncurses::start_color()
{
	::start_color();
}

bool ncurses::has_colors()
{
	return ::has_colors();
}

bool ncurses::can_change_color()
{
	return ::can_change_color();
}

