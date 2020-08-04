#ifndef __LINKEDLIST_HPP__
#define __LINKEDLIST_HPP__

#include <memory>

namespace Experimental
{
	class Node {
	public:
		Node() {}

		int value_;
		std::shared_ptr<Node> next_;
	};

	class LinkedList {
	public:
		LinkedList() : head_(nullptr), current_(nullptr) {}
		void Insert(int value) {
			if (Empty()) {
				head_ = std::make_shared<Node>();
				head_->value_ = value;
				head_->next_ = nullptr;

				current_ = head_;
			}
			else {
				current_->next_ = std::make_shared<Node>();
				current_->next_->value_ = value;
				current_->next_->next_ = nullptr;

				current_ = current_->next_;
			}
		}

		Node* Head() { return head_.get(); }
		bool Empty() { return !head_; }
	private:
		std::shared_ptr<Node> head_;
		std::shared_ptr<Node> current_;
	};
}

#endif // __LINKEDLIST_HPP__