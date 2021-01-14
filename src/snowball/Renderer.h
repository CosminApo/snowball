#include "component.h" /* Included for inheritance */
#include <rend/rend.h> /* rend::Texture, rend::Shader, rend::Mesh */
#include <memory> /* smart pointers */

namespace snowball
{
	// Forward declared structures.
	struct UIElement;
	/**
	* \brief The class responsible for displaying Entities on the screen.
	* 
	* This class stores the Shader, Shape and Texture associated with the Entity it is linked to.
	* It is also able to render the Entity using those properties.
	*/
	struct Renderer : public Component
	{
		friend struct ::snowball::UIElement; ///< Friends with UIElement to access the shape and texture.

		void onInitialize(); ///< Base initialize function inherited from Component. Used for creating the object.
		void onRender();  ///< Base render function inherited from Entity. Used for rendering every frame.
		void setModel(std::string _path); ///< Sets the Model of the Entity.
		void setShader(std::string _path); ///< Sets the Shader of the Entity.
		void setTexture(std::string _path); ///< Sets the Texture of the Entity.
		std::shared_ptr<rend::Mesh> getShape(); ///< Returns the Model stored.

	private:
		std::shared_ptr<rend::Shader> shader; ///< Stores the Shader associated with the Entity this Render Component is linked to.
		std::shared_ptr<rend::Mesh> shape; ///< Stores the Model associated with the Entity this Render Component is linked to.
		std::shared_ptr<rend::Texture> tex; ///< Stores the Texture associated with the Entity this Render Component is linked to.

	};
}