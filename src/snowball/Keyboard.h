#include <vector> /* std::vector */

namespace snowball
{
	// Forward declared structure.
	struct Core;
	/**
	* \brief Provides keyboard input handling. 
	* 
	* This class stores which key is pressed and which one is not. It also allows the engine to 
	* determine whether a key was pressed this frame.
	*/
	struct Keyboard
	{
		bool getKey(int key);  ///< Returns whether a key is currently pressed or not.
		bool getUpKey(int key); ///< Returns whether a key was pressed this frame or not.
		bool getDownKey(int key);  ///< Returns whether a key was released this frame or not.
		void deleteKey(int& key);  ///< Removes a key from the list of keys currently pressed.
	private:
		friend struct snowball::Core; ///< Friends with Core to access the vectors of keys.
		std::vector<int> keys; ///< Stores all the currently pressed keys.
		std::vector<int> downKeys; ///< Stores the keys pressed this frame.
		std::vector<int> upKeys; ///< Stores the keys released this frame.
	};
}