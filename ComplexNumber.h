#pragma once
#include <iostream>

/*реализация класса комплексных чисел*/

class ComplexNumber {
private:
	double Re;
	double Im;
public:
	ComplexNumber() {
		Re = 0;
		Im = 0;
	}

	ComplexNumber(double number) {
		Re = number;
		Im = number;
	}

	ComplexNumber(double re, double im) {
		Re = re;
		Im = im;
	}

	ComplexNumber(const ComplexNumber &other) {
		Re = other.Re;
		Im = other.Im;
	}

	ComplexNumber(int other) {
		Re = other;
		Im = 0;
	}

	ComplexNumber& operator = (const ComplexNumber &other) {
		Re = other.Re;
		Im = other.Im;
		return *this;
	}

	ComplexNumber& operator = (int other) {
		Re = other;
		Im = 0;
		return *this;
	}
	
	ComplexNumber& operator += (ComplexNumber &other) {
		Re += other.Re;
		Im += other.Im;
		return *this;
	}

	ComplexNumber& operator -= (ComplexNumber &other) {
		Re -= other.Re;
		Im -= other.Im;
		return *this;
	}

	ComplexNumber& operator *= (ComplexNumber &other) {
		Re = Re * other.Re - Im * other.Im;
		Im = Re * other.Im + Im * other.Re;
		return *this;
	}

	ComplexNumber& operator /= (ComplexNumber &other) {
		ComplexNumber temp;
		double r = other.Re * other.Re + other.Im * other.Im;
		temp.Re = (Re * other.Re + Im * other.Im) / r;
		temp.Im = (Im * other.Re - Re * other.Im) / r;
		Re = temp.Re;
		Im = temp.Im;
		return *this;
	}	

	ComplexNumber& operator - () {
		Re = -Re;
		Im = -Im;
		return *this;
	}
	
	ComplexNumber operator + (const ComplexNumber &other) const {
		return ComplexNumber (Re + other.Re, Im + other.Im);
	}

	ComplexNumber operator - (const ComplexNumber &other) const {
		return ComplexNumber (Re - other.Re, Im - other.Im);
	}

	ComplexNumber operator * (const ComplexNumber &other) const {
		return ComplexNumber (Re * other.Re - Im * other.Im, Re * other.Im + Im * other.Re);
	}

	ComplexNumber operator / (const ComplexNumber &other) const {
		ComplexNumber temp;
		double r = other.Re * other.Re + other.Im * other.Im;
		temp.Re = (Re * other.Re + Im * other.Im) / r;
		temp.Im = (Im * other.Re - Re * other.Im) / r;
		return temp;
	}

	bool operator == (const ComplexNumber &other) const {
		return ((Re == other.Re) && (Im == other.Im));
	}

	bool operator != (const ComplexNumber &other) const {
		return (!(*this == other));
	}

	bool operator < (const ComplexNumber & other) const {
		return ((Re < other.Re) && (Im < other.Im));
	}

	bool operator <= (const ComplexNumber & other) const {
		return ((Re < other.Re) && (Im < other.Im) || (*this == other));
	}

	bool operator > (const ComplexNumber & other) const {
		return ((!(*this < other)) && (*this != other));
	}
	
	friend std::ostream & operator<< (std::ostream &, const ComplexNumber &);   
	friend std::istream & operator>> (std::istream &, ComplexNumber &);  
};

std::ostream& operator<< (std::ostream &out, const ComplexNumber &other);
std::istream& operator>> (std::istream &in, ComplexNumber &other);
