module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:NotFoundException;
import :Exception;

export namespace Atlas
{
	template<typename SenderType = void , typename... Args>
	class DLLApi NotFoundException :
		public Exception<SenderType , Args...>
	{
		public:
		NotFoundException( const char* message , const SenderType* source = nullptr , const Args&&... arguments )  :
			Exception<SenderType , Args...>( message , source , std::forward<Args>( arguments )... )
		{}
	};
}