module;

#include "../../../Macros/Macros.h"

export module AtlasAdapters:CountAdapter;

import AtlasConcepts;
import AtlasTypeInfo;

export namespace Atlas::Adapters
{
	template<typename CountedType>
	class DLLApi CountAdapter :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = true;


		public:
		constexpr inline static auto Count( const CountedType& instance ) noexcept
		{
			return 1;
		}
	};
	
	template<typename CountedType> 
		requires Concept::IsStandardCountable<CountedType>
	class DLLApi CountAdapter<CountedType> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept ( std::declval<CountedType>( ).size( ) );

			
	    public:
		constexpr inline static auto Count(const CountedType& instance) 
			noexcept( IsNoexcept )
		{
			return instance.size( );
		}
	};

	template<typename CountedType>
		requires Concept::HasCountFunction<CountedType>
	class DLLApi CountAdapter<CountedType> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept ( std::declval<CountedType>( ).Count( ) );

			
	    public:
		constexpr inline static auto Count(const CountedType& instance) 
			noexcept( IsNoexcept )
		{
			return instance.Count();
		}
	};

	template<>
	class DLLApi CountAdapter<std::string> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept ( std::declval<std::string>( ).length( ) );


		public:
		constexpr inline static auto Count( const std::string& instance )
			noexcept( IsNoexcept )
		{
			return instance.length( );
		}
	};

	template<>
	class DLLApi CountAdapter<char*> :
		public std::true_type
	{
		public:
		constexpr inline static auto Count( const char* instance )
			noexcept( true )
		{
			unsigned int i = 0;

			while ( instance[i++] != '\0' )
			{
				i++;
			}

			return i;
		}

		public: template<unsigned int Size>
		constexpr inline static auto Count( const char( &instance )[Size] )
		{
			return Size;
		}
	};
}
