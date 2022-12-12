module;

#include "../../../../Macros/Macros.h"

export module AtlasAPI:IteratorAPI;

import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas
{
	/// <summary>
	/// An API that calls the appropriate iterator adapter
	/// </summary>
	class DLLApi IteratorAPI
	{
	
	public:
		
		/// <summary>
		/// Returns the element the iterator is on
		/// </summary>
		template<typename TIterator>
		constexpr static inline auto Current( const TIterator& iterator )
			noexcept ( Concept::IsNoexceptCurrent<const TIterator&> )
		{
			return IteratorAdapter<const TIterator&>::Current( iterator );
		}

	    /// <summary>
		///Moves the iterator the specified steps
		/// </summary>
		template<typename TIterator>
		constexpr static inline bool Move( TIterator& iterator , int step = 1 )
			noexcept ( Concept::IsNoexceptMove<TIterator&> )
		{
			return IteratorAdapter<TIterator&>::Move( iterator , step );
		}
	};
}
