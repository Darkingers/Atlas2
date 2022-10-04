module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:ArgumentException;
import :Exception;

export namespace Atlas
{
	class DLLApi ArgumentException :
		public Exception
	{
		public:
		constexpr ArgumentException( const std::string& message , const void* source = nullptr ) noexcept :
			Exception( message , source )
		{}

		public:
		constexpr ArgumentException( const ArgumentException& other ) noexcept :
			Exception( other )
		{}
	};
}