module;

#include "../../Macros/Macros.h"

export module AtlasVariadicHelpers;
export import :ContainChecker;
export import :ConditionChecker;
export import :ConditionCounter;
export import :Counter;

export namespace Atlas
{
	class DLLApi VariadicHelper
	{
		public: template<typename... Args>
		constexpr static inline auto Count( const Args&... arguments )
		{
			return Counter::Count( std::forward<const Args&>( arguments )... );
		}

		public: template<typename CollectionType , typename... Args>
		constexpr static inline auto CountAny( const CollectionType& collection , const Args&... arguments )
		{
			return ConditionCounter<CollectionType>::CountAny( collection , std::forward<const Args&>( arguments )... );
		}

		public: template<typename CollectionType , typename... Args>
		constexpr static inline auto CountAll( const CollectionType& collection , const Args&... arguments )
		{
			return ConditionCounter<CollectionType>::CountAll( collection , std::forward<const Args&>( arguments )... );
		}

		public: template<typename DataType , typename... Args>
		constexpr static inline bool AnyFulfills( const DataType& data , const Args&... arguments )
		{
			return ConditionChecker<DataType>::AnyFulfills( data , std::forward<const Args&>( arguments )... );
		}

		public: template<typename DataType , typename... Args>
		constexpr static inline bool AllFulfills( const DataType& data , const Args&... arguments )
		{
			return ConditionChecker<DataType>::AllFulfills( data , std::forward<const Args&>( arguments )... );
		}

		public: template<typename DataType , typename... Args>
		constexpr static inline bool AnyContains( const DataType& data , const Args&... arguments )
		{
			return ContainChecker<DataType>::AnyContains( data , std::forward<const Args&>( arguments )... );
		}

		public: template<typename DataType , typename... Args>
		constexpr static inline bool AllContains( const DataType& data , const Args&... arguments )
		{
			return ContainChecker<DataType>::AllContains( data , std::forward<const Args&>( arguments )... );
		}
	};
}