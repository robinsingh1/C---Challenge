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
void transpose(int matrix[], int matrix_transpose[]);
void kernel_filter(int matrix[], int transform_matrix[]);
void print_matrix(int matrix[]);
void fill_with_random_data(int matrix_dx[], int matrix_dy[]);
void compute_min_and_max(int matrix[]);

int height=0;
int width=0;
int * dy_matrix;
int main (int argc, char ** argv)
{
    initial(height, width); //Ask user to enter size of the matrix
    		
    int * matrix; 
    int * matrix_transpose; 
    int * dx_matrix;
    
    matrix = new int [height*width];
    matrix_transpose = new int [height*width];
    dx_matrix = new int [height*width];
    dy_matrix = new int [height*width];
    
    fill_with_random_data(matrix, matrix_transpose);
    print_matrix(matrix);
  
    cout << "Transpose Matrix \n";
    //
    transpose(matrix, matrix_transpose);
    print_matrix(dy_matrix);
    
    cout << "kernel filter\n";
    boost::thread workerone(kernel_filter, matrix, dx_matrix);
    boost::thread workertwo(kernel_filter, matrix_transpose, dy_matrix);
    workerone.join();
    workertwo.join();
    
    delete[] matrix;
    delete[] matrix_transpose;
    
    int * dy_matrix_transpose;
    dy_matrix_transpose = new int [height*width];
    // kernel filter is applied along a transposed matrix(dy_matrix)
    // values stored in junk_matrix(matrix_dy)
    // matrix_dy is untransposed values place in dy_matrix;
    
    cout << "Untranspose Matrix\n";
    transpose(dy_matrix, dy_matrix_transpose);
    
    cout << "dx_matrix\n";
    print_matrix(dx_matrix);
    cout << "\ndy_matrix\n";
    print_matrix(dy_matrix);
    
    cout << "compute min and max\n";
    boost::thread workerthree(compute_min_and_max , dx_matrix);
    boost::thread workerfour(compute_min_and_max,dy_matrix);
    workerthree.join();
    workerfour.join();
    
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
    height = 4;
    width = 4;
}

void fill_with_random_data(int matrix_dx[], int matrix_dy[]){
    int i;
    srand(time(NULL));
    cout << "fill with random data \n";
    for(i=0;i<height*width;i++){
        matrix_dx[i] = rand() % 10;
        matrix_dy[i] = matrix_dx[i];
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

void transpose(int matrix[], int matrix_transpose[]){
	int i, b, c; 			/* Counters */
	b = 0;				    /* Column # */
    c = 0;				    /* Row #    */
	for(i=0;i<height*width;i++){
		if(i%width==0){
			b=0;
            c++;
        }
		matrix_transpose[i] = matrix[b*height+(c-1)];
        b++;
	}
}

void kernel_filter(int matrix[], int transform_matrix[]){
    boost::timer::auto_cpu_timer t("%t sec CPU, %w sec real\n");
    int i, x1, x2, x3;
    int kernel[3] = {-1, 0, 1};

    for (i=0;i<height*width; i++){
        x1 = (i%width==0) ? 0 : kernel[0] * matrix[i-1];
        x2 = kernel[1] * matrix[i];
        x3 = (i%width==width-1) ? 0 : kernel[2] * matrix[i+1];

        transform_matrix[i] = x1 + x2 + x3;
    }
}

void compute_min_and_max(int matrix[]){
    boost::timer::auto_cpu_timer t("%t sec CPU, %w sec real\n");
    int max_val, min_val, a;
   
    min_val = matrix[0];
    max_val = matrix[0];
    for (a=0;a<width*height; a++){
        if (matrix[a] < min_val)
            min_val = matrix[a];
        if (matrix[a] > max_val)
            max_val = matrix[a];
    }
    cout << "The min value is equal to " << min_val << endl;
    cout << "The max value is equal to " << max_val << endl;
}
