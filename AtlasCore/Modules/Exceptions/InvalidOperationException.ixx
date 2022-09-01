module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:InvalidOperationException;
import :Exception;

export namespace Atlas
{
	template<typename SenderType = void , typename... Args>
	class DLLApi InvalidOperationException :
		public Exception<SenderType , Args...>
	{
		public:
		InvalidOperationException( const char* message , const SenderType* source = nullptr , const Args&&... arguments )  :
			Exception<SenderType , Args...>( message , source , std::forward<Args>( arguments )... )
		{}
	};
}