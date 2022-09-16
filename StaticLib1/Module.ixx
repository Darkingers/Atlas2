module;

#include <thread>
#include <chrono>

export module AsyncExtensions;

export namespace Atlas
{
	class Async
	{
		public: template<typename InvokableType>
			inline static void Invoke( InvokableType type )
		{
			std::thread t( type );
			t.detach( );
		}

		public: template<typename InvokableType>
			static void WaitUntil( InvokableType condition , unsigned int timeout_ms = -1 , unsigned int sleep_ms = 100 )
		{
			auto sleepDuration = std::chrono::milliseconds( sleep_ms );
			if ( timeout_ms == -1 )
			{
				while ( !condition( ) )
				{
					std::this_thread::sleep_for( sleepDuration );
				}
			}
			else
			{
				unsigned int current = 0;

				while ( current < timeout_ms )
				{
					if ( condition( ) )
					{
						return;
					}

					std::this_thread::sleep_for( sleepDuration );
					current += sleep_ms;
				}
			}
		}
	};
}