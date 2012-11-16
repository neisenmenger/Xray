//============================================================================
// Name        : pointere_example.cpp
// Author      : Nancy Eisenmenger
//============================================================================

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int testEndianess();

int main()
{

	uint16_t* datamatrix; // pointer to matrix of loaded data
	int row = 2157; // rows of data
	int column = 2112; // columns of data	
	int j, Endianess;	
	ifstream::pos_type size;
	char * memblock; // char array into which we read binary file
	ifstream datafile;

	Endianess = testEndianess(); // tests to see if the computer uses little or big endian format for binary data

	//	datafile.open ("~/../../../cygdrive/c/Users/Nancy/Documents/Cpp_Project/data/cl_bpan15_t60_12x3_01_avg_05060546.bin", ios::in | ios::binary | ios::ate ); 
	datafile.open ("./cl_bpan15_t60_12x3_01_avg_05060546.bin", ios::in|ios::binary|ios::ate);
	if (datafile.is_open())
	{ 
		// reads in data from binary file
		size = datafile.tellg();
		memblock = new char [size];
		datafile.seekg (0, ios::beg);
		datafile.read (memblock, size);
		datafile.close();
		cout << "length of char array is " << size << endl;
		cout << "the complete file content is in memory" << endl;
		// creates an array of unsigned 16 bit integers into which binary data is copied from the char array
		datamatrix = new (nothrow) uint16_t [size/2];
		if(datamatrix)
		{
			if(Endianess == 0) // if little Endian
			{
			memcpy(datamatrix, memblock, size);	
			cout << "Size char is: " << sizeof(char) << " and size of uint16_t is: " << sizeof(uint16_t) << endl;
			cout << "Data is "; 
			}
			else // if big Endian
			cout << "Ooops, this computer uses big Endian. You'll have to modify the code before the data file can be read properly." << endl;// you need to reverse the character arrays before the memcpy() step.
		/*	for (int i = 0; i < size/2; i++)
			{	
				cout << datamatrix[i] << " ";		
			}*/ 
		}		
	delete[] memblock; // now that data is in an int array, deletes char array
	}	
  	else cout << "Unable to open file";	

	// debugging code: outputs a test file to be compared with a tab delimited text file
	ofstream outfile;
	outfile.open("testout.csv", ios::out);
	for(j = 0; j < size/2; j++)
	{
		outfile << datamatrix[j] ;
	//	if(j!=(size/2)  && (j+1)%column == 0)
		if(j!=(size/2)  && (j+1)%row == 0)
		{
		outfile << endl;
	//	cout << "j is " <<j << " and data is: " << datamatrix[j] << endl;
		}
		else
		outfile << "	";	
	}
	outfile.close();	
	return 0;
}


// Detects Endianess (little or big) of the system
// Returns 0 for little Endian and 1 for big Endian
int testEndianess()
{
	uint16_t i = 1;
	int j;
	char *c = (char*)&i;
	if (*c)
	{
		cout << "Little endian"<< endl;
		j = 0;
	}
	else
	{
		cout << "Big endian"<< endl;
		j = 1;
	}
	// getchar();
	return j;
}
