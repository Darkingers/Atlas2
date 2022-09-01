module;

#include "../../../Macros/Macros.h"
#include <tuple>

export module AtlasExceptions:Exception;
import AtlasDefinitions;

export namespace Atlas
{
	class DLLApi Exception
	{
		public: const void* Sender;
		public: const char* Message;


		public:
		Exception( const char* message , const void* source = nullptr ) noexcept :
			Message( message ) ,
			Sender( source )
		{}
	};

	template<typename SenderType = void , typename... Args>
	class DLLApi ExtentedException :
		public Exception
	{
		private: using ArgumentHolder = std::tuple<Args...>;

		public: const ArgumentHolder Arguments;


		public:
		ExtentedException( const char* message , const void* source, const Args&... arguments ) noexcept  :
			Exception( message, source ),
			Arguments( std::forward<const Args&>(arguments)... )
		{}

		public: template<unsigned int Index>
		DeduceIndexedArgumentType<Index , ArgumentHolder> GetArgument( ) const noexcept
		{
			return std::get<Index>( Arguments );
		}
	};

	template<template<typename...> typename ExceptionType,  typename... Args>
	void Throw(const char* message, void* source, const Args&... arguments )
	{
		throw ExceptionType<Args...>( message , source, std::forward<const Args&>( arguments )... );
	}

	template<template<typename...> typename ExceptionType , typename... Args>
	void Throw( const char* message , const Args&... arguments )
	{
		throw ExceptionType<Args...>( message , nullptr, std::forward<const Args&>( arguments )... );
	}

	template<template<typename...> typename ExceptionType , typename... Args>
	void Throw( const Args&... arguments )
	{
		throw ExceptionType<Args...>( "" , nullptr, std::forward<const Args&>( arguments )... );
	}
}