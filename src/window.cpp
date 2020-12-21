#include "ncursespp/window.h"
#include "ncursespp/color.h"

#include <algorithm>

#include <ncurses.h>

#undef getch
#undef refresh

namespace ncurses
{
Window::Window(WINDOW* window_)
	: window{window_}
{}

Window::Window(Window& parent_, Rect r_)
	: window{subwin(parent_.window, r_.s.h, r_.s.w, r_.p.y, r_.p.x)}
	, parent{&parent_}
{}

Window::Window(Rect r_)
	: window{newwin(r_.s.h, r_.s.w, r_.p.y, r_.p.x)}
{}

Window::Window(Window&& other)
	: window{other.window}
{
	other.window = nullptr;
}

Window& Window::operator=(Window&& other)
{
	std::swap(window, other.window);
	return *this;
}

Window::~Window()
{
	if (window != nullptr)
	{
		delwin(window);
	}
}

void Window::draw_border()
{
	wborder(window, '|', '|', '-', '-', '+', '+', '+', '+');
}

void Window::repaint()
{
	refresh();
}

void Window::refresh()
{
	wrefresh(window);
}

void Window::clear()
{
	wclear(window);
}

void Window::focus(bool on)
{
	focused = on;	
	repaint();
}

int Window::getch()
{
	return wgetch(window);
}

int Window::setcolor(Color fg, Color bg)
{
	short color_pair_id = static_cast<short>(fg) * 16 + static_cast<short>(bg);
	init_pair(color_pair_id, static_cast<short>(fg), static_cast<short>(bg));
	return wattron(window, COLOR_PAIR(color_pair_id));
}

Rect Window::get_rect() const
{
	Rect r;
	int maxx, maxy;
	getmaxyx(window, maxy, maxx);
	getyx(window, r.p.y, r.p.x);
	r.s = {maxx - r.p.x, maxy - r.p.y};
	return r;
}
}
