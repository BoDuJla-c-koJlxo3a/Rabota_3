#pragma once
#include "sequence.h"

typedef struct {
	bool notEmpty;
	bool isList;
	Sequence<char>* data;
} entry;

entry* realok(entry* arr, int* size) {
	int count = 0;
	for (int i = 0; i < *size; i++) {
		if (arr[i].notEmpty) {
			count++;
		}
		
	}
	if (count < (*size / 3)) {
		entry* out = new entry[count + 2];
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
		entry* out = new entry[2*(*size)];
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
		entry* out = new entry[*size];
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

void disp(entry* arr, int size) {
	std::cout << '\n';
	for (int i = 0; i < size; i++) {
		std::cout << i << " - ";
		if (arr[i].notEmpty) {
			for (int j = 0; j < arr[i].data->GetLength(); j++) {
				std::cout << arr[i].data->Get(j);
			}
			std::cout << "\n";
		}
		else {
			std::cout << "*empty*\n";
		}
	}
}

int modify(Sequence<char>* arr) {
	while (true) {
		int type = -1;
		char item = 'A';
		int pos = 0;
		std::cout << "1 - Append item\n2 - Prepend\n3 - Insert\n4 - Show yor sequence\n5 - Save\n6 - Delete\n";
		std::cin >> type;
		switch (type) {
		case 1:
			std::cout << "Enter item\n>";
			std::cin >> item;
			arr->Append(item);
			std::cout << "OK\n";
			break;
		case 2:
			std::cout << "Enter item\n>";
			std::cin >> item;
			arr->Prepend(item);
			std::cout << "OK\n";
			break;
		case 3:
			std::cout << "Enter item\n>";
			std::cin >> item;
			std::cout << std::endl;
			while (pos < 0 || pos > arr->GetLength()) {
				std::cout << "Enter position (0 - " << arr->GetLength() << ")\n";
				std::cin >> pos;
			}
			try {
				arr->InsertAt(item, pos);
			}
			catch (int) {
				std::cout << "Index out of range!\n";
				break;
			}
			std::cout << "OK\n";
			break;
		case 4:
			for (int i = 0; i < arr->GetLength(); i++) {
				std::cout << arr->Get(i);
			}
			std::cout << "\n";
			break;
		case 5:
			if (arr->GetLength() == 0) {
				std::cout << "Zero-size sequence will not be saved.\n";
				delete arr;
				return 1;
			}
			std::cout << "OK\n";
			return 0;
		case 6:
			delete arr;
			return 1;
		default:
			break;
		}
	}
}

Sequence<char>* newSeq() {
	int type = 0;
	std::cout << "Type:\n1 - Array\n2 - LinkedList\n";
	std::cin >> type;
	Sequence<char>* out = 0;
	if (type == 1) {
		std::cout << "OK\n";
		out = new ArraySequence<char>();
	}
	if (type == 2) {
		std::cout << "OK\n";
		out = new LinkedListSequence<char>();
	}
	if (type != 1 && type != 2) {
		std::cout << "Wrong input( Sequence will NOT be created!\n";
		return 0;
	}
	if (modify(out)) {
		return 0;
	}
	return out;
}

void testingInterface() {
	entry* arr = new entry[2];
	int size = 2;
	for (int i = 0; i < size; i++) {
		arr[i].notEmpty = false;
		arr[i].data = 0;
	}
	while (true) {
		int r = 0, a = 0, b = 0, c = -1, d = -1, i = 0;
		Sequence<char>* ptr = 0;
		disp(arr, size);
		std::cout << "1 - Create sequence\n2 - Modify sequence\n3 - Get subsequence\n4 - Concat\n5 - Exit\n";
		std::cin >> r;
		std::cout << std::endl;
		switch (r) {
		case 1:
			ptr = newSeq();
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
				std::cout << "Choose sequence (0 - " << size - 1 << ")\n";
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
				std::cout << "Choose sequence (0 - " << size - 1 << ")\n";
				std::cin >> c;
			}
			if (!arr[c].notEmpty) {
				std::cout << "This cell is empty! Try another one!\n";
				break;
			}
			for (int i = 0; i < arr[c].data->GetLength(); i++) {
				std::cout << arr[c].data->Get(i);
			}
			std::cout << "\n";
			std::cout << "Enter: start index, end index\n";
			std::cin >> a >> b;
			try {
				ptr = arr[c].data->GetSubsequence(a, b);
			}
			catch (int w) {
				if (w == -1) {
					std::cout << "Wrong order!\n";
				}
				else {
					std::cout << "Index out of range!\n";
				}
				break;
			}
			arr = realok(arr, &size);
			while (arr[i].notEmpty) {
				i++;
			}
			arr[i].data = ptr;
			arr[i].notEmpty = true;
			break;
		case 4:
			while (c < 0 || c >= size) {
				std::cout << "Choose sequence (0 - " << size - 1 << ")\n";
				std::cin >> c;
			}
			if (!arr[c].notEmpty) {
				std::cout << "This cell is empty! Try another one!\n";
				break;
			}
			while (d < 0 || d >= size) {
				std::cout << "Choose second sequence (0 - " << size - 1 << ")\n";
				std::cin >> d;
			}
			if (!arr[d].notEmpty) {
				std::cout << "This cell is empty! Try another one!\n";
				break;
			}
			ptr = arr[c].data->Concat(arr[d].data);
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
			for (int i = 0; i < size; i++) {
				if (arr[i].notEmpty) {
					delete arr[i].data;
				}
			}
			delete arr;
			return;
		default:
			break;
		}
	}
}
