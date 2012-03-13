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

void transpose(unsigned char matrix[], unsigned char matrix_transpose[]);
void kernel_filter(unsigned char matrix[], unsigned char transform_matrix[]);
void fill_with_random_data(unsigned char matrix_dx[], unsigned char matrix_dy[]);
void compute_min_and_max(unsigned char matrix[]);

int height=0;
int width=0;
unsigned char * dy_matrix;

int main (int argc, char ** argv)
{
  	width = atoi(argv[1]);
		height = atoi(argv[2]);

		unsigned char * M; 
    unsigned char * M_transpose; 
    unsigned char * dx_matrix;
    
    M = new unsigned char [height*width];
    M_transpose = new unsigned char [height*width];
    dx_matrix = new unsigned char [height*width];
    dy_matrix = new unsigned char [height*width];
    
    fill_with_random_data(M, M_transpose);
    transpose(M, M_transpose);
    cout << "Apply kernel filter\n";
    boost::thread workerone(kernel_filter, M, dx_matrix);
    boost::thread workertwo(kernel_filter, M_transpose, dy_matrix);
    workerone.join();
    workertwo.join();
    
    delete[] M;
    delete[] M_transpose;
    
    unsigned char * dy_matrix_transpose;
    dy_matrix_transpose = new unsigned char [height*width];
    
    cout << "Untranspose Matrix\n";
    transpose(dy_matrix, dy_matrix_transpose);
    
    cout << "compute min and max\n";
    boost::thread workerthree(compute_min_and_max , dx_matrix);
    boost::thread workerfour(compute_min_and_max, dy_matrix_transpose);
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

void fill_with_random_data(unsigned char matrix_dx[], unsigned char matrix_dy[]){
    int i;
    srand(time(NULL));
    cout << "fill with random data \n";
    for(i=0;i<height*width;i++){
        matrix_dx[i] = rand() % 10;
        matrix_dy[i] = matrix_dx[i];
    }
}

void transpose(unsigned char matrix[], unsigned char matrix_transpose[]){
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

void kernel_filter(unsigned char matrix[], unsigned char transform_matrix[]){
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

void compute_min_and_max(unsigned char matrix[]){
    boost::timer::auto_cpu_timer t("%t sec CPU, %w sec real\n");
    int max_val, min_val, i;
   
    min_val = matrix[0];
    max_val = matrix[0];
    for (i=0;i<width*height; i++){
        if (matrix[i] < min_val)
            min_val = matrix[i];
        if (matrix[i] > max_val)
            max_val = matrix[i];
    }
    cout << "The min value is equal to " << min_val << endl;
    cout << "The max value is equal to " << max_val << endl;
}
