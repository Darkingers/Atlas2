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
		constexpr Exception( const std::string message ="" , const void* source = nullptr ) noexcept :
			Message( message ) ,
			Source( source )
		{}
	};
}