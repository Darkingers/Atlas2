module;

#include "../../../../Macros/Macros.h"

export module AtlasExceptions:DLLException;

import :Exception;

export namespace Atlas
{
	class DLLApi DLLException :
		public Exception
	{
		
	public:
		
		constexpr DLLException( const std::string& message ) noexcept :
			Exception( message )
		{}
			
		constexpr DLLException( const DLLException& other ) noexcept :
			Exception( other)
		{}
	};
}