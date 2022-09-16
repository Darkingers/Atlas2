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
			Throw<AdapterResolveException>( "Could not resolve " + typeid( ClearAdapter ).name( ) + "(" + typeid( ClearedType ).name( )+")" );
		}
	};
	
	template<typename ClearedType> 
		requires Concept::IsStandardClearable<ClearedType>
	class DLLApi ClearAdapter<ClearedType> :
		public std::true_type
	{
		private: static constexpr bool IsNoExcept = noexcept ( std::declval<ClearedType>.clear( ) );

		public:
		inline static void Clear( ClearedType& instance ) noexcept ( IsNoExcept )
		{
			instance.clear( );
		}
	};

	template<typename ClearedType>
		requires Concept::HasClearFunction<ClearedType>
	class DLLApi ClearAdapter<ClearedType> :
		public std::true_type
	{
		private: static constexpr bool IsNoExcept = noexcept ( std::declval<ClearedType>.Clear( ) );

		public:
		inline static void Clear( ClearedType& instance ) noexcept ( IsNoExcept )
		{
			instance.Clear( );
		}
	};
}