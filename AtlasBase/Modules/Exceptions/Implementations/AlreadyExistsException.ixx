module;

#include "../../../../Macros/Macros.h"

export module AtlasExceptions:AlreadyExistsException;

import :Exception;

export namespace Atlas
{
	class DLLApi AlreadyExistsException :
		public Exception
	{
		
	public:
		
		constexpr AlreadyExistsException( const std::string& message ) noexcept :
			Exception( message )
		{}
		
		constexpr AlreadyExistsException( const AlreadyExistsException& other ) noexcept :
			Exception( other )
		{}
	};
}