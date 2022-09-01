module;

#include "../../Macros/Macros.h"

export module AtlasInterfaces:ICloneable;

export namespace Atlas
{
	template<typename DataType>
	class DLLApi ICloneable 
	{
		public:
		virtual DataType Clone( ) const  = 0;
	};
}