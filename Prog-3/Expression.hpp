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
public:
    Operation(){
        cout << "constructeur Operation" << endl;
    }

    virtual ~Operation(){
        cout << "destructeur Operation" << endl;
    }

    // friend ostream& operator<<( ostream& out, Expression const & e );
    // virtual ostream & affiche(ostream & out) const = 0;

    // virtual Expression * derive(string v) const = 0;

};

class Addition : public Operation {
public:
    Addition(Expression * a1, Expression * a2){
        somme[0] = a1;
        somme[1] = a2;
        cout << "constructeur Addition" << endl;
    }

    ~Addition(){
        cout << "destructeur Addition" << endl;
    }

    ostream & affiche(ostream & out) const{
        return out << "(" << *somme[0] << " + " << *somme[1] << ")";
    }
    
    Expression * derive(string v) const{
        return new Addition(somme[0]->derive(v) , somme[1]->derive(v));
    }

private:
    Expression * somme[2];
};

class Multiplication : public Operation {
public:
    Multiplication(Expression * a1, Expression * a2){
        produit[0] = a1;
        produit[1] = a2;
        cout << "constructeur Multiplication" << endl;
    }
    
    ~Multiplication(){
        cout << "destructeur Multiplication" << endl;
    }

    ostream & affiche(ostream & out) const{
        return out << "(" << *produit[0] << " * " << *produit[1] << ")";
    }
private:
    Expression * produit[2];
};