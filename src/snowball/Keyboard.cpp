#include "keyboard.h"

namespace snowball
{
	bool Keyboard::getKey(int key)
	{
		for (size_t ki = 0; ki < keys.size(); ki++) // Loop through all the keys currently pressed.
		{
			if (keys.at(ki) == key) // If the key matches the one queried. 
			{
				return true;
			}
		}
		return false;
	}
	bool Keyboard::getUpKey(int key)
	{
		for (size_t ki = 0; ki < upKeys.size(); ki++) // Loop through all the keys pressed this frame.
		{
			if (upKeys.at(ki) == key) // If the key matches the one queried. 
			{
				return true;
			}
		}
		return false;
	}
	bool Keyboard::getDownKey(int key)
	{
		for (size_t ki = 0; ki < downKeys.size(); ki++) // Loop through all the keys released this frame.
		{
			if (downKeys.at(ki) == key) // If the key matches the one queried. 
			{
				return true;
			}
		}
		return false;
	}
	void Keyboard::deleteKey(int& key)
	{
		for (std::vector<int>::iterator it = keys.begin(); it != keys.end();) // Loop through all the keys currently pressed.
		{
			if (*it == key) // If the key matches the one queried. 
			{
				//delete key 
				it = keys.erase(it);
			}
			else it++;
		}
	}
}