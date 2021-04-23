#include "ncursespp/window.h"

#include <algorithm>

#include <ncurses.h>

#undef getch
#undef refresh
#undef addstr
#undef mvaddstr
#undef mvaddnstr

#include "ncursespp/color.h"
#include "ncursespp/error.h"

ncurses::Window::Window(WINDOW* window_)
	: window{window_}
{
	keypad(window, true);
}

ncurses::Window::Window(Rect r)
	: Window{newwin(r.s.h, r.s.w, r.p.y, r.p.x)}
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

void ncurses::Window::move_cursor(Point p)
{
	wmove(window, p.y, p.x);
}

ncurses::Point ncurses::Window::get_cursor()
{
	Point p;
	getyx(window, p.y, p.x);
	return p;
}

void ncurses::Window::addstr(std::string_view s)
{
	waddstr(window, s.data());
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

void ncurses::Window::set_color(Color fg, Color bg)
{
	auto fg_index = static_cast<short>(fg);
	auto bg_index = static_cast<short>(bg);

	short color_pair_id = static_cast<short>(fg_index * 16 + bg_index);
	init_pair(color_pair_id, fg_index, bg_index);

	palette = color_pair_id;

	wattron(window, COLOR_PAIR(palette));
}

void ncurses::Window::fill_background()
{
	wbkgdset(window, COLOR_PAIR(palette));
}

attr_t compileAttributes(ncurses::AttributeSet const& attributes)
{
	auto attrs = attr_t{0};
	if (attributes[ncurses::Attribute::Normal])  // redundant but whatever
	{
		attrs |= A_NORMAL;
	}
	if (attributes[ncurses::Attribute::StandOut])
	{
		attrs |= A_STANDOUT;
	}
	if (attributes[ncurses::Attribute::Underline])
	{
		attrs |= A_UNDERLINE;
	}
	if (attributes[ncurses::Attribute::Reverse])
	{
		attrs |= A_REVERSE;
	}
	if (attributes[ncurses::Attribute::Blink])
	{
		attrs |= A_BLINK;
	}
	if (attributes[ncurses::Attribute::Dim])
	{
		attrs |= A_DIM;
	}
	if (attributes[ncurses::Attribute::Bold])
	{
		attrs |= A_BOLD;
	}
	if (attributes[ncurses::Attribute::Protect])
	{
		attrs |= A_PROTECT;
	}
	if (attributes[ncurses::Attribute::Invis])
	{
		attrs |= A_INVIS;
	}
	if (attributes[ncurses::Attribute::AltCharset])
	{
		attrs |= A_ALTCHARSET;
	}
	if (attributes[ncurses::Attribute::Italic])
	{
		attrs |= A_ITALIC;
	}
	return attrs;
}

void ncurses::Window::set_attributes(AttributeSet attributes)
{
	wattr_set(window, compileAttributes(attributes), palette, nullptr);
}

ncurses::AttributeSet parseAttributes(attr_t const& attrs)
{
	auto attributes = ncurses::AttributeSet{};
	if (attrs & A_STANDOUT)
	{
		attributes.set(ncurses::Attribute::StandOut);
	}
	if (attrs & A_UNDERLINE)
	{
		attributes.set(ncurses::Attribute::Underline);
	}
	if (attrs & A_REVERSE)
	{
		attributes.set(ncurses::Attribute::Reverse);
	}
	if (attrs & A_BLINK)
	{
		attributes.set(ncurses::Attribute::Blink);
	}
	if (attrs & A_DIM)
	{
		attributes.set(ncurses::Attribute::Dim);
	}
	if (attrs & A_BOLD)
	{
		attributes.set(ncurses::Attribute::Bold);
	}
	if (attrs & A_PROTECT)
	{
		attributes.set(ncurses::Attribute::Protect);
	}
	if (attrs & A_INVIS)
	{
		attributes.set(ncurses::Attribute::Invis);
	}
	if (attrs & A_ALTCHARSET)
	{
		attributes.set(ncurses::Attribute::AltCharset);
	}
	if (attrs & A_ITALIC)
	{
		attributes.set(ncurses::Attribute::Italic);
	}
	return attributes;
}

ncurses::AttributeSet ncurses::Window::get_attributes()
{
	attr_t attrs;
	short color_pair;
	wattr_get(window, &attrs, &color_pair, nullptr);
	return parseAttributes(attrs);
}

void ncurses::Window::add_attributes(ncurses::AttributeSet attributes)
{
	wattr_on(window, compileAttributes(attributes), nullptr);
}

void ncurses::Window::remove_attributes(ncurses::AttributeSet attributes)
{
	wattr_off(window, compileAttributes(attributes), nullptr);
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

void ncurses::Window::move_to(Point p)
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
