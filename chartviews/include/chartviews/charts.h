#ifndef CHARTS_H_
#define CHARTS_H_

#include <cassert>
#include <utility>

namespace nav_chartviews{ 

typedef unsigned char uchar; 

struct Coordinate 
{
    int x, y;
};

struct Color
{
    uchar R, G, B;
    friend Color operator+(const Color& lf, const Color& rt){
        auto ret = Color{(lf.R+rt.R)/2, (lf.G+rt.G)/2, (lf.B+rt.B)/2};
        return std::move(ret);
    }
    friend bool operator==(const Color& lf, const Color& rt){
        return (lf.R == rt.R && lf.G == rt.G && lf.B == rt.B); 
    }
};


struct Chart
{
    Chart(int x1, int y1, int x2, int y2, uchar r=0, uchar g=0, uchar b=0)
         : color{r,g,b}   { initPosAB(x1, y1, x2, y2); }
    Chart(int x1, int y1, int x2, int y2, Color c)
         : color{c.R, c.G, c.B} { initPosAB(x1, y1, x2, y2); }         
    Chart(Coordinate pos1, Coordinate pos2, Color c) 
        : color{c.R, c.G, c.B}  { initPosAB(pos1.x, pos1.y, pos2.x, pos2.y); } 
    friend bool operator==(const Chart& lf, const Chart& rt){
        return lf.posL.x == rt.posL.x && lf.posL.y == rt.posL.y 
               && lf.posR.x == rt.posR.x && lf.posR.y == rt.posR.y 
               && lf.color == rt.color;
    }
    bool isPointIn(int X, int Y){ 
        return posL.x <= X && X <= posR.x  && posL.y <= Y && Y<= posR.y;
    }
    Coordinate posL;
    Coordinate posR;
    Color color;
private:
    //sj, make sure to use the points topLeft and bottomRight
    void initPosAB(int x1, int y1, int x2, int y2){
        if(x1 < x2) { posL.x = x1; posR.x = x2 ;}  
        else { posL.x = x2; posR.x = x1 ;}
        if(y1 < y2) { posL.y = y1; posR.y = y2 ;}
        else { posL.y = y2; posR.y = y1; }
    }    
};

class View{
public:
    View(Chart* a, Chart* b=nullptr):pChA(a),pChB(b){ 
        if(a == nullptr && b!=nullptr) {
            pChA = b; pChB = a;  
        }
        assert(pChA!=nullptr);  //sj, make sure pChA not null
    }
    bool DoChartsOverlap(){
        if(pChB==nullptr) return false;
        if(pChA->posR.x < pChB->posL.x || pChB->posR.x < pChA->posL.x)
            return false;
        if(pChA->posR.y < pChB->posL.y || pChB->posR.y < pChA->posL.y)
            return false;
        return true;
    }
    Color GetColor(int X, int Y){
        bool isPInA = pChA->isPointIn(X, Y); 
        bool isPInB = pChB!=nullptr ? pChB->isPointIn(X,Y): false;
        if(isPInA && isPInB) {
            return pChA->color + pChB->color;
        }
        else if(isPInA && !isPInB){
            return pChA->color;
        }
        else if(!isPInA && isPInB){
            return pChB->color;
        }
        else return Color{0,0,0}; //sj default;
    }

private:
    Chart* pChA;
    Chart* pChB;
};

}
#endif