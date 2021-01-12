
namespace snowball
{
	struct Mouse 
	{
		int getXpos();
		int getYpos();
		void setXpos(int _x);
		void setYpos(int _y);
	private:
		int x_pos, y_pos;
	};
}