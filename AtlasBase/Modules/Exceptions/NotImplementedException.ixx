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
		NotImplementedException( const std::string& message , const void* source = nullptr ) noexcept :
			Exception( message , source )
		{}

		public:
		NotImplementedException( const NotImplementedException& other ) noexcept :
			Exception( other )
		{}
	};
}