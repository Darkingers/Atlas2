module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:AlreadyExistsException;
import :Exception;

export namespace Atlas
{
	class DLLApi AlreadyExistsException :
		public Exception
	{
		public:
		constexpr AlreadyExistsException( const std::string& message , const void* source = nullptr ) noexcept :
			Exception( message , source )
		{}
	};
}