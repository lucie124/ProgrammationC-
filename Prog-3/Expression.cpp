#include "Expression.hpp"
#include <typeinfo>


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

Multiplication::~Multiplication(){
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


/*
** Simplifications
*** Les possibilités de simplification des expressions :
**** Additions et Multiplications des Nombres: ((1 + 1) + (2 * 2)) = 6
**** Additions des Multiplications de meme variable: ((2 * x) + (3 * x)) = (5 * x) ; ((x * y) + (y * x)) = (2 * (x * y))

*** Principe : Appel récursif de la fonction simplifie(), au niveau d'addition et de multiplication, 
    si les deux elements sont nombres, on effectue la simplification.
    Probleme : J'ai pas trouvé la façon pour l'identification du type nombre

*/




Nombre * Nombre::simplifie() const{
    // cout << typeid(this).name() << endl;
    // cout << "Nombre::simplifie" << endl;
    return new Nombre(this->valeur);
}

Variable * Variable::simplifie() const{
    return new Variable(this->nom);
}

Expression * Addition::simplifie() const{
    // cout << typeid(this->somme[0]).name() << endl;
    if(typeid(this->somme[0]) == typeid(Nombre *) && typeid(this->somme[1]) == typeid(Nombre *)){
        // cout << "Addition::simplifie - 2Nombre" << endl;
        return new Nombre(this->somme[0]->valeur + this->somme[1]->valeur);
    }
    else{
        // cout << "Addition::simplifie" << endl;
        return new Addition(this->somme[0]->simplifie(), this->somme[1]->simplifie());
    }
}

Expression * Multiplication::simplifie() const{
    // cout << typeid(this->produit[0]).name() << endl;
    if(typeid(this->produit[0]) == typeid(Nombre *) && typeid(this->produit[1]) == typeid(Nombre *)){
        // cout << "Multiplication::simplifie - 2Nombre" << endl;
        return new Nombre((this->produit[0]->valeur) * (this->produit[1]->valeur));
    }
    else{
        // cout << "Multiplication::simplifie" << endl;
        return new Multiplication(this->produit[0]->simplifie(), this->produit[1]->simplifie());
    }
}