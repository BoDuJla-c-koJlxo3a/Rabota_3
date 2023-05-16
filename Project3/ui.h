#pragma once
#include "matrix.h"
#include "complex.h"

template <class T> class entry {

public:
	
	bool notEmpty;
	Matrix<T>* data;
};

template <typename T>
entry<T>* realok(entry<T>* arr, int* size) {
	int count = 0;
	for (int i = 0; i < *size; i++) {
		if (arr[i].notEmpty) {
			count++;
		}
		
	}
	if (count < (*size / 3)) {
		entry<T>* out = new entry<T>[count + 2];
		int t = 0;
		for (int i = 0; i < *size; i++) {
			if (arr[i].notEmpty) {
				out[t] = arr[i];
				t++;
			}
		}
		*size = count + 2;
		for (int i = t; i < *size; i++) {
			out[i].data = 0;
			out[i].notEmpty = false;
		}
		delete arr;
		return out;
	}
	if (count >= *size - 1) {
		entry<T>* out = new entry<T>[2*(*size)];
		int t = 0;
		for (int i = 0; i < *size; i++) {
			if (arr[i].notEmpty) {
				out[t] = arr[i];
				t++;
			}
		}
		*size = 2 * (*size);
		for (int i = t; i < *size; i++) {
			out[i].data = 0;
			out[i].notEmpty = false;
		}
		delete arr;
		return out;
	}
	if (arr[*size - 1].notEmpty) {
		entry<T>* out = new entry<T>[*size];
		int t = 0;
		for (int i = 0; i < *size; i++) {
			if (arr[i].notEmpty) {
				out[t] = arr[i];
				t++;
			}
		}
		for (int i = t; i < count; i++) {
			out[i].data = 0;
			out[i].notEmpty = false;
		}
		delete arr;
		return out;
	}
	return arr;
}

template <typename T>
void disp(entry<T>* arr, int size) {
	std::cout << '\n';
	for (int i = 0; i < size; i++) {
		std::cout << i << " - ";
		if (arr[i].notEmpty) {
			std::cout << "Matrix";
			std::cout << "\n";
		}
		else {
			std::cout << "*empty*\n";
		}
	}
	std::cout << "===========\n";
}

template <typename T>
int modify(Matrix<T>* arr) {
	while (true) {
		int type = -1, m = -1, n = -1, r = 0;
		T item;
		std::cout << "1 - Set number\n2 - Multiply row\n3 - Multiply column\n4 - Add row\n5 - Add column\n6 - Swap rows\n7 - Swap columns\n8 - Show yor matrix\n9 - Save\n0 - Delete\n";
		std::cin >> type;
		switch (type) {
		case 1:
			std::cout << "Enter number\n>";
			std::cin >> item;
			while (m < 0 || m >= arr->GetHeigth()) {
				std::cout << "Enter row (0 - " << arr->GetHeigth() - 1 << ")\n";
				std::cin >> m;
			}
			while (n < 0 || n >= arr->GetWidth()) {
				std::cout << "Enter column (0 - " << arr->GetWidth() - 1 << ")\n";
				std::cin >> n;
			}
			arr->SetIJ(m, n, item);
			std::cout << "OK\n";
			break;
		case 2:
			std::cout << "Enter number\n>";
			std::cin >> item;
			while (m < 0 || m >= arr->GetHeigth()) {
				std::cout << "Enter row (0 - " << arr->GetHeigth() - 1 << ")\n";
				std::cin >> m;
			}
			arr->MultRow(m, item);
			std::cout << "OK\n";
			break;
		case 3:
			std::cout << "Enter number\n>";
			std::cin >> item;
			while (n < 0 || n >= arr->GetWidth()) {
				std::cout << "Enter column (0 - " << arr->GetWidth() - 1 << ")\n";
				std::cin >> n;
			}
			arr->MultColumn(n, item);
			std::cout << "OK\n";
			break;
		case 4:
			while (m < 0 || m >= arr->GetHeigth()) {
				std::cout << "Which row (0 - " << arr->GetHeigth() - 1 << ")?\n";
				std::cin >> m;
			}
			while (n < 0 || n >= arr->GetHeigth()) {
				std::cout << "Where (0 - " << arr->GetHeigth() - 1 << ")?\n";
				std::cin >> n;
			}
			while (r < 1 || r > 2) {
				std::cout << "1 - '+'\n2 - '-'\n";
				std::cin >> r;
			}
			switch (r) {
			case 1:
				arr->AddRow(m, n);
				break;
			case 2:
				arr->SubtractRow(m, n);
				break;
			}
			std::cout << "OK\n";
			break;
		case 5:
			while (m < 0 || m >= arr->GetWidth()) {
				std::cout << "Which column (0 - " << arr->GetWidth() - 1 << ")?\n";
				std::cin >> m;
			}
			while (n < 0 || n >= arr->GetWidth()) {
				std::cout << "Where (0 - " << arr->GetWidth() - 1 << ")?\n";
				std::cin >> n;
			}
			while (r < 1 || r > 2) {
				std::cout << "1 - '+'\n2 - '-'\n";
				std::cin >> r;
			}
			switch (r) {
			case 1:
				arr->AddColumn(m, n);
			case 2:
				arr->SubtractColumn(m, n);
			}
			std::cout << "OK\n";
			break;
		case 6:
			while (m < 0 || m >= arr->GetHeigth()) {
				std::cout << "Which row (0 - " << arr->GetHeigth() - 1 << ")?\n";
				std::cin >> m;
			}
			while (n < 0 || n >= arr->GetHeigth()) {
				std::cout << "And which row (0 - " << arr->GetHeigth() - 1 << ")?\n";
				std::cin >> n;
			}
			arr->SwapRows(m,n);
			std::cout << "OK\n";
			break;
		case 7:
			while (m < 0 || m >= arr->GetWidth()) {
				std::cout << "Which column (0 - " << arr->GetWidth() - 1 << ")?\n";
				std::cin >> m;
			}
			while (n < 0 || n >= arr->GetWidth()) {
				std::cout << "And which column (0 - " << arr->GetWidth() - 1 << ")?\n";
				std::cin >> n;
			}
			arr->SwapColumns(m, n);
			std::cout << "OK\n";
			break;
		case 8:
			for (int i = 0; i < arr->GetHeigth(); i++) {
				for (int j = 0; j < arr->GetWidth(); j++) {
					std::cout << arr->GetIJ(i, j) << ' ';
				}
				std::cout << '\n';
			}
			break;
		case 9:
			std::cout << "OK\n";
			return 0;
		case 0:
			delete arr;
			return 1;
		default:
			break;
		}
	}
}

