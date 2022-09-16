module;

#include "../../../Macros/Macros.h"
#include <mutex>

export module AtlasTask;
import AtlasDefinitions;
import AtlasExceptions;
import AtlasFunctionalTraits;
import AtlasTypeInfo;
import AtlasMethods;
import AtlasAsync;

export namespace Atlas
{
	namespace Implementation
	{
		template<typename ReturnType, typename TaskType>
		class TaskBase
		{
			protected: using InvokedType = Definition::LambdaFunction<ReturnType>;

			protected: std::mutex _mutex;
			protected: InvokedType _invoked;
			protected: Exception _error;
			protected: bool _isFailed;
			protected: bool _isCompleted;
			protected: bool _isSuccess;
			protected: bool _isRunning;

			public:
			TaskBase( InvokedType invoked ) noexcept :
				_invoked( invoked ) ,
				_isFailed( false ) ,
				_isCompleted( false ) ,
				_isSuccess( false ) ,
				_isRunning( false )
			{}

			public:
			bool IsFailed( unsigned int timeout_ms = -1 , unsigned int sleep_ms = 100 ) const
			{
				Wait( timeout_ms , sleep_ms );
				return _isFailed;
			}

			public:
			bool IsSuccess( unsigned int timeout_ms = -1 , unsigned int sleep_ms = 100 ) const
			{
				Wait( timeout_ms , sleep_ms );
				return _isSuccess;
			}

			public:
			bool IsCompleted( ) const noexcept
			{
				return _isCompleted;
			}

			public:
			bool IsRunning( ) const noexcept
			{
				return _isRunning;
			}

			public:
			Exception Error( unsigned int timeout_ms = -1 , unsigned int sleep_ms = 100 ) const
			{
				Wait( timeout_ms , sleep_ms );
				return _error;
			}

			public:
			TaskType& Invoke( )
			{
				if ( _isRunning || _isCompleted || _isFailed )
				{
					return static_cast<TaskType&>( *this );
				}

				const std::lock_guard<std::mutex> lock( _mutex );

				if ( _isRunning || _isCompleted || _isFailed )
				{
					return static_cast<TaskType&>(*this);
				}

				_isRunning = true;

				try
				{
					static_cast<TaskType*>(this)->InternalInvoke( );

					_isSuccess = true;
				}
				catch ( Exception e )
				{
					_error = e;
					_isFailed = true;
				}

				_isRunning = false;
				_isCompleted = true;

				return static_cast<TaskType&>( *this );
			}

			public:
			void AsyncInvoke( )
			{
				if ( _isRunning || _isCompleted )
				{
					return;
				}

				const std::lock_guard<std::mutex> lock( _mutex );

				if ( _isRunning || _isCompleted )
				{
					return;
				}

				_isRunning = true;

				Async::Invoke( Method::Create( this , &TaskBase<ReturnType,TaskType>::Invoke ) );
			}

			public:
			void Wait( unsigned int timeout_ms = -1 , unsigned int sleep_ms = 100 ) const
			{
				Async::WaitUntil( [ this ]( )
				{
					return _isCompleted;
				} , timeout_ms , sleep_ms );
			}

			protected:
			virtual void InternalInvoke( ) = 0;
		};
	}

	template<typename ReturnType>
	class DLLApi Task :
		public Implementation::TaskBase<ReturnType, Task<ReturnType>>,
		public Trait::Invokable<Task<ReturnType>& , Task<ReturnType>>
	{
		private: using TaskType = Task<ReturnType>;
		private: using BaseType = Implementation::TaskBase<ReturnType , Task<ReturnType>>;
		private: using StoredResultType = std::conditional<Type<ReturnType>::IsReference , ReturnType* , ReturnType>;
		private: using AccessedResultType = std::conditional<Type<ReturnType>::IsReference , ReturnType& , ReturnType>;

		private: StoredResultType _result;


		public:
		Task( BaseType::InvokedType invoked ) noexcept :
			BaseType( invoked )
		{}

		public:
		AccessedResultType Result( unsigned int timeout = -1 , unsigned int sleep_ms = 100 ) const
		{
			this->Wait( timeout ,sleep_ms );
			if constexpr ( Type<ReturnType>::IsReference )
			{
				return ( *_result );		
			}
			else
			{
				return _result;
			}		
		}

		public:
		void InternalInvoke( )
		{
			if constexpr ( Type<ReturnType>::IsReference )
			{
				_result = &(this->_invoked)( );
			}
			else
			{
				_result = ( this->_invoked )( );
			}
		}
	};

	template<>
	class DLLApi Task<void> :
		public Implementation::TaskBase<void , Task<void>> ,
		public Trait::Invokable<Task<void>& , Task<void>>
	{
		private: using BaseType = Implementation::TaskBase<void , Task<void>>;


		public:
		Task( BaseType::InvokedType invoked ) noexcept :
			BaseType( invoked )
		{}

		public:
		void InternalInvoke( )
		{
			( this->_invoked )( );
		}
	};
}