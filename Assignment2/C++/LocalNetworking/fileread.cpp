#include <stdio.h>
#include <iostream>

using namespace std;

// An unsigned char can store 1 Bytes (8bits) of data (0-255)
typedef unsigned char BYTE;

/* As the Shapefile First Four Byte store Integer of 32 bit and
Is of BigEndian Byte order, so to convert first four byte in
proper integer format following readBEInt code is used*/

int main(int argc, char** argv)
{
    const char *Path = argv[1];
	BYTE *buffer;			// Pointer to buffer data
	FILE *file = NULL;		// File pointer data structure

	if ((file = fopen(Path, "r")) == NULL) // Open the file in binary mode using the "rb" format string
	{
		cout << "Could not open specified file" << endl;   // This also checks if the file exists and/or can be opened for reading correctly
	}
	else
    {
		cout << "File opened successfully" << endl;
    }

	// Allocate space of the buffer of about 100000 BYTE
	buffer = new BYTE[100000];

	fread(buffer, 100000, 1, file);

	/* Till now you had accessed file */
	/*Now, for accesing first four bytes*/
	int convert;
    char  *add;
    add = new char[100000];
    int j=-1;

    for (int i = 0; i <= 4; i++) // storing first four byte in add  character array
    {
        j++;
        add[j] = buffer[i];
    }   //converting first four byte to integer type
    cout<<buffer<<endl;
}