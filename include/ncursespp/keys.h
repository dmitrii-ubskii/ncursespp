#ifndef NCURSESPP_KEYS_H_
#define NCURSESPP_KEYS_H_

#include <functional>

namespace ncurses
{
struct Key
{
	int keycode;

	constexpr operator int() const { return keycode; }

	bool operator==(Key const& other) const { return keycode == other.keycode; }

	static Key const Null;
	static Key const Escape;

	static Key const Enter;
	static Key const Backspace;

	static Key const Home;
	static Key const End;
	static Key const PageUp;
	static Key const PageDown;

	static Key const Down;
	static Key const Up;
	static Key const Left;
	static Key const Right;

	static constexpr Key Ctrl(Key k) { return {k.keycode & 037}; }
	static constexpr Key F(int n) { return {0410 + n}; }
};

constexpr Key Key::Null = {-1};  // ERR

// also Alt
constexpr Key Key::Escape = {033};

// not KEY_ENTER (that's actually a numpad enter key)
constexpr Key Key::Enter = {'\n'};
constexpr Key Key::Backspace = {0407};  // KEY_BACKSPACE

constexpr Key Key::Home = {0406};  // KEY_HOME
constexpr Key Key::End = {0550};  // KEY_END
constexpr Key Key::PageDown = {0522};  // KEY_NPAGE
constexpr Key Key::PageUp = {0523};  // KEY_PPAGE

constexpr Key Key::Down = {0402};  // KEY_DOWN
constexpr Key Key::Up = {0403};  // KEY_UP
constexpr Key Key::Left = {0404};  // KEY_LEFT
constexpr Key Key::Right = {0405};  // KEY_RIGHT
}

namespace std
{
template <>
struct hash<ncurses::Key>
{
	std::size_t operator()(const ncurses::Key& k) const noexcept
	{
		return (std::hash<int>()(k.keycode));
	}
};
}

#endif // NCURSESPP_KEYS_H_
