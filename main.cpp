//
//  main.cpp
//  Practice
//
//  Created by Robin Singh on 12-02-04.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctime>
#include <boost/thread.hpp>
using namespace std;

void initial(int &height, int &width);
double timer(bool on_or_off);
void kernel_filter(int matrix[], int transform_matrix[], bool dx_matrix);
void print_matrix(int matrix[]);
void compute_min_and_max(int matrix[]);

int height,width;

int main ()
{
    int a;
    bool start=true, stop=false;
    int * matrix;
    int * dx_matrix;
    int * dy_matrix;
    
    height = 0;
    width = 0;
    initial(height, width);
    
    matrix = new int [height*width];
    dx_matrix = new int [height*width];
    dy_matrix = new int [height*width];
    
    delete[] matrix;
    delete[] dx_matrix;
    delete[] dy_matrix;

    cout << "fill with random data \n";
    srand((unsigned)time(0)); 
    for(a=0;a<height*width;a++)
            matrix[a] = rand() % 10;
    
    
    timer(start);
        cout << "kernel filter\n";
        kernel_filter(matrix, dx_matrix, true);    //dx_matrix
        kernel_filter(matrix, dy_matrix, false);   //dy_matrix
    cout << "This is the time taken=" << timer(stop) << endl;

    
    timer(start);
        cout << "compute min and max\n";
        compute_min_and_max(dx_matrix);
        compute_min_and_max(dy_matrix);
    cout << "This is the time taken=" << timer(stop) << endl;

    return 0;
}

//********************************************
//********************************************
//********************************************
//********************************************
//********************************************
//********************************************

void initial(int &height, int &width){
    cout << "Please enter the height : ";
    //cin >> height;
    cout << "Thanks\n";
    cout << "Please enter the width : ";
    //cin >> width;
    cout << "Thanks\n";
    //return height and width
    height = 900;
    width = 900;
}

void print_matrix(int matrix[]){
    int h, x=1;
    for(h=0;h<height*width;h++){
        cout << matrix[h] << " ";
        if (h == (width*x-1)){
            cout << "\n";
            x++;
        }
    }
}

double timer(bool on){
    //Timer Function
    clock_t startClock, tempClock;
    double timeCount;
    
    if (on){
        startClock = clock();
    } else {
        tempClock = clock();
        timeCount = tempClock-startClock;
    }
    return timeCount;
}

void kernel_filter(int matrix[], int transform_matrix[], bool dx_matrix){
    int a, b, c, temp,x1, x2, x3, y1, y2, y3;
    char kernel[3] = {-1, 0, 1};
    int value_array[height*width];
    
    if (dx_matrix){
        c=0;
        b=0;
        for (a=0;a<height*width; a++){
                x1 = kernel[0] * matrix[a-1];
                x2 = kernel[1] * matrix[a];
                x3 = kernel[2] * matrix[a+1];

                value_array[b] = a;
                b++;
                if (a == (width*c)){
                    x1 = 0;
                    c++;
                }
                else if (a == width*c-1){
                    x3 = 0;
                }
            
            transform_matrix[a] = x1 + x2 + x3;
        }
    } else {
        b = 0;
        c = 0;
        for (a=0;a<height*width; a++){
                y1 = kernel[0] * matrix[a-width];
                y2 = kernel[1] * matrix[a];
                y3 = kernel[2] * matrix[a+width];
            
                if (a < width)
                    y1 = 0;
                else if (a >= (height-1)*width)
                    y3 = 0;
            
                b++;
                value_array[b] = matrix[a];
                transform_matrix[a] = y1 + y2 + y3;
        }

    }
}

void compute_min_and_max(int matrix[]){
    int max_val1;
    int min_val1;
    int a;
    min_val1 = matrix[0];
    max_val1 = matrix[0];
    for (a=0;a<width*height; a++){
            if (matrix[a] < min_val1)
                min_val1 = matrix[a];
            if (matrix[a] > max_val1)
                max_val1 = matrix[a];
    }
    cout << "The min value is equal to " << min_val1 << endl;
    cout << "The max value is equal to " << max_val1 << endl;
}