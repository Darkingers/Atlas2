module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:ArgumentException;
import :Exception;

export namespace Atlas
{
	template<typename SenderType = void , typename... Args>
	class DLLApi ArgumentException :
		public Exception<SenderType , Args...>
	{
		public:
		ArgumentException( const char* message , const SenderType* source = nullptr , const Args&&... arguments )  :
			Exception<SenderType , Args...>( message , source , std::forward<Args>( arguments )... )
		{}
	};
}