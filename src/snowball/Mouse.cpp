#include "Mouse.h"
namespace snowball
{
	int Mouse::getXpos()
	{
		return x_pos; // Return the X position.
	}
	int Mouse::getYpos()
	{
		return y_pos; // Return the Y position.
	}
	void Mouse::setXpos(int _x)
	{
		x_pos = _x; // Set the X position.
	}
	void Mouse::setYpos(int _y)
	{
		y_pos = _y; // Set the Y position.
	}
}