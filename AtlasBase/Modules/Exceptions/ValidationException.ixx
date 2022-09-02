module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:ValidationException;
import :Exception;

export namespace Atlas
{
	class DLLApi ValidationException :
		public Exception
	{
		public:
		ValidationException( const char* message , const void* source = nullptr ) noexcept :
			Exception( message , source )
		{}
	};
}