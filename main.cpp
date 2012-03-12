//
//  main.cpp
//  Practice
//
//  Created by Robin Singh on 12-02-04.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <boost/thread.hpp>
#include <boost/timer/timer.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctime>

using namespace std;

void initial(int &height, int &width);
void transpose(int matrix[], int transpose_matrix[]);
void untranspose(int matrix[], int transpose_matrix[]);
void kernel_filter(int matrix[], int transform_matrix[]);
void print_matrix(int matrix[]);
void fill_with_random_data(int matrix_dx[], int matrix_dy[]);
void compute_min_and_max(int matrix[]);

int height=0;
int width=0;
int * dy_matrix;
//char kernel[3]={-1,0,1};
int main (int argc, char ** argv)
{
    int * matrix_dx;
    int * matrix_dy;
    int * dx_matrix;
    
    matrix_dx = new int [height*width];
    matrix_dy = new int [height*width];
    dx_matrix = new int [height*width];
    dy_matrix = new int [height*width];
    
    initial(height, width);
    fill_with_random_data(matrix_dx, matrix_dy);
    print_matrix(matrix_dx);
    
    cout << "kernel filter\n";
    // matrix_dy original matrix
    // matrix_dy is turned and placed into dy_matrix
    // now dy_matrix has been transposed 
    // matrix_dy original but junk
    
    cout << "Transpose Matrix \n";
//   transpose(matrix_dy, dy_matrix);
    cout << "boost\n";
//   boost::thread workerone(kernel_filter, matrix_dx, dx_matrix);
//    boost::thread workertwo(kernel_filter, dy_matrix, matrix_dy);
//    workerone.join();
//    workertwo.join();
		kernel_filter(matrix_dx, dx_matrix);
    //kernel_filter(dy_matrix, matrix_dy);
    // kernel filter is applied along a transposed matrix(dy_matrix)
    // values stored in junk_matrix(matrix_dy)
    // matrix_dy is untransposed values place in dy_matrix;
    cout << "Untranspose Matrix\n";
	//untranspose(matrix_dy, dy_matrix);
    cout << "dx_matrix\n";
    print_matrix(dx_matrix);
    cout << "\ndy_matrix\n";
    print_matrix(dy_matrix);
    cout << "compute min and max\n";
        //boost::thread workerthree(compute_min_and_max,dx_matrix);
        //boost::thread workerfour(compute_min_and_max,dy_matrix);
        //workerthree.join();
        //workerfour.join();
	compute_min_and_max(dx_matrix);
	compute_min_and_max(dy_matrix);
    
    delete[] matrix_dx;
    delete[] matrix_dy;
    delete[] dx_matrix;
    delete[] dy_matrix;
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
    height = 4;
    width = 4;
}

void fill_with_random_data(int matrix_dx[], int matrix_dy[]){
    int a;
    cout << "fill with random data \n";
    for(a=0;a<height*width;a++){
        matrix_dx[a] = rand() % 10;
        matrix_dy[a] = matrix_dx[a];
    }
}

void print_matrix(int matrix[]){
    int h, x=1;
    int a = 0;
    for(h=0;h<height*width;h++){
        cout << matrix[a + h] << " ";
        if (h == (width*x-1)){
            cout << "\n";
            x++;
        }
    }
}

void transpose(int transpose_matrix[], int transposed_matrix[]){
	int a, b, c;
	b = 0;
	c = 0;
	for(a=0;a<height*width;a++){
		if(a==(width*c)){
			c++;
			b=0;
		}
		transposed_matrix[a] = transpose_matrix[b*height+(c-1)];	
	}
}

void untranspose(int matrix[], int transpose_matrix[]){
	int a, b, c;
	b = 0;
	c = 0;
	for(a=0;a<height*width;a++){
		if(a==width*c){
			c++;
			b=0;
		}
		transpose_matrix[b*height+(c-1)] = matrix[a];
	}
}

void kernel_filter(int matrix[], int transform_matrix[]){
    //boost::timer::auto_cpu_timer t("%t sec CPU, %w sec real\n");
    int a,b,c,d, x1, x2, x3;
    int kernel[3] = {-1, 0, 1};
    int * previous_matrix;
    int * ahead_matrix;
    
    previous_matrix = new int [height*width];
    ahead_matrix = new int [height*width];
    
    
    c=0;
    for (a=0;a<height*width; a++){
        //cout << matrix[a] << ",";
        previous_matrix[a] = matrix[a-1];
        ahead_matrix[a] = matrix[a+1];
    }
    //cout << "\n\n";
    for (a=0;a<height*width; a++){
        b=a-1;
        d=a+1;
        if (a > 0)
            x1 = kernel[0] * previous_matrix[a];
        x2 = kernel[1] * matrix[a];
        x3 = kernel[2] * ahead_matrix[a];
        
        if (a == width*c){
            x1 = 0;
            c++; //row  #
        } else if (a == width*c-1)
            x3 = 0;
        transform_matrix[a] = x1 + x2 + x3;
    }
    delete[] previous_matrix;
    delete[] ahead_matrix;
}


void compute_min_and_max(int matrix[]){
    //boost::timer::auto_cpu_timer t("%t sec CPU, %w sec real\n");
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
