#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include "functions.h"

int main(int argc, char * argv[]){
	int c = 0;
	char * key = NULL;
	char * msg = NULL;
	bool isDebug = false;
	bool toDecrypt = false;

	static struct option long_options[] = {
    	{ "debug", 0, NULL, 'a' },
    	{ "help", 0, NULL, 'h' },
	{ 0, 0, 0, 0}};

	while ((c = getopt_long(argc, argv, "k:m:dh", long_options, NULL)) != -1){
		switch (c){
			case 'h':
				print_usage(argv);
				return 0;
			case 'k':
				key = optarg;
				break;
			case 'm':
				msg = optarg;
				break;
			case 'd':
				toDecrypt = true;
				break;
			case 'a':
				isDebug = true;
				break;
			case '?':
				break;
			
			default:
				return -1;
		}
	}

	if (key && msg){
		int msgLength = 0;
		int keyLength = 0;
		if (get_length(msg, key, &msgLength, &keyLength, toDecrypt, isDebug) == -1){
			printf("[ERR]: Key or message cannot be empty.\n");
			return -1;
		}
		if (toDecrypt == false){
			char * encryptedMsg = NULL;
			encryptedMsg = XOR(msg, key, msgLength, keyLength);
			print_encrypted(encryptedMsg, msgLength);
			free(encryptedMsg);
		}
		if (toDecrypt == true) {
			char * preparedMsg = NULL;
			char * decryptedMsg = NULL;
			intermediate_process(msgLength, &preparedMsg, msg);
			decryptedMsg = XOR(preparedMsg, key, msgLength, keyLength);
			printf("%s\n", decryptedMsg);
			
			// Cleanup 
			free(preparedMsg);
			free(decryptedMsg);
		}
	} else {
		printf("Key and message are required arguments.\n");
		printf("Try %s --help.\n", argv[0]);
	}

	return EXIT_SUCCESS;
}
