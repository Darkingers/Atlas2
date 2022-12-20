module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:ShiftAdapters;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename TCollection> requires
		( !Concept::IsIndexable<TCollection> ) &&
		Concept::HasIterator<TCollection>
	class DLLApi ShiftAdapter<TCollection& , const unsigned int , const int , const unsigned int> :
		public std::true_type
	{
		
	private:

		using ConstIteratorType = typename CollectionTraits<TCollection>::ConstIteratorType;
		using IteratorType = typename CollectionTraits<TCollection>::IteratorType;

	public:

		constexpr static inline void Shift( TCollection collection , const unsigned int shiftStart , const int shiftOffset , const unsigned int shiftLength )
			noexcept
			(  
				Concept::IsNoexceptLength<TCollection> &&
				Concept::HasNoexceptIterator<TCollection>&&
				Concept::HasNoexceptConstIterator<TCollection>&&
				Concept::IsNoexceptCopy<ConstIteratorType , ConstIteratorType , IteratorType>
			)
		{
			auto start = IteratorAPI::ConstAt( collection , shiftStart );
			const auto end = IteratorAPI::ConstAt( collection , shiftStart + shiftLength );
			
			auto target = IteratorAPI::At( collection , shiftStart + shiftOffset );

			ManipulationAPI::Copy( start , end , target );
		}
	};
}