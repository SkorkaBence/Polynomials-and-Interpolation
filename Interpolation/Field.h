#ifndef H_FIELD
#define H_FIELD

#include <iostream>

template<int N>
class Field {
private:
	unsigned int value;
public:
	Field() { this->setValue(0); }
	Field(int def) { this->setValue(def); }

	void setValue(int v) {
		while (v < 0) {
			v += N;
		}
		unsigned int uv = v;
		value = uv % N;
	}

	int getValue() const {
		return value;
	}

	void operator = (int v) {
		this->setValue(v);
	}

	void echo(std::ostream& out) {
		out << value;
	}

	friend std::ostream& operator << (std::ostream& out, const Field<N>& v) {
		out << v.value;
		return out;
	}

	friend std::istream& operator >> (std::istream& in, Field<N>& v) {
		int dt;
		in >> dt;
		v.setValue(dt);
		return in;
	}

	Field<N> operator + (const Field<N>& t) {
		Field<N> f(value + t.getValue());
		return f;
	}

	void operator += (const Field<N>& t) {
		this->setValue(value + t.getValue());
	}

	Field<N> operator - (const Field<N>& t) {
		Field<N> f(value - t.getValue());
		return f;
	}

	void operator -= (const Field<N>& t) {
		this->setValue(value - t.getValue());
	}

	Field<N> operator * (const Field<N>& t) {
		Field<N> f(value * t.getValue());
		return f;
	}

	void operator *= (const Field<N>& t) {
		this->setValue(value * t.getValue());
	}

	Field<N> operator / (const Field<N>& t) {
		Field<N> f(value / t.getValue());
		return f;
	}

	void operator /= (const Field<N>& t) {
		this->setValue(value / t.getValue());
	}

	bool operator == (const Field<N>& t) {
		return this->value == t.getValue();
	}

	bool operator != (const Field<N>& t) {
		return this->value != t.getValue();
	}

	bool operator < (const Field<N>& t) {
		return this->value < t.getValue();
	}

	bool operator > (const Field<N>& t) {
		return this->value > t.getValue();
	}

	bool operator <= (const Field<N>& t) {
		return this->value <= t.getValue();
	}

	bool operator >= (const Field<N>& t) {
		return this->value >= t.getValue();
	}

	Field<N> operator ++ () {
		this->setValue(value + 1);
		return this;
	}

	Field<N> operator -- () {
		this->setValue(value - 1);
		return this;
	}
};

#endif
