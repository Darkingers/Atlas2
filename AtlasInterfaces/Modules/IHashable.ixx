module;

#include "../../Macros/Macros.h"

export module AtlasInterfaces:IHashable;

export namespace Atlas
{
	class DLLApi IHashable
	{
		virtual unsigned int GetHash( ) const  = 0;
	};
}