#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

struct pt{
    float x, y;

    pt();
    pt(float a, float b);

    pt operator + (const pt & p) const;
    pt operator - (const pt & p) const;

    float cross(const pt & p) const;
};

float vektorski_produkt(pt A,pt B, pt P);

bool je_li_tocka_unutar_poligona(std::vector<pt> Q, pt P);

float duljina_dvije_tocke(pt A, pt B);

float duljina_brida_i_tocke(pt A, pt B, pt P);

float minimalna_udaljenost_tocke_i_poligona(std::vector<pt> Q,pt P);

void reorder_polygon(std::vector<pt> & P);

std::vector<pt> minkowski(std::vector<pt> P, std::vector<pt> Q);

std::vector<pt> negativni_poligon(std::vector<pt> Q);

float minimalna_udaljenost_2_poligona(std::vector<pt> P, std::vector<pt> Q);

void ispisi_koordinate_poligona(std::vector<pt> P);

float minimalna_udaljenost_tocke_i_poligona_iznutra(std::vector<pt> Q, pt P);

float vrijeme_do_polijetanja(std::vector<pt> P, std::vector<pt> Q);
#endif