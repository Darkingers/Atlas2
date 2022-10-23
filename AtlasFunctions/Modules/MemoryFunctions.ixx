module;

#include "../../Macros/Macros.h"

export module AtlasMemoryFunctions;
import AtlasValidation;
import AtlasConfiguration;

export namespace Atlas
{
	namespace Implementation
	{
		template<typename DataType>
		class Memory
		{
			public:
			constexpr static inline unsigned int GetHash( const DataType* memoryLocation , const unsigned int memorySize ) 
			{
				const unsigned int shift = (unsigned int) log2( 1 + sizeof( DataType ) * memorySize );
				return (unsigned int) ( memoryLocation ) >> shift;
			}
		};
	}

	class DLLApi Memory
	{
		public: template<typename DataType>
		constexpr static inline auto GetHash( const DataType* memoryLocation , const unsigned int memorySize )
		{
			Validate::IsNotNull( memoryLocation );
			Validate::IsPositive( memorySize );

			return Implementation::Memory<DataType>::GetHash( memoryLocation , memorySize );
		}
	};
}