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
		InvalidOperationException( const char* message , const void* source = nullptr ) noexcept :
			Exception( message , source )
		{}
	};
}