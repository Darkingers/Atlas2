module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:NotFoundException;
import :Exception;

export namespace Atlas
{
	class DLLApi NotFoundException :
		public Exception
	{
		public:
		constexpr NotFoundException( const std::string& message , const void* source = nullptr ) noexcept :
			Exception( message , source )
		{}
	};
}