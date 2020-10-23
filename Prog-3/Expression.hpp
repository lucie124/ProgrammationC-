#include <iostream>
#include <string>
using namespace std;


int compteur = 0;
int compteur2 = 0;

class Expression {

public:
    Expression(){
        // cout << "constructeur Expression" << endl;
    }
    virtual ~Expression(){
        // cout << "destructeur Expression" << endl;
    }

    friend ostream& operator<<( ostream& out, Expression const & e );
    virtual ostream & affiche(ostream & out) const = 0;

    virtual Expression * derive(string v) const = 0;
};



class Nombre : public Expression {
public:
    Nombre(int n);
    ~Nombre();
    ostream & affiche(ostream & out) const;
    Nombre * derive( string v ) const;

private:
    int valeur;
};

class Variable : public Expression {
public:
    Variable(string s);
    ~Variable();
    ostream & affiche(ostream & out) const;
    Nombre * derive( string v ) const;

private:
    string nom;
};


class Operation : public Expression {
public:
    Operation(){
        // cout << "constructeur Operation" << endl;
    }
    virtual ~Operation(){
        // cout << "destructeur Operation" << endl;
    }
};

class Addition : public Operation {
public:
    Addition(Expression * a1, Expression * a2);
    ~Addition();
    ostream & affiche(ostream & out) const;
    Expression * derive(string v) const;

private:
    Expression * somme[2];
};

class Multiplication : public Operation {
public:
    Multiplication(Expression * a1, Expression * a2);
    ~Multiplication();
    ostream & affiche(ostream & out) const;
    Expression * derive(string v) const;

private:
    Expression * produit[2];
};
