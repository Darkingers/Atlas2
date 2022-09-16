module;

#include <utility>

export module AtlasExceptions;
export import :AbortRequestedException;
export import :AccessException;
export import :AdapterResolveException;
export import :AlreadyExistsException;
export import :ArgumentException;
export import :DLLException;
export import :Exception;
export import :IncompatibleTypeException;
export import :InvalidOperationException;
export import :NotFoundException;
export import :NotImplementedException;
export import :NullException;
export import :TimeoutException;
export import :ValidationException;

import AtlasConcepts;
import AtlasMeta;

export namespace Atlas
{
	template<typename ExceptionType , typename... Args>
		requires Concept::IsMore<sizeof...( Args ) , 0>
	void Throw( const char* message , const void* source , const Args&... arguments )
	{
		throw Meta::Extended<ExceptionType , const char* , const void*>::Create( message , source , std::forward<const Args&>( arguments )... );
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
		throw Meta::Extended<ExceptionType , const char* , const void*>::Create( "" , nullptr , std::forward<const Args&>( arguments )... );
	}

	template<typename ExceptionType>
	void Throw( const char* message = "" , const void* source = nullptr )
	{
		throw ExceptionType( message , source );
	}
}