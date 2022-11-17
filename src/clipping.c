#include "include/trace.h"
#include "include/clipping.h"

int calcule_code(float x, float y, float xmin, float ymin, float xmax, float ymax)
{
    int code = 0;
    if (x < xmin)
        code += 1;
    if (x > xmax)
        code += 2;
    if (y < ymin)
        code += 4;
    if (y > ymax)
        code += 8;
    return code;
}
void cohen_sutherland(float xa, float ya, float xb, float yb, float xmin, float ymin, float xmax, float ymax, float attribut)
{
    int codeA = calcule_code(xa, ya, xmin, ymin, xmax, ymax);
    int codeB = calcule_code(xb, yb, xmin, ymin, xmax, ymax);
    float m = (yb - ya) / (xb - xa);
    float x, y;
    int codeExt;
    bool accept = false;
    bool fin = false;
    while (!fin)
    {
        if (codeA == 0 && codeB == 0)
        {
            accept = true;
            fin = true;
        }
        else
        {
            if ((codeA & codeB) != 0)
            {
                fin = true;
            }
            else
            {
                codeExt = codeA;
                if (codeA == 0)
                {
                    codeExt = codeB;
                }
                if ((codeExt & 8) == 8)
                {
                    x = xa + (ymax - ya) / m;
                    y = ymax;
                }
                else
                {
                    if ((codeExt & 4) == 4)
                    {
                        x = xa + (ymin - ya) / m;
                        y = ymin;
                    }
                    else
                    {
                        if ((codeExt & 2) == 2)
                        {
                            y = ya + (xmax - xa) * m;
                            x = xmax;
                        }
                        else
                        {
                            if ((codeExt & 1) == 1)
                            {
                                y = ya + (xmin - xa) * m;
                                x = xmin;
                            }
                        }
                    }
                }
                if (codeExt == codeA)
                {
                    xa = x;
                    ya = y;
                    codeA = calcule_code(xa, ya, xmin, ymin, xmax, ymax);
                }
                else
                {
                    xb = x;
                    yb = y;
                    codeB = calcule_code(xb, yb, xmin, ymin, xmax, ymax);
                }
            }
        }
    }
    if (accept)
    {
        xa = floorf(xa);
        xb = floorf(xb);
        ya = floorf(ya);
        yb = floorf(yb);
        bresenhamGeneral(xa, xb, ya, yb);
    }
}