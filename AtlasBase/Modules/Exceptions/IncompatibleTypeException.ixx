module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:IncompatibleTypeException;

import :Exception;

export namespace Atlas
{
	class DLLApi IncompatibleTypeException :
		public Exception
	{
		public:
		constexpr IncompatibleTypeException( const std::string& message , const void* source = nullptr ) noexcept :
			Exception( message , source )
		{}

		public:
		constexpr IncompatibleTypeException( const IncompatibleTypeException& other ) noexcept :
			Exception( other )
		{}
	};
}