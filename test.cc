#include <iostream>
#include <math.h>
using namespace std;

double a=0,b=0,c=0,d=0,e=0,f=0;
//y = kx + c
double resolution_height = 9;
double resolution_length = 16;
double resolution_diag = sqrt(resolution_height*resolution_height + resolution_length*resolution_length);
double resolution = resolution_height/resolution_length;

double y1_k = 0;
double y1_c = 0;

double y2_k = 0;
double y2_c = 0;

double y3_k = 0;
double y3_c = 0;

double y4_k = 0;
double y4_c = 0;

//left distance
double height_k = 0;
double height_c = 0;

double length_k = 0;
double length_c = 0;
//right distance
double right_height_k = 0;
double right_height_c = 0;

double right_length_k = 0;
double right_length_c = 0;

double c_ef = 0;
double a_ef = 0;
double a_ce = 0;
double f_ce = 0;

void getData(double a_arg, double b_arg, double c_arg, double d_arg, double e_arg, double f_arg)
{
    a=a_arg, b=b_arg, c=c_arg, d=d_arg, e=e_arg, f=f_arg;
    y1_k = (d-c)/e;
    y1_c = c;

    y2_k = (-c/a);
    y2_c = c;

    y3_k = f/(b-a);
    y3_c = -f*a/(b-a);

    y4_k = -(d-f)/(b-e);
    y4_c = d - (e*(f-d))/(b-e);

//ac上的点与上边长cd垂直距离H的函数H=kx+c的k值 
    height_k = y1_k - y2_k;
    height_c = y1_c - y2_c;

//ac上的点与右边长垂直距离L的函数L=kx+c的k值 
    length_k = (a*c - c*b - a*f)/(a*f);
    length_c = a + c*(b-a)/f;

//af上的点与上边长ef垂直距离H的函数H=kx+c的k值 
    right_height_k = y4_k - y3_k;
    right_height_c = y4_c - y3_c;

//af上的点与左边长垂直距离L的函数L=kx+c的k值 
    right_length_k = 1+(a*f)/(c*(b-a));
    right_length_c = -(a*a*f)/(c*(b-a)) - a;

//c点经过斜率为k(resolution)的线到与ef点相交的坐标x,k=resolution
    double c_ef_x = (d - e*(f-d)/(b-e) - c)/(resolution + (d-f)/(b-e));
//a点经过斜率为k(resolution)的线到与ef点相交的坐标x,k=resolution
    double a_ef_x = (d - e*(f-d)/(b-e) + a*resolution)/(resolution + (d-f)/(b-e));
    c_ef = c_ef_x * resolution_diag / resolution_length;
    a_ef = a_ef_x * resolution_diag / resolution_length;
//    cout << "c_ef is " << c_ef << " , a_ef is " << a_ef << endl;

    double a_ce_x = (a*resolution-c)/((d-c)/e + resolution);
    double f_ce_x = (resolution*b + f - c)/((d-c)/e + resolution);
    a_ce = (a - a_ce_x) * resolution_diag / resolution_length;
    f_ce = (b - f_ce_x) * resolution_diag / resolution_length;
//    cout << "a_ce is " << a_ce << " , f_ce is " << f_ce << endl;
}

double f1(double x)
{
    return y1_k * x + y1_c;
}
double f2(double x)
{
    return y2_k * x + y2_c;
}
double f3(double x)
{
    return y3_k * x + y3_c;
}
double f4(double x)
{
    return y4_k * x + y4_c;
}


double getHeight(double x)
{
    return height_k * x + height_c;
}

double getLength(double x)
{
    return length_k * x + length_c;
}

double getDiag(double x)
{
    return c_ef + (x/a)*(a_ef-c_ef);
}

double right_getHeight(double x)
{
    return (y4_k * x + y4_c) - (y3_k * x + y3_c);
}

double right_getLength(double x)
{
    return right_length_k * x + right_length_c;
}

double right_getDiag(double x)
{
    return a_ce + (x-a)/(b-a)*(f_ce-a_ce);
}

double getMin(double x, double y, double z)
{
    return x<y?(x<z?x:z):(y<z?y:z);
}
void printPoint(double x, double smax)
{
    if(x<a)
    {
        printf("(%f, %f), (%f, %f), (%f, %f), (%f, %f) \n\n", x, f2(x)+smax*resolution_height,
                        x,f2(x),
                        x+smax*resolution_length, f2(x),
                        x+smax*resolution_length, f2(x)+smax*resolution_height);
    }
    else
    {
        printf("(%f, %f), (%f, %f), (%f, %f), (%f, %f)\n\n", x-smax*resolution_length, f3(x)+smax*resolution_height,
                        x-smax*resolution_length, f3(x),
                        x,f3(x),
                        x,f3(x)+smax*resolution_height);
    }
}

void setResolution(double height, double length)
{
    resolution_height = height;
    resolution_length = length;
    resolution_diag = sqrt(resolution_height*resolution_height + resolution_length*resolution_length);
    resolution = resolution_height/resolution_length;
}
int main(int argc, char** argv)
{
    cout << "main start" << endl;
    double smax =0;
    double tmp_min = 0;
    double height = 0;
    double length = 0;
    double diag = 0;
    double pos_x = 0;
    double pos_y = 0;
    double area = 0;
    //fill a,b,c,d,e,f and get square
    getData(7, 10, 9, 10, 4, 6);
    for(double x = 0; x < b; x+= b/1000)
    {
        if(x < a)
        {
            height = getHeight(x);
            length = getLength(x);
            diag = getDiag(x);
            pos_y = f2(x);
        }else
        {
            height = right_getHeight(x);
            length = right_getLength(x);
            diag = right_getDiag(x);
            pos_y = f3(x);
        }
        tmp_min = getMin(height/resolution_height, length/resolution_length, diag/resolution_diag);
        if(smax < tmp_min)
        {
            smax = tmp_min;
            area = smax * smax * resolution_height * resolution_length;
            pos_x = x;
            //cout << "SQUARE [" << smax * resolution_height << " * " << smax * resolution_length << "] , S: " << area << endl;
            //printPoint(x, smax);
        }
    }
            cout << "SQUARE [" << smax * resolution_height << " * " << smax * resolution_length << "] , S: " << area << endl;
            printPoint(pos_x, smax);
    return 0;
}
