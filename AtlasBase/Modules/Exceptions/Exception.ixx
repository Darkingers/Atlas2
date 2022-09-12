module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:Exception;
import AtlasDefinitions;
import AtlasConcepts;
import AtlasMeta;

export namespace Atlas
{
	class DLLApi Exception
	{
		public: const void* Source;
		public: const char* Message;


		public:
		Exception( const char* message ="" , const void* source = nullptr ) noexcept :
			Message( message ) ,
			Source( source )
		{}
	};

	template<typename ExceptionType,  typename... Args>
		requires Concept::IsMore<sizeof...(Args), 0>
	void Throw(const char* message, const void* source, const Args&... arguments )
	{
		throw Meta::Extended<ExceptionType , const char* , const void*>::Create( message, source, std::forward<const Args&>( arguments )... );
	}

	template<typename ExceptionType , typename... Args>
		requires Concept::IsMore<sizeof...( Args ) , 0>
	void Throw( const char* message , const Args&... arguments )
	{
		throw Meta::Extended<ExceptionType , const char* , const void*>::Create( message , nullptr , std::forward<const Args&>( arguments )... );
	}

	template<typename ExceptionType , typename... Args>
		requires Concept::IsMore<sizeof...( Args ) , 0>
	void Throw( const void* source , const Args&... arguments )
	{
		throw Meta::Extended<ExceptionType , const char* , const void*>::Create( "" , source , std::forward<const Args&>( arguments )... );
	}

	template<typename ExceptionType , typename... Args>
		requires Concept::IsMore<sizeof...( Args ) , 0>
	void Throw( const Args&... arguments )
	{
		throw Meta::Extended<ExceptionType , const char* , const void*>::Create( "", nullptr, std::forward<const Args&>( arguments )... );
	}

	template<typename ExceptionType>
	void Throw( const char* message ="" , const void* source = nullptr )
	{
		throw ExceptionType( message , source );
	}
}