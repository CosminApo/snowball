#include "keyboard.h"

namespace snowball
{
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