#include <iostream>
#include "geometry.h"

using namespace std;

int main(){

    int BrojTocaka1Poligona;
    int BrojTocaka2Poligona;
    
    pt temp;
    float x;
    float y;
    string koordinate;
    vector<pt> P, Q;
    pt ishodiste = pt(0, 0);

    cout<<"Unesi koliko tocaka ima poligon zračne luke i poligon oblaka"<<endl;
    cin>>BrojTocaka1Poligona>>BrojTocaka2Poligona;

    for(int i=0;i<BrojTocaka1Poligona;i++){
        cout<<"Unesi koordinate "<<i+1<<". tocke zračne luke"<<endl;
        cin>>x>>y;
        temp=pt(x,y);
        P.push_back(temp);
    }
    for(int i=0;i<BrojTocaka2Poligona;i++){
        cout<<"Unesi koordinate "<<i+1<<". tocke oblaka"<<endl;
        cin>>x>>y;
        temp=pt(x,y);
        Q.push_back(temp);
    }
    
    vector<pt> R = minkowski(P, negativni_poligon(Q));
    
    if(je_li_tocka_unutar_poligona(R, ishodiste)==false){
        cout<<"Oblak nije iznad zračne luke"<<endl;
        cout<<"Vrijeme do mogućeg polaska: "<<0<<endl;
    } 

    else{
        cout<<"Oblak je iznad zračne luke "<<endl;
        cout<<"Vrijeme do mogućeg polaska: "<<vrijeme_do_polijetanja(P,Q)<<" (60 sekundi manje jer je putnik pogledao nakon 1 minute)"<<endl;
    } 

    return 0;
}