#include <iostream>
using namespace std;

class Fraction {

   public:
        Fraction ();
        Fraction (int);
        Fraction (int, int);
        int getNumer ();
        void setNumer (int);
        int getDenom ();
        void setDenom (int) ;
        double toDecimal ();
        void toString ();
        friend bool isEqual (Fraction , Fraction);
        bool isEqualM (Fraction);
        ~Fraction();
        //overloaded operators
        Fraction operator+(const Fraction &);
        bool operator== (const Fraction &);
        friend ostream& operator<< (ostream&, const Fraction&);
    private:
        int numer;
        int denom;

};
//implementation

bool Equals (Fraction f1, Fraction f2) {
    if ( f1.getNumer() * f2.getDenom() == f2.getNumer() * f1.getDenom() )
        return true;
    else return false;
 }
Fraction :: Fraction (int n, int d ) {
    numer = n ; denom = d;}

void Fraction :: setNumer (int nn) { numer = nn ;}

void Fraction :: setDenom (int dd) { denom = dd ;}

int Fraction :: getNumer () { return numer ; }

int Fraction :: getDenom () {return denom ; }

 double Fraction:: toDecimal () {
   return ((float)numer/ (float)denom) ;}

 void Fraction:: toString () {
    cout <<" The Fraction : "<< numer << '/'<< denom<<endl;  }

///*
// This is the friend function
 bool isEqual (Fraction f1, Fraction f2) {
     cout<<endl<<"----Friend Function Call----";
    if (f1.numer * f2.denom == f2.numer * f1.denom) return true;
    else return false;
 }

bool Fraction :: isEqualM (Fraction f1){
    cout<<endl<<"----Member Function Call----";
   // if (f1.getNumer() * denom == numer * f1.getDenom()) return true;
    if (f1.numer * denom == numer * f1.denom) return true;
    else return false;
}

bool isEqualTP (Fraction f1, Fraction f2) {
     cout<<endl<<"----Third Party Function Call----";
    if (f1.getNumer() * f2.getDenom() == f2.getNumer() * f1.getDenom()) return true;
    else return false;
}



//Driver
int main() {
    Fraction f1 (1,7);
    Fraction f2 (3,14);
    Fraction f3 (3, 21);
    //cout<<" Decimal of F1 :" << f1.toDecimal()<<endl;
    if (f1.isEqualM(f2)) cout<<" f1 equals f2" <<endl;
    if (isEqual(f1,f2)) cout<<" f1 equals f2" <<endl;
    if (isEqualTP(f1,f2)) cout<<" f1 equals f2" <<endl;
    //isEqual(f2,f3);
    //isEqualTP(f2,f3);
   // f1.toString();

    {
     Fraction f2 (5, 6);
     f2.toString();
    }
    return 0;
}