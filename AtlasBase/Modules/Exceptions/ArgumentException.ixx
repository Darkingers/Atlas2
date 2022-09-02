module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:ArgumentException;
import :Exception;

export namespace Atlas
{
	class DLLApi ArgumentException :
		public Exception
	{
		public:
		ArgumentException( const char* message , const void* source = nullptr ) noexcept :
			Exception( message , source )
		{}
	};
}