#include "ncursespp/ncurses.h"

#include <ncurses.h>

ncurses::Ncurses::Ncurses()
	: Window{initscr()}
{
	curs_set(0);
	start_color();
	cbreak(true);
	echo(false);
	keypad(window, true);
	// nonl();
	// intrflush(stdscr, false);
}

ncurses::Ncurses::~Ncurses()
{
	endwin();
}

void ncurses::Ncurses::cbreak(bool on)
{
	on ? ::cbreak() : nocbreak();
}

void ncurses::Ncurses::raw(bool on)
{
	on ? ::raw() : noraw();
}

void ncurses::Ncurses::echo(bool on)
{
	on ? ::echo() : noecho();
}

bool ncurses::Ncurses::has_colors()
{
	return ::has_colors();
}
