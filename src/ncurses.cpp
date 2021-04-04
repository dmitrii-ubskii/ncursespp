#include "ncursespp/ncurses.h"
#include "ncursespp/color.h"

#include <ncurses.h>

ncurses::Ncurses::Ncurses()
	: Window{initscr()}
{
	ncurses::start_color();
	cbreak(true);
	echo(false);
	set_escdelay(0);
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

void ncurses::Ncurses::set_cursor_visible(bool visible)
{
	curs_set(visible);
}
