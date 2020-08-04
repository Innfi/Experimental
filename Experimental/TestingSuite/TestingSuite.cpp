#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace TestingSuite
{
	class DummyElementGenerator {
	public:
		DummyElementGenerator(int count) {
			elementCount = count;
			currentCount = 0;
		}

		bool SetElements() {
			if (elementCount > 1000) return false;

			int tryCount = 0;

			while (true) {
				if (tryCount >= 10) return false;

				int element = rand() % 1000;

				if (elementIndex_[element] == 1) {
					tryCount++;
					continue;
				}
				tryCount = 0;

				elementIndex_[element] = 1;
				element_[currentCount++] = element;

				if (currentCount == elementCount) break;
			}

			return true;
		}

		int element_[1000] = { 0 };
		int elementIndex_[1000] = { 0 };

		int elementCount;
		int currentCount;

	};

	TEST_CLASS(Exp1SingleLinkedList) {
	public:
		TEST_METHOD(InitiallyEmpty) {
			Experimental::LinkedList list;

			Assert::AreEqual(list.Empty(), true);
		}

		TEST_METHOD(InsertNGetSingleNode) {
			Experimental::LinkedList list;

			int value = 1;
			list.Insert(value);

			auto node = list.Head();

			Assert::AreEqual(node->value_, value);
		}

		TEST_METHOD(InsertMultiNodes) {
			int count = 10;
			DummyElementGenerator gen(count);
			Assert::AreEqual(gen.SetElements(), true);

			Experimental::LinkedList list;

			for (int i = 0; i < count; i++) list.Insert(gen.element_[i]);

			AssertElementOrder(gen, list.Head());
		}

		void AssertElementOrder(const DummyElementGenerator& gen, Experimental::Node* node) {
			for (int i = 0; i < gen.currentCount; i++) {
				Assert::AreEqual(gen.element_[i], node->value_);
				node = node->next_.get();
			}
		}
	};

	TEST_CLASS(Exp2Heap)
	{
	public:
		TEST_METHOD(TestHeapSingleElement) {
			Experimental::Heap heap;
			heap.Insert(5);

			Assert::AreEqual(heap.Root(), 5);
		}

		TEST_METHOD(TestHeapInsertMultipleElement) {
			Experimental::Heap heap;
			heap.Insert(5);
			heap.Insert(2);
			heap.Insert(6);

			Assert::AreEqual(heap.Root(), 2);
			heap.Pop();
			Assert::AreEqual(heap.Root(), 5);
			heap.Pop();
			Assert::AreEqual(heap.Root(), 6);
			heap.Pop();
		}

		TEST_METHOD(TestHeapRandom) {
			int elementCount =  500;
			DummyElementGenerator gen(elementCount);

			Assert::AreEqual(gen.SetElements(), true);

			auto elements = gen.element_;
			Experimental::Heap heap;

			for (int i = 0; i < elementCount; ++i) heap.Insert(elements[i]);
			
			AssertMinHeapProperty(heap, elementCount);
		}

		void AssertMinHeapProperty(Experimental::Heap& heap, int elementCount) {
			for (int i = 0; i < elementCount-1; i++) {
				auto currentElement = heap.Root();
				heap.Pop();
				auto nextElement = heap.Root();

				Assert::AreEqual(currentElement < nextElement, true);
			}
		}
	};

	TEST_CLASS(Exp3RBTree) {
	public:
		TEST_METHOD(Test1SingleElementBlack) {
			using namespace Experimental;

			int first = 1;
			RbTree tree;
			tree.Insert(first);

			auto root = tree.Root().get();

			Assert::AreEqual(root->isRed_, false);
			Assert::AreEqual(first, root->value_);
		}

		TEST_METHOD(Test2Insert3NodesBalancedOrder) {
			using namespace Experimental;

			RbTree tree;
			tree.Insert(2);
			tree.Insert(1);			
			tree.Insert(3);

			auto root = tree.Root().get();

			Assert::AreEqual(root->isRed_, false);
			Assert::AreEqual(root->value_, 2);

			auto left = root->leftChild_.get();
			Assert::AreEqual(left->isRed_, true);
			Assert::AreEqual(left->value_, 1);

			auto right = root->rightChild_.get();
			Assert::AreEqual(right->isRed_, true);
			Assert::AreEqual(right->value_, 3);
		}

		TEST_METHOD(Test3LeftRotation) {
			using namespace Experimental;

			RbTree tree;
			tree.Insert(1);
			tree.Insert(2);
			tree.Insert(3);

			auto root = tree.Root().get();

			Assert::AreEqual(root->isRed_, false);
			Assert::AreEqual(root->value_, 2);

			auto left = root->leftChild_.get();
			Assert::AreEqual(left->isRed_, true);
			Assert::AreEqual(left->value_, 1);

			auto right = root->rightChild_.get();
			Assert::AreEqual(right->isRed_, true);
			Assert::AreEqual(right->value_, 3);
		}

		TEST_METHOD(Test4RLRotation) {
			using namespace Experimental;

			RbTree tree;
			tree.Insert(1);
			tree.Insert(6);
			tree.Insert(4);

			auto root = tree.Root().get();

			Assert::AreEqual(root->isRed_, false);
			Assert::AreEqual(root->value_, 4);

			auto left = root->leftChild_.get();
			Assert::AreEqual(left->isRed_, true);
			Assert::AreEqual(left->value_, 1);

			auto right = root->rightChild_.get();
			Assert::AreEqual(right->isRed_, true);
			Assert::AreEqual(right->value_, 6);
		}

		TEST_METHOD(Test5RightRotation) {
			using namespace Experimental;

			RbTree tree;
			tree.Insert(5);
			tree.Insert(3);
			tree.Insert(1);

			auto root = tree.Root().get();

			Assert::AreEqual(root->isRed_, false);
			Assert::AreEqual(root->value_, 3);

			auto left = root->leftChild_.get();
			Assert::AreEqual(left->isRed_, true);
			Assert::AreEqual(left->value_, 1);

			auto right = root->rightChild_.get();
			Assert::AreEqual(right->isRed_, true);
			Assert::AreEqual(right->value_, 5);
		}

		TEST_METHOD(Test6LRRotation) {
			using namespace Experimental;

			RbTree tree;
			tree.Insert(10);
			tree.Insert(4);
			tree.Insert(5);

			auto root = tree.Root().get();
			Assert::AreEqual(root->isRed_, false);
			Assert::AreEqual(root->value_, 5);

			auto left = root->leftChild_.get();
			Assert::AreEqual(left->isRed_, true);
			Assert::AreEqual(left->value_, 4);

			auto right = root->rightChild_.get();
			Assert::AreEqual(right->isRed_, true);
			Assert::AreEqual(right->value_, 10);
		}

		TEST_METHOD(Test7Recoloring) {
			using namespace Experimental;

			RbTree tree;
			tree.Insert(5);
			tree.Insert(2);
			tree.Insert(7);
			tree.Insert(8);

			auto root = tree.Root().get();
			Assert::AreEqual(root->isRed_, false);
			Assert::AreEqual(root->value_, 5);

			auto left = root->leftChild_.get();
			Assert::AreEqual(left->isRed_, false);
			Assert::AreEqual(left->value_, 2);

			auto right = root->rightChild_.get();
			Assert::AreEqual(right->isRed_, false);
			Assert::AreEqual(right->value_, 7);

			auto leaf = right->rightChild_.get();
			Assert::AreEqual(leaf->isRed_, true);
			Assert::AreEqual(leaf->value_, 8);
		}

		TEST_METHOD(Test8AssertRBAttrs) {
			
		}
	};
}