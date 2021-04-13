#ifndef NCURSESPP_WINDOW_H__
#define NCURSESPP_WINDOW_H__

#include <string_view>

#include "ncursespp/color.h"
#include "ncursespp/geometry.h"
#include "ncursespp/keys.h"

extern "C"
{
	typedef struct _win_st WINDOW;
	int mvwprintw(WINDOW*, int y, int x, char const* fmt,...);
	int wprintw(WINDOW*, char const* fmt,...);
	int wrefresh(WINDOW*);
}

namespace ncurses
{
class Window
{
public:
	Window(WINDOW* window_);
	Window(Rect r);

	Window(Window const&) = delete;
	Window& operator=(Window const&) = delete;

	Window(Window&&);
	Window& operator=(Window&&);

	~Window();

	void draw_border();
	void refresh();
	void clear();
	void erase();
	void focus(bool on);

	void move(Point);

	void mvaddstr(Point, std::string_view);
	void mvaddnstr(Point, std::string_view, int count);

	template <typename ...Args>
	void printw(char const* fmt, Args ...args)
	{
		wprintw(window, fmt, args...);
		wrefresh(window);
	}

	template <typename ...Args>
	void mvprintw(Point p, char const* fmt, Args ...args)
	{
		mvwprintw(window, p.y, p.x, fmt, args...);
		wrefresh(window);
	}

	Key getch();

	int setcolor(Color fg, Color bg);
	void setbackground(Color fg, Color bg);

	Rect get_rect() const;

protected:
	WINDOW* window;

	Window* parent;

	bool focused = false;
};
}

#endif // NCURSESPP_WINDOW_H__
