module;

#include "../../../../Macros/Macros.h"

export module AtlasVariadicHelpers:ConditionChecker;

export namespace Atlas
{
	template<typename DataType>
	class DLLApi ConditionChecker
	{
		public: template<typename ConditionType, typename... Args>
		constexpr static inline bool AnyFulfills( const DataType& data, const ConditionType& condition, const Args&... arguments )
		{
			const bool fulfills = condition( data );

			if constexpr ( sizeof...( arguments )>0 )
			{
				return fulfills || ConditionChecker<DataType>::AnyFulfills( data , std::forward<const Args&>( arguments )... );
			}
			else
			{
				return fulfills;
			}
		}

		public: template<typename ConditionType, typename... Args>
		constexpr static inline bool AllFulfills( const DataType& data, const ConditionType& condition, const Args&... arguments )
		{
			const bool fulfills = condition( data );

			if constexpr ( sizeof...( arguments )>0 )
			{
				return fulfills && ConditionChecker<DataType>::AllFulfills( data , std::forward<const Args&>( arguments )... );
			}
			else
			{
				return fulfills;
			}
		}
	};
}