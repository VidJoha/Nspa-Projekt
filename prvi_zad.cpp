#include <iostream>
#include "geometry.h"

using namespace std;

int main(){
    
    int BrojTocaka1Poligona;
    int BrojTocaka2Poligona;

    cout<<"Unesi koliko tocaka ima 1. poligon"<<endl;
    cin>>BrojTocaka1Poligona;
    cout<<"Unesi koliko tocaka ima 2. poligon"<<endl;
    cin>>BrojTocaka2Poligona;

    pt temp;
    float x;
    float y;
    string koordinate;
    vector<pt> P, Q;
    pt ishodiste = pt(0, 0);
    
    for(int i=0;i<BrojTocaka1Poligona;i++){
        cout<<"Unesi koordinate "<<i+1<<". tocke 1. poligona"<<endl;
        cin>>x>>y;
        temp=pt(x,y);
        P.push_back(temp);
    }
    for(int i=0;i<BrojTocaka2Poligona;i++){
        cout<<"Unesi koordinate "<<i+1<<". tocke 2. poligona"<<endl;
        cin>>x>>y;
        temp=pt(x,y);
        Q.push_back(temp);
    }
    
    vector<pt> R = minkowski(P, negativni_poligon(Q));

    ispisi_koordinate_poligona(minkowski(P,Q));

    if(je_li_tocka_unutar_poligona(R, ishodiste)) cout<<"Poligoni se presijecaju"<<endl;

    else cout<<"Udaljenost izmedju dva poligona je "<<minimalna_udaljenost_2_poligona(P, Q)<<endl;

    return 0;
}
