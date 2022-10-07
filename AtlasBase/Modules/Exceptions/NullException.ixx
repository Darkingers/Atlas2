module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:NullException;

import :Exception;

export namespace Atlas
{
	class DLLApi NullException :
		public Exception
	{
		public:
		constexpr NullException( const std::string& message , const void* source = nullptr ) noexcept :
			Exception( message , source )
		{}

		public:
		constexpr NullException( const NullException& other ) noexcept :
			Exception( other )
		{}
	};
}