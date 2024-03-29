module;

#include "../../../Macros/Macros.h"

export module AtlasCollections:LinkNode;
import AtlasDefinitions;

export namespace Atlas
{
	/*template<typename DataType>
	class DLLApi LinkNode
	{
		private: using LinkNodeType = LinkNode<DataType>;

		public: DataType Data;
		public: LinkNodeType* Next;
		public: LinkNodeType* Previous;


		public:
		LinkNode( const DataType& data )  :
			Data( data )
		{

		}

		public: template<typename... TArgs>
		LinkNode( TArgs&&... args ) 
		{
			if constexpr ( sizeof...( TArgs ) > 0 )
			{
				this->Add( std::forward<TArgs>(TArgs)... );
			}
		}

		public:
		LinkNode( DataType&& data )  :
			Data(  std::move(data) )
		{

		}

		public:
		~LinkNode() 
		{
		}

		public:
		LinkNode& First() const 
		{
			if ( Previous != nullptr )
			{
				return Previous->First();
			}
			else
			{
				return *this;
			}
		}

		public:
		LinkNode* First(Condition<DataType> condition) const 
		{
			LinkNode* first = condition(*Data) ? this : nullptr;
			LinkNode* current = Previous;
			
			while ( current != nullptr )
			{
				if ( condition( *current ) )
				{
					first = current;
				}

				current = current->Previous;
			}

			if ( first != nullptr )
			{
				return first;
			}
			else
			{
				current = Next;
				while ( current != nullptr )
				{
					if ( condition( *current ) )
					{
						return current;
					}

					current = current->Next;
				}

				return nullptr;
			}
		}

		public:
		LinkType* First( Condition<DataType> condition ) const 
		{
			return this->First( [&condition] ( const LinkType& link )
			{
				return condition( link.Data );
			} );
		}
		
		public: 
		LinkType& Last() const 
		{
			if ( Next != nullptr )
			{
				return Next->Last();			
			}
			else
			{
				return *this;
			}
		}

		public:
		LinkType* Last( Condition<LinkType> condition ) const 
		{
			LinkType* last = condition( *this ) ? this : nullptr;
			LinkType* current = Next;

			while ( current != nullptr )
			{
				if ( condition( *current ) )
				{
					last = current;
				}

				current = current->Next;
			}

			if ( last != nullptr )
			{
				return last;
			}
			else
			{
				current = Previous;
				while ( current != nullptr )
				{
					if ( condition( *current ) )
					{
						return current;
					}
					current = current->Previous;
				}

				return nullptr;
			}
		}

		public:
		LinkType* Last( Condition<DataType> condition ) const 
		{
			return this->Last( [&condition] ( const LinkType& link )
			{
				return condition( link.Data );
			} );
		}

		public:
		const bool Contains(const DataType& data) const 
		{
			return this->Any( [&data] ( const LinkType link )
			{
				return data == link.Data;
			} );
		}

		public:
		const bool Any( Condition<DataType> condition ) const 
		{
			return this->Any( [&condition] ( const LinkType& link )
			{
				return condition( link.Data );
			}
		}

		public:
		const bool Any( Condition<LinkType> condition ) const 
		{
			if ( condition(*this))
			{
				return true;
			}
			else
			{			
				return ( Next != nullptr && Next->Any( condition ) ) || ( Previous != nullptr && Previous->Any( condition ) );
			}		
		}
	
		public: 
		LinkType& DeleteFollowingLinks() 
		{
			if ( Next != nullptr )
			{
				Next->DeleteFollowingLinks();
				delete Next;
			}

			Next = nullptr;

			return *this;
		}
		
		public:
		LinkType& DeleteFollowingLinksIf( Condition<DataType> condition ) 
		{
			return this->DeleteFollowingLinksIf( [&condition] ( const LinkType& link )
			{
				return condition( link.Data );
			} );
		}

		public:
		LinkType& DeleteFollowingLinksIf( Condition<LinkType> condition) 
		{
			if ( Next == nullptr )
			{
				return *this;
			}

			LinkType* start = this;
			LinkType* current = this->Next;
			bool doExit = false;

			while ( true )
			{
				while ( condition( *current ) )
				{
					if ( current->Next == nullptr )
					{
						delete current;
						doExit = true;
						break;
					}
					else
					{
						current = current->Next;
						delete current->Previous;
					}
				}

				if ( doExit )
				{
					start->Next = nullptr;
					break;
				}
				else
				{
					start->Next = current;
					current->Previous = start;

					start = current;
					current = start->Next;
				}
			}

			return *this;
		}

		public: 
		LinkType& DeletePreviousLinks() 
		{
			if ( Previous != nullptr )
			{
				Previous->DeletePreviousLinks();
				delete Previous;
			}

			Previous = nullptr;

			return *this;
		}

		public:
		LinkType& DeletePreviousLinksIf( Condition<DataType> condition ) 
		{
			return this->DeletePreviousLinksIf( [&condition] ( const LinkType& link )
			{
				return condition( link.Data );
			} );
		}

		public:
		LinkType& DeletePreviousLinksIf( Condition<LinkType> condition ) 
		{
			if ( Previous == nullptr )
			{
				return *this;
			}

			LinkType* start = this;
			LinkType* current = this->Previous;
			bool doExit = false;

			while ( true )
			{
				while ( condition( *current) )
				{
					if ( current->Previous == nullptr )
					{
						delete current;
						doExit = true;
						break;
					}
					else
					{
						current = current->Previous;
						delete current->Next;
					}
				}

				if ( doExit )
				{
					start->Previous = nullptr;
					break;
				}
				else
				{
					start->Previous = current;
					current->Next = start;

					start = current;
					current = start->Previous;
				}
			}

			return *this;
		}

		public: template<typename... TArgs>
		LinkType& InsertBefore( LinkType& inserted, TArgs... args ) 
		{
			LinkType* previous = Previous;

			inserted.Next = this;
			inserted.Previous = previous;

			Previous = &inserted;

			if ( previous != nullptr )
			{
				previous->Next = &inserted;
			}

			if constexpr ( sizeof...( TArgs ) == 0 )
			{
				return inserted;
			}
			else
			{
				return inserted.InsertBefore( TArgs... );				
			}		
		}
		
		public: template<typename... TArgs>
		LinkType& InsertBefore( DataType& inserted, TArgs... args ) 
		{
			return this->InsertBefore( *new LinkType( inserted ), TArgs... );
		}
		
		public: template<typename TCollection, typename... TArgs> requires Concepts::AtlasIterableCollection<TCollection, DataType, Functor<DataType>, Condition<DataType>>
		LinkType& InsertBefore( TCollection& collection, TArgs... args )
		{
			LinkType* last = this;
			collection.ForEach( [&last] ( DataType& data ) mutable
			{		
				last = &last->InsertBefore( data );
			} );

			if constexpr ( sizeof...( TArgs ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->InsertBefore( TArgs... );				
			}
		}

		public: template<typename TCollection, typename... TArgs> requires Concepts::AtlasIterableCollection<TCollection, LinkType, Functor<LinkType>, Condition<LinkType>>
		LinkType& InsertBefore( TCollection& collection, TArgs... args )
		{
			LinkType* last = this;
			collection.ForEach( [&last] ( LinkType& link ) mutable
			{
				last = &last->InsertBefore( link );
			} );

			if constexpr ( sizeof...( TArgs ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->InsertBefore( TArgs... );			
			}
		}

		public: template<typename TCollection, typename... TArgs> requires Concepts::StandardIterableCollection<TCollection, DataType>
		LinkType& InsertBefore( TCollection& collection, TArgs... args )
		{
			LinkType* last = this;
			for ( auto data : collection )
			{
				last = &last->InsertBefore( *data );
			}

			if constexpr ( sizeof...( TArgs ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->InsertBefore( TArgs... );
			}
		}

		public: template<typename TCollection, typename... TArgs> requires Concepts::StandardIterableCollection<TCollection, LinkType>
		LinkType& InsertBefore( TCollection& collection, TArgs... args )
		{
			LinkType* last = this;
			for ( auto link : collection )
			{
				last = &last->InsertBefore( *link );
			}

			if constexpr ( sizeof...( TArgs ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->InsertBefore( TArgs... );			
			}
		}

		public: template<typename... TArgs>
		LinkType& InsertAfter( LinkType& inserted, TArgs... args ) 
		{
			LinkType* next = Next;

			inserted.Next = next;
			inserted.Previous = this;

			Next = &inserted;

			if ( next != nullptr )
			{
				next->Previous = &inserted;
			}


			if constexpr ( sizeof...( TArgs ) == 0 )
			{
				return inserted;
			}
			else
			{
				return inserted.InsertAfter( TArgs... );			
			}
		}

		public: template<typename... TArgs>
		LinkType& InsertAfter( DataType& inserted, TArgs... args ) 
		{
			return this->InsertAfter( *new LinkType( inserted ), TArgs... );
		}

		public: template<typename TCollection, typename... TArgs> requires Concepts::AtlasIterableCollection<TCollection, DataType, Functor<DataType>, Condition<DataType>>
		LinkType& InsertAfter( TCollection& collection, TArgs... args )
		{
			LinkType* last = this;
			collection.ForEach( [&last] ( DataType& data ) mutable
			{
				last = &last->InsertAfter( data );
			} );

			if constexpr ( sizeof...( TArgs ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->InsertAfter( TArgs... );			
			}
		}

		public: template<typename TCollection, typename... TArgs> requires Concepts::AtlasIterableCollection<TCollection, LinkType, Functor<LinkType>, Condition<LinkType>>
		LinkType& InsertAfter( TCollection& collection, TArgs... args )
		{
			LinkType* last = this;
			collection.ForEach( [&last] ( LinkType& link ) mutable
			{
				last = &last->InsertAfter( link );
			} );

			if constexpr ( sizeof...( TArgs ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->InsertAfter( TArgs... );
			}
		}

		public: template<typename TCollection, typename... TArgs> requires Concepts::StandardIterableCollection<TCollection, DataType>
		LinkType& InsertAfter( TCollection& collection, TArgs... args )
		{
			LinkType* last = this;
			for ( auto data : collection )
			{
				last = &last->InsertAfter( *data );
			}

			if constexpr ( sizeof...( TArgs ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->InsertAfter( TArgs... );				
			}
		}

		public: template<typename TCollection, typename... TArgs> requires Concepts::StandardIterableCollection<TCollection, LinkType>
		LinkType& InsertAfter( TCollection& collection, TArgs... args )
		{
			LinkType* last = this;
			for ( auto link : collection )
			{
				last = &last->InsertAfter( *link );
			}

			if constexpr ( sizeof...( TArgs ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->InsertAfter( TArgs... );			
			}
		}

		public: template<typename... TArgs>
		LinkType& Add( TArgs... args )
		{
			return this->Add( TArgs... );
		}

		public: template<typename... TArgs>
		LinkType& Add( DataType& data, TArgs... args )
		{
			return this->Add( *new LinkType( data), TArgs... ) );
		}

		public: template<typename... TArgs>
		LinkType& Add( LinkType& link, TArgs... args )
		{
			Next = link;
			link->Previous = *this;

			if constexpr ( sizeof...( TArgs ) == 0 )
			{
				return link;
			}
			else
			{
				return link->Add( TArgs... );
			}
		}

		public: template<typename TCollection, typename... TArgs> requires Concepts::AtlasIterableCollection<TCollection, DataType, Functor<DataType>, Condition<DataType>>
		LinkType& Add( TCollection& collection, TArgs... args )
		{
			LinkType* last = this;
			collection.ForEach( [&last] ( DataType& data ) mutable
			{
				last = &last->Add( data );
			} );

			if constexpr ( sizeof...( TArgs ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->Add( TArgs... );
			}
		}

		public: template<typename TCollection, typename... TArgs> requires Concepts::AtlasIterableCollection<TCollection, LinkType, Functor<LinkType>, Condition<LinkType>>
		LinkType& Add( TCollection& collection, TArgs... args )
		{
			LinkType* last = this;
			collection.ForEach( [&last] ( LinkType& link ) mutable
			{
				last = &last->Add( link );
			} );

			if constexpr ( sizeof...( TArgs ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->Add( TArgs... );
			}
		}

		public: template<typename TCollection, typename... TArgs> requires Concepts::StandardIterableCollection<TCollection, DataType>
		LinkType& Add( TCollection& collection, TArgs... args )
		{
			LinkType* last = this;
			for ( DataType* data : collection )
			{			
				last = &last->Add( data );
			}

			if constexpr ( sizeof...( TArgs ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->Add( TArgs... );
			}
		}

		public: template<typename TCollection, typename... TArgs> requires Concepts::StandardIterableCollection<TCollection, LinkType>
		LinkType& Add( TCollection& collection, TArgs... args )
		{
			LinkType* last = this;
			for ( LinkType* link : collection )
			{
				last = &last->Add( data );
			}

			if constexpr ( sizeof...( TArgs ) == 0 )
			{
				return *last;
			}
			else
			{
				return last->Add( TArgs... );
			}
		}*/
	//};
}