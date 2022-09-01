module;

#include "../../../Macros/Macros.h"

export module AtlasVariadic:VariadicConditionCounter;
import AtlasDefinitions;
import :VariadicConditionChecker;

export namespace Atlas
{
	template<typename CollectionType, typename DataType> 
	class DLLApi VariadicConditionCounter
	{
		public: template<typename ConditionType, typename... Args>
		inline static constexpr auto CountAny(const CollectionType& collection, const Args&... conditions ) 
		{
			using IteratorType = DeduceConstIteratorType<CollectionType>;
			using Checker = VariadicConditionChecker<DataType>;

			const IteratorType endIterator = collection.cend();
			IteratorType currentIterator = collection.cbegin();

			auto counter = Checker::Any( *currentIterator , std::forward<const Args&>( conditions )... );

			for (std::advance(currentIterator, 1); currentIterator != endIterator; std::advance(currentIterator,1) )
			{
				counter += Checker::Any( *currentIterator, std::forward<const Args&>( conditions )... );
			}

			return counter;
		}

		public: template<typename ConditionType, typename... Args>
		inline static constexpr auto CountAll(const CollectionType& collection,const Args&... conditions ) 
		{
			using IteratorType = DeduceConstIteratorType<CollectionType>;
			using Checker = VariadicConditionChecker<DataType>;

			const IteratorType endIterator = collection.cend();
			IteratorType currentIterator = collection.cbegin();

			auto counter = Checker::All( *currentIterator , std::forward<const Args&>( conditions )... );

			for ( std::advance( currentIterator , 1 ); currentIterator != endIterator; std::advance( currentIterator , 1 ) )
			{
				counter += Checker::All( *currentIterator , std::forward<const Args&>( conditions )... );
			}

			return counter;
		}
	};
}