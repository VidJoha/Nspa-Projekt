#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "geometry.h"

using namespace std;

int main(){
    
    fstream myFile;
    int KolikoTocaka;
    string NazivFilea;

    
    float a;
    for(int i=1;i<8;i++){
        KolikoTocaka=pow(10,i);
        NazivFilea="sample"+to_string(i)+".txt";
        myFile.open(NazivFilea, ios::out);
        if(myFile.is_open()){
            myFile << KolikoTocaka << " "<<KolikoTocaka <<endl; 
        }
        for(int j=0;j<KolikoTocaka;j++){
            a=static_cast<float>(j)/KolikoTocaka;
            
            myFile << 10*cos((a)*2*M_PI) << " " << 10*sin((a)*2*M_PI)<<" ";
        }
        myFile <<endl;
        for(int j=0;j<KolikoTocaka;j++){
            a=static_cast<float>(j)/KolikoTocaka;
            
            myFile << 10*cos((a)*2*M_PI) << " " << 30+10*sin((a)*2*M_PI)<<" ";
        }
        myFile.close();

    }
    
    cout<<"Sve ispisano"<<endl;
    

    return 0;
}
