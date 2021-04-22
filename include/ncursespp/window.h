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
}

namespace ncurses
{
class Window
{
public:
	Window(WINDOW*);
	Window(Rect);

	Window(Window const&) = delete;
	Window& operator=(Window const&) = delete;

	Window(Window&&);
	Window& operator=(Window&&);

	~Window();

	void draw_border();
	void refresh();
	void clear();
	void erase();

	void move_cursor(Point);

	void addstr(std::string_view);
	void mvaddstr(Point, std::string_view);
	void mvaddnstr(Point, std::string_view, int count);

	template <typename ...Args>
	void printw(char const* fmt, Args ...args)
	{
		wprintw(window, fmt, args...);
		refresh();
	}

	template <typename ...Args>
	void mvprintw(Point p, char const* fmt, Args ...args)
	{
		mvwprintw(window, p.y, p.x, fmt, args...);
		refresh();
	}

	Key getch();

	int set_color(Color fg, Color bg);
	void fill_background();

	Point get_position() const;
	Size get_size() const;
	Rect get_rect() const;

	int get_x() const;
	int get_y() const;

	int get_width() const;
	int get_height() const;

	void move_to(Point);
	void resize(Size);

protected:
	WINDOW* window;

	short palette;
};
}

#endif // NCURSESPP_WINDOW_H__
