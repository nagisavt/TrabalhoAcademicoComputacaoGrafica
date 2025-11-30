#ifndef MAT_H
#define MAT_H

#include <cmath>

struct ponto4D{
    double x, y, z ,w;
    ponto4D(double _x = 0, double _y = 0, double _z = 0, double _w  = 1)
        : x(_x), y(_y), z(_z), w(_w){}
};

struct Matriz4x4{
    double m[4][4];

    Matriz4x4() {
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++) m[i][j] = 0.0;
        }
    }
};

inline Matriz4x4 multplicarMatrizes(const Matriz4x4& A, const Matriz4x4 B){
    Matriz4x4 R;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k <4; k++){
                R.m[i][j] += A.m[i][k] * B.m[k][j];
            }
        }
    }
    return R;
}

inline ponto4D transformarPonto(const Matriz4x4& M, const ponto4D& p){
    ponto4D r;
    r.x = M.m[0][0]*p.x + M.m[0][1]*p.y + M.m[0][2]*p.z + M.m[0][3]*p.w;
    r.y = M.m[1][0]*p.x + M.m[1][1]*p.y + M.m[1][2]*p.z + M.m[1][3]*p.w;
    r.z = M.m[2][0]*p.x + M.m[2][1]*p.y + M.m[2][2]*p.z + M.m[2][3]*p.w;
    r.w = M.m[3][0]*p.x + M.m[3][1]*p.y + M.m[3][2]*p.z + M.m[3][3]*p.w;
    return r;
}

inline Matriz4x4 identidade() {
    Matriz4x4 res;
    for(int i=0; i<4; i++) res.m[i][i] = 1;
    return res;
}

inline Matriz4x4 matrizTranslacao(double dx, double dy, double dz){
    Matriz4x4 res = identidade();
    res.m[0][3] = dx;
    res.m[1][3] = dy;
    res.m[2][2] = dz;
    return res;
}

inline Matriz4x4 matrizEscala(double dx, double dy, double dz){
    Matriz4x4 res = identidade();
    res.m[0][3] = dx;
    res.m[1][3] = dy;
    res.m[2][3] = dz;
    return res;
}

inline Matriz4x4 rotacaoZ(double angGraus){
    Matriz4x4 res = identidade();
    double rad = angGraus * M_PI / 180.0;
    double c = cos(rad);
    double s = sin(rad);
    res.m[0][0] = c; res.m[0][1] = -s;
    res.m[1][0] = s; res.m[1][1] = c;
    return res;
}

inline Matriz4x4 rotacaoX(double angGraus){
    Matriz4x4 res = identidade();
    double rad = angGraus * M_PI / 180.0;
    double c = cos(rad);
    double s = sin(rad);
    res.m[1][1] = c; res.m[1][2] = -s;
    res.m[2][1] = s; res.m[2][2] = c;
    return res;
}

inline Matriz4x4 rotacaoY(double angGraus){
    Matriz4x4 res = identidade();
    double rad = angGraus * M_PI / 180.0;
    double c = cos(rad);
    double s = sin(rad);
    res.m[0][0] = c; res.m[0][2] = -s;
    res.m[2][0] = s; res.m[2][2] = c;
    return res;
}

inline Matriz4x4 projecaoOrtogonal() {
    Matriz4x4 res = identidade();
    res.m[2][2] = 0.0;
    return res;
}

inline Matriz4x4 projecaoPerspectiva(double d){
    Matriz4x4 res = identidade();
    res.m[3][2] = 1.0/d;
    res.m[3][3] = 0.0;
    return res;
}

inline Matriz4x4 matrizViewport(double width, double height){
    Matriz4x4 res = identidade();
    res.m[0][0] = width/ 2.0;
    res.m[1][1] = -height / 2.0;
    res.m[0][3] = width / 2.0;
    res.m[1][3] = height / 2.0;
    return res;
}

inline Matriz4x4 matrizPerspectiva(double d){
    Matriz4x4 res = identidade();
    res.m[3][3] = 0.0;
    if(d != 0){
        res.m[3][2]=1.0/d;
    }
    return res;
}

#endif // MAT_H
