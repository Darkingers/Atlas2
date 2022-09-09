module;

#include "../../Macros/Macros.h"

export module AtlasInterfaces:IConverter;

export namespace Atlas::Interface
{
	template<typename DataType, typename ConvertedDataType>
	class DLLApi IConverter
	{
		public:
		virtual ConvertedDataType Convert( DataType& data ) const = 0;
	};
}