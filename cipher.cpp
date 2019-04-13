#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
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
	 * THE LAST BLOCK IF NECESSARY.if (!cipher->setKey(cipherKey))
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
			cipherKey[i] = cipherKeyString[i];
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
	if (!cipher->setKey(cipherKey)) {
		fprintf(stderr, "ERROR [%s %s %d]:  Invalid cipher key!\n",	
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}
	
	// Open file
	ifstream inputFileStream;
	ofstream outputFileStream;
	inputFileStream.open(inputFileName);
	int fileSize = inputFileStream.tellg();

	unsigned char * blockCiphertext = new unsigned char [blockSize];
	stringstream sstr;
	unsigned char c;


	int tempInt = 0;

	while (inputFileStream >> c) {
		unsigned char * blockPlaintext = new unsigned char [8] ; 
		fill(blockPlaintext, blockPlaintext + 8, ' ');
		blockPlaintext[0] = c;
		cout << blockPlaintext << endl;
		for (int i = 1; i < 8; ++i) {
			if (inputFileStream >> c && !inputFileStream.eof()) {
				blockPlaintext[i] = c;
				cout << blockPlaintext << endl;
			}
			else {
				break;
			}
		}
		cout << endl;

		 
		if (encodingType == "ENC") {
			cout << "ENC: " << tempInt;
			tempInt++;


			blockCiphertext = cipher->encrypt(blockPlaintext);
		}
		else {
			cout << "DEC:" << tempInt;
			tempInt++;


			blockCiphertext = cipher->decrypt(blockPlaintext);
		}
		sstr << blockCiphertext;
		delete [] blockPlaintext;
	}
					
	


	inputFileStream.close();
	outputFileStream.open(outputFileName);
	outputFileStream << sstr.rdbuf();
	outputFileStream.close();


	delete [] blockCiphertext;
	
	return 0;
}
