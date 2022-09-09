module;

#include "../../Macros/Macros.h"

export module AtlasInterfaces:IExecutable;

export namespace Atlas::Interface
{
	template<typename ReturnType>
	class DLLApi IExecutable
	{
		public:
		virtual ReturnType Execute( ) = 0;
	};
}