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
    Fraction f1(5, 10);
    Fraction f2 (4,10);
    Fraction f4 (2,5);

    bool f3 = f1.operator>(f2);
    cout<<f1.toDecimal()<<endl;
    f1.toString();
    f2.reduce();
    f2.toString();
    cout<<f2.operator== (f4)<<endl;
    cout<<f2.operator< (f1)<<endl;
    cout<<f4.operator< (f1)<<endl;
    cout<<f4.operator<= (f2)<<endl;
    cout<<f2.operator> (f1)<<endl;
    cout<<f4.operator> (f1)<<endl;
    cout<<f4.operator>= (f2)<<endl;
    Fraction f5;
    f5.operator=(f1);
    f5.toString();
    Fraction f6 (1,3);
    f6.operator++();
    f6.toString();
    Fraction f7 (2,3);
    f7.operator--();
    f7.toString();
    return 0;
}
