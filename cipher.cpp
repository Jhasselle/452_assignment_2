#include <string>
#include <iostream>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"

#define VALID_KEY_LENGTH 16
using namespace std;

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
	unsigned char cipherKey [VALID_KEY_LENGTH];
	string encodingType = argv[3];
	char * inputFileName = argv[4];
	char * outputFileName = argv[5];
	
	CipherInterface* cipher = NULL; 

	// Check if all arguments are present
	if (!outputFileName || !inputFileName) {
		fprintf(stderr, "ERROR [%s %s %d]: Missing arguments\n",	
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}

	// check key length
	for (int i = 0; i < VALID_KEY_LENGTH; ++i) {

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

	
	if (cipherType == "DES" || cipherType == "des" ) {
		/* Create an instance of the DES cipher */	
		cipher = new DES(); 
	}
	else if (cipherType == "AES" || cipherType == "aes") {
		cipher = new AES(); 
	}
	else {
		fprintf(stderr, "ERROR [%s %s %d]: Invalid encryption type. Please use DES or AES\n",	
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}

	//DES

		
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

	/* Perform encryption */
	// string cipherText = cipher->encrypt("hello world");
	
	// /* Perform decryption */
	// cipher->decrypt(cipherText);	
	
	return 0;
}
