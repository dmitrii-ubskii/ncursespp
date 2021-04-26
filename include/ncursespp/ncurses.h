#ifndef NCURSESPP_NCURSES_H_
#define NCURSESPP_NCURSES_H_

#include "ncursespp/window.h"

namespace ncurses
{
class Ncurses: public Window
{
public:
	Ncurses();
	~Ncurses();

	void raw(bool);
	void cbreak(bool);
	void echo(bool);
	void set_cursor_visible(bool);
};
}

#endif // NCURSESPP_NCURSES_H_
