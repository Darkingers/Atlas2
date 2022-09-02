module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:TimeoutException;
import :Exception;

export namespace Atlas
{
	class DLLApi TimeoutException :
		public Exception
	{
		public:
		TimeoutException( const char* message , const void* source = nullptr ) noexcept  :
			Exception( message , source )
		{}
	};
}