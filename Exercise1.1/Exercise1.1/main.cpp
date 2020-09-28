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

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//Functions

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


void test_1()
{
    std::vector<int> tab(10);
    random_tab(tab);
    print_tab(tab);
    return;
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//Main

int main()
{
    test_1();
    
    return 0;
}








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
