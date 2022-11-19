module;

#include "../../../../Macros/Macros.h"

export module AtlasExceptions:NotFoundException;

import :Exception;

export namespace Atlas
{
	class DLLApi NotFoundException :
		public Exception
	{
		public:
		constexpr NotFoundException( const std::string& message ) noexcept :
			Exception( message , nullptr )
		{}
		
		public:
		constexpr NotFoundException( const std::string& message , const void* source ) noexcept :
			Exception( message , source )
		{}

		public:
		constexpr NotFoundException( const NotFoundException& other ) noexcept :
			Exception( other )
		{}
	};
}