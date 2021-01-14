#pragma once
#include <exception> /* Included for inheritance */
#include <string>  /* std::string */

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
		Exception(const std::string& message);  ///< Constructor that takes in an error message as a string.
		virtual ~Exception() throw(); ///< Virtual destructor so that its always called.
		virtual const char* what() const throw(); ///< Function that outputs the message.

	private:
		std::string message; ///< The error message to be displayed.

	};


}
