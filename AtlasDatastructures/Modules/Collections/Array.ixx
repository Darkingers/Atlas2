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
		requires Concept::IsDerivedFrom<AllocatorTemplate<DataType>, Interface::IAllocator<DataType>>
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

		private: constexpr static inline bool DoEventHandling = EventHandlerType::value;
		

		private: AllocatorType _allocator;


		public: template<typename... Args>
		constexpr ArrayBase( Args&&... arguments ) noexcept
		{
			if constexpr (sizeof...(arguments) > 0 )
			{
				ArrayType::Add( std::forward<Args&&>( arguments )... );
			}
		}

		public:
		constexpr ~ArrayBase() noexcept
		{
			
		}

		public:
		constexpr inline const unsigned int GetHash() const
		{
			return Memory::GetHash( ArrayType::GetLocation(0), ArrayType::GetSize( ) ) ^ Memory::GetHash(*this, sizeof(ArrayType) );
		}

		public: 
		constexpr inline const unsigned int GetSize() const
		{
			return _allocator.GetSize( );
		}
		
		public: 
		constexpr inline const DataType& GetConst( const unsigned int index ) const
		{
			return ( *this )[index];
		}
		
		public:
		constexpr inline DataType& Get( const unsigned int index )
		{
			return ( *this )[index];
		}

		public:
		constexpr ArrayType& Resize( const unsigned int newSize )
		{
			if ( newSize == ArrayType::GetSize( ) )
			{
				return *this;
			}

			Validate::IsPositive( newSize );
			
			if constexpr ( DoEventHandling)
			{
				const int removed = ArrayType::GetSize( ) - newSize;
				
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
		constexpr ArrayType& Reserve( const unsigned int reservedSize )
		{
			ArrayType::Resize( ArrayType::GetSize( ) + reservedSize );

			return *this;
		}

		public:
		constexpr ArrayType& Trim( const unsigned int trimSize )
		{
			ArrayType::Resize( ArrayType::GetSize( ) - trimSize );

			return *this;
		}

		public: template<typename... Args>
		constexpr ArrayType& Add( Args&&... arguments )
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
		constexpr ArrayType& Remove( const Args&... arguments )
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
		constexpr ArrayType& Insert( const unsigned int index , Args&&... arguments )
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
		constexpr ArrayType& ReplaceFrom( const unsigned int index , Args&&... arguments )
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
		constexpr ArrayType& Clear( )
		{
			ArrayType::Trim( GetSize( ) );

			return  *this;
		}

		public:
		constexpr ArrayType& ShiftLeft( const unsigned int index , const unsigned int offset )
		{
			ArrayType::Shift( index , GetSize( ) - index , -offset );

			return  *this;
		}

		public:
		constexpr ArrayType& ShiftRight( const unsigned int index , const unsigned int offset )
		{
			ArrayType::Shift( index , GetSize( ) - index , offset );

			return   *this;
		}

		public:
		constexpr ArrayType& Shift( const unsigned int index , const unsigned int size , const unsigned int offset )
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
		constexpr DataType& operator[]( const unsigned int index )
		{
			ArrayType::ValidateIndex( index );

			return _allocator[index];
		}

		private:
		constexpr void ValidateIndex(const unsigned int index ) const
		{
			Validate::IsPositive( index );
			Validate::IsLess( index , GetSize( ) );
		}

		private:
		constexpr inline DataType* GetLocation( const unsigned int index ) const
		{
			return &( *this )[index];
		}
    };
}