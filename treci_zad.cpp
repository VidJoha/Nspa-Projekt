#include <iostream>
#include "geometry.h"

using namespace std;

int main(){
    int broj_poligona, broj_vrhova, broj_zadataka;
    int prvi, drugi;
    float x, y;
    pair <int, int> temp;
    pt temp_point;
    vector<pt> temp_polygon;
    vector<vector<pt>> list;
    vector <pair<int, int>> zadaci;

    cout << "Unesite broj poligona"<<endl;
    cin >> broj_poligona;

    for (int i = 0; i < broj_poligona; i++){
        cout << "Unesite broj vrhova "<< i+1 <<". poligona"<<endl;
        cin >> broj_vrhova;
        for(int j = 0; j < broj_vrhova; j++){
            cout << "Unesite koordinate "<< j+1 <<". vrha " << i+1 << ". poligona"<<endl;
            cin >> x >> y;
            temp_point = pt (x,y);
            temp_polygon.push_back(temp_point);
        }
        list.push_back(temp_polygon);
        temp_polygon.clear();
    }

    cout << "Unesite broj zadataka"<<endl;
    cin >> broj_zadataka;
    cout << "Sada ce se za svaki zadatak izracunati Minkowskijeva suma svih poligona od i-tog do j-tog indeksa. "<<endl;
    for (int i = 0; i < broj_zadataka; i++){
        cout << "Za " << i + 1 << 
        ". zadatak, odredite indekse pocetnog i zavrsnog poligona (0 - "<< broj_poligona - 1 << ")"<< endl;
        cin >> prvi >> drugi;
        temp = pair <int, int> (prvi, drugi);
        zadaci.push_back(temp);
    }

    vector<pt> R;

    for (int i = 0; i < broj_zadataka; i++){
        R = list[zadaci[i].first];
        for(int j = zadaci[i].first + 1; j < zadaci[i].second + 1; j++){
            R = minkowski(R, list[j]);
        }
        cout << "Broj vrhova Minkowskijeve sume " << i + 1 << ". zadatka: " << R.size() << endl;
    }

}