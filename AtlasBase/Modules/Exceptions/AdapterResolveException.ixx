module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:AdapterResolveException;

import :Exception;

export namespace Atlas
{
	class DLLApi AdapterResolveException :
		public Exception
	{
		public:
		constexpr AdapterResolveException( const std::string& message ) noexcept :
			Exception( message , nullptr )
		{}
		
		public:
		constexpr AdapterResolveException( const std::string& message , const void* source ) noexcept :
			Exception( message , source )
		{}

		public:
		constexpr AdapterResolveException( const AdapterResolveException& other ) noexcept :
			Exception( other )
		{}
	};
}