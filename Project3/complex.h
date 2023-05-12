#pragma once
#include <iostream>

struct Complex {

	float re;
	float im;

	Complex(float r, float i) : re(r), im(i) {}

	Complex() {
		re = 0;
		im = 0;
	}
	
	Complex(int num) {
		re = (float)num;
		im = 0;
	}

	Complex(float num) {
		re = num;
		im = 0;
	}

	Complex operator+ (Complex& other) {
		return Complex(re + other.re, im + other.im);
	}

	Complex operator* (Complex& other) {
		return Complex(re*other.re - im*other.im, im*other.re + re*other.im);
	}

	friend std::ostream& operator<< (std::ostream& out, const Complex& num)
	{
		out << "(" << num.re << ", " << num.im << ')';
		return out;
	}

	friend std::istream& operator>> (std::istream& in, Complex num)
	{
		in >> num.re;
		in >> num.im;
		return in;
	}

};