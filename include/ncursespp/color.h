#ifndef NCURSESPP_COLOR_H_
#define NCURSESPP_COLOR_H_

namespace ncurses
{
enum class Color: short
{
	Black = 0,
	Red = 1,
	Green = 2,
	Brown = 3,
	Blue = 4,
	Purple = 5,
	Cyan = 6,
	Gray = 7,
	DarkGray = 8,
	LightRed = 9,
	LightGreen = 10,
	Yellow = 11,
	LightBlue = 12,
	LightPurple = 13,
	LightCyan = 14,
	White = 15
};

struct Palette
{
	short color_pair = 0;
};

constexpr Palette DefaultPalette{0};
}

#endif // NCURSESPP_COLOR_H_
