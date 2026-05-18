#include "geometry.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;


pt::pt(){
    x=0;
    y=0;
}

pt::pt(float a, float b){
    x=a;
    y=b;
}

pt pt::operator + (const pt & p) const {
    return pt{x + p.x, y + p.y};
}

pt pt::operator - (const pt & p) const {
    return pt{x - p.x, y - p.y};
}

float pt::cross(const pt & p) const {
    return x * p.y - y * p.x;
}
//formula za vektorski produkt
//   U.x*V.y - U.y*V.x

//   U=B-A=(B.x-A.x , B.y-A.y)
//   V=P-A=(P.x-A.x , P.y-A.y)

//   UxV=(B.x-A.x)*(P.y-A.y) - (B.y-A.y)*(P.x-A.x)

//funkcija za vektorski produkt
//imaš tocku A i tocku B koji cine jednu duzinu AB
//BITNO ZA RAZUMIT
//zanima te je li P s lijeve ili s desne strane te duzine
//ako funkcija vraća pozitivnu vrijednost onda je s lijeve
//ako vraća negativnu vrijednost onda je s desne

float vektorski_produkt(pt A,pt B, pt P){
    return (B.x-A.x)*(P.y-A.y) - (B.y-A.y)*(P.x-A.x);
}

bool je_li_tocka_unutar_poligona(vector<pt> Q, pt P){
    //Ideja je binarnim traženjem suzit moguće područje točke na područje koje određuje kut Q[index],Q[0],Q[Index+1]
    //Nakon što smo suzili treba samo provjeriti je li lijevo ili desno od brida Q[Index]Q[Index+1]
    //Vrhovi su indexirani suprotno smjeru kazaljke na satu
    int n= Q.size();
    //Ako poligon ima samo 2 tocke nemoze imati nijednu tocku u sebi
    if(n<3){
        return false;
    }
    
    //  Situacija 1, P je desno od prvog brida:
    //
    //  Q[n-1]
    //    \*
    //     \*
    //      Q[0]-------Q[1]
    //        \*
    //         \*
    //           P
    if(vektorski_produkt(Q[0],Q[1],P)<0){
        return false;
    }

    //  Situacija 2, P je lijevo od zadnjeg brida:
    //
    //  Q[n-1]
    //    \*
    //     \*
    // P----Q[0]-------Q[1]
    if(vektorski_produkt(Q[0],Q[n-1],P)>0){
        return false;
    }
    //Krecemo traziti u kojem se "trokutu" P nalazi
    //Provjerimo s koje strane vektorskog produkta Q[0] i Q[mid] nalazi
    //I onda pomaknemo low ili high ovisno o tome gdje je P   
    
    int low=1;
    int high=n-1;
    int index=1;
    while(low<=high){
        int mid=(low+high)/2;
        if(vektorski_produkt(Q[0],Q[mid],P)>=0){
            index=mid;
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    //Kada dođemo do situacije kada low>high na indexu index je 1. vrh, a na 
    //indexu index+1 drugi vrh koji trebamo provjeriti
    //P se nalazi u području kuta koji određuju index, 0 i index+1
    //I sada samo trebamo provjeriti nalazi li se unutar poligona ili izvan njega
    //To će vrijediti ako je vektorski produkt pozitivan, ako je s lijeve strane brida
    if(vektorski_produkt(Q[index],Q[index+1],P)>=0){
        return true;
    }
    else{
        return false;
    }
}

float duljina_dvije_tocke(pt A, pt B){
    return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}

float duljina_brida_i_tocke(pt A, pt B, pt P){
//   V=B-A   (B.x-A.x , B.y-A.y)
//   W=P-A   (P.x-A.x , P.y-A.y)
//   
//   duljina_V= sqrt((B.x-A.x)^2+(B.y-A.y)^2)

//   ¤ - skalarni produkt
//   T=(W¤V)/(duljina_V^2)
//   (W.x*V.x + W.y*V.y)/(duljina_V^2)
//   
//   trazeni_vektor=P-(A+T*V)
//   (P.x-(A.x+T*V.x),)
//   trazena_duljina=duljina_dvije_tocke(trazeni_vektor.x,trazeni_vektor.y)

    float Wx=P.x-A.x;
    float Wy=P.y-A.y;
    float Vx=B.x-A.x;
    float Vy=B.y-A.y;

    float duljina_V=duljina_dvije_tocke(A,B);
    //Ako je A==B vrati udaljenost od A do P
    if(duljina_V==0){
        return duljina_dvije_tocke(P,A);
    }
    //Neka fancy šmancy formula koja kao računa T koji nam treba za najbližu točku
    float T=(Wx*Vx + Wy*Vy)/(duljina_V*duljina_V);

    if(T < 0) return duljina_dvije_tocke(P, A);
    if(T > 1) return duljina_dvije_tocke(P, B);

    pt najbliza_tocka;
    najbliza_tocka.x=A.x+T*(Vx);
    najbliza_tocka.y=A.y+T*(Vy);

    
    return duljina_dvije_tocke(P,najbliza_tocka);
}
float minimalna_udaljenost_tocke_i_poligona(vector<pt> Q,pt P){
    if(je_li_tocka_unutar_poligona(Q,P)==true){
        return 0;
    }
    float min = duljina_brida_i_tocke(Q[0], Q[1], P);
    float duljina;
    Q.push_back(Q[0]);    
    for (size_t i = 1; i < Q.size(); i++){
        duljina = duljina_brida_i_tocke(Q[i-1], Q[i], P);
        if (duljina < min) min = duljina;
    }
    return min;
}

void reorder_polygon(vector<pt> & P){
    size_t pos = 0;
    for(size_t i = 1; i < P.size(); i++){
        if(P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x))
            pos = i;
    }
    rotate(P.begin(), P.begin() + pos, P.end());
}

vector<pt> minkowski(vector<pt> P, vector<pt> Q){
    // the first vertex must be the lowest
    reorder_polygon(P);
    reorder_polygon(Q);
    // we must ensure cyclic indexing
    P.push_back(P[0]);
    P.push_back(P[1]);
    Q.push_back(Q[0]);
    Q.push_back(Q[1]);
    // main part
    vector<pt> result;
    size_t i = 0, j = 0;
    while(i < P.size() - 2 || j < Q.size() - 2){
        result.push_back(P[i] + Q[j]);
        auto cross = (P[i + 1] - P[i]).cross(Q[j + 1] - Q[j]);
        if(cross >= 0 && i < P.size() - 2)
            ++i;
        if(cross <= 0 && j < Q.size() - 2)
            ++j;
    }
    return result;
}
vector<pt> negativni_poligon(vector<pt> Q){
    //obrni svaku koordinatu
    vector<pt> temp;
    pt t;
    size_t i=0;
    while(i<Q.size()){
        t=pt (-Q[i].x,-Q[i].y);
        temp.push_back(t);
        i++;
    }
    return temp;
}
float minimalna_udaljenost_2_poligona(vector<pt> P, vector<pt> Q){
    vector<pt> NegativQ= negativni_poligon(Q);
    vector<pt> Minkowski= minkowski(P,NegativQ);
    pt ishodiste=pt(0,0);
    return minimalna_udaljenost_tocke_i_poligona(Minkowski,ishodiste);

}


void ispisi_koordinate_poligona(vector<pt> P){
    for(int i=0;i<P.size();i++){
        cout<<P[i].x<<" "<<P[i].y<<endl;
    }
}

float minimalna_udaljenost_tocke_i_poligona_iznutra(vector<pt> Q,pt P){
    float min = duljina_brida_i_tocke(Q[0], Q[1], P);
    float duljina;
    Q.push_back(Q[0]);    
    for (size_t i = 1; i < Q.size(); i++){
        duljina = duljina_brida_i_tocke(Q[i-1], Q[i], P);
        if (duljina < min) min = duljina;
    }
    return min;
}
float vrijeme_do_polijetanja(vector<pt> P, vector<pt> Q){
    vector<pt> NegativQ= negativni_poligon(Q);
    vector<pt> Minkowski= minkowski(P,NegativQ);
    pt ishodiste=pt(0,0);
    
    return minimalna_udaljenost_tocke_i_poligona_iznutra(Minkowski,ishodiste)-60;
}