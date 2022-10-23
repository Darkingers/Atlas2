module;

#include "../../../../Macros/Macros.h"

export module AtlasExceptions:DLLException;

import :Exception;

export namespace Atlas
{
	class DLLApi DLLException :
		public Exception
	{
		public:
		constexpr DLLException( const std::string& message ) noexcept :
			Exception( message , nullptr )
		{}
			
		public:
		constexpr DLLException( const std::string& message , const void* source ) noexcept :
			Exception( message , source )
		{}

		public:
		constexpr DLLException( const DLLException& other ) noexcept :
			Exception( other)
		{}
	};
}