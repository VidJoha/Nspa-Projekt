#include <iostream>
#include "geometry.h"

using namespace std;

class Node {
public:
    vector<pt> polygon;
    Node* left;
    Node* right;

    Node() {
        left = right = nullptr;
    }
};

class DRQ{
public:
    int N;
    vector<vector<pt>> list;
    Node* tree;

    DRQ(vector<vector<pt>> input){
        list = input;
        N = list.size();
        tree = nullptr;
    }

    void build(){
        tree = build(1, N);
    }

    Node* build(int l, int r){
        Node* cvor = new Node();

        if (l == r){
            cvor->polygon = list[l - 1]; // mozda bez -1 
            return cvor;
        }
    
        int m = (l + r) / 2;
        cvor->left = build(l, m);
        cvor->right = build(m+1, r);

        cvor->polygon = minkowski(cvor->left->polygon, cvor->right->polygon);

        return cvor;
        
    }

    vector<pt> query(int l, int r){
        return query(tree, 1, N, l, r);
    }
    vector<pt> query(Node* node, int a, int b, int l, int r){
        if(!node || a > r || b < l){
            return {};
        }

        if (a >= l && b <= r) return node->polygon;
        
        int m = (a + b) / 2;

        if (r <= m) return query (node->left, a, m, l, r);    

        if(l > m) return query (node->right, m + 1, b, l, r);

        vector<pt> leftTree = query(node->left, a, m, l, r);
        vector<pt> rightTree = query(node->right, m+1, b, l, r);

        if(leftTree.empty()) return rightTree;
        if(rightTree.empty()) return leftTree;

        return minkowski(leftTree, rightTree);
    
    }

    void update(int novi, vector<pt> x){
        update(tree, 1, N, novi, x);
    }

    void update(Node* node, int a, int b, int novi, vector<pt> x){
        if (a == b){
            node->polygon = x;
            return;
        }

        int m = (a + b) / 2;

        if(novi >= a && novi <= m) update(node->left, a, m, novi, x);
        else update(node->right, m + 1, b, novi, x);

        node->polygon = minkowski(node->left->polygon, node->right->polygon);
    }
};

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
        ". zadatak, odredite indekse pocetnog i zavrsnog poligona "<< endl << "(odaberite broj izmedju 1 i "<< broj_poligona << ")"<< endl;
        cin >> prvi >> drugi;
        temp = pair <int, int> (prvi, drugi);
        zadaci.push_back(temp);
    }

    DRQ drq(list);
    drq.build();

    vector<pt> R;

    for (int i = 0; i < broj_zadataka; i++){
        R = drq.query(zadaci[i].first, zadaci[i].second);
        cout << "Broj vrhova Minkowskijeve sume " << i + 1 << ". zadatka: " << R.size() << endl;
    }


}