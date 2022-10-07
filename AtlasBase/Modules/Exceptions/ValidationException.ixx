module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:ValidationException;

import :Exception;

export namespace Atlas
{
	class DLLApi ValidationException :
		public Exception
	{
		public:
		constexpr ValidationException( const std::string& message , const void* source = nullptr ) noexcept :
			Exception( message , source )
		{}

		public:
		constexpr ValidationException( const ValidationException& other ) noexcept :
			Exception( other )
		{}
	};
}