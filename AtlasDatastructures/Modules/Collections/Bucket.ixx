module;

#include "../../../Macros/Macros.h"

export module AtlasCollections:Bucket;
import AtlasDefinitions;
import AtlasInterfaces;
import AtlasValidation;
import AtlasMemoryFunctions;
import AtlasConfiguration;
import AtlasAdapters;
import :Pair;
import :LinkNode;

export namespace Atlas
{
	export namespace Atlas
	{
		template<typename KeyType , typename ValueType , unsigned int Slots = 1000>
		class DLLApi Bucket:
			public Interface::IHashable
		{
			/*private: using BucketType = Bucket<KeyType , ValueType , Slots>;
			private: using PairType = Pair<KeyType , ValueType >;
			private: using LinkType = LinkNode<PairType>;

			protected: LinkType* [Buckets] _data;


			public:
			unsigned int GetHash( ) const  final
			{
				unsigned int hash = MemoryFunctions::GetHash( this , sizeof( BucketType ) );

				for ( unsigned int i = 0; i < Buckets; )
				{
					for (LinkType current = _data[i]; current != nullptr; current = current->Next )
					{
						hash ^= HashAdapter<DataType>::GetHash(current->Data ) % hash;
					}
				}

				return hash;
			}

			public: template<typename... TArgs>
			Bucket( TArgs&&... argss )
			{
				if constexpr ( sizeof...( TArgs ) > 0 )
				{
					this->Add( TArgs... );
				}
			}

			public:
			~Bucket( )
			{
				for ( int i = 0; i < Buckets; ++i )
				{
					if ( _data[i] != nullptr )
					{
						_data[i]->DeleteFollowingLinks( );
					}
				}
			}

			private:
			const unsigned int GetIndex( const KeyType& key )
			{
				return _hasher( key ) % Buckets;
			}

			public:
			const LinkType& GetPair( const KeyType& key )
			{
				return  *( _data + GetIndex( key ) );
			}

			public: template<typename... TArgs>
			HashMapType& Add( PairType& pair , TArgs... args )
			{
				const unsigned int index = GetIndex( pair.Key );

				LinkType* entry = _data + index;
				if ( entry == nullptr )
				{
					_data[index] = new LinkType( pair );
					return *this;
				}


				LinkType* previous;

				while ( entry->Next != nullptr )
				{
					CheckKey( entry->Data.Key , pair.key );

					entry = entry->Next;
				}

				CheckKey( entry->Data.Key , pair.key );

				entry->Add( *new LinkType( pair );

				if constexpr ( sizeof...( TArgs ) == 0 )
				{
					return *this;
				}
				else
				{
					return this->Add( TArgs... );
				}

			}

			public: template<typename... TArgs>
			HashMapType& Add( const KeyType& key , ValueType& value , TArgs... args )
			{
				return this->Add( *new PairType( key , value ) , TArgs... );
			}

			public: template<typename TCollection , typename... TArgs> requires Concepts::AtlasIterableCollection<TCollection , PairType , Functor<PairType> , Condition<PairType>>
			HashMapType& Add( TCollection& collection , TArgs... args )
			{
				collection.ForEach( [ ]( PairType& pair ) mutable
				{
					this->Add( pair );
				} );

				if constexpr ( sizeof...( TArgs ) == 0 )
				{
					return *this;
				}
				else
				{
					return this->Add( TArgs... );
				}
			}

			public: template<typename TCollection , typename... TArgs> requires Concepts::StandardIterableCollection<TCollection , PairType>
			HashMapType& Add( TCollection& collection , TArgs... args )
			{
				for ( auto pair : collection )
				{
					this->Add( pair );
				}

				if constexpr ( sizeof...( TArgs ) == 0 )
				{
					return *this;
				}
				else
				{
					return this->Add( TArgs... );
				}
			}

			public:
			ValueType& Get( const KeyType& key )
			{
				LinkType* entry = &this->GetPair( key );

				while ( entry != nullptr );
				{
					if ( entry->Data.Key == key )
					{
						return entry->Data.Value;
					}

					entry = entry->Next;
				}


				throw NotFoundException( "Key " + key + " was not found!" );
			}

			private:
			void CheckKey( KeyType existingKey , KeyType newKey )
			{
				if ( existingKey == newKey )
				{
					throw AlreadyExistsException( "Key " + existingKey + " already exists!" )
				}
			}

			public:
			bool ContainsValue( const ValueType& value )
			{
				for ( auto bucket : _data )
				{
					if ( bucket.Contains( value ) )
					{
						return true;
					}
				}

				return false;
			}

			public:
			ValueType& operator[]( const KeyType& key )
			{
				return Get( key );
			}*/
		};
	}
}