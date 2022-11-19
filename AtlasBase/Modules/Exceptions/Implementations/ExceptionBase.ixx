module;

#include "../../../../Macros/Macros.h"

export module AtlasExceptions:ExceptionBase;

import AtlasConcepts;
import AtlasIntegration;

export namespace Atlas
{
	class DLLApi ExceptionBase :
		public Exception
	{
		public: const std::string ExceptionMessage;

			
		public: template<typename StringType>
			requires Concept::HasToString<StringType>
		constexpr ExceptionBase( const StringType& string)
			noexcept :
			ExceptionMessage( string.ToString() )
		{}

		public:
		constexpr ExceptionBase( const std::string& string )
			noexcept :
			ExceptionMessage( string )
		{}

		public:

		public:
		virtual ~ExceptionBase( ) = default;

		public:
		const char* ToString( ) const 
			noexcept override
		{
			return ExceptionMessage.c_str();
		}
	};
}