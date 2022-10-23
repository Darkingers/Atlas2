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
			Exception( message , nullptr )
		{}

		public: 
		constexpr AbortRequestedException( const std::string& message , const void* source ) noexcept :
			Exception( message , source )
		{}

		public: 
		constexpr AbortRequestedException( const AbortRequestedException& other ) noexcept :
			Exception( other )
		{}	
	};
}