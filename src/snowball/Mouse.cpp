#include "Mouse.h"
namespace snowball
{
	int Mouse::getXpos()
	{
		return x_pos;
	}
	int Mouse::getYpos()
	{
		return y_pos;
	}
	void Mouse::setXpos(int _x)
	{
		x_pos = _x;
	}
	void Mouse::setYpos(int _y)
	{
		y_pos = _y;
	}
}