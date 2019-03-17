#ifndef __RBTREE_HPP__
#define __RBTREE_HPP__


namespace Experimental
{
	class RbNode {
	public:
		RbNode(int value): value_(value), isRed_(true),
				leftChild_(nullptr), rightChild_(nullptr), parent_(nullptr),
				isLeft_(true) {}

		int value_;

		std::shared_ptr<RbNode> leftChild_;
		std::shared_ptr<RbNode> rightChild_;
		std::shared_ptr<RbNode> parent_;

		bool isRed_;
		bool isLeft_;
	};

	enum DoubleRedType {
		Initial = 0,
		RR,
		RL,
		LL,
		LR
	};

	class RbTree {
	public:
		RbTree() : root_(nullptr) {}

		void Insert(int value) {
			std::shared_ptr<RbNode> node(new RbNode(value));

			Insert(node);
		}

		void Insert(std::shared_ptr<RbNode> node) {
			if (root_ == nullptr) {
				root_ = node;
				root_->isRed_ = false;
				return;
			}
			
			insertIteration(node);
		}

		std::shared_ptr<RbNode> Root() {
			return root_;
		}
	
	private:
		void insertIteration(std::shared_ptr<RbNode> node) {
			auto current = root_;

			while (true) {
				if (current->value_ > node->value_) {
					if (current->leftChild_ == nullptr) {
						current->leftChild_ = node;
						node->parent_ = current;
						break;
					}
					else {
						current = current->leftChild_;
					}
				}
				else {
					if (current->rightChild_ == nullptr) {
						current->rightChild_ = node;
						node->isLeft_ = false;
						node->parent_ = current;
						break;
					}
					else {
						current = current->rightChild_;
					}
				}
			}

			if (isDoubleRed(node)) {
				if (isRedAunt(node)) { //red aunt: recolor
					doRecoloring(node);
				}
				else { //black aunt: rotation
					doRotation(node);
				}
			}

			setRoot();
		}

		bool isDoubleRed(std::shared_ptr<RbNode> node) {
			return node->isRed_ && node->parent_->isRed_;
		}

		bool isRedAunt(std::shared_ptr<RbNode> node) {
			auto parent = node->parent_;
			std::shared_ptr<RbNode> aunt;

			if (parent->isLeft_) aunt = parent->parent_->rightChild_;
			else aunt = parent->parent_->leftChild_;

			if (aunt == nullptr) return false;

			return aunt->isRed_;
		}

		void doRecoloring(std::shared_ptr<RbNode> node) {
			auto grandParent = node->parent_->parent_;
			grandParent->isRed_ = true;
			grandParent->leftChild_->isRed_ = false;
			grandParent->rightChild_->isRed_ = false;
		}

		void doRotation(std::shared_ptr<RbNode> node) {
			std::shared_ptr<RbNode> newParent;

			auto doubleRedType = ToDoubleRedType(node);
			switch (doubleRedType)
			{
			case Experimental::RR:
				newParent = leftRotation(node);
				break;
			case Experimental::RL:
				rightSingleRotation(node);
				newParent = leftRotation(node->rightChild_);
				break;
			case Experimental::LL:
				newParent = rightRotation(node);
				break;
			case Experimental::LR:
				leftSingleRotation(node);
				newParent = rightRotation(node->leftChild_);
				break;
			default:				
				break;
			}

			newParent->isRed_ = false;
			newParent->leftChild_->isRed_ = true;
			newParent->rightChild_->isRed_ = true;
		}

		DoubleRedType ToDoubleRedType(std::shared_ptr<RbNode> node) {
			if (!node->isLeft_ && !(node->parent_->isLeft_)) { //left rotation
				return DoubleRedType::RR;
			}
			else if (node->isLeft_ && !(node->parent_->isLeft_)) { //RL rotation
				return DoubleRedType::RL;
			}
			else if (node->isLeft_ && (node->parent_->isLeft_)) { //right rotation
				return DoubleRedType::LL;
			}
			else if (!node->isLeft_ && (node->parent_->isLeft_)) { //LR rotation 
				return DoubleRedType::LR;
			}

			return DoubleRedType::Initial;
		}

		std::shared_ptr<RbNode> leftRotation(std::shared_ptr<RbNode> node) {
			auto newParent = node->parent_;
			auto newLeft = newParent->parent_;
			bool isLeftChild = newLeft->isLeft_;
			auto unchangedParent = newLeft->parent_;

			newParent->parent_ = unchangedParent;
			if (unchangedParent != nullptr) {
				if (isLeftChild) unchangedParent->leftChild_ = newParent;
				else unchangedParent->rightChild_ = newParent;
			}

			newParent->leftChild_ = newLeft;
			newLeft->parent_ = newParent;

			return newParent;
		}

		void rightSingleRotation(std::shared_ptr<RbNode> node) {
			auto grandParent = node->parent_->parent_;
			auto newRight = node->parent_;

			grandParent->rightChild_ = node;
			node->parent_ = grandParent;

			node->rightChild_ = newRight;
			newRight->parent_ = node;

			newRight->leftChild_ = nullptr;			
		}

		std::shared_ptr<RbNode> rightRotation(std::shared_ptr<RbNode> node) {
			auto newParent = node->parent_;
			auto newRight = newParent->parent_;
			bool isLeftChild = newRight->isLeft_;
			auto unchangedParent = newRight->parent_;

			newParent->parent_ = unchangedParent;
			if (unchangedParent != nullptr) {
				if (isLeftChild) unchangedParent->leftChild_ = newParent;
				else unchangedParent->rightChild_ = newParent;
			}

			newParent->rightChild_ = newRight;
			newRight->parent_ = newParent;

			return newParent;
		}

		void leftSingleRotation(std::shared_ptr<RbNode> node) {
			auto unchangedParent = node->parent_->parent_;
			auto newChild = node->parent_;

			node->parent_ = unchangedParent;
			unchangedParent->leftChild_ = node;

			node->leftChild_ = newChild;
			newChild->parent_ = node;
			newChild->rightChild_ = nullptr;
		}

		void setRoot() {
			auto temp = root_;

			while (temp->parent_ != nullptr) temp = temp->parent_;

			root_ = temp;

			if (root_->isRed_ == true) root_->isRed_ = false;
		}

		std::shared_ptr<RbNode> root_;
	};
}

#endif // __RBTREE_HPP__