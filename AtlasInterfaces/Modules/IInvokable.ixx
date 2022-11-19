module;

#include "../../Macros/Macros.h"

export module AtlasInterfaces:IInvokable;

export namespace Atlas::Interface
{
	template<typename ReturnType , typename... Arguments>
	class DLLApi IInvokable
	{
		public:
		virtual ReturnType Invoke( Arguments&&... arguments ) = 0;
	};
}