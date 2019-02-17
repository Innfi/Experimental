#include "stdafx.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestingSuite
{
	class DummyElementGenerator {
	public:
		DummyElementGenerator(int count) {
			InitIndex();
			InitElements();

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

		int element_[1000];		
		int elementCount;
		int currentCount;

		int elementIndex_[1000];
	private:
		void InitIndex() { for (int i = 0; i < 1000; ++i) elementIndex_[i] = 0; }		
		void InitElements() { for (int i = 0; i < 100; ++i) element_[i] = 0; }

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
}