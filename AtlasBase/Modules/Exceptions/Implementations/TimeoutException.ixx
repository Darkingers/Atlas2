module;

#include "../../../../Macros/Macros.h"

export module AtlasExceptions:TimeoutException;

import :Exception;

export namespace Atlas
{
	class DLLApi TimeoutException :
		public Exception
	{
		public:
		constexpr TimeoutException( const std::string& message ) noexcept :
			Exception( message , nullptr )
		{}
		
		public:
		constexpr TimeoutException( const std::string& message , const void* source  ) noexcept  :
			Exception( message , source )
		{}

		public:
		constexpr TimeoutException( const TimeoutException& other ) noexcept :
			Exception( other )
		{}
	};
}