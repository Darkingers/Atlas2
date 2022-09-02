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
			inline static int Comparator( const DataType& instanceA, const DataType& instanceB ) 
			{
				return instanceA - instanceB;
			}
		};
	}	

	class DLLApi Default
	{
		public: template<typename DataType>
		inline static int Comparator( const DataType& instanceA, const DataType& instanceB ) 
		{
			return Implementation::Default<DataType>::Comparator( instanceA, instanceB );
		}	
	};
}