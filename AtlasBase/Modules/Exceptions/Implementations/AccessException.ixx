module;

#include "../../../../Macros/Macros.h"

export module AtlasExceptions:AccessException;

import :Exception;

export namespace Atlas
{
	class DLLApi AccessException :
		public Exception
	{
		public:
		constexpr AccessException( const std::string& message ) noexcept :
			Exception( message , nullptr )
		{}
		
		public:
		constexpr AccessException( const std::string& message , const void* source ) noexcept :
			Exception( message , source )
		{}

		public:
		constexpr AccessException( const AccessException& other ) noexcept :
			Exception( other )
		{}	
	};
}