#ifndef NCURSESPP_KEYS_H_
#define NCURSESPP_KEYS_H_

#include <functional>

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

	bool operator==(Key const& other) const { return keycode == other.keycode; }

	static Key const Escape;

	static Key const Enter;
	static Key const Backspace;

	static Key const Home;
	static Key const End;
	static Key const PageUp;
	static Key const PageDown;

	static Key const Up;
	static Key const Down;
	static Key const Left;
	static Key const Right;

	static constexpr Key Ctrl(Key k) { return {k.keycode & 037}; }
	static constexpr Key F(int n) { return {KEY_F(n)}; }
};

// also Alt
constexpr Key Key::Escape = {27};

// overriding KEY_ENTER (actually a numpad enter key)
constexpr Key Key::Enter = {'\n'};
constexpr Key Key::Backspace = {KEY_BACKSPACE};

constexpr Key Key::Home = {KEY_HOME};
constexpr Key Key::End = {KEY_END};
constexpr Key Key::PageUp = {KEY_PPAGE};
constexpr Key Key::PageDown = {KEY_NPAGE};

constexpr Key Key::Up = {KEY_UP};
constexpr Key Key::Down = {KEY_DOWN};
constexpr Key Key::Left = {KEY_LEFT};
constexpr Key Key::Right = {KEY_RIGHT};
}

namespace std
{
template <>
struct hash<ncurses::Key>
{
	std::size_t operator()(const ncurses::Key& k) const
	{
		using std::size_t;
		using std::hash;

		// Compute individual hash values for first,
		// second and third and combine them using XOR
		// and bit shifting:

		return (hash<int>()(k.keycode));
	}
};
}

#endif // NCURSESPP_KEYS_H_
