module;

#include "../../Macros/Macros.h"

export module AtlasInterfaces:IInvokable;

export namespace Atlas
{
	template<typename ReturnType , typename... Args>
	class DLLApi IInvokable
	{
		public:
		virtual ReturnType Invoke( Args&&... arguments ) = 0;
	};
}