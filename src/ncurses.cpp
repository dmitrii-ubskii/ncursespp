#include "ncursespp/ncurses.h"

#include <ncurses.h>

namespace ncurses
{
Ncurses::Ncurses()
	: Window{initscr()}
{
	curs_set(0);
	start_color();
	raw(true);
	echo(false);
	keypad(window, true);
	// nonl();
	// intrflush(stdscr, false);
}

Ncurses::~Ncurses()
{
	endwin();
}

void Ncurses::raw(bool on)
{
	on ? ::raw() : noraw();
}

void Ncurses::echo(bool on)
{
	on ? ::echo() : noecho();
}

bool Ncurses::has_colors()
{
	return ::has_colors();
}
}
