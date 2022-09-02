module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:IncompatibleTypeException;
import :Exception;

export namespace Atlas
{
	class DLLApi IncompatibleTypeException :
		public Exception
	{
		public:
		IncompatibleTypeException( const char* message , const void* source = nullptr ) noexcept :
			Exception( message , source )
		{}
	};
}