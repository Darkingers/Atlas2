module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:TimeoutException;
import :Exception;

export namespace Atlas
{

	template<typename SenderType = void , typename... Args>
	class DLLApi TimeoutException :
		public Exception<SenderType , Args...>
	{
		public:
		TimeoutException( const char* message , const SenderType* source = nullptr , const Args&&... arguments )  :
			Exception<SenderType , Args...>( message , source , std::forward<Args>( arguments )... )
		{}
	};
}