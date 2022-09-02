module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:AdapterResolveException;
import :Exception;

export namespace Atlas
{
	class DLLApi AdapterResolveException :
		public Exception
	{
		public:
		AdapterResolveException( const char* message , const void* source = nullptr ) noexcept :
			Exception( message , source )
		{}
	};
}