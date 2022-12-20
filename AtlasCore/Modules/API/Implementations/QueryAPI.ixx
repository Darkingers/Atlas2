module;
#include "../../../../Macros/Macros.h"

export module AtlasAPI:QueryAPI;

import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas
{
	class DLLApi QueryAPI
	{
		
	public:
		
		template<typename TExpected, typename... TArgs>
		constexpr static inline auto CountType(const TArgs&&... args )
			noexcept( noexcept( (QueryAPI::CountType<TExpected>(args) + ...) ) )
		{
			return ( QueryAPI::CountType<TExpected>( args ) + ... );
		}

		template<typename TExpected, typename TActual>
		constexpr static inline auto CountType( const TActual& data )
			noexcept ( Concept::IsNoexceptCountType<TExpected , const TActual&> )
		{
			return CountTypeAdapter<TExpected, const TActual&>::Count( data );
		}

		template<typename TExpected , typename TActual> requires 
			Concept::IsFundamental<TActual>
		constexpr static inline auto CountType( TActual data )
			noexcept ( Concept::IsNoexceptCountType<TExpected , TActual> )
		{
			return CountTypeAdapter<TExpected ,TActual>::Count( data );
		}

		template<typename TActual>
		constexpr static inline auto Length( const TActual& current )
			noexcept ( Concept::IsNoexceptCountType<const TActual&> )
		{
			return LengthAdapter<const TActual&>::Length( TActual );
		}

		template<typename TActual> requires
			Concept::IsFundamental<TActual>
		constexpr static inline auto Length( const TActual current )
			noexcept ( Concept::IsNoexceptCountType<const TActual> )
		{
			return LengthAdapter<const TActual>::Length( current );
		}

		template<typename... TArgs>
		constexpr static inline bool Contains( const TArgs&&... args )
			noexcept ( Concept::IsNoexceptContain<const TArgs&&...> )
		{
			return ContainAdapter<const TArgs&&...>::Contains( std::forward<const TArgs&&>( args )... );
		}

		template<typename TCollection, typename... TArgs> requires
			Concept::IsCollection<TCollection>
		constexpr static inline bool Contains(const TCollection& collection, const TArgs&&... args )
			noexcept ( Concept::IsNoexceptContain<const TCollection& , const TArgs&&...> )
		{
			return ContainAdapter<const TArgs&&...>::Contains(collection, std::forward<const TArgs&&>( args )... );
		}

		template<typename... TArgs>
		constexpr static inline auto CountElement( const TArgs&&... args )
			noexcept ( Concept::IsNoexceptCountElement<const TArgs&&...> )
		{
			return CountElementAdapter<const TArgs&&...>::Count( std::forward<TArgs&&>( args )... );
		}

		template<typename TCollection , typename... TArgs> requires
			Concept::IsCollection<TCollection>
		constexpr static inline auto CountElement( const TCollection& collection , const TArgs&&... args )
			noexcept ( Concept::IsNoexceptCountElement<const TCollection& , const TArgs&&...> )
		{
			return CountElementAdapter<const TCollection& , const TArgs&&...>::Count( collection , std::forward<const TArgs&&>( args )... );
		}

		template<typename... TArgs>
		constexpr static inline auto IsMatch( const TArgs&&... args )
			noexcept ( Concept::IsNoexceptMatch<const TArgs&&...> )
		{
			return MatchAdapter<const TArgs&&...>::Match( std::forward<TArgs&&>( args )... );
		}

		template<typename TCollection , typename... TArgs> requires
			Concept::IsCollection<TCollection>
		constexpr static inline auto IsMatch( const TCollection& collection , const TArgs&&... args )
			noexcept ( Concept::IsNoexceptMatch<const TCollection& , const TArgs&&...> )
		{
			return MatchAdapter<const TCollection& , const TArgs&&...>::Match( collection , std::forward<const TArgs&&>( args )... );
		}

		template<typename... TArgs>
		constexpr static inline auto ContainsPattern( const TArgs&&... args )
			noexcept ( Concept::IsNoexceptContainPattern<const TArgs&&...> )
		{
			return ContainPatternAdapter<TArgs&&...>::ContainsPattern( std::forward<TArgs&&>( args )... );
		}

		template<typename TCollection, typename TPattern> requires
			Concept::IsCollection<TCollection> &&
			Concept::IsCollection<TPattern> &&
			Concept::IsSame<typename CollectionTraits<TCollection>::ElementType , typename CollectionTraits<TPattern>::ElementType>
		constexpr static inline auto ContainsPattern( const TCollection& collection , const TPattern& pattern )
			noexcept ( Concept::IsNoexceptContainPattern<const TCollection& , const TPattern&> )
		{
			return ContainPatternAdapter<const TCollection& , const TPattern&>::ContainsPattern( collection , pattern );
		}

		template<typename... TArgs>
		constexpr static inline auto CountPattern( const TArgs&&... args )
			noexcept ( Concept::IsNoexceptCountPattern<const TArgs&&...> )
		{
			return CountPatternAdapter<TArgs&&...>::CountPattern( std::forward<TArgs&&>( args )... );
		}

		template<typename TCollection , typename TPattern> requires
			Concept::IsCollection<TCollection>&&
			Concept::IsCollection<TPattern>&&
			Concept::IsSame<typename CollectionTraits<TCollection>::ElementType , typename CollectionTraits<TPattern>::ElementType>
		constexpr static inline auto CountPattern( const TCollection& collection , const TPattern& pattern )
			noexcept ( Concept::IsNoexceptCountPattern<const TCollection& , const TPattern&> )
		{
			return CountPatternAdapter<const TCollection& , const TPattern&>::CountPattern( collection , pattern );
		}

		template<typename... TArgs>
		constexpr static inline auto Any( const TArgs&&... args )
			noexcept ( Concept::IsNoexceptAny<const TArgs&&...> )
		{		
			return AnyAdapter<const TArgs&&...>::Any( std::forward<TArgs&&>( args )... );
		}

		template<typename TCollection , typename... TArgs> requires
			Concept::IsCollection<TCollection>
		constexpr static inline auto Any( const TCollection& collection , const TArgs&&... args )
			noexcept ( Concept::IsNoexceptAny<const TCollection& , const TArgs&&...> )
		{
			return AnyAdapter<const TCollection& , const TArgs&&...>::Any( collection , std::forward<const TArgs&&>( args )... );
		}

		template<typename... TArgs>
		constexpr static inline auto All( const TArgs&&... args )
			noexcept ( Concept::IsNoexceptAll<const TArgs&&...> )
		{
			return AllAdapter<const TArgs&&...>::All( std::forward<TArgs&&>( args )... );			
		}

		template<typename TCollection , typename... TArgs> requires
			Concept::IsCollection<TCollection>
		constexpr static inline auto All( const TCollection& collection , const TArgs&&... args )
			noexcept ( Concept::IsNoexceptAll<const TCollection& , const TArgs&&...> )
		{
			return AllAdapter<const TCollection& , const TArgs&&...>::All( collection , std::forward<const TArgs&&>( args )... );
		}
	};
}
