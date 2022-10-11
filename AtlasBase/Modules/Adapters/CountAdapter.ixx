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
		private: constexpr static bool IsNoexcept = noexcept ( Type<CountedType>::Intance( ).size( ) );

			
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
		private: constexpr static bool IsNoexcept = noexcept ( Type<CountedType>::Intance( ).Count( ) );

			
	    public:
		constexpr inline static auto Count(const CountedType& instance) 
			noexcept( IsNoexcept )
		{
			return instance.Count();
		}
	};
}
