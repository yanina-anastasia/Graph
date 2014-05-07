#include "ComplexNumber.h"

std::ostream& operator<< (std::ostream &out, const ComplexNumber &other) {
	out << other.Re << " + " << other.Im << "i";
	return out;
}

std::istream& operator>> (std::istream &in, ComplexNumber &other) {
	in >> other.Re >> other.Im;
	return in;
}
