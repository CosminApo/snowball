namespace snowball
{
	/**
	* \brief Provides mouse input handling.
	* 
	*  This class stores the current mouse cursor's X and Y position.
	*/
	struct Mouse 
	{
		int getXpos(); ///< Returns the current X position of the mouse cursor. 
		int getYpos();  ///< Returns the current Y position of the mouse cursor. 
		void setXpos(int _x); ///< Sets the current X position of the mouse cursor. 
		void setYpos(int _y); ///< Sets the current Y position of the mouse cursor. 
	private:
		int x_pos, y_pos; ///< Stores the X and Y position of the mouse cursor.
	};
}