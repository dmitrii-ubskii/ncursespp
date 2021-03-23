#ifndef NCURSESPP_KEYS_H_
#define NCURSESPP_KEYS_H_

#include <curses.h>
#undef getch
#undef refresh
#undef mvaddstr
#undef mvaddnstr

namespace ncurses
{
struct Key
{
	int keycode;

	constexpr operator int() const { return keycode; }

	static Key const Enter;
	static Key const Backspace;
					 
	static Key const Up;
	static Key const Down;
	static Key const Left;
	static Key const Right;

	static constexpr Key Ctrl(Key k) { return {k.keycode & 037}; }
	static constexpr Key F(int n) { return {KEY_F(n)}; }
};

// overriding KEY_ENTER (actually a numpad enter key)
constexpr Key Key::Enter = {'\n'};
constexpr Key Key::Backspace = {KEY_BACKSPACE};

constexpr Key Key::Up = {KEY_UP};
constexpr Key Key::Down = {KEY_DOWN};
constexpr Key Key::Left = {KEY_LEFT};
constexpr Key Key::Right = {KEY_RIGHT};
}

#endif // NCURSESPP_KEYS_H_
