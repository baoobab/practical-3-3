#include "complex.h"
#include "cmath"

TComplex::TComplex() {
}

TComplex::TComplex(const double& r) {
    this->re = r;
    this->im = 0;
}

TComplex::TComplex(const double& r, const double& i) {
    this->re = r;
    this->im = i;
}

bool TComplex::operator==(TComplex c) {
    return (this->re == c.re) && (this->im == c.im);
}

bool TComplex::operator!=(TComplex c) {
    return !(*this == c); // Инвертируем оператор равенства
}

ostream& operator<<(ostream& os, TComplex c) {
    os << "(";
    if (c.im < 0) os << c.re << c.im << "i";
    else os << c.re << "+" << c.im << "i";
    os << ")";

    return os;
}

istream& operator>>(istream& is, TComplex& c) {
    double real, imag;
    if (is >> real >> imag) { // Проверяем успешность ввода
        c.re = real;
        c.im = imag;
    }
    return is;
}

TComplex pow(TComplex base, int exponent) {
    TComplex result(1); // Начальное значение (1 + 0i)

    if (exponent == 0) {
        return result;
    }

    for (int i = 1; i <= abs(exponent); i++) {
        result = result * base; // Умножаем результат на базу
    }

    if (exponent < 0) {
        // Если степень отрицательная, возвращаем обратное значение
        return TComplex(result.re / (result.re * result.re + result.im * result.im),
                        -result.im / (result.re * result.re + result.im * result.im));
    }

    return result;
}

TComplex TComplex::operator*(TComplex c) {
    TComplex rc; // результирующее комплексное число
    rc.re = this->re*c.re - this->im*c.im;
    rc.im = this->re*c.im + this->im*c.re;

    return rc;
}

TComplex TComplex::operator/(TComplex c) {
    TComplex rc; // результирующее комплексное число

    // Вычисляем действительную и мнимую части
    rc.re = (this->re * c.re + this->im * c.im) / (c.re * c.re + c.im * c.im); // (a*c + b*d) / (c^2 + d^2)
    rc.im = (this->im * c.re - this->re * c.im) / (c.re * c.re + c.im * c.im); // (b*c - a*d) / (c^2 + d^2)

    return rc;
}

TComplex TComplex::operator+(TComplex c) {
    TComplex rc; // результирующее комплексное число
    rc.re = this->re+c.re;
    rc.im = this->im+c.im;

    return rc;
}

TComplex& TComplex::operator+=(TComplex c) {
    this->re = this->re+c.re;
    this->im = this->im+c.im;

    return *this;
}

TComplex& TComplex::operator-=(TComplex c) {
    this->re = this->re-c.re;
    this->im = this->im-c.im;

    return *this;
}


// Унарный минус
TComplex& TComplex::operator-() {
    this->re = -this->re;
    this->im = -this->im;
    return *this;
}

// Бинарный минус
TComplex TComplex::operator-(TComplex c) {
    TComplex rc; // результирующее комплексное число
    rc.re = this->re-c.re;
    rc.im = this->im-c.im;

    return TComplex(this->re - c.re, this->im - c.im);
}

// Функция для вычисления модуля
double TComplex::modulus() {
    return sqrt(this->re * this->re + this->im * this->im);
}

// Функция для вычисления аргумента
double TComplex::argument() {
    return atan2(this->im, this->re);
}

// Оператор больше
bool TComplex::operator>(TComplex c) {
    double r1 = this->modulus();
    double r2 = c.modulus();
    if (r1 != r2) {
        return r1 > r2;
    }
    return this->argument() > c.argument();
}

// Оператор меньше
bool TComplex::operator<(TComplex c) {
    double r1 = this->modulus();
    double r2 = c.modulus();
    if (r1 != r2) {
        return r1 < r2;
    }
    return this->argument() < c.argument();
}

// Оператор больше или равно
bool TComplex::operator>=(TComplex c) {
    return !(*this < c); // Если не меньше, то больше или равно
}

// Оператор меньше или равно
bool TComplex::operator<=(TComplex c) {
    return !(*this > c); // Если не больше, то меньше или равно
}

TComplex sqrt(TComplex num) {
    if (num.re == 0 && num.im == 0) {
        return TComplex(0, 0); // Квадратный корень из нуля
    }

    double r = sqrt(num.re * num.re + num.im * num.im); // Модуль
    double sqrtReal = sqrt((r + num.re) / 2);
    double sqrtImag = (num.im >= 0 ? 1 : -1) * sqrt((r - num.re) / 2); // Сигнум для мнимой части

    return TComplex(sqrtReal, sqrtImag);
}
