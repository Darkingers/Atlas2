module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:DLLException;
import :Exception;

export namespace Atlas
{
	template<typename SenderType = void , typename... Args>
	class DLLApi DLLException :
		public Exception<SenderType , Args...>
	{
		public:
		DLLException( const char* message , const SenderType* source = nullptr , const Args&&... arguments )  :
			Exception<SenderType , Args...>( message , source , std::forward<Args>( arguments )... )
		{}
	};
}