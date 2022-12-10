module;

#include "../../../../Macros/Macros.h"

export module AtlasExtensions:Throw;

import AtlasConcepts;

import :Extended;

export namespace Atlas
{
	template<typename ExceptionType, typename... TArgs>
	constexpr DLLApi void Throw( TArgs&&... args )
	{
		throw Extended<ExceptionType>::Construct( std::forward<TArgs&&>( TArgs )... );
	}

	template<typename ExceptionType>
	constexpr DLLApi void Throw( const std::string& message = "" , const void* source = nullptr )
	{		
		throw ExceptionType( message , source );
	}

	template<typename ExceptionType>
	constexpr DLLApi void Throw( const char* message = "" , const void* source = nullptr )
	{
		throw ExceptionType( message , source );
	};
}