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
		AlreadyExistsException( const char* message , const void* source = nullptr ) noexcept :
			Exception( message , source )
		{}
	};
}