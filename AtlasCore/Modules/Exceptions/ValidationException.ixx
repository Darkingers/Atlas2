module;

#include "../../../Macros/Macros.h"

export module AtlasExceptions:ValidationException;
import :Exception;

export namespace Atlas
{
	template<typename SenderType = void , typename... Args>
	class DLLApi ValidationException :
		public Exception<SenderType , Args...>
	{
		public:
		ValidationException( const char* message , SenderType* source = nullptr, const Args&&... arguments )  :
			Exception<SenderType , Args...>( message , source , std::forward<Args>(arguments)... )
		{}
	};
}