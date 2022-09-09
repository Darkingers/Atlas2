module;

#include "../../../Macros/Macros.h"
#include <type_traits>

export module AtlasCollections:Array;
import AtlasInterfaces;
import AtlasConcepts;
import AtlasExceptions;
import AtlasIterators;
import AtlasCollectionTraits;
import AtlasValidation;
import AtlasConfiguration;
import AtlasMemoryFunctions;
import AtlasDataFunctions;
import AtlasVariadics;
import :Package;


export namespace Atlas
{
	template<typename DataType , template<typename> typename AllocatorTemplate , template<typename> typename EventHandlerTemplate>
	requires IsDerivedFrom<AllocatorTemplate<DataType>, IAllocator<DataType>>
	class DLLApi ArrayBase :
		public Trait::Searchable<ArrayBase<DataType, AllocatorTemplate , EventHandlerTemplate>>,
		public Trait::Sortable<ArrayBase<DataType , AllocatorTemplate , EventHandlerTemplate>>,
		public Trait::Analysable<ArrayBase<DataType , AllocatorTemplate , EventHandlerTemplate>>,
		public Trait::Enumerable<ArrayBase<DataType , AllocatorTemplate , EventHandlerTemplate>>,
		public Interface::IHashable,
		public EventHandlerTemplate<DataType>

	{		
		private: using ArrayType = ArrayBase<DataType, EventHandlerTemplate , EventHandlerTemplate>;
		private: using AllocatorType = EventHandlerTemplate<DataType>;
		private: using IteratorType = ContinousMemoryIterator<DataType>;
		private: using EventHandlerType = EventHandlerTemplate<DataType>;

		private: inline static constexpr bool DoEventHandling = EventHandlerType::value;
		

		private: AllocatorType _allocator;


		public: template<typename... Args>
		ArrayBase( Args&&... arguments ) 
		{
			if constexpr (sizeof...(arguments) > 0 )
			{
				ArrayType::Add( std::forward<Args&&>( arguments )... );
			}
		}

		public:
		~ArrayBase() 
		{
			
		}

		public:
		inline const unsigned int GetHash() const 
		{
			return Memory::GetHash( ArrayType::GetLocation(0), ArrayType::GetSize( ) ) ^ Memory::GetHash(*this, sizeof(ArrayType) );
		}

		public: 
		inline const unsigned int GetSize() const 
		{
			return _allocator.GetSize( );
		}
		
		public: 
		inline const DataType& GetConst( const unsigned int index ) const
		{
			return ( *this )[index];
		}
		
		public:
		inline DataType& Get( const unsigned int index ) 
		{
			return ( *this )[index];
		}

		public:
		ArrayType& Resize( const unsigned int newSize ) 
		{
			if constexpr ( Configuration::EnableArgumentCheck )
			{
				Ensure::IsPositive( newSize );
			}

			if ( newSize == ArrayType::GetSize( ) )
			{
				return *this;
			}

			const int removed = ArrayType::GetSize( ) - newSize;
			
			if constexpr ( DoEventHandling)
			{
				if ( removed > 0 )
				{
					auto removedItems = CreatePackage( ArrayType::GetLocation( newSize ) , removed , true );

					_allocator.Allocate( newSize );

					EventHandlerType::InvokeRemoved( std::move(removedItems) );
				}
				else
				{
					_allocator.Allocate( newSize );
				}
			}
			else
			{
				_allocator.Allocate( newSize );
			}

			*this;
		}

		public:
		ArrayType& Reserve( const unsigned int reservedSize ) 
		{
			ArrayType::Resize( ArrayType::GetSize( ) + reservedSize );

			return *this;
		}

		public:
		ArrayType& Trim( const unsigned int trimSize ) 
		{
			ArrayType::Resize( ArrayType::GetSize( ) - trimSize );

			return *this;
		}

		public: template<typename... Args>
		ArrayType& Add( Args&&... arguments ) 
		{
			const unsigned int index = ArrayType::GetSize( );
			const unsigned int added = Variadic::Count( std::forward<const Args&>( arguments )... );

			ArrayType::Reserve( added );

			DataFunctions::ReplaceFrom( *this, index , std::forward<Args&&>( arguments )... );

			if constexpr ( DoEventHandling )
			{
				EventHandlerType::InvokeAdded( CreatePackage( ArrayType::GetLocation( index ) , added , true ) );
			}

			return *this;
		}

		public: template<typename... Args>
		ArrayType& Remove( const Args&... arguments ) 
		{
			unsigned int removed = 0;

			for ( unsigned int i = 0; i < ArrayType::GetSize( ); ++i )
			{
				if ( Variadic::AnyFulfills( _allocator[i] , std::forward<const Args&>( arguments )... ) )
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

			ArrayType::Trim( removed );

			return *this;
		}

		public: template<typename... Args>
		ArrayType& Insert( const unsigned int index , Args&&... arguments ) 
		{
			ArrayType::ValidateIndex( index );

			const unsigned int inserted = Variadic::Count( std::forward<Args&&>( arguments )... );
			
			ArrayType::ShiftRight( index , inserted );

			DataFunctions::ReplaceFrom( *this , index , std::forward<Args&&>( arguments )... );

			if constexpr ( DoEventHandling )
			{
				EventHandlerType::InvokeAdded( CreatePackage( ArrayType::GetLocation( index ) , inserted , true ) );
			}

			return *this;
		}

		public: template<typename... Args>
		ArrayType& ReplaceFrom( const unsigned int index , Args&&... arguments ) 
		{
			ArrayType::ValidateIndex( index );

			const unsigned int replaced = Variadic::Count( std::forward<const Args&>( arguments )... );

			if constexpr (DoEventHandling )
			{
				auto removed = CreatePackage( GetLocation( index ) , replaced , true );

				DataFunctions::ReplaceFrom( *this , index , std::forward<Args&&>( arguments )... );

				auto added = CreatePackage( GetLocation( index ) , replaced , true );

				EventHandlerType::Invoke( std::move( added ) , std::move( removed ) );
			}
			else
			{
				DataFunctions::ReplaceFrom( *this , index , std::forward<Args&&>( arguments )... );
			}

			return *this;
		}

		public:
		ArrayType& Clear( ) 
		{
			ArrayType::Trim( GetSize( ) );

			return  *this;
		}

		public:
		ArrayType& ShiftLeft( const unsigned int index , const unsigned int offset ) 
		{
			ArrayType::Shift( index , GetSize( ) - index , -offset );

			return  *this;
		}

		public:
		ArrayType& ShiftRight( const unsigned int index , const unsigned int offset ) 
		{
			ArrayType::Shift( index , GetSize( ) - index , offset );

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

					auto removed = CreatePackage( GetLocation( start ) , size, true );
					
					DataFunctions::Shift( *this , index , size , offset );

					EventHandlerType::InvokeRemoved( std::move( removed ) );
				}
				else
				{
					DataFunctions::Shift( *this , index , size , offset );
				}
			}
			else
			{
				DataFunctions::Shift( *this , index , size , offset );
			}

			return  *this;
		}
	
		public:
		DataType& operator[]( const unsigned int index )
		{
			ArrayType::ValidateIndex( index );

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

		private:
		inline DataType* GetLocation( const unsigned int index ) const
		{
			return &_allocator[index];
		}
    };
}