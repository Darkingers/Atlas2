module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:NotImplementedException;
import :Exception;

export namespace Atlas
{
	class DLLApi NotImplementedException :
		public Exception
	{
		public:
		NotImplementedException( const char* message , const void* source = nullptr ) noexcept :
			Exception( message , source )
		{}
	};
}