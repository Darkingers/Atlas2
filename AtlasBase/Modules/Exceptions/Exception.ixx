module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:Exception;
import AtlasConverters;

export namespace Atlas
{
	class DLLApi Exception
	{
		public: const void* Source;
		public: const std::string Message;


		public:
		constexpr Exception( const std::string message ="" , const void* source = nullptr ) noexcept :
			Message( message ) ,
			Source( source )
		{}

		public:	
		constexpr Exception( const Exception& other ) noexcept :
			Message( other.Message ) ,
			Source( other.Source )
		{}	

		constexpr virtual std::string ToString( ) const
		{
			if ( Source == nullptr )
			{
				return Message;
			}
			else
			{
				return Message + " at " + Convert<std::string>::From( Source );
			}
		}
	};
}