module;

#include "../../../Macros/Macros.h"

export module AtlasExtensions:Throw;

import AtlasConcepts;

import :Extended;

export namespace Atlas
{
	template<typename ExceptionType , typename... Args>
		requires Concept::IsMore<sizeof...( Args ) , 0>
	constexpr DLLApi void Throw( const std::string& message , const void* source , const Args&... arguments )
	{
		throw Extended<ExceptionType , const std::string& , const void*>::Allocate( message , source , std::forward<const Args&>( arguments )... );
	}

	template<typename ExceptionType , typename... Args>
		requires Concept::IsMore<sizeof...( Args ) , 0>
	constexpr DLLApi void Throw( const char* message , const void* source , const Args&... arguments )
	{
		throw Extended<ExceptionType , const std::string& , const void*>::Allocate( message , source , std::forward<const Args&>( arguments )... );
	}

	template<typename ExceptionType , typename... Args>
		requires Concept::IsMore<sizeof...( Args ) , 0>
	constexpr DLLApi void Throw( const std::string& message , const Args&... arguments )
	{
		throw Extended<ExceptionType , const std::string& , const void*>::Allocate( message , nullptr , std::forward<const Args&>( arguments )... );
	}

	template<typename ExceptionType , typename... Args>
		requires Concept::IsMore<sizeof...( Args ) , 0>
	constexpr DLLApi void Throw( const char* message , const Args&... arguments )
	{
		throw Extended<ExceptionType , const std::string& , const void*>::Construct( message , nullptr , std::forward<const Args&>( arguments )... );
	}

	template<typename ExceptionType , typename... Args>
		requires Concept::IsMore<sizeof...( Args ) , 0>
	constexpr DLLApi void Throw( const void* source , const Args&... arguments )
	{
		throw Extended<ExceptionType , const std::string& , const void*>::Allocate( "" , source , std::forward<const Args&>( arguments )... );
	}

	template<typename ExceptionType , typename... Args>
		requires Concept::IsMore<sizeof...( Args ) , 0>
	constexpr DLLApi void Throw( const Args&... arguments )
	{
		throw Extended<ExceptionType , const std::string& , const void*>::Allocate( "" , nullptr , std::forward<const Args&>( arguments )... );
	}

	template<typename ExceptionType>
	constexpr DLLApi void Throw( const std::string& message = "" , const void* source = nullptr )
	{		throw new ExceptionType( message , source );
	}

	template<typename ExceptionType>
	constexpr DLLApi void Throw( const char* message = "" , const void* source = nullptr )
	{
		throw ExceptionType( message , source );
	};
}