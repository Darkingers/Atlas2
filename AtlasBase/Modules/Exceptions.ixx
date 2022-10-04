module;

#include <utility>
#include <string>

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
import AtlasExtensions;

export namespace Atlas
{
	template<typename ExceptionType , typename... Args>
		requires Concept::IsMore<sizeof...( Args ) , 0>
	constexpr void Throw( const std::string& message , const void* source , const Args&... arguments )
	{
		throw Extended<ExceptionType , const std::string& , const void*>::Allocate( message , source , std::forward<const Args&>( arguments )... );
	}

	template<typename ExceptionType , typename... Args>
		requires Concept::IsMore<sizeof...( Args ) , 0>
	constexpr void Throw( const char* message , const void* source , const Args&... arguments )
	{
		throw Extended<ExceptionType , const std::string& , const void*>::Allocate( message , source , std::forward<const Args&>( arguments )... );
	}

	template<typename ExceptionType , typename... Args>
		requires Concept::IsMore<sizeof...( Args ) , 0>
	constexpr void Throw( const std::string& message , const Args&... arguments )
	{
		throw Extended<ExceptionType , const std::string& , const void*>::Allocate( message , nullptr , std::forward<const Args&>( arguments )... );
	}

	template<typename ExceptionType , typename... Args>
		requires Concept::IsMore<sizeof...( Args ) , 0>
	constexpr void Throw( const char* message , const Args&... arguments )
	{
		throw Extended<ExceptionType , const std::string& , const void*>::Allocate( message , nullptr , std::forward<const Args&>( arguments )... );
	}

	template<typename ExceptionType , typename... Args>
		requires Concept::IsMore<sizeof...( Args ) , 0>
	constexpr void Throw( const void* source , const Args&... arguments )
	{
		throw Extended<ExceptionType , const std::string& , const void*>::Allocate( "" , source , std::forward<const Args&>( arguments )... );
	}

	template<typename ExceptionType , typename... Args>
		requires Concept::IsMore<sizeof...( Args ) , 0>
	constexpr void Throw( const Args&... arguments )
	{
		throw Extended<ExceptionType , const std::string& , const void*>::Allocate( "" , nullptr , std::forward<const Args&>( arguments )... );
	}

	template<typename ExceptionType>
	constexpr void Throw( const std::string& message = "" , const void* source = nullptr )
	{
		throw new ExceptionType( message , source );
	}

	template<typename ExceptionType>
	constexpr void Throw( const char* message = "" , const void* source = nullptr )
	{
		throw new ExceptionType( message , source );
	}
}