module;

#include "../../../../Macros/Macros.h"

export module AtlasExceptions:IncompatibleTypeException;

import :Exception;

export namespace Atlas
{
	class DLLApi IncompatibleTypeException :
		public Exception
	{
		
	public:
		
		constexpr IncompatibleTypeException( const std::string& message ) noexcept :
			Exception( message  )
		{}

		constexpr IncompatibleTypeException( const IncompatibleTypeException& other ) noexcept :
			Exception( other )
		{}
	};
}