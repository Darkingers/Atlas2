module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:AccessException;
import :Exception;

export namespace Atlas
{
	class DLLApi AccessException :
		public Exception
	{
		public:
		AccessException( const char* message , const void* source = nullptr )noexcept :
			Exception( message , source )
		{}
	};
}