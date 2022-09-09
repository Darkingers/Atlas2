module;

#include "../../../Macros/Macros.h"

export module AtlasIterators:ContinousMemoryIterator;
import AtlasInterfaces;

export namespace Atlas
{
    template<typename DataType>
    class DLLApi ContinousMemoryIterator :
        public Interface::IIterator<DataType>
    {
        private: using IteratorType = ContinousMemoryIterator<DataType>;

        public: using iterator_category = std::random_access_iterator_tag;
        public: using difference_type = std::ptrdiff_t;
        public: using value_type = DataType;
        public: using pointer = DataType*;
        public: using reference = DataType&;

       
        private: DataType* _current;


        public:
        ContinousMemoryIterator( DataType* current )  :
            _current( current )
        {

        }

        public:
        ~ContinousMemoryIterator( ) final
        {

        }

        public: 
        DataType& operator*() final
        { 
            return *_current;
        }

        public: 
        DataType* operator->() final
        { 
            return _current;
        }

        public: 
        IteratorType& operator++()  final
        {
            _current++;
            return *this; 
        }

        public:
        IteratorType operator++( int ) final
        { 
            IteratorType tmp = *this;
            ++( *this );
            return tmp; 
        }

        public:
        IteratorType& operator--( )  final
        {
            _current--;
            return *this;
        }

        public:
        IteratorType operator--( int ) final
        {
            IteratorType tmp = *this;
            --( *this );
            return tmp;
        }

        friend bool operator== ( const IteratorType& a, const IteratorType& b ) 
        {
            return a._current == b._current;
        };

        friend bool operator!= ( const IteratorType& a, const IteratorType& b )
        { 
            return a._current != b._current;
        };
    };
}
