#include <snowball/snowball.h>
#include <SDL.h>


int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 800;



struct Player : public Component
{
    int dummy;
};

int main(int argc, char* argv[])
{

    std::shared_ptr<Core> core = Core::initialize();
	
    std::shared_ptr<Entity> pe = core->addEntity();
  
    std::shared_ptr<Player> pc = pe->addComponent<Player>();


	return 0;
}