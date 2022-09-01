module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:AlreadyExistsException;
import :Exception;

export namespace Atlas
{
	template<typename SenderType = void , typename... Args>
	class DLLApi AlreadyExistsException :
		public Exception<SenderType , Args...>
	{
		public:
		AlreadyExistsException( const char* message , const SenderType* source = nullptr , const Args&&... arguments )  :
			Exception<SenderType , Args...>( message , source , std::forward<Args>( arguments )... )
		{}
	};
}