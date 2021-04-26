#ifndef NCURSESPP_GEOMETRY_H_
#define NCURSESPP_GEOMETRY_H_

namespace ncurses
{
struct Point
{
	int x;
	int y;
};

struct Size
{
	int w;
	int h;
};

struct Rect
{
	Point p;
	Size s;
};
}

#endif // NCURSESPP_GEOMETRY_H_
