module;

#include "../../../Macros/Macros.h"
#include <type_traits>

export module AtlasCollections:Array;
import AtlasInterfaces;
import AtlasConcepts;
import AtlasExceptions;
import AtlasIterators;
import AtlasTraits;
import AtlasValidation;
import AtlasConfiguration;
import AtlasMemoryFunctions;
import AtlasDataFunctions;
import AtlasVariadic;


export namespace Atlas
{
	template<typename DataType , template<typename> typename Allocator , template<typename> typename EventHandler>
	requires IsDerivedFrom<Allocator<DataType>, IAllocator<DataType>>
	class DLLApi ArrayBase :
		public Searchable<ArrayBase<DataType,Allocator,EventHandler>>,
		public Sortable<ArrayBase<DataType , Allocator , EventHandler>>,
		public Analysable<ArrayBase<DataType , Allocator , EventHandler>>,
		public Enumerable<ArrayBase<DataType , Allocator , EventHandler>>,		
		public EventHandler<DataType>,
		public IHashable 
	{		
		private: using ArrayType = ArrayBase<DataType, Allocator, EventHandler>;
		private: using AllocatorType = Allocator<DataType>;
		private: using IteratorType = ContinousMemoryIterator<DataType>;
		private: using EventHandlerType = EventHandler<DataType>;

		private: inline static constexpr bool DoEventHandling = EventHandlerType::value;
		

		private: AllocatorType _allocator;


		public: template<typename... Args>
		ArrayBase( Args... arguments ) 
		{
			if constexpr (sizeof...(arguments) > 0 )
			{
				ArrayType::Add( arguments... );
			}
		}

		public:
		~ArrayBase() 
		{
			
		}

		public:
		inline const unsigned int GetHash() const 
		{
			return Memory::GetHash( _allocator.GetLocation(), GetSize( ) ) ^ Memory::GetHash(*this, sizeof(ArrayType) );
		}

		public: 
		inline const unsigned int GetSize() const 
		{
			return _allocator.GetSize( );
		}
		
		public: 
		inline const DataType& GetConst( const unsigned int position ) const 
		{
			return _allocator[position];
		}
		
		public:
		inline DataType& Get( const unsigned int index ) 
		{
			return _allocator[index];
		}

		public:
		ArrayType& Resize( const unsigned int newSize ) 
		{
			if constexpr ( Configuration::EnableArgumentCheck )
			{
				Ensure::IsPositive( newSize );
			}

			if ( newSize == GetSize( ) )
			{
				return *this;
			}

			if constexpr ( DoEventHandling )
			{
				if ( newSize < GetSize( ) && GetSize( )>0 )
				{
					EventHandler::ItemsRemoved
					(
						Iterator( GetLocation( newSize ) ) ,
						Iterator( GetLocation( GetSize( ) ) )
					);
				}
			}

			_allocator.Allocate( newSize );

			if constexpr ( DoEventHandling )
			{
				EventHandler::Invoke( );
			}

			*this;
		}

		public:
		ArrayType& Reserve( const unsigned int reservedSize ) 
		{
			Resize( GetSize( ) + reservedSize );

			return *this;
		}

		public:
		ArrayType& Trim( const unsigned int trimSize ) 
		{
			Resize( GetSize( ) - trimSize );

			return *this;
		}

		public: template<typename... Args>
		ArrayType& Add( Args&&... arguments ) 
		{
			const unsigned int index = GetSize( );

			Reserve( VariadicCounter::Count( std::forward<Args>( arguments )... ) );

			DataFunctions::ReplaceFrom( *this, index , std::forward<Args>( arguments )... );

			if constexpr ( DoEventHandling )
			{
				EventHandler::ItemsAdded
				(
					Iterator( GetLocation( index ) ) ,
					Iterator( GetLocation( GetSize( ) ) )
				);

				EventHandler::Invoke( );
			}

			return *this;
		}

		public: template<typename... Args>
		ArrayType& Remove( const Args&&... arguments ) 
		{
			unsigned int removed = 0;

			for ( unsigned int i = 0; i < GetSize( ); ++i )
			{
				if ( VariadicConditionChecker<const DataType&>::Any( _allocator[i] , std::forward<Args>( arguments )... ) )
				{
					++removed;
				}
				else
				{
					if constexpr ( DoEventHandling )
					{
						DataType temp = _allocator[i];
						_allocator[i] = _allocator[i - removed];
						_allocator[i - removed] = temp;
					}
					else
					{
						_allocator[i - removed] = _allocator[i];
					}
				}
			}

			Trim( removed );

			return *this;
		}

		public: template<typename... Args>
		ArrayType& Insert( const unsigned int index , Args&&... arguments ) 
		{
			ValidateIndex( index );

			const unsigned int inserted = VariadicCounter::Count( std::forward<Args>( arguments )... );
			ShiftRight( index , inserted );

			DataFunctions::ReplaceFrom( *this , index , std::forward<Args>( arguments )... );

			if constexpr ( DoEventHandling )
			{
				EventHandler::ItemsAdded
				(
						Iterator( GetLocation( index ) ) ,
						Iterator( GetLocation( index + inserted ) )
				);

				EventHandler::Invoke( );
			}

			return *this;
		}

		public: template<typename... Args>
		ArrayType& ReplaceFrom( const unsigned int index , Args&&... arguments ) 
		{
			ValidateIndex( index );

			const unsigned int replaced = VariadicCounter::Count( std::forward<Args>( arguments )... );

			if constexpr ( DoEventHandling )
			{
				EventHandler::ItemsRemoved
				(
						Iterator( GetLocation( index ) ) ,
						Iterator( GetLocation( index + replaced ) )
				);
			}

			DataFunctions::ReplaceFrom( *this , index , std::forward<Args>( arguments )... );

			if constexpr ( DoEventHandling )
			{
				EventHandler::ItemsAdded
				(
						Iterator( GetLocation( index ) ) ,
						Iterator( GetLocation( index + replaced ) )
				);

				EventHandler::Invoke( );
			}

			return *this;
		}

		public:
		ArrayType& Clear( ) 
		{
			Trim( GetSize( ) );

			return  *this;
		}

		public:
		ArrayType& ShiftLeft( const unsigned int index , const unsigned int offset ) 
		{
			Shift( index , GetSize( ) - index , -offset );

			return  *this;
		}

		public:
		ArrayType& ShiftRight( const unsigned int index , const unsigned int offset ) 
		{
			Shift( index , GetSize( ) - index , offset );

			return   *this;
		}

		public:
		ArrayType& Shift( const unsigned int index , const unsigned int size , const unsigned int offset ) 
		{
			if constexpr ( DoEventHandling )
			{
				if ( offset < 0 )
				{
					const unsigned int start = index + offset;
					EventHandler::ItemsRemoved
					(
							Iterator( GetLocation( start ) ) ,
							Iterator( GetLocation( start + size ) )
					);
				}
			}

			DataFunctions::Shift( *this , index , size , offset );

			if constexpr ( DoEventHandling )
			{
				EventHandler::Invoke( );
			}

			return  *this;
		}
	
		public:
		DataType& operator[]( const unsigned int index )
		{
			ValidateIndex( index );

			return _allocator[index];
		}

		private:
		void ValidateIndex(const unsigned int index ) const
		{
			if constexpr ( Configuration::EnableArgumentCheck )
			{
				Ensure::IsPositive( index );
				Ensure::IsLess( index , GetSize( ) );
			}
		}
    };
}