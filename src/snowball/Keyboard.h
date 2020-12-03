#include <vector>

namespace snowball
{
	struct Core;
	struct Keyboard
	{
		bool getKey(int key);
		bool getUpKey(int key);
		bool getDownKey(int key);
		void deleteKey(int& key);
	private:
		friend struct snowball::Core;
		std::vector<int> keys;
		std::vector<int> downKeys;
		std::vector<int> upKeys;

	};
}