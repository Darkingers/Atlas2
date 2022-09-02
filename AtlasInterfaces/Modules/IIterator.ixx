module;

#include "../../Macros/Macros.h"

export module AtlasInterfaces:IAllocator;

export namespace Atlas
{
	template<typename DataType>
    class DLLApi IIterator
    {
        public:
        virtual ~IIterator( ) = 0;

        public:
        virtual DataType& operator*( ) = 0;

        public:
        virtual DataType* operator->( ) = 0;

        public:
        virtual IIterator<DataType>& operator++( ) = 0;

        public:
        virtual IIterator<DataType> operator++( int) = 0;

        public:
        virtual IIterator<DataType>& operator--( ) = 0;

        public:
        virtual IIterator<DataType> operator--( int ) = 0;
    };
}