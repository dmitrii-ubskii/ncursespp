#include "ncursespp/window.h"

#include <algorithm>

#include <ncurses.h>

#undef getch
#undef refresh
#undef mvaddstr
#undef mvaddnstr

#include "ncursespp/color.h"
#include "ncursespp/error.h"

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

void ncurses::Window::erase()
{
	werase(window);
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

void ncurses::Window::mvaddstr(Point p, std::string_view s)
{
	mvwaddstr(window, p.y, p.x, s.data());
}

void ncurses::Window::mvaddnstr(Point p, std::string_view s, int count)
{
	mvwaddnstr(window, p.y, p.x, s.data(), count);
}

ncurses::Key ncurses::Window::getch()
{
	return {wgetch(window)};
}

int ncurses::Window::setcolor(Color fg, Color bg)
{
	auto fg_index = static_cast<short>(fg);
	auto bg_index = static_cast<short>(bg);

	short color_pair_id = static_cast<short>(fg_index * 16 + bg_index);
	init_pair(color_pair_id, fg_index, bg_index);

	return wattron(window, COLOR_PAIR(color_pair_id));
}

void ncurses::Window::setbackground(Color fg, Color bg)
{
	auto fg_index = static_cast<short>(fg);
	auto bg_index = static_cast<short>(bg);

	short color_pair_id = static_cast<short>(fg_index * 16 + bg_index);
	init_pair(color_pair_id, fg_index, bg_index);

	wbkgdset(window, COLOR_PAIR(color_pair_id));
}

ncurses::Size ncurses::Window::get_size() const
{
	Size s;
	getmaxyx(window, s.h, s.w);
	return s;
}

ncurses::Point ncurses::Window::get_position() const
{
	Point p;
	getbegyx(window, p.y, p.x);
	return p;
}

ncurses::Rect ncurses::Window::get_rect() const
{
	return {get_position(), get_size()};
}

int ncurses::Window::get_x() const
{
	return get_position().x;
}

int ncurses::Window::get_y() const
{
	return get_position().y;
}

int ncurses::Window::get_width() const
{
	return get_size().w;
}

int ncurses::Window::get_height() const
{
	return get_size().h;
}

void ncurses::Window::moveTo(Point p)
{
	mvwin(window, p.y, p.x);
}

void ncurses::Window::resize(Size s)
{
	if (s.h <= 0 || s.w <= 0)
	{
		throw ncurses::Error{
			"Window::resize() requires dimensions be greater than 0; got "
			"[" + std::to_string(s.w) + "×" + std::to_string(s.h) + "]"
		};
	}
	wresize(window, s.h, s.w);
}
