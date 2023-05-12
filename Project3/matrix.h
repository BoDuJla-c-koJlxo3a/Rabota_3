#pragma once
#include "sequence.h"
#include "complex.h"

template <class T> class Matrix {

private:

	Sequence<T>* data;
	int heigth;
	int width;

	T Get(int index) {
		T item;
		try {
			item = data->Get(index);
		}
		catch (int w) {
			throw w; //zero-length
		}
		return item;
	}

	void Swap(int a, int b) {
		T item;
		try {
			item = this->Get(a);
		}
		catch (int w) {
			throw(w);
		}
		data->Set(a, this->Get(b));
		data->Set(b, item);
	}

public:

	Matrix<T>(T* items, int h, int w) {
		try {
			data = new LinkedListSequence<T>(items, w * h);
		}
		catch (int w) {
			throw w; //zero-length | out of range
		}
		heigth = h;
		width = w;
	}
	Matrix<T> (Sequence<T>* items, int h, int w) {
		if (items->GetLength() != h * w) {
			throw(-1);
		}
		data = items;
		heigth = h;
		width = w;
	}

	Matrix<T> (int h, int w, T item) {
		try {
			data = new LinkedListSequence<T>(h*w, item);
		}
		catch (int w) {
			throw w; //zero-length | out of range
		}
		heigth = h;
		width = w;
	}

	~Matrix() {
		delete data;
	}

	T GetIJ(int i, int j) {
		if (i < 0 || j < 0) {
			throw(-1);
		}
		if (i >= heigth) {
			throw(i);
		}
		if (j >= width) {
			throw(j);
		}
		T item;
		int index = i * width + j;
		try {
			item = data->Get(index);
		}
		catch (int w) {
			throw w; //zero-length
		}
		return item;
	}

	void SetIJ(int i, int j, T item) {
		if (i < 0 || j < 0) {
			throw(-1);
		}
		if (i >= heigth) {
			throw(i);
		}
		if (j >= width) {
			throw(j);
		}
		int index = i * width + j;
		try {
			data->Set(index, item);
		}
		catch (int w) {
			throw w; //zero-length
		}
	}

	int GetWidth() {
		return width;
	}

	int GetHeigth() {
		return heigth;
	}

	Matrix<T>* Sum(Matrix<T>* matr) {
		if (heigth != matr->GetHeigth() || width != matr->GetWidth()) {
			throw(-1);
		}
		LinkedListSequence<T>* list = new LinkedListSequence<T>();
		for (int i = 0; i < heigth * width; i++) {
			list->Append(data->Get(i) + matr->Get(i));
		}
		Matrix<T>* out = new Matrix(list, heigth, width);
		return out;
	}

	Matrix<T>* ScalarMult(T num) {
		LinkedListSequence<T>* list = new LinkedListSequence<T>();
		for (int i = 0; i < heigth * width; i++) {
			list->Append(data->Get(i)*num);
		}
		Matrix<T>* out = new Matrix(list, heigth, width);
		return out;
	}

	void SwapColumns(int a, int b) {
		if (a < 0 || b < 0) {
			throw(-1);
		}
		if (a >= width) {
			throw(a);
		}
		if (b >= width) {
			throw(b);
		}
		for (int i = 0; i < heigth; i++) {
			this->Swap(a + i*width, b + i * width);
		}
	}

	void SwapRows(int a, int b) {
		if (a < 0 || b < 0) {
			throw(-1);
		}
		if (a >= heigth) {
			throw(a);
		}
		if (b >= heigth) {
			throw(b);
		}
		for (int i = 0; i < width; i++) {
			this->Swap(i + a * width, i + b * width);
		}
	}

	void MultColumn(int col, T num) {
		if (col < 0) {
			throw(-1);
		}
		if (col >= width) {
			throw(col);
		}
		for (int i = 0; i < heigth; i++) {
			data->Set(i*width + col, (data->Get(i * width + col))*num);
		}
	}

	void MultRow(int row, T num) {
		if (row < 0) {
			throw(-1);
		}
		if (row >= heigth) {
			throw(row);
		}
		for (int i = 0; i < width; i++) {
			data->Set(row * width + i, (data->Get(row * width + i)) * num);
		}
	}
	
	void AddColumn(int from, int to) {
		if (from < 0 || to < 0) {
			throw(-1);
		}
		if (from >= width) {
			throw(from);
		}
		if (to >= width) {
			throw(to);
		}
		for (int i = 0; i < heigth; i++) {
			data->Set(to + i * width, data->Get(from + i * width) + data->Get(to + i * width));
		}
	}

	void AddRow(int from, int to) {
		if (from < 0 || to < 0) {
			throw(-1);
		}
		if (from >= heigth) {
			throw(from);
		}
		if (to >= heigth) {
			throw(to);
		}
		for (int i = 0; i < width; i++) {
			data->Set(i + to * width, data->Get(i + from * width) + data->Get(i + to * width));
		}
	}

	void SubtractColumn(int from, int to) {
		if (from < 0 || to < 0) {
			throw(-1);
		}
		if (from >= width) {
			throw(from);
		}
		if (to >= width) {
			throw(to);
		}
		for (int i = 0; i < heigth; i++) {
			data->Set(to + i * width, data->Get(to + i * width) - data->Get(from + i * width));
		}
	}

	void SubtractRow(int from, int to) {
		if (from < 0 || to < 0) {
			throw(-1);
		}
		if (from >= heigth) {
			throw(from);
		}
		if (to >= heigth) {
			throw(to);
		}
		for (int i = 0; i < width; i++) {
			data->Set(i + to * width, data->Get(i + to * width) - data->Get(i + from * width));
		}
	}
};