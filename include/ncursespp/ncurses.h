#ifndef NCURSESPP_NCURSES_H_
#define NCURSESPP_NCURSES_H_

#include "ncursespp/color.h"
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

	bool has_colors();
	bool can_change_color();
	void register_palette(Palette, Color fg, Color bg);
};
}

#endif // NCURSESPP_NCURSES_H_
