#include <iostream>
#include <cmath>
#include <string>
using namespace std;

class Fraction {
public:
    Fraction();
    Fraction(int numerator, int denominator);
    void set(int numerator_, int denominator_ = 1);
    int getNumer ();
    int getDenom ();
    double toDecimal (); 
    void toString ();   
    void reduce();
    bool operator==(const Fraction &other) const;
    bool operator<=(const Fraction &other) const;
    bool operator>=(const Fraction &other) const;
    bool operator<(const Fraction &other) const;
    bool operator>(const Fraction &other) const;
    Fraction &operator=(const Fraction &other);
    Fraction &operator++();
    Fraction &operator--(); 
    int compare(const Fraction &other) const;
private:
    int numerator;
    int denominator;

};

Fraction::Fraction() : numerator(0), denominator(1) {}

Fraction::Fraction(int numberator, int denominator) {
    set(numberator, denominator);
}

void Fraction::set(int numberator_, int denominator_) {
    if (denominator_ != 0) {
        numerator = numberator_;
        denominator = denominator_;
        reduce();
    } 
}

int Fraction :: getNumer () { return numerator ; }

int Fraction :: getDenom () {return denominator ; }

double Fraction:: toDecimal () {
    return ((float)numerator/ (float)denominator) ;
}

void Fraction::reduce() {
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
    int a = numerator;
    int b = denominator;
    int c;
    if (a < 0)
        a = -a;

    while (b > 0) {
        c = a % b;
        a = b;
        b = c;
    }
    numerator /= a;
    denominator /= a;
}
void Fraction:: toString () {
    cout << numerator << '/'<< denominator<<endl;  }
bool Fraction::operator==(const Fraction &other) const {
    return (compare(other) == 0) ? true : false;
}

bool Fraction::operator<(const Fraction &other) const {
    return (compare(other) < 0) ? true : false;
}

bool Fraction::operator>(const Fraction &other) const {
    return (compare(other) > 0) ? true : false;
}

bool Fraction::operator<=(const Fraction &other) const {
    return (compare(other) <= 0) ? true : false;
}

bool Fraction::operator>=(const Fraction &other) const {
    return (compare(other) >= 0) ? true : false;
}

Fraction &Fraction::operator=(const Fraction &other) {
    numerator = other.numerator;
    denominator = other.denominator;
    return *this;
}

Fraction &Fraction::operator++() {
    numerator = numerator + 1;
    return *this;
}
Fraction &Fraction::operator--() {
    numerator = numerator - 1;
    return *this;
}

int Fraction::compare(const Fraction &other) const{
    int fraction =  numerator * other.denominator - other.numerator*denominator;
    if (fraction > 0)
        return 1;
    else if (fraction == 0)
        return 0;
    else
        return -1;}

int main() {
    return 0;
}
