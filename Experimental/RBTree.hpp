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

		void doRotation(std::shared_ptr<RbNode> node) {
			std::shared_ptr<RbNode> newParent;

			if (!node->isLeft_ && !(node->parent_->isLeft_)) { //left rotation
				newParent = leftRotation(node);
			}
			else if (node->isLeft_ && !(node->parent_->isLeft_)) { //RL rotation
				rightSingleRotation(node);
				newParent = leftRotation(node->rightChild_);
			}

			newParent->isRed_ = false;
			newParent->leftChild_->isRed_ = true;
			newParent->rightChild_->isRed_ = true;
		}

		std::shared_ptr<RbNode> leftRotation(std::shared_ptr<RbNode> node) {
			auto newParent = node->parent_;
			auto newLeft = newParent->parent_;
			auto unchangedParent = newLeft->parent_;

			newParent->leftChild_ = newLeft;
			newLeft->parent_ = newParent;

			newParent->parent_ = unchangedParent;

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