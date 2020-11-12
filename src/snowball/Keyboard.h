#include <vector>

namespace snowball
{
	struct Core;
	struct Keyboard
	{
		bool getKey(int key);
		void deleteKey(int& key);
	private:
		friend struct snowball::Core;
		std::vector<int> keys;
	};
}