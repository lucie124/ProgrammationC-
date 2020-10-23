#include <iostream>
#include <string>
using namespace std;


int compteur = 0;
int compteur2 = 0;

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
        compteur +=1;
        compteur2 +=1;
    }

    ~Nombre(){
        cout << "destructeur Nombre" << endl;
        compteur -=1;
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
        compteur +=1;
        compteur2 +=1;
    }

    ~Variable(){
        cout << "destructeur Variable" << endl;
        compteur -=1;
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


class Operation : public Expression {



};