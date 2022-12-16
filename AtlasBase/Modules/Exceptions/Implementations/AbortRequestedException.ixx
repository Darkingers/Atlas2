module;

#include "../../../../Macros/Macros.h"

export module AtlasExceptions:AbortRequestedException;

import :Exception;

export namespace Atlas
{
	class DLLApi AbortRequestedException :
		public Exception
	{
		
	public:
		
		constexpr AbortRequestedException( const std::string& message ) noexcept :
			Exception( message )
		{}

		constexpr AbortRequestedException( const AbortRequestedException& other ) noexcept :
			Exception( other )
		{}	
	};
}