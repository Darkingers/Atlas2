module;

#include "../../Macros/Macros.h"

export module AtlasDefaultFunctions;

export namespace Atlas
{
	namespace Implementation
	{
		template<typename DataType>
		class Default
		{
			public:
			constexpr static inline auto Comparator( const DataType& instanceA, const DataType& instanceB )
			{
				return instanceA - instanceB;
			}
		};
	}	

	class DLLApi Default
	{
		public: template<typename DataType>
		constexpr static inline auto Comparator( const DataType& instanceA, const DataType& instanceB )
		{
			return Implementation::Default<DataType>::Comparator( instanceA, instanceB );
		}	
	};
}