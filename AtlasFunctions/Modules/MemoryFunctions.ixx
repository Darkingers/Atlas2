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
			inline static unsigned int GetHash( const DataType* memoryLocation , const unsigned int memorySize ) 
			{
				const unsigned int shift = (unsigned int) log2( 1 + sizeof( DataType ) * memorySize );
				return (unsigned int) ( memoryLocation ) >> shift;
			}
		};
	}

	class DLLApi Memory
	{
		public: template<typename DataType>
		inline static unsigned int GetHash( const DataType* memoryLocation , const unsigned int memorySize )
		{
			if constexpr ( Configuration::EnableArgumentCheck )
			{
				Ensure::IsNotNull( memoryLocation );
				Ensure::IsPositive( memorySize );
			}

			return Implementation::Memory<DataType>::GetHash( memoryLocation , memorySize );
		}
	};
}