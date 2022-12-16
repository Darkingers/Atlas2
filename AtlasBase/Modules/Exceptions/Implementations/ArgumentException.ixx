module;

#include "../../../../Macros/Macros.h"

export module AtlasExceptions:ArgumentException;

import :Exception;

export namespace Atlas
{
	class DLLApi ArgumentException :
		public Exception
	{
		
	public:
		
		constexpr ArgumentException( const std::string& message ) noexcept :
			Exception( message  )
		{}

		constexpr ArgumentException( const ArgumentException& other ) noexcept :
			Exception( other )
		{}
	};
}