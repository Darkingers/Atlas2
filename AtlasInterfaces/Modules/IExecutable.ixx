module;

#include "../../Macros/Macros.h"

export module AtlasInterfaces:IExecutable;

export namespace Atlas
{
	template<typename ReturnType>
	class DLLApi IExecutable
	{
		public:
		virtual ReturnType Execute( ) = 0;
	};
}