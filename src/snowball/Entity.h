#include <vector> /* std::vector */
#include "component.h" /* Included for instantiation */
#include <memory> /* smart pointers */
#include "transform.h" /* Included for shortcut */
#include <string> /* std::string */
#include "Exception.h" /* Error handling */

namespace snowball
{
	// Forward declared structures
	struct Component;
	struct Core;

	/**
	*  \brief The base class for the Entities.
	*
	*  The Entity part of the Entity - Components system. An Entity can be thought of
	*  as a GameObject in other Engine. On their own, they are empty containers without any functionality,
	*  but they can be linked to multiple Components to gain features.
	*
	*/
	struct Entity
	{

		friend struct ::snowball::Core; ///< Friends with Core to access the Self and Core pointers.

		template <typename T>
		std::shared_ptr<T> addComponent() ///< Template function for adding a Component without paramaters.
		{
			std::shared_ptr<T> rtn = std::make_shared<T>(); // Create a pointer of type T
			rtn->entity = self; // Set the Entity pointer to this one
			components.push_back(rtn); // Add the component to the list
			 
			rtn->onInitialize(); // Initialize the component. 

			return rtn;
		}

		template <typename T, typename ... Args>
		std::shared_ptr<T> addComponent(Args&&... args) ///< Template function for adding a Component with paramaters.
		{
			std::shared_ptr<T> rtn = std::make_shared<T>(); // Create a pointer of type T
			rtn->entity = self; // Set the Entity pointer to this one
			components.push_back(rtn); // Add the component to the list

			rtn->onInitialize(std::forward<Args>(args)...); // Initialize the component with parameters.

			return rtn;
		}

		template <typename T>
		std::shared_ptr<T> getComponent() ///< Template function for returning a Component from the list of Components.
		{
			for (size_t ci = 0; ci < components.size(); ci++) // Iterate through the list of Components. 
			{
				std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(components.at(ci)); // Try to cast the Component into a pointer of type T.
				if (rtn) // If the cast succeded.
				{
					return rtn;
				}
			}
			return NULL;
			throw snowball::Exception("Failed to get Component. \n");
		}
		
		void tick(); ///< Base tick function that handles events every tick. To be overwritten in child classes.
		void render(); ///< Base tick function that handles events every render. To be overwritten in child classes.
		

		std::shared_ptr<Core> getCore(); ///< Returns a pointer to the Core object that this Entity is linked to. 

	private:
		std::vector<std::shared_ptr<Component>> components; ///< Stores a reference to each Component attached to this Entity.
		std::weak_ptr<Core> core; ///< Stores a reference to the Core structure this Entity is linked to.
		std::weak_ptr<Entity> self; ///< Stores a smart pointer to itself. (Used as a better "this" keyword)

	};
}

