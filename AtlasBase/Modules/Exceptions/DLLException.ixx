module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:DLLException;
import :Exception;

export namespace Atlas
{
	class DLLApi DLLException :
		public Exception
	{
		public:
		DLLException( const char* message , const void* source = nullptr ) noexcept :
			Exception( message , source )
		{}
	};
}