template <typename T>
Matrix<T>* newMatr() {
	int h = 0, w = 0;
	while (h <= 0) {
		std::cout << "Enter number of rows(heigth)\n";
		std::cin >> h;
	}
	while (w <= 0) {
		std::cout << "Enter number of columns(width)\n";
		std::cin >> w;
	}
	T* list = new T[w * h];
	for (int i = 0; i < h; i++) {
		std::cout << "Enter row #" << i << "\n";
		for (int j = 0; j < w; j++) {
			std::cin >> list[i * w + j];
		}
	}
	Matrix<T>* out = new Matrix<T>(list, h, w);
	if (modify(out)) {
		return 0;
	}
	return out;
}

template <typename T>
void testingInterface() {
	entry<T>* arr = new entry<T>[2];
	int size = 2;
	for (int i = 0; i < size; i++) {
		arr[i].notEmpty = false;
		arr[i].data = 0;
	}
	while (true) {
		int r = 0, c = -1, d = -1, i = 0;
		T item;
		Matrix<T>* ptr = 0;
		disp(arr, size);
		std::cout << "1 - Create matrix\n2 - Modify matrix\n3 - Sum\n4 - Scalar multiply\n5 - Exit\n";
		std::cin >> r;
		std::cout << std::endl;
		switch (r) {
		case 1:
			ptr = newMatr<T>();
			if (ptr) {
				arr = realok(arr, &size);
				while (arr[i].notEmpty) {
					i++;
				}
				arr[i].data = ptr;
				arr[i].notEmpty = true;
			}
			break;
		case 2:
			while (c < 0 || c >= size) {
				std::cout << "Choose matr (0 - " << size - 1 << ")\n";
				std::cin >> c;
			}
			if (!arr[c].notEmpty) {
				std::cout << "This cell is empty! Try another one!\n";
				break;
			}
			if (modify(arr[c].data)) {
				arr[c].data = 0;
				arr[c].notEmpty = false;
			}
			arr = realok(arr, &size);
			break;
		case 3:
			while (c < 0 || c >= size) {
				std::cout << "Choose matrix (0 - " << size - 1 << ")\n";
				std::cin >> c;
			}
			if (!arr[c].notEmpty) {
				std::cout << "This cell is empty! Try another one!\n";
				break;
			}
			while (d < 0 || d >= size) {
				std::cout << "Choose another matrix (0 - " << size - 1 << ")\n";
				std::cin >> d;
			}
			if (!arr[d].notEmpty) {
				std::cout << "This cell is empty! Try another one!\n";
				break;
			}
			ptr = arr[c].data->Sum(arr[d].data);
			if (ptr) {
				arr = realok(arr, &size);
				while (arr[i].notEmpty) {
					i++;
				}
				arr[i].data = ptr;
				arr[i].notEmpty = true;
			}
			break;
		case 4:
			while (c < 0 || c >= size) {
				std::cout << "Choose matrix (0 - " << size - 1 << ")\n";
				std::cin >> c;
			}
			if (!arr[c].notEmpty) {
				std::cout << "This cell is empty! Try another one!\n";
				break;
			}
			std::cout << "Enter number\n>";
			std::cin >> item;
			ptr = arr[c].data->ScalarMult(item);
			if (ptr) {
				arr = realok(arr, &size);
				while (arr[i].notEmpty) {
					i++;
				}
				arr[i].data = ptr;
				arr[i].notEmpty = true;
			}
			break;
		case 5:
			for (int j = 0; j < size; j++) {
				if (arr[j].notEmpty) {
					delete arr[j].data;
				}
			}
			delete arr;
			return;
		default:
			break;
		}
	}
}
