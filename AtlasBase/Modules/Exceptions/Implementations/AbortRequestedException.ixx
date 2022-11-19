module;

#include "../../../../Macros/Macros.h"

export module AtlasExceptions:AbortRequestedException;

import :ExceptionBase;

export namespace Atlas
{
	class DLLApi AbortRequestedException :
		public ExceptionBase
	{
		public:
		constexpr AbortRequestedException( const std::string& message ) noexcept :
			ExceptionBase( message , nullptr )
		{}

		public: 
		constexpr AbortRequestedException( const std::string& message , const void* source ) noexcept :
			ExceptionBase( message , source )
		{}

		public: 
		constexpr AbortRequestedException( const AbortRequestedException& other ) noexcept :
			ExceptionBase( other )
		{}	
	};
}