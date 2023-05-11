#pragma once
#include "dynarr.h"
#include "linlist.h"

template <class T> class Sequence {

public:

	virtual T GetFirst() const = 0;
	virtual T GetLast() const = 0;
	virtual T Get(int index) const = 0;
	virtual void Set(int index, T item) const = 0;
	virtual int GetLength() const = 0;
	virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
	virtual void Append(T item) = 0;
	virtual void Prepend(T item) = 0;
	virtual void InsertAt(T item, int index) = 0;
	virtual Sequence <T>* Concat(Sequence <T>* list) const = 0;

};

template <class T> class ArraySequence : public Sequence<T> {

private:

	DynamicArray<T>* data;

public:

	ArraySequence<T>(T* items, int count) {
		try {
			data = new DynamicArray<T>(items, count);
		}
		catch(int w) {
			throw(w);
		}
	}

	ArraySequence<T>() {
		try {
			data = new DynamicArray<T>(0);
		}
		catch (int w) {
			throw(w);
		}
	}

	ArraySequence<T>(int count, T item) {
		try {
			data = new DynamicArray<T>(count, item);
		}
		catch (int w) {
			throw(w);
		}
	}

	ArraySequence<T>(const DynamicArray<T>& list) {
		try {
			data = new DynamicArray<T>(list);
		}
		catch (int w) {
			throw(w);
		}
	}

	~ArraySequence<T>() {
		delete data;
	}

	T GetFirst() const override {
		T item;
		try {
			item = data->Get(0);
		}
		catch(int w) {
			throw w; //zero-length
		}
		return item;
	}

	T GetLast() const override {
		T item;
		try {
			item = data->Get(data->GetSize() - 1);
		}
		catch (int w) {
			throw w; //zero-length
		}
		return item;
	}

	T Get(int index) const override {
		T item;
		try {
			item = data->Get(index);
		}
		catch (int w) {
			throw w; //zero-length
		}
		return item;
	}

	void Set(int index, T item) const override {
		try {
			data->Set(index, item);
		}
		catch (int w) {
			throw w; //zero-length | out of range
		}
	}

	int GetLength() const override {
		return data->GetSize();
	}

	Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
		ArraySequence<T>* seq = new ArraySequence<T>();
		delete seq->data;
		try {
			seq->data = data->GetSubArray(startIndex, endIndex);
		}
		catch (int w) {
			delete seq;
			throw w; // out of range/wrong order
		}
		return seq;
	}

	void Append(T item) override {
		data->Resize(data->GetSize() + 1);
		data->Set(data->GetSize() - 1, item);
	}

	void Prepend(T item) override {
		data->Prepend(item);
	}

	void InsertAt(T item, int index) override {
		try {
			data->InsertAt(item, index);
		}
		catch (int w) {
			throw w;
		}
	}

	Sequence <T>* Concat(Sequence<T>* list) const override {
		ArraySequence<T>* out = new ArraySequence<T>(0);
		for (int i = 0; i < data->GetSize(); i++) {
			out->Append(data->Get(i));
		}
		for (int i = 0; i < list->GetLength(); i++) {
			out->Append(list->Get(i));
		}
		return out;
	}
};

template <class T> class LinkedListSequence : public Sequence<T> {

private:

	LinkedList<T>* data;

public:

	LinkedListSequence<T>(T* items, int count) {
		try {
			data = new LinkedList<T>(items, count);
		}
		catch (int w) {
			throw w; //zero-length | out of range
		}
	}

	LinkedListSequence<T>() {
		data = new LinkedList<T>();
	}

	LinkedListSequence<T>(int count, T item) {
		try {
			data = new LinkedList<T>(count, item);
		}
		catch (int w) {
			throw w; //zero-length | out of range
		}
	}

	LinkedListSequence<T>(const LinkedList<T>& list) {
		try {
			data = new LinkedList<T>(list);
		}
		catch (int w) {
			throw w; //zero-length | out of range
		}
	}

	~LinkedListSequence<T>() {
		delete data;
	}

	T GetFirst() const override {
		T item;
		try {
			item = data->GetFirst();
		}
		catch (int w) {
			throw w; //zero-length
		}
		return item;
	}

	T GetLast() const override {
		T item;
		try {
			item = data->GetLast();
		}
		catch (int w) {
			throw w; //zero-length
		}
		return item;
	}

	T Get(int index) const override {
		T item;
		try {
			item = data->Get(index);
		}
		catch (int w) {
			throw w; //zero-length
		}
		return item;
	}

	void Set(int index, T item) const override {
		try {
			data->Set(index, item);
		}
		catch (int w) {
			throw w; //zero-length | out of range
		}
	}

	int GetLength() const override {
		return data->GetLength();
	}

	Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
		LinkedListSequence<T>* seq = new LinkedListSequence<T>();
		delete seq->data;
		try {
			seq->data = data->GetSubList(startIndex, endIndex);
		}
		catch (int w) {
			delete seq;
			throw w; // out of range/wrong order
		}
		return seq;
	}

	void Append(T item) override {
		data->Append(item);
	}

	void Prepend(T item) override {
		data->Prepend(item);
	}

	void InsertAt(T item, int index) override {
		try {
			data->InsertAt(item, index);
		}
		catch (int w) {
			throw w;
		}
	}

	Sequence <T>* Concat(Sequence<T>* list) const override {
		LinkedListSequence<T>* out = new LinkedListSequence<T>();
		for (int i = 0; i < data->GetLength(); i++) {
			out->Append(data->Get(i));
		}
		for (int i = 0; i < list->GetLength(); i++) {
			out->Append(list->Get(i));
		}
		return out;
	}
};