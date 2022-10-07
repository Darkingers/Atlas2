module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:InvalidOperationException;

import :Exception;

export namespace Atlas
{
	class DLLApi InvalidOperationException :
		public Exception
	{
		public:
		constexpr InvalidOperationException( const std::string& message , const void* source = nullptr ) noexcept :
			Exception( message , source )
		{}

		public:
		constexpr InvalidOperationException( const InvalidOperationException& other ) noexcept :
			Exception( other )
		{}
	};
}