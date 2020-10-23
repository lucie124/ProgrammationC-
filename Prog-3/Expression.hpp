#include <iostream>
#include <string>
using namespace std;

class Expression {

public:
    Expression(){
        cout << "constructeur Expression" << endl;
    }

    virtual ~Expression(){
        cout << "destructeur Expression" << endl;
    }

    // virtual Expression * derivation() = 0;
    friend ostream& operator<<( ostream& out, Expression & e );

    virtual ostream & affiche(ostream & out) const = 0;
};



class Nombre : public Expression {
public:
    Nombre(int n){
        valeur = n;
        cout << "constructeur Nombre" << endl;
    }

    ~Nombre(){
        cout << "destructeur Nombre" << endl;
    }

    ostream & affiche(ostream & out) const{
        return out << valeur;
    }

private:
    int valeur;

};

class Variable : public Expression {

public:
    Variable(string s){
        nom = s;
        cout << "constructeur Variable" << endl;
    }

    ~Variable(){
        cout << "destructeur Variable" << endl;
    }

    ostream & affiche(ostream & out) const{
        return out << nom;
    }

private:
    string nom;

};