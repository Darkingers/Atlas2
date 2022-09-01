module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:AccessException;
import :Exception;

export namespace Atlas
{
	template<typename SenderType = void , typename... Args>
	class DLLApi AccessException :
		public Exception<SenderType , Args...>
	{
		public:
		AccessException( const char* message , const SenderType* source = nullptr , const Args&&... arguments )  :
			Exception<SenderType , Args...>( message , source , std::forward<Args>( arguments )... )
		{}
	};
}