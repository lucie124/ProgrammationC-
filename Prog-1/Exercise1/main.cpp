//
//  main.cpp
//  Exercise1.1
//
//  Created by zhaoqi_ge on 2020/9/28.
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//Head
#include <iostream>
using namespace std ;
#include <vector> // for vector<>
#include <cstdlib> //for rand()
#include <functional> //for function
#include <forward_list> //for forward_list
//typedef bool (*func) (int,int);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//Functions

//1. Tris

//1.1. Tri par ordre croissant

void print_tab(vector<int> V) //Afficher le tableau
{
    cout << "[ ";
    for(int n : V) {
        cout << n << " ";
    }
    cout << "]" << endl;
    return;
}

void random_tab(vector<int> &V)
{
    srand((unsigned)time(NULL));
    for(int i = 0 ; i < V.size() ; i++)
    {
        V[i] = (int)rand()%(100);
    }
    return;
}

void sort_tab_1(vector<int> &V)
{
    int a = (int)V.size();
    for(int i = 0; i < a - 1; i++)
    {
        for(int j = 0; j < a - 1 - i; j++)
        {
            int temp = 0;
            if(V[j]>V[j+1]){
                temp = V[j];
                V[j] = V[j+1];
                V[j+1] = temp;
            }
        }
    }
    return;
}

void test_1()
{
    std::vector<int> tab(10);
    random_tab(tab);
    cout << "before sorting: ";
    print_tab(tab);
    sort_tab_1(tab);
    cout << "after sorting: ";
    print_tab(tab);
    
    return;
}

//1.2. Tri selon un autre critère

bool lessfc(int a, int b)
{
    bool x = 0;
    if(a<b){
        x = 1;
    }
    return x;
}

bool greaterfc(int a, int b)
{
    bool x = 0;
    if(a>b){
        x = 1;
    }
    return x;
}

void sort_tab_2(vector<int> &V, std::function<bool(int,int)> pfunc)
{
    int a = (int)V.size();
    for(int i = 0; i < a - 1; i++)
    {
        for(int j = 0; j < a - 1 - i; j++)
        {
            int temp = 0;
            if(pfunc(V[j],V[j+1])){
                temp = V[j];
                V[j] = V[j+1];
                V[j+1] = temp;
            }
        }
    }
}

void test_2()
{
    std::vector<int> tab(10);
    random_tab(tab);
    std::vector<int> tab2 = tab;
    cout << "before sorting: ";
    print_tab(tab);
    sort_tab_2(tab, [](int a, int b){return a < b;});
    sort_tab_2(tab2, [](int a, int b){return a > b;});
    cout << "after sorting less: ";
    print_tab(tab);
    cout << "after sorting greater: ";
    print_tab(tab2);
}

//2. Listes

//2.1. Création, affichage

std::forward_list<int> random_list(unsigned int a)
{
    std::forward_list< int > L;
    srand((unsigned)time(NULL));
    for(int i=0; i<a; i++)
    {
        L.push_front((int)rand()%(100));
    }
    return L;
}

void print_list(std::forward_list<int> L)
{
    cout << "[ ";
    for(int l : L) {
        cout << l << " ";
    }
    cout << "]" << endl;
    return;
}

//2.2. Application

std::forward_list<int> map(std::forward_list<int> L, std::function<int(int)> pfunc)
{
    std::forward_list<int> Lfi;
    std::forward_list<int> Lf;
//    Lf.push_front(1);
//    auto prec = Lf.before_begin();
//    auto curr = Lf.begin();
//    Lf.pop_front();
//    for(int l : L) {
//        Lfi.push_front(l);
//    }
    for(int m : L) {
        Lf.push_front(pfunc(m));
    }
    return Lf;
}

void test_3()
{
    std::forward_list<int> L = random_list(10);
    cout << "before mapping: ";
    print_list(L);
    std::forward_list<int> Lf;
    Lf = map(L, [](int a){return a*3;});
    cout << "after mapping: ";
    print_list(Lf);
}

//2.3. Filtrage
std::forward_list<int> filter(std::forward_list<int> L, std::function<bool(int)> pfunc)
{
    std::forward_list<int> Lp;
    for(int l : L) {
        if(pfunc(l)){
            Lp.push_front(l);
        }
    }
    return Lp;
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//Main

int main()
{
    test_3();
    
    return 0;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//Commentaires
/*
 Q: Que constatez-vous en comparant l'ordre des éléments de la liste initiale et celui de la liste résultat ? Pouvez-vous l'expliquer (sous forme de commentaire dans votre fichier source) ? Ne pas essayer d'inverser le résultat, ce point sera repris dans la partie bonus.
 A: Le résultat est normalement inversé, c'est-à-dire que le dernier élément sort de fonction map est le multiple de celui de le premier élément dans la list initiale. C'est en fait du à la construction de la list chaînée, on parcourt la chaîne avec un pointeur. On connaît que le début de la chaîne mais pas la fin, donc on ne peut faire que push_front mais pas after.
    Quand je construiais mon code, j'avais pris en compte de ce point et ai inversé la liste une fois plus. Le résultat de mon code est donc dans l'ordre synchronisé.
 




*/
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//Brouillons



//std::vector<int> tab = {7, 5, 16, 8};
//cout << "tableau content: " ;
//print_tab(tab);
//cout << endl;
//
//random_tab(tab);
//print_tab(tab);


//std::vector<int> tab(10);   // tableau de 10 entiers
//
//std::vector<int> v = {7, 5, 16, 8};
//tab.push_back(25);
//tab.push_back(13);
//for(int n : tab) {
//    cout << n << " ";
//}
//cout << endl;
//int premier = tab[0];       // Accès au premier élément
//cout << "premier variable dans le tableau = " << premier << endl;
//tab[tab.size() - 1] = 5;    // Modification du dernier élément
