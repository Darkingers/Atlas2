module;

#include "../../../../Macros/Macros.h"

export module AtlasExceptions:NullException;

import :Exception;

export namespace Atlas
{
	class DLLApi NullException :
		public Exception
	{
		
	public:
		
		constexpr NullException( const std::string& message ) noexcept :
			Exception( message )
		{}
		
		constexpr NullException( const NullException& other ) noexcept :
			Exception( other )
		{}
	};
}