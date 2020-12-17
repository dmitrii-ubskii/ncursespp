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
		void mvprintw(int x, int y, char const* fmt, Args ...args)
		{
			mvwprintw(window, y, x, fmt, args...);
			wrefresh(window);
		}

		template <typename ...Args>
		std::size_t mvprintw_wrap(int x, int y, std::size_t width, char const* fmt, Args ...args);

		template <typename ...Args>
		void mvprintw_chop(int x, int y, std::size_t width, char const* fmt, Args ...args);

		int wgetch();
		virtual void handle_key(int) {}

		int setcolor(Color fg, Color bg);

		Rect get_rect() const;

	protected:
		WINDOW* window;

		Window* parent;

		bool focused = false;
};

template <typename ...Args>
std::size_t Window::mvprintw_wrap(int x, int y, std::size_t width, char const* fmt, Args ...args)
{
	auto len = static_cast<std::size_t>(std::snprintf(nullptr, 0, fmt, args...) + 1);
	auto buf = std::make_unique<char[]>(len);
	std::snprintf(buf.get(), len, fmt, args...);

	int lines_printed = 0;
	auto cur_idx = 0ul;
	auto line_buffer = std::make_unique<char[]>(width + 1);

	auto find_next_space = [&](std::size_t pos)
	{
		return static_cast<std::size_t>(std::find_if(
			buf.get() + pos, buf.get() + len, [](char c) -> bool { return std::isspace(c); }
		) - buf.get());
	};

	while (cur_idx < len)
	{
		std::fill(line_buffer.get(), line_buffer.get() + width, ' ');
		line_buffer[width] = '\0';

		std::size_t next_space = find_next_space(cur_idx);
		if (next_space == len)
		{
			next_space = len;
		}

		if (next_space - cur_idx > width)
		{
			std::strncpy(line_buffer.get(), buf.get() + cur_idx, width);
			cur_idx += width;
		}
		else
		{
			auto break_point = next_space;
			while (next_space - cur_idx <= width)
			{
				break_point = next_space;
				if (buf[break_point] == '\n')
				{
					break;
				}
				next_space = find_next_space(break_point + 1);
				if (next_space == len)
				{
					if (len <= cur_idx + width)
					{
						break_point = len;
					}
					break;
				}
			}
			std::strncpy(line_buffer.get(), buf.get() + cur_idx, break_point - cur_idx);
			for (auto i = 0ul; i < width; i++)
			{
				auto& c = line_buffer[i];
				if (c == '\0')
				{
					c = ' ';
				}
			}
			line_buffer[width] = '\0';
			cur_idx = break_point + 1;
		}
		mvwprintw(window, y + lines_printed, x, "%s", line_buffer.get());
		lines_printed++;
	}
	wrefresh(window);
	return static_cast<std::size_t>(lines_printed);
}

template <typename ...Args>
void Window::mvprintw_chop(int x, int y, std::size_t width, char const* fmt, Args ...args)
{
	// FIXME some characters take several columns while still being one byte (e.g. ^H)
	auto buf = std::make_unique<char[]>(width + 1);
	auto len = static_cast<std::size_t>(std::snprintf(buf.get(), width + 1, fmt, args...));
	for (auto i = 0ul; i < width; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			len = i;
			break;
		}
	}

	if (len > width)
	{
		std::strncpy(buf.get() + width - 3, "...", 4);
	}
	else
	{
		for (auto i = len; i < width; i++)
		{
			buf.get()[i] = ' ';
		}
		buf.get()[width] = '\0';
	}
	mvwprintw(window, y, x, buf.get());
	wrefresh(window);
}
}

#endif // NCURSESPP_WINDOW_H__
