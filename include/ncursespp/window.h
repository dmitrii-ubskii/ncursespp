#ifndef NCURSESPP_WINDOW_H__
#define NCURSESPP_WINDOW_H__

#include <algorithm>
#include <bits/c++config.h>
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <memory>
#include <string_view>
#include <type_traits>

#include "ncursespp/color.h"
#include "ncursespp/geometry.h"

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
		Window(Window& parent, Rect r);
		Window(Rect r);

		Window(Window const&) = delete;
		Window& operator=(Window const&) = delete;

		Window(Window&&);
		Window& operator=(Window&&);

		virtual ~Window();

		Window subwindow(Rect subwindow_area)
		{
			return subwindow<Window>(subwindow_area);
		}

		template<typename T, typename ...Args>
		T subwindow(Args ...args)
		{
			return T{*this, std::forward<Args>(args)...};
		}

		void draw_border();
		virtual void repaint();
		void refresh();
		void clear();
		void focus(bool on);

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

		int wgetch();
		virtual void handle_key(int) {}

		int setcolor(Color fg, Color bg);

		Rect get_rect() const;

	protected:
		WINDOW* window;

		Window* parent;

		bool focused = false;
};
}

#endif // NCURSESPP_WINDOW_H__
