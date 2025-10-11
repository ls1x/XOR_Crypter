#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>

char * XOR(char * message, char * key, int msgLength, int keyLength){
	char * out = NULL;
	out = calloc(msgLength,sizeof(char));
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
	printf("%s -k [KEY] -m [MESSAGE] --ml [MSG_LENGTH] --kl [KEY_LENGTH]\n", argv[0]);
	printf("%s -k [KEY] -m [HEX] --ml [MSG_LENGTH] --kl [KEY_LENGTH] -d [DECRYPT]\n", argv[0]);
}

void print_encrypted(char * message, int size){
	for (int i = 0; i < size; i++){
		printf("\\x%x",message[i]);
	}
	printf("\n");
}

int main(int argc, char * argv[]){
	int c = 0;
	char * key = NULL;
	char * keyLengthChar = NULL;
	char * msg = NULL;
	char * msgLengthChar = NULL;
	bool toDecrypt = false;

	static struct option long_options[] = {
    	{ "kl", 1, NULL, 'b' },
    	{ "ml", 1, NULL, 'a' },
    	{ 0, 0, 0, 0}};

	while ((c = getopt_long(argc,argv,"k:m:d", long_options, NULL)) != -1){
		switch (c){
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
				msgLengthChar = optarg;
				break;
			case 'b':
				keyLengthChar = optarg;
				break;
			case '?':
				break;
			
			default:
				return -1;
		}
	}

	if (key && msg && msgLengthChar && keyLengthChar){
		// Preparation
		char *endptr = NULL;
		int msgLength = 0;
		msgLength = strtol(msgLengthChar, &endptr, 10);
		int keyLength = 0;
		keyLength = strtol(keyLengthChar, &endptr, 10);
		
		if (toDecrypt == false){
			char * encMsg = NULL;
			encMsg = XOR(msg, key, msgLength, keyLength);
			print_encrypted(encMsg, msgLength);
			free(encMsg);
		} else {
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
		}
	} else {
		printf("Key, message and their respective sizes are required arguments.\n");
		print_usage(argv);
	}

	return EXIT_SUCCESS;
}
