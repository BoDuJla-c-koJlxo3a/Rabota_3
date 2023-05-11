#pragma once

template <class T> class DynamicArray {

private:

	int size;
	T* arr;

public:

	DynamicArray(T* items, int count) {
		if (count < 0) {
			size = 0;
			arr = 0;
			throw(1);
		}
		size = count;
		if (count == 0) {
			arr = 0;
		}
		else {
			arr = new T[count];
			for (int i = 0; i < count; i++) {
				arr[i] = items[i];
			}

		}
	}

	DynamicArray(int count) {
		if (count < 0) {
			size = 0;
			arr = 0;
			throw(-1);
		}
		size = count;
		if (count == 0) {
			arr = 0;
		}
		else {
			arr = new T[count];
		}
	}

	DynamicArray(int count, T item) {
		if (count < 0) {
			size = 0;
			arr = 0;
			throw(-1);
		}
		size = count;
		if (count == 0) {
			arr = 0;
		}
		else {
			arr = new T[count];
			for (int i = 0; i < count; i++) {
				arr[i] = item;
			}
		}
	}

	DynamicArray(const DynamicArray<T> &dynar) {
		if (dynar.size < 0) {
			size = 0;
			arr = 0;
			throw(-1);
		}
		size = dynar.size;
		arr = new T[size];
		for (int i = 0; i < size; i++) {
			arr[i] = dynar.arr[i];
		}
	}

	~DynamicArray() {
		size = 0;
		delete arr;
	}

	T Get(int index) {
		if (index < 0 || index >= size) {
			throw(index);            //index out of range
		}
		if (size <= 0) {
			throw(-1);              //zero-length arr
		}
		return arr[index];
	}

	int GetSize() {
		return size;
	}

	void Set(int index, T value) {
		if (index < 0 || index >= size) {
			throw(index);              //index out of range
		}
		if (size <= 0) {
			throw(-1);              //zero-length arr
		}
		arr[index] = value;
	}

	void Resize(int newSize) {
		if (newSize < 0) {
			throw(1);              // < 0
		}
		if (newSize == 0) {
			size = 0;
			arr = 0;
		}
		int n = 0;
		if (size < newSize) {
			n = size;
		}
		else {
			n = newSize;
		}
		size = newSize;
		T* arr2 = new T[newSize];
		for (int i = 0; i < n; i++) {
			arr2[i] = arr[i];
		}
		for (int i = n; i < newSize; i++) {
			arr2[i] = 0;
		}
		delete arr;
		arr = arr2;
	}

	void Prepend(T item) {
		this->Resize(size + 1);
		for (int i = size - 1; i > 0; i--) {
			arr[i] = arr[i - 1];
		}
		arr[0] = item;
	}

	void InsertAt(T item, int index) {
		if (index < 0 || index > size) {
			throw(index); //index out of range
		}
		this->Resize(size + 1);
		if (index == 0) {
			this->Prepend(item);
			return;
		}
		if (index == size - 1) {
			this->Set(size - 1, item);
			return;
		}
		for (int i = size - 1; i > index; i--) {
			arr[i] = arr[i - 1];
		}
		arr[index] = item;
	}


	DynamicArray<T>* GetSubArray(int startIndex, int endIndex) {
		if (startIndex < 0 || endIndex < 0 || startIndex >= size || endIndex >= size) {
			throw(1);     // index out of range;
		}
		if (startIndex > endIndex) {
			throw(-1);    // wrong order
		}
		DynamicArray<T>* a = new DynamicArray<T>(0);
		a->size = endIndex - startIndex + 1;
		a->arr = new T[a->size];
		for (int i = startIndex; i <= endIndex; i++) {
			a->arr[i - startIndex] = arr[i];
		}
		return a;
	}
};