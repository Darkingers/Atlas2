module;

#include "../../Macros/Macros.h"

export module AtlasInterfaces:IHashable;

export namespace Atlas::Interface
{
	class DLLApi IHashable
	{
		public:
		virtual unsigned int GetHash( ) const  = 0;
	};
}