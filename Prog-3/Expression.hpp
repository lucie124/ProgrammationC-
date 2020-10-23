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

    friend ostream& operator<<( ostream& out, Expression const & e );
    virtual ostream & affiche(ostream & out) const = 0;

    virtual Expression * derive(string v) const = 0;
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

    ostream & affiche(ostream & out) const {
        return out << valeur;
    }

    Nombre * derive( string v ) const {
        return new Nombre(0);
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

    Nombre * derive( string v ) const {
        if(nom == v){
            return new Nombre(1);
        }
        else{
            return new Nombre(0);
        }
    }
private:
    string nom;
};