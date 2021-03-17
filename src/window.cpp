#include "ncursespp/window.h"
#include "ncursespp/color.h"

#include <algorithm>

#include <ncurses.h>

#undef getch
#undef refresh
#undef mvaddstr

ncurses::Window::Window(WINDOW* window_)
	: window{window_}
{
	keypad(window, true);
}

ncurses::Window::Window(Rect r_)
	: Window{newwin(r_.s.h, r_.s.w, r_.p.y, r_.p.x)}
{}

ncurses::Window::Window(Window&& other)
	: window{other.window}
{
	other.window = nullptr;
}

ncurses::Window& ncurses::Window::operator=(Window&& other)
{
	std::swap(window, other.window);
	return *this;
}

ncurses::Window::~Window()
{
	if (window != nullptr)
	{
		delwin(window);
	}
}

void ncurses::Window::draw_border()
{
	box(window, 0, 0);
}

void ncurses::Window::refresh()
{
	wrefresh(window);
}

void ncurses::Window::clear()
{
	wclear(window);
}

void ncurses::Window::focus(bool on)
{
	focused = on;	
}

void ncurses::Window::move(Point p)
{
	wmove(window, p.y, p.x);
}

void ncurses::Window::mvaddstr(Point p, std::string const& s)
{
	mvwaddstr(window, p.y, p.x, s.c_str());
}

int ncurses::Window::getch()
{
	return wgetch(window);
}

int ncurses::Window::setcolor(Color fg, Color bg)
{
	auto fg_index = static_cast<short>(fg);
	auto bg_index = static_cast<short>(bg);

	short color_pair_id = static_cast<short>(fg_index * 16 + bg_index);
	init_pair(color_pair_id, fg_index, bg_index);

	return wattron(window, COLOR_PAIR(color_pair_id));
}

ncurses::Rect ncurses::Window::get_rect() const
{
	Rect r;
	int maxx, maxy;
	getmaxyx(window, maxy, maxx);
	getyx(window, r.p.y, r.p.x);
	r.s = {maxx - r.p.x, maxy - r.p.y};
	return r;
}
