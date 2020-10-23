#include "Expression.hpp"

ostream& operator<<( ostream& out, Expression const & e )
{
        e.affiche(out);
        return out;
}

/*
** Constructeurs
*/
Nombre::Nombre(int n){
    valeur = n;
    // cout << "constructeur Nombre" << endl;
    // compteur +=1;
    // compteur2 +=1;
}

Variable::Variable(string s){
    nom = s;
    // cout << "constructeur Variable" << endl;
    // compteur +=1;
    // compteur2 +=1;
}

Addition::Addition(Expression * a1, Expression * a2){
    somme[0] = a1;
    somme[1] = a2;
    // cout << "constructeur Addition" << endl;
}

Multiplication::Multiplication(Expression * a1, Expression * a2){
    produit[0] = a1;
    produit[1] = a2;
    // cout << "constructeur Multiplication" << endl;
}

/*
** Destructeurs
*/
Nombre::~Nombre(){
    // cout << "destructeur Nombre" << endl;
    // compteur -=1;
}

Variable::~Variable(){
    // cout << "destructeur Variable" << endl;
    // compteur -=1;
}

Addition::~Addition(){
    // cout << "destructeur Addition" << endl;
}

Multiplication::~Multiplication{
    // cout << "destructeur Multiplication" << endl;
}

/*
** Affichages
*/
ostream & Nombre::affiche(ostream & out) const {
    return out << valeur;
}

ostream & Variable::affiche(ostream & out) const{
    return out << nom;
}

ostream & Addition::affiche(ostream & out) const{
    return out << "(" << *somme[0] << " + " << *somme[1] << ")";
}

ostream & Multiplication::affiche(ostream & out) const{
    return out << "(" << *produit[0] << " * " << *produit[1] << ")";
}

/*
** Derivations
*/
Nombre * Nombre::derive( string v ) const {
    return new Nombre(0);
}

Nombre * Variable::derive( string v ) const {
    if(nom == v){
        return new Nombre(1);
    }
    else{
        return new Nombre(0);
    }
}

Expression * Addition::derive(string v) const{
    return new Addition(somme[0]->derive(v) , somme[1]->derive(v));
}

Expression * Multiplication::derive(string v) const{
    return new Addition(new Multiplication(produit[0]->derive(v), produit[1]), new Multiplication(produit[0], produit[1]->derive(v)));
}
