//============================================================================
// Name        : pointere_example.cpp
// Author      : Nancy Eisenmenger
//============================================================================

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;


int main()
{

	uint16_t* datamatrix;
	int row = 2157;
	int column = 2112;	
	int j;	
	ifstream::pos_type size;
	char * memblock;
	cout << "test" << endl;
	ifstream datafile;
//	datafile.open ("~/../../../cygdrive/c/Users/Nancy/Documents/Cpp_Project/data/cl_bpan15_t60_12x3_01_avg_05060546.bin", ios::in | ios::binary | ios::ate ); 
	datafile.open ("./cl_bpan15_t60_12x3_01_avg_05060546.bin", ios::in|ios::binary|ios::ate);
	if (datafile.is_open())
	 { 
	size = datafile.tellg();
	memblock = new char [size];
	datafile.seekg (0, ios::beg);
	datafile.read (memblock, size);// assumes that the machine reads little endian
	datafile.close();
	cout << "length of char array is " << size << endl;
	cout << "the complete file content is in memory" << endl;
	datamatrix = new (nothrow) uint16_t [size/2];
	if(datamatrix)
	{
		memcpy(datamatrix, memblock, size);	
		cout << "Data is "; 
/*	for (int i = 0; i < size/2; i++)
		{	
			cout << datamatrix[i] << " ";		
		}*/ 
	}		
	delete[] memblock;
}
  else cout << "Unable to open file";	

	ofstream outfile;
	outfile.open("testout.csv", ios::out);
	for(j = 0; j < size/2; j++)
	{
		outfile << datamatrix[j] ;
		if(j > 1 && (j+1)%column == 0)
		{
		outfile << endl;
	//	cout << j << " ";
		}
		else
		outfile << "	";	
	}
	outfile.close();	
	return 0;
}

