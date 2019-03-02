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

	TEST_CLASS(TestHeap)
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

	TEST_CLASS(TestSingleLinkedList) {
	public:
		TEST_METHOD(CallLinkedList) {

			Experimental::LinkedList list;
		}

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

	TEST_CLASS(TestRBTree) {
	public:
		TEST_METHOD(TestCallRBTreeEmpty) {
			Experimental::RbTree rb;

			/*Assert::AreEqual(rb.Empty(), true);

			auto rootElement = rb.Root();
			Assert::AreEqual((rootElement == nullptr), true);*/
		}

		//TEST_METHOD(TestSingleElementBlack)
		//{
		//	Experimental::RbElement firstElement = {Experimental::RbElementType::Black, 1};
		//	
		//	Experimental::RbTree rb;
		//	//rb.Insert(firstElement);
		//	
		//	Assert::AreEqual(rb.Empty(), false);

		//	auto rootElement = rb.Root();
		//	Assert::AreEqual((rootElement->type_ == firstElement.type_), true);
		//	Assert::AreEqual((rootElement->value_ == firstElement.value_), true);
		//}

		//TEST_METHOD(TestFirstRedElement)
		//{
		//	auto blackElement = GetBlackElement(2);
		//	auto redElement = GetRedElement(1);

		//	Experimental::RbTree rb;
		//	rb.Insert(blackElement);
		//	rb.Insert(redElement);

		//	auto rootElement = rb.Root();
		//	AssertSameElement(blackElement, *rootElement);

		//	auto left = rootElement->left;
		//	AssertSameElement(redElement, *left);
		//}

		//Experimental::RbElement GetBlackElement(int value) {
		//	return Experimental::RbElement{ Experimental::RbElementType::Black, value};
		//}

		//Experimental::RbElement GetRedElement(int value) {
		//	return Experimental::RbElement{ Experimental::RbElementType::Red, value };
		//}

		//void AssertSameElement(Experimental::RbElement lhs, Experimental::RbElement rhs) {
		//	Assert::AreEqual((lhs.type_ == rhs.type_), true);
		//	Assert::AreEqual((lhs.value_ == rhs.value_), true);
		//}

		TEST_METHOD(TestUniquePtr) {
			std::unique_ptr<int> test;

			auto mysterious = test.get();

			int dummy = 1;
		}
	};
}