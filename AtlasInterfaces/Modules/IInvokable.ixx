module;

#include "../../Macros/Macros.h"

export module AtlasInterfaces:IInvokable;

export namespace Atlas::Interface
{
	template<typename ReturnType , typename... TArgs>
	class DLLApi IInvokable
	{
		public:
		virtual ReturnType Invoke( TArgs&&... args ) = 0;
	};
}