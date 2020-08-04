#pragma once

#ifndef __HEAP_HPP__
#define __HEAP_HPP__


namespace Experimental
{
	enum HeapErrors {
		Ok = 0,
		InsertDuplicate = 1,
		ElementDuplicate = 2
	};

	class Element {
	public:
		Element() : value_(0) {}
		Element(int v) : value_(v) {}
		int value_;
	};

	class Heap { // min heap
	public:
		Heap() : currentIndex_(0) { }

		HeapErrors Insert(const int elem) {
			nodes_[++currentIndex_] = elem;

			return TrySiftUp();
		}

		const int Root() { return nodes_[1]; }

		HeapErrors Pop() {
			nodes_[1] = nodes_[currentIndex_];
			nodes_[currentIndex_] = 0;
			currentIndex_--;

			return TrySiftDown();
		}

	protected:
		HeapErrors TrySiftUp() {
			int index = currentIndex_;

			if (index == 1) return HeapErrors::Ok;

			while (index > 1) {
				if (nodes_[index] < Parent(index)) Swap(index, ParentIndex(index));

				index = ParentIndex(index);
			}

			return HeapErrors::Ok;
		}

		HeapErrors TrySiftDown() {
			int index = 1;

			while (index < currentIndex_) {
				auto minValue = LeftNode(index);
				int nextIndex = LeftNodeIndex(index);

				if (minValue == 0) break;

				if (RightNode(index) > 0 && minValue > RightNode(index)) {
					minValue = RightNode(index);
					nextIndex = RightNodeIndex(index);
				}

				if (nodes_[index] > minValue) Swap(index, nextIndex);

				index = nextIndex;
			}

			return HeapErrors::Ok;
		}

		const int ParentIndex(int index) { return index / 2; }
		const int LeftNodeIndex(int index) { return index * 2; }
		const int RightNodeIndex(int index) { return index * 2+1; }

		const int Parent(int index) { return nodes_[ParentIndex(index)]; }
		const int LeftNode(int index) { return nodes_[LeftNodeIndex(index)]; }
		const int RightNode(int index) { return nodes_[RightNodeIndex(index)]; }

		void Swap(int indexA, int indexB) {
			auto temp = nodes_[indexA];
			nodes_[indexA] = nodes_[indexB];
			nodes_[indexB] = temp;
		}

		int nodes_[1000] = { 0 };
		int currentIndex_;
	};		
}

#endif // Heap.hpp
