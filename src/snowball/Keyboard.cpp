#include "keyboard.h"

namespace snowball
{
	//maybe refractor this three with some macro / enum
	bool Keyboard::getKey(int key)
	{
		for (size_t ki = 0; ki < keys.size(); ki++)
		{
			if (keys.at(ki) == key)
			{
				return true;
			}
		}
		return false;
	}
	bool Keyboard::getUpKey(int key)
	{
		for (size_t ki = 0; ki < upKeys.size(); ki++)
		{
			if (upKeys.at(ki) == key)
			{
				return true;
			}
		}
		return false;
	}
	bool Keyboard::getDownKey(int key)
	{
		for (size_t ki = 0; ki < downKeys.size(); ki++)
		{
			if (downKeys.at(ki) == key)
			{
				return true;
			}
		}
		return false;
	}
	void Keyboard::deleteKey(int& key)
	{
		for (std::vector<int>::iterator it = keys.begin(); it != keys.end();)
		{
			if (*it == key)
			{
				//delete key 
				it = keys.erase(it);
			}
			else it++;
		}
	}
}