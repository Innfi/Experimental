#pragma once

#include "pch.h"
#include <iostream>


namespace Experimental
{

#define MAX_SIZE 100

	template <typename T>
	class ArrayList {
	public:
		ArrayList();
		virtual ~ArrayList();

		void AddToFront(const T& data);
		/*void AddToBack(const T& data);
		void DeleteData(int pos);
		bool IsEmpty();
		bool IsFull();
		int Size();
		const T& GetData(int pos);
		void Clear();
		void Display();*/

	private:
		T list_[MAX_SIZE];
		int length_;
	};

	template<typename T>
	ArrayList<T>::ArrayList() {
		length_ = 0;
	}

	template<typename T>
	ArrayList<T>::~ArrayList() {
	}

	template<typename T>
	void ArrayList<T>::AddToFront(const T& data) {
		for (int i = length_; i >= 0; --i) {
			list_[i + 1] = list_[i];
		}

		list_[0] = data;
		++length_;
	}
}