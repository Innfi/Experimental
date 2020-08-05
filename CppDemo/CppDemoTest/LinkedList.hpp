#ifndef __LINKED_LIST_HPP__
#define __LINKED_LIST_HPP__


namespace CppDemoLinkedList
{
	template<typename T> 
	class Node {
	public:
		T Element;
		Node() {}
		Node(T element): Element(element) {}

		Node<T>* Next() { return next_.get(); }
		Node<T>* Prev() { 
			auto test = prev_.lock();
			return test.get();
		}
		
		std::shared_ptr<Node<T>> next_;
		std::weak_ptr<Node<T>> prev_;		
	};

	template<typename T> 
	class LinkedList {
	public:
		LinkedList() { }

		void Insert(T item) {
			if (Root.get() == nullptr) {
				Root = std::make_shared<Node<T>>(item);
				current_ = Root;
				return;
			}

			auto newNode = std::make_shared<Node<T>>(item);

			current_->next_ = newNode;
			newNode->prev_ = current_;
			current_ = newNode;
		}

		Node<T>* Search(T item) const {
			auto searchResult = SearchItem(item);
			if (searchResult == nullptr) return nullptr;

			return searchResult.get();
		}

		bool Remove(T item) {
			auto targetNode = SearchItem(item);
			if (targetNode == nullptr) return false;

			auto prevNode = targetNode->prev_.lock();
			if (prevNode == nullptr) {
				targetNode->next_->prev_.lock() = nullptr;
				Root = targetNode->next_;
				return true;
			}

			auto nextNode = targetNode->next_;
			prevNode->next_ = nextNode;

			if(nextNode != nullptr) nextNode->prev_ = prevNode;
			
			return true;
		}		

		std::shared_ptr<Node<T>> Root;
	private:
		std::shared_ptr<Node<T>> SearchItem(T item) const {
			auto temp = Root;
			while (temp.get() != nullptr) {
				if (temp->Element == item) return temp;

				temp = temp->next_;
			}

			return nullptr;
		}

		std::shared_ptr<Node<T>> current_;
	};
}

#endif // LinkedList.hpp