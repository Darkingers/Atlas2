module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:Exception;

export namespace Atlas
{
	class DLLApi Exception
	{
		public: const void* Source;
		public: const std::string Message;

			
		public:
		constexpr Exception( const std::string& message) noexcept :
			Message( message ) ,
			Source( nullptr )
		{}
		
		public:
		constexpr Exception( const std::string& message, const void* source) noexcept :
			Message( message ) ,
			Source( source )
		{}

		public:	
		constexpr Exception( const Exception& other ) noexcept :
			Message( other.Message ) ,
			Source( other.Source )
		{}	

		public:
		virtual ~Exception( ) 		
		{}

		public:
		virtual std::string ToString( ) const 		
		{
			return Message;
		}
	};
}