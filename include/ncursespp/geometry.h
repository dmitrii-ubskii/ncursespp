#ifndef NCURSESPP_GEOMETRY_H__
#define NCURSESPP_GEOMETRY_H__

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

#endif // NCURSESPP_GEOMETRY_H__
