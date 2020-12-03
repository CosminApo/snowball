#include <exception>
#include <string>

namespace snowball
{
	/**
   * \brief Provides better exception handling.
   * 
   * Class inherits from the exception class in the standard library, 
   * but it adds the function of displaying an error message.
   */
	struct Exception : public std::exception
	{
		Exception(const std::string& message);
		virtual ~Exception() throw();
		virtual const char* what() const throw();

	private:
		std::string message; ///< The error message to be displayed.

	};


}
