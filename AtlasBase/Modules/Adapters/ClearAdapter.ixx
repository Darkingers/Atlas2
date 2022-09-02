module;

#include "../../../Macros/Macros.h"

export module AtlasAdapters:ClearAdapter;
import AtlasConcepts;
import AtlasExceptions;

export namespace Atlas::Adapters
{
	template<typename ClearedType>
	class DLLApi ClearAdapter :
		public std::false_type
	{
		public:
		inline static void Clear( ClearedType& instance )
		{
			throw AdapterResolveException( "Could not resolve ClearAdapter" , &instance );
		}
	};
	
	template<typename ClearedType>
		requires IsStandardClearable<ClearedType>
	class DLLApi ClearAdapter<ClearedType> :
		public std::true_type
	{
		private: static constexpr bool NoExcept = noexcept ( std::declval<ClearedType>.clear( ) );

		public:
		inline static void Clear( ClearedType& instance ) noexcept ( NoExcept )
		{
			instance.clear( );
		}
	};

	template<typename ClearedType>
		requires HasClearFunction<ClearedType>
	class DLLApi ClearAdapter<ClearedType> :
		public std::true_type
	{
		private: static constexpr bool NoExcept = noexcept ( std::declval<ClearedType>.Clear( ) );

		public:
		inline static void Clear( ClearedType& instance ) noexcept ( NoExcept )
		{
			instance.Clear( );
		}
	};
}