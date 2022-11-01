#include <stdbool.h>

int calcule_code (float x, float y, float xmin, float ymin, float xmax, float ymax) {
int code = 0 ;
    if( x < xmin )
        code += 1 ;
    if( x > xmax)
        code += 2 ;
    if( y < ymin )
        code += 4 ;
    if(y > ymax)
        code += 8 ;
    return code ;
}

void cohen_sutherland(float xa, float ya, float xb, float yb, float xmin, float ymin, float xmax, float ymax, float attribut){
    int codeA = calcule_code(xa,ya,xmin,ymin,xmax,ymax);
    int codeB = calcule_code(xb,yb,xmin,ymin,xmax,ymax);
    float m= (yb-ya)/(xb-xa);
    float x,y;
    bool accept=false;
    bool fin= false;
    while(!fin){
        if(codeA==0 && codeB==0){
            accept=true;
            fin=true;
        }
        else{
            int codeExt =codeA;
            if((codeA&codeB)==0){
                codeExt = codeB;
            }
            if((codeExt&8)==1){
                x = xa+(ymax-ya)/m;
                y  = ymax; 
            }
            else{
                if((codeExt&4)==1){
                    y= ya+(xmax-xa)*m;
                    x=xmax;
                }
                else{
                    if((codeExt&2)==1){
                        y= ya+(xmax-xa)*m;
                        x=xmax;
                    }
                    else{
                        if((codeExt&1)==1){
                            y= ya+(xmin-xa)*m;
                            x= xmin;
                        }
                    }
                }
            }
            if(codeExt==codeA){
                xa=x;
                ya=y;
                codeA=calcule_code(xa,ya,xmin,ymin,xmax,ymax);
            }
            else{
                xb=x;
                yb=y;
                codeB=calcule_code(xb,yb,xmin,ymin,xmax,ymax);
            }
        }
    }
    if(accept){
        bresenhamGeneral(xa,)
    }
}