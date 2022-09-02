module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:AbortRequestedException;
import :Exception;

export namespace Atlas
{
	class DLLApi AbortRequestedException :
		public Exception
	{
		public: AbortRequestedException( const char* message , const void* source = nullptr ) noexcept :
			Exception( message , source )
		{}
	};
}