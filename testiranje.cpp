#include <iostream>
#include "geometry.h"
#include <fstream>
#include <string>
#include <chrono>
using namespace std;

int main(){
    int KojiAlgoritam;
    cout<<"Koji algoritam zelis (1)=efikasni (2)=neefikasni"<<endl;
    cin>>KojiAlgoritam;

    int KojiFile;
    cout<<"Koliko tocaka zelis? (1)=10,(2)=100,(3)=1000,(4)=10000,(5)=100000 (6)=1000000 (7)=10000000"<<endl;
    cin>>KojiFile;
    int BrojTocaka1Poligona;
    int BrojTocaka2Poligona;
    
    
    pt temp;
    float x;
    float y;
    string koordinate;
    vector<pt> P, Q;
    pt ishodiste = pt(0, 0);
        
    
    string File="sample"+to_string(KojiFile)+".txt";
    fstream myFile(File,ios::in);

    myFile>>BrojTocaka1Poligona;
    myFile>>BrojTocaka2Poligona;

    for(int i=0;i<BrojTocaka1Poligona;i++){
        myFile>>x>>y;
        temp=pt(x,y);
        P.push_back(temp);
    }

    for(int i=0;i<BrojTocaka2Poligona;i++){
        myFile>>x>>y;
        temp=pt(x,y);
        Q.push_back(temp);
    }
    
    if(KojiAlgoritam==1){
        auto start = chrono::high_resolution_clock::now();
        vector<pt> R = minkowski(P, negativni_poligon(Q));

        if(je_li_tocka_unutar_poligona(R, ishodiste)){
            auto finish = chrono::high_resolution_clock::now();
            auto microseconds = chrono::duration_cast<chrono::microseconds>(finish-start);
            cout<<"Poligoni se presijecaju"<<endl;
            cout<<"Vrijeme izvedbe "<<microseconds.count()<<" mikrosekundi"<<endl;
        } 
        
        
        else{
            auto finish = chrono::high_resolution_clock::now();
            auto microseconds = chrono::duration_cast<chrono::microseconds>(finish-start);
            cout<<"(Efikasni algoritam) Udaljenost izmedju dva poligona je "<<minimalna_udaljenost_2_poligona(P, Q)<<endl;
            cout<<"Vrijeme izvedbe "<<microseconds.count()<<" mikrosekundi"<<endl;
        } 

    }

    float MinUdaljenost;
    if(KojiAlgoritam==2){
        MinUdaljenost=duljina_dvije_tocke(P[0],Q[0]);
        P.push_back(P[0]);
        Q.push_back(Q[0]);
        vector<pt> R = minkowski(P, negativni_poligon(Q));
        auto start = chrono::high_resolution_clock::now();
        if(je_li_tocka_unutar_poligona(R, ishodiste)){
            auto finish = chrono::high_resolution_clock::now();
            auto microseconds = chrono::duration_cast<chrono::microseconds>(finish-start);
            cout<<"Poligoni se presijecaju"<<endl;
            cout<<"Vrijeme izvedbe "<<microseconds.count()<<" mikrosekundi"<<endl;
        } 
        else{
            for(int i=0;i<P.size()-1;i++){
                for(int j=0;j<Q.size()-1;j++){
                    if(MinUdaljenost>duljina_brida_i_tocke(Q[j],Q[j+1],P[i])){
                        MinUdaljenost=duljina_brida_i_tocke(Q[j],Q[j+1],P[i]);
                    }
                    if(MinUdaljenost>duljina_brida_i_tocke(P[i],P[i+1],Q[j])){
                        MinUdaljenost=duljina_brida_i_tocke(P[i],P[i+1],Q[j]);
                    }
                    if(MinUdaljenost>duljina_dvije_tocke(P[i],Q[j])){
                        MinUdaljenost=duljina_dvije_tocke(P[i],Q[j]);
                    }
                    
                }
            }
        }
        
        auto finish = chrono::high_resolution_clock::now();
        auto microseconds = chrono::duration_cast<chrono::microseconds>(finish-start);
        cout<<"(Spori algoritam) Udaljenost izmedju dva poligona je "<<MinUdaljenost<<endl;
        cout<<"Vrijeme izvedbe "<<microseconds.count()<<" mikrosekundi"<<endl;
    }
    return 0;
}
