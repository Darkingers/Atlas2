module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:NullException;
import :Exception;

export namespace Atlas
{
	class DLLApi NullException :
		public Exception
	{
		public:
		NullException( const char* message , const void* source = nullptr ) noexcept :
			Exception( message , source )
		{}
	};
}