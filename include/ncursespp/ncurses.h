#ifndef NCURSESPP_NCURSES_H__
#define NCURSESPP_NCURSES_H__

#include "ncursespp/window.h"

namespace ncurses
{
class Ncurses: public Window
{
	public:
		Ncurses();
		~Ncurses();

		void raw(bool);
		void echo(bool);

		bool has_colors();
};
}

#endif // NCURSESPP_NCURSES_H__
