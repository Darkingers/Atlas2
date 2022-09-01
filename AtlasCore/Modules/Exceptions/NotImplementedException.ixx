module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:NotImplementedException;
import :Exception;

export namespace Atlas
{

	template<typename SenderType = void , typename... Args>
	class DLLApi NotImplementedException :
		public Exception<SenderType , Args...>
	{
		public:
		NotImplementedException( const char* message , const SenderType* source = nullptr , const Args&&... arguments )  :
			Exception<SenderType , Args...>( message , source , std::forward<Args>( arguments )... )
		{}
	};
}