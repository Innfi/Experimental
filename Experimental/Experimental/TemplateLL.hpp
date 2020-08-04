#ifndef __TEMPLATELL_HPP__
#define __TEMPLATELL_HPP__

namespace Experimental
{
    template<typename Type> 
    class Node {
    public:
        Type Value;
        Node<Type>* Link;
	};

    template<typename Type>
    class List {
    public:
        List() {
            this->header = NULL;
        }
        virtual ~List() {}
        void AddFirst(Type item) {
            Node<Type>* newNode = new Node<Type>;
            if(this->header == NULL) {
                this->header = newNode;
                newNode->Value = item;
            }
        }
        void Add(int position, Type item);
        Type Delete(int position);
        void Replace(int position, Type item);
        void Find(Type item);
        void GetEntry(int position);
        void GetLength();
        bool IsEmpty();
        void Print();
    private:
        Node<Type>* header;
    };
}

#endif // TemplateLL.hpp