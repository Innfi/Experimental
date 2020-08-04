#include "pch.h"
#include "CppUnitTest.h"
#include "../CppDemo/LinkedList.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace CppDemo
{
	TEST_CLASS(CppDemoTest) {
	public:
		TEST_METHOD(Test0CallNode) {
			Node<int> node;
			node.Element = 0;

			Assert::AreEqual(node.Element, 0);
		}

		TEST_METHOD(Test0NodeNextIsNull) {
			Node<int> node;
			Assert::AreEqual(node.Next() == nullptr, true);
		}

		TEST_METHOD(Test0NodePrevIsNull) {
			Node<int> node;
			Assert::AreEqual(node.Prev() == nullptr, true);
		}

		TEST_METHOD(Test0LinkNextNode) {
			auto node{ std::make_shared<Node<int>>(1) };

			int targetValue = 3;
			auto nextNode{ std::make_shared<Node<int>>(targetValue) };

			node->next_ = nextNode;
			Assert::AreEqual(node->Next()->Element, targetValue);
		}

		TEST_METHOD(Test0LinkPrevNode) {
			auto node{ std::make_shared<Node<int>>(1) };

			int targetValue = 7;
			auto prevNode{ std::make_shared<Node<int>>(7) };

			node->prev_ = prevNode;
			Assert::AreEqual(node->Prev()->Element, targetValue);
		}

		TEST_METHOD(Test0CallLL) {
			LinkedList<int> ll;
		}
		
		TEST_METHOD(Test0LLRootElementNull) {
			LinkedList<int> ll;

			Assert::AreEqual(ll.Root.get() == nullptr, true);
		}
		
		TEST_METHOD(Test1InsertFirstItem) {
			LinkedList<int> ll;

			ll.Insert(1);

			Assert::AreEqual(ll.Root.get()->Element, 1);
		}

		TEST_METHOD(Test1InsertNextItem) {
			LinkedList<int> ll;
			ll.Insert(1);
			ll.Insert(3);

			auto root = ll.Root.get();
			auto nextNode = root->Next();

			Assert::AreEqual(nextNode != nullptr, true);			
			Assert::AreEqual(nextNode->Element, 3);
			Assert::AreEqual(nextNode->Prev()->Element, 1);

			ll.Insert(5);
			auto otherNode = nextNode->Next();
			Assert::AreEqual(otherNode != nullptr, true);
			Assert::AreEqual(otherNode->Element, 5);
			Assert::AreEqual(otherNode->Prev()->Element, 3);
		}

		TEST_METHOD(Test1SearchItemNullPtrForEmptyLL) {
			LinkedList<int> ll;
			auto searchResult = ll.Search(12345);
			Assert::AreEqual(searchResult == nullptr, true);
		}

		TEST_METHOD(Test1SearchItemNullptrForInvalidItem) {
			LinkedList<int> ll;
			ll.Insert(1);
			ll.Insert(3);
			ll.Insert(5);

			auto searchResult = ll.Search(4);
			Assert::AreEqual(searchResult == nullptr, true);
		}

		TEST_METHOD(Test1SearchItem) {
			LinkedList<int> ll;
			ll.Insert(1);
			ll.Insert(3);
			ll.Insert(5);
			ll.Insert(7);
			ll.Insert(11);
			
			auto searchResult = ll.Search(5);
			Assert::AreEqual(searchResult != nullptr, true);
			Assert::AreEqual(searchResult->Element, 5);
			Assert::AreEqual(searchResult->Next()->Element, 7);
			Assert::AreEqual(searchResult->Prev()->Element, 3);
		}
	};
}
