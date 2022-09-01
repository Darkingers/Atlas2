module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:NullException;
import :Exception;

export namespace Atlas
{
	template<typename SenderType = void , typename... Args>
	class DLLApi NullException :
		public Exception<SenderType , Args...>
	{
		public:
		NullException( const char* message , const SenderType* source = nullptr , const Args&&... arguments )  :
			Exception<SenderType , Args...>( message , source , std::forward<Args>( arguments )... )
		{}
	};
}