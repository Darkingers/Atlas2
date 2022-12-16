module;
#include "../../../../Macros/Macros.h"

export module AtlasAPI:CollectionAPI;

import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas
{
	/// <summary>
	/// An API that calls the appropriate adapter for the collection.
	/// </summary>
	class DLLApi QueryAPI
	{
		
	public:

		/// <summary>
		/// Check if the collection contains the given element
		/// </summary>
		template<typename TCollection , typename TElement, typename... Args>
		constexpr static inline bool Contains( const TCollection collection, const TElement& element, const Args&... args )
			noexcept ( Concept::IsNoexceptContain<const TCollection , const TElement&> )
		{
			bool contains =  ContainAdapter<const TCollection , const TElement&>::Contains( collection , element );
			
			if constexpr ( sizeof...( args ) > 0 )
			{
				return contains && QueryAPI::Contains( collection , args... );
			}
			else
			{
				return contains;
			}
		}

	    /// <summary>
	    /// Check if the collection contains the given element
	    /// </summary>
		template<typename TCollection , typename TElement , typename... Args> requires
			Concept::IsFundamental<TElement>
		constexpr static inline bool Contains( const TCollection collection , const TElement element , const Args&... args )
			noexcept ( Concept::IsNoexceptContain<const TCollection , const TElement> )
		{
			bool contains = ContainAdapter<const TCollection , const TElement>::Contains( collection , element );

			if constexpr ( sizeof...( args ) > 0 )
			{
				return contains && QueryAPI::Contains( collection ,  args... );
			}
			else
			{
				return contains;
			}
		}

		/// <summary>
		/// Count the elements with TExpected type in the given collection
		/// </summary>
		template<typename TExpected, typename TActual>
		constexpr static inline auto CountType( const TActual& data )
			noexcept ( Concept::IsNoexceptCountType<TExpected , const TActual&> )
		{
			return CountTypeAdapter<TExpected, const TActual&>::Count( data );
		}

		/// <summary>
		/// Count the elements with TExpected type in the given collection
		/// </summary>
		template<typename TExpected , typename TActual> requires 
			Concept::IsFundamental<TActual>
		constexpr static inline auto CountType( TActual data )
			noexcept ( Concept::IsNoexceptCountType<TExpected , TActual> )
		{
			return CountTypeAdapter<TExpected ,TActual>::Count( data );
		}

		/// <summary>
		/// Count the given elements in the given collection
		/// <summary>
		template<typename TIterator, typename TElement>
		constexpr static inline auto CountElement( const TIterator start , const unsigned int step , const TElement& element )
			noexcept ( Concept::IsNoexceptCountElement<const TIterator , const TElement&> )
		{
			return CountElementAdapter<const TIterator , const TElement&>::Count( start , step , element );
		}

		/// <summary>
		/// Count the given elements in the given collection
		/// <summary>
		template<typename TIterator , typename TElement> requires 
			Concept::IsFundamental<TElement>
		constexpr static inline auto CountElement( const TIterator start , const unsigned int step , const TElement element )
			noexcept ( Concept::IsNoexceptCountElement<const TIterator , const TElement> )
		{
			return CountElementAdapter<const TIterator , const TElement>::Count( start , step , element );
		}

		/// <summary>
		/// Matches a collection against another.
		/// </summary>
		template<typename TA, typename TB>
		constexpr static inline auto IsMatch( const TA& a , const TB& b ,const unsigned int matchLength )
			noexcept ( Concept::IsNoexceptMatch<const TA& , const TB&> )
		{
			return MatchAdapter<const TA& , const TB&>::Match( a , b , matchLength );
		}

		/// <summary>
		/// Checks whether a collection contains a pattern
		/// </summary>
		template<typename TCollection , typename TPattern>
		constexpr static inline auto ContainsPattern( const TCollection& collection , const TPattern& pattern , const unsigned int matchLength )
			noexcept ( Concept::IsNoexceptContainPattern<const TCollection& , const TPattern&> )
		{
			return MatchAdapter<const TCollection& , const TPattern&>::Contains( collection , pattern , matchLength );
		}
	};
}
