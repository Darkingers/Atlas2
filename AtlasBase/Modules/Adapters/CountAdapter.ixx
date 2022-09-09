module;

#include "../../../Macros/Macros.h"

export module AtlasAdapters:CountAdapter;
import AtlasConcepts;
import AtlasExceptions;

export namespace Atlas::Adapters
{
	template<typename CountedType>
	class DLLApi CountAdapter :
		public std::true_type
	{
		public:
		inline static auto Count( const CountedType& instance ) noexcept
		{
			return 1;
		}
	};
	
	template<typename CountedType> 
		requires Concept::IsStandardCountable<CountedType>
	class DLLApi CountAdapter<CountedType> :
		public std::true_type
	{
		private: static constexpr bool IsNoExcept = noexcept ( std::declval<CountedType>( ).size( ) );

	    public:
		inline static auto Count(const CountedType& instance) noexcept( IsNoExcept )
		{
			return instance.size( );
		}
	};

	template<typename CountedType>
		requires Concept::HasCountFunction<CountedType>
	class DLLApi CountAdapter<CountedType> :
		public std::true_type
	{
		private: static constexpr bool IsNoExcept = noexcept ( std::declval<CountedType>( ).Count( ) );

	    public:
		inline static auto Count(const CountedType& instance) noexcept( IsNoExcept )
		{
			return instance.Count();
		}
	};
}