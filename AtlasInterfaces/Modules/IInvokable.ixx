module;

#include "../../Macros/Macros.h"

export module AtlasInterfaces:IInvokable;

export namespace Atlas::Interface
{
	template<typename ReturnType , typename... Args>
	class DLLApi IInvokable
	{
		public:
		virtual ReturnType Invoke( Args&&... arguments ) = 0;
	};
}