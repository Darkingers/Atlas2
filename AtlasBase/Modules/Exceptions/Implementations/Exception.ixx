module;

#include "../../../../Macros/Macros.h"

export module AtlasExceptions:Exception;

import AtlasConcepts;
import AtlasCoreInterfaces;

export namespace Atlas
{
	class DLLApi Exception :
		public IException
	{
		
	public: 
		
		const std::string ExceptionMessage;

			
		template<typename StringType> requires 
			Concept::HasToString<StringType>
		constexpr Exception( const StringType& string)
			noexcept :
			ExceptionMessage( string.ToString() )
		{}

		constexpr Exception( const std::string& string )
			noexcept :
			ExceptionMessage( string )
		{}

		virtual ~Exception( ) = default;

		const char* ToString( ) const 
			noexcept override
		{
			return ExceptionMessage.c_str();
		}
	};
}