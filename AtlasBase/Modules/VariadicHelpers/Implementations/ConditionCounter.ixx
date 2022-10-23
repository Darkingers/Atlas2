module;

#include "../../../../Macros/Macros.h"

export module AtlasVariadicHelpers:ConditionCounter;
import AtlasDefinitions;
import :ConditionChecker;

export namespace Atlas::Variadics
{
	template<typename CollectionType> 
	class DLLApi ConditionCounter
	{
		private: using DataType = Deduce::CollectionContainedType<CollectionType>;
			
		
		public: template<typename ConditionType, typename... Args>
		constexpr static inline auto CountAny(const CollectionType& collection, const Args&... conditions )
		{
			const auto endIterator = collection.cend();
			auto currentIterator = collection.cbegin();

			auto counter = ConditionChecker<DataType>::Any( *currentIterator , std::forward<const Args&>( conditions )... );

			for (std::advance(currentIterator, 1); currentIterator != endIterator; std::advance(currentIterator,1) )
			{
				counter += ConditionChecker<DataType>::Any( *currentIterator, std::forward<const Args&>( conditions )... );
			}

			return counter;
		}

		public: template<typename ConditionType, typename... Args>
		constexpr static inline auto CountAll(const CollectionType& collection,const Args&... conditions )
		{
			const auto endIterator = collection.cend();
			auto currentIterator = collection.cbegin();

			auto counter = ConditionChecker<DataType>::All( *currentIterator , std::forward<const Args&>( conditions )... );

			for ( std::advance( currentIterator , 1 ); currentIterator != endIterator; std::advance( currentIterator , 1 ) )
			{
				counter += ConditionChecker<DataType>::All( *currentIterator , std::forward<const Args&>( conditions )... );
			}

			return counter;
		}
	};
}