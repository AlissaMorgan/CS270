// P1 Assignment
// Author: Alissa Morgan
// Date:   8/28/2002
// Class:  CS270
// Email:  alissa.morgan@colostate.edu

// Include files
#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>

//global arrays
double input[5];
double output[4];

// calculating volume functions
void computeSphere(double radius, double *addressOfVolume)
{
	// Compute area
	double result = (4.0 / 3.0) * 3.141593 * radius * radius * radius;

	// Dereference pointer to return result
	*addressOfVolume = result;
}
void computeCube(double side, double *addressOfVolume)
{
	// Compute area
	double result = side * side * side;

	// Dereference pointer to return result
	*addressOfVolume = result;
}
void computeTetrahedron(double side, double *addressOfVolume)
{
	// Compute area
	double result = 0.117851 * side * side * side;

	// Dereference pointer to return result
	*addressOfVolume = result;
}
void computeCylinder(double radius, double height, double *addressOfVolume)
{
	// Compute area
	double result = 3.141593 * radius * radius * height;

	// Dereference pointer to return result
	*addressOfVolume = result;
}


int main(int argc, char *argv[])
{
	// Check number of arguments
	if (argc != 6) {
        	printf("usage: ./P1 <double> <double> <double> <double> <double>\n");
        	return EXIT_FAILURE;
    	}

    	// Parse arguments
	for (int i = 0; i <= 4; ++i){
		input[i] = atof(argv[i + 1]);
	}

	// Call functions
	computeSphere(input[0], &output[0]);
	computeCube(input[1], &output[1]);
	computeTetrahedron(input[2], &output[2]);
	computeCylinder(input[3], input[4], &output[3]);

	// Print volume	
	printf("SPHERE, radius = %.5f, volume = %.5f.\n", input[0], output[0]);
	printf("CUBE, side = %.5f, volume = %.5f.\n", input[1], output[1]);
	printf("TETRAHEDRON, side = %.5f, volume = %.5f.\n", input[2], output[2]);
	printf("CYLINDER, radius = %.5f, height = %.5f, volume = %.5f.\n", input[3], input[4], output[3]);

	// Return success
	return EXIT_SUCCESS;
}
