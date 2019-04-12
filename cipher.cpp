#include <string>
#include <iostream>
#include <fstream>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"
using namespace std;
#define DES_KEY_LENGTH 16
#define AES_KEY_LENGTH 32

int main(int argc, char** argv)
{
	/**
	 * TODO: Replace the code below	with your code which can SWITCH
	 * between DES and AES and encrypt files. DO NOT FORGET TO PAD
	 * THE LAST BLOCK IF NECESSARY.
	 *
	 * NOTE: due to the incomplete skeleton, the code may crash or
	 * misbehave.
	 */


	string cipherType = argv[1];
	char * cipherKeyString = argv[2];
	string cipherKeyStringSpiteCpp = argv[2];
	string encodingType = argv[3];
	char * inputFileName = argv[4];
	char * outputFileName = argv[5];

	CipherInterface* cipher = NULL; 
	unsigned int cipherKeyLength = cipherKeyStringSpiteCpp.length();
	unsigned char cipherKey [cipherKeyLength];
	unsigned int blockSize = 0;

	// Check if all arguments are present
	if (!outputFileName || !inputFileName) {
		fprintf(stderr, "ERROR [%s %s %d]: Missing arguments\n",	
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}

		// check key length
	for (int i = 0; i < cipherKeyLength; ++i) {

		if (cipherKeyString[i] == '\0')
		{
			fprintf(stderr, "ERROR [%s %s %d]: Invalid key length. Please use an alpha-numeric key of length 16\n",	
			__FILE__, __FUNCTION__, __LINE__);
			exit(-1);
		}
		else {
			cipherKey[i] = cipherKeyString[i];
		}
	}
	

	



	if ((cipherType == "DES" || cipherType == "des") && cipherKeyLength == DES_KEY_LENGTH) {
		/* Create an instance of the DES cipher */	
		cipher = new DES(); 
		blockSize = DES_KEY_LENGTH / 2;
	}
	else if ((cipherType == "AES" || cipherType == "aes") && cipherKeyLength == AES_KEY_LENGTH)  {
		cipher = new AES(); 
		blockSize = AES_KEY_LENGTH / 2;
	}
	else {
		fprintf(stderr, "ERROR [%s %s %d]: Invalid encryption type. Please use DES or AES \n",	
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}



	
	
	
	/* Error checks */
	if(!cipher)
	{
		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}
	
	// cipher->setKey((unsigned char*)cipherKey);
	cipher->setKey(cipherKey);
	
	// Open file
	ifstream inputFileStream;
	inputFileStream.open (inputFileName);
	string str = "";
	int tempInt = 0;
	while (!inputFileStream.eof()) {
		unsigned char * block = new unsigned char [blockSize];
		int i = 0;
		while (!inputFileStream.eof() || i < blockSize) {
			++tempInt;
			unsigned char c = inputFileStream.get();
			cout << c;
			++i;
		}
		cout << endl;
		
	}
	// inputFileStream >> "Writing this to a file.\n";
	cout << tempInt;
	inputFileStream.close();


	/* Perform encryption */
	// string cipherText = cipher->encrypt("hello world");
	
	// /* Perform decryption */
	// cipher->decrypt(cipherText);	
	
	return 0;
}
