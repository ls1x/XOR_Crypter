#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>

char * XOR(char * message, char * key, int msgLength, int keyLength){
	char * out = NULL;
	out = calloc(msgLength+1,sizeof(char));
	if (out == NULL){
		printf("The allocator failed (out).\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < msgLength; i++){
		out[i] = message[i] ^ key[i % keyLength];
	}
	return out;
}

void print_usage(char * argv[]){
	printf("XOR_Crypter - Staging v1.0\n");
	printf("%s [-h], [--help]: Prints this.\n", argv[0]);
	printf("%s [-k <KEY>] [-m <MESSAGE>]: Encrypts message using key.\n", argv[0]);
	printf("%s [-k <KEY>] [-m <HEX>] [-d]: Decrypts message using key.\n", argv[0]);
	printf("%s [--debug] enables debug output (key/message size info).\n", argv[0]);	
}

void print_encrypted(char * message, int size){
	for (int i = 0; i < size; i++){
		printf("\\x%02x",message[i]);
	}
	printf("\n");
}

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
		// Preparation
		char *endptr = NULL;
		int msgLength = 0;
		int keyLength = 0;
		int j = 0;
		while(key[j] != '\0'){
			keyLength++;
			j++;
		}
		j = 0;
		if (keyLength < 1){
			printf("KeyLength or msgLength cannot be zero.\n");
			return 0;
		}
		if (toDecrypt == false){
			while(msg[j] != '\0'){
				msgLength++;
				j++;
			}
			if (isDebug == true){
				printf("msgLength: %d\n", msgLength);
				printf("keyLength: %d\n", keyLength);
			}
			char * encMsg = NULL;
			encMsg = XOR(msg, key, msgLength, keyLength);
			print_encrypted(encMsg, msgLength);
			free(encMsg);
		} else {
			// Counting msgLength
			while(msg[j] != '\0'){
				if (msg[j] == 'x'){
					msgLength++;
				}
				j++;
			}
			if (isDebug == true){
				printf("msgLength: %d\n", msgLength);
				printf("keyLength: %d\n", keyLength);
			}
			// Prepare intermediate array
			int * arr = calloc(msgLength, sizeof(int));
			if (arr == NULL){
				printf("The allocation failed (arr).\n");
				exit(EXIT_FAILURE);
			}
			arr[0] = strtol(strtok(msg, "\\x"), &endptr, 16);
			for (int i = 1; i < msgLength; i++){
				arr[i] = strtol(strtok(NULL, "\\x"), &endptr, 16);
			}
			
			// Decryption
			char* decMsg = NULL;
			char* arrChar = calloc(msgLength + 1, sizeof(char));
			if (arrChar == NULL){
				printf("The allocator failed (arrChar).\n");
				exit(EXIT_FAILURE);
			}
			for (int i = 0; i < msgLength; i++){
				arrChar[i] = (char)arr[i];
			}
			decMsg = XOR(arrChar, key, msgLength, keyLength);
			printf("%s\n", decMsg);
			
			// Cleanup 
			free(arr);
			free(arrChar);
			free(decMsg);
		}
	} else {
		printf("Key and message are required arguments.\n");
		printf("Try %s --help.\n", argv[0]);
	}

	return EXIT_SUCCESS;
}
