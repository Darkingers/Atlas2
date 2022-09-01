module;

#include "../../../Macros/Macros.h"

export module AtlasAdapters:CountAdapter;
import AtlasConcepts;

export namespace Atlas
{
	template<typename CountedType>
	class DLLApi CountAdapter :
		public std::true_type
	{
		public:
		inline static constexpr auto Count(const CountedType& instance) noexcept
		{
			return 1;
		}
	};

	template<typename CountedType> 
		requires IsStandardCountable<CountedType>
	class DLLApi CountAdapter<CountedType> :
		public std::true_type
	{
		private: static constexpr bool NoExcept = noexcept ( std::declval<CountedType>( ).size( ) );

	    public:
		inline static constexpr auto Count(const CountedType& instance) noexcept( NoExcept )
		{
			return instance.size( );
		}
	};

	template<typename CountedType>
		requires HasCountFunction<CountedType>
	class DLLApi CountAdapter<CountedType> :
		public std::true_type
	{
		private: static constexpr bool NoExcept = noexcept ( std::declval<CountedType>( ).Count( ) );

	    public:
		inline static constexpr auto Count(const CountedType& instance) noexcept( NoExcept )
		{
			return instance.Count();
		}
	};
}