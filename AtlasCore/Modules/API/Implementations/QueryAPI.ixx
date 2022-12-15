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
		template<typename TITerator , typename TElement, typename... Args>
		constexpr static inline bool Contains( const TITerator& start, const TITerator& end , const TElement& element, const Args&... args )
			noexcept ( Concept::IsNoexceptContain<const TITerator& , const TElement&> )
		{
			bool contains =  ContainAdapter<const TITerator&,const TElement&>::Contains( start, end , element );
			
			if constexpr ( sizeof...( args ) > 0 )
			{
				return contains && QueryAPI::Contains( start , end , args... );
			}
			else
			{
				return contains;
			}
		}

	    /// <summary>
	    /// Check if the collection contains the given element
	    /// </summary>
		template<typename TITerator , typename TElement , typename... Args>
			requires Concept::IsFundamental<TElement>
		constexpr static inline bool Contains( const TITerator& start , const TITerator& end , const TElement element , const Args&... args )
			noexcept ( Concept::IsNoexceptContain<const TITerator& , const TElement&> )
		{
			bool contains = ContainAdapter<const TITerator& , const TElement&>::Contains( start , end , element );

			if constexpr ( sizeof...( args ) > 0 )
			{
				return contains && QueryAPI::Contains( start , end , args... );
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
		constexpr static inline auto Count( const TActual& data )
			noexcept ( Concept::IsNoexceptCount<TExpected , const TActual&> )
		{
			return CountAdapter<TExpected, const TActual&>::Count( data );
		}

		/// <summary>
		/// Count the elements with TExpected type in the given collection
		/// </summary>
		template<typename TExpected , typename TActual>
			requires Concept::IsFundamental<TActual>
		constexpr static inline auto Count( TActual data )
			noexcept ( Concept::IsNoexceptCount<TExpected , TActual> )
		{
			return CountAdapter<TExpected ,TActual>::Count( data );
		}

	};
}
