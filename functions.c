#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char * XOR(char * message, char * key, int msgLength, int keyLength){
	char * out = NULL;
        out = calloc(msgLength+1,sizeof(char));
        if (out == NULL){
                printf("[ERR]: The allocator failed (XOR - out).\n");
                exit(EXIT_FAILURE);
        }
        for (int i = 0; i < msgLength; i++){
                out[i] = message[i] ^ key[i % keyLength];
        }
        return out;
}

int get_length(char * message, char * key, int * msgLengthOut, int * keyLengthOut, bool toDecrypt, bool isDebug){
	int i = 0;
	int keyLength = 0;
	int msgLength = 0;
	while(key[i] != '\0'){
		keyLength++;
		i++;
	}
	
	i = 0;
	if (toDecrypt == false){
		while(message[i] != '\0'){
			msgLength++;
			i++;
		}
	} else {
		while(message[i] != '\0'){
			if (message[i] == 'x'){
				msgLength++;
			}
			i++;
		}
	}
	if (msgLength < 1){
		printf("[ERR]: MsgLength cannot be zero.\n");
		return -1;
	}
	if (keyLength < 1){
		printf("[ERR]: KeyLength cannot be zero.\n");
		return -1;
	}
	if (isDebug == true){
		printf("MsgLength: %d\n", msgLength);
		printf("KeyLength: %d\n", keyLength);
	}
	*msgLengthOut = msgLength;
	*keyLengthOut = keyLength;
	return 0;
}

int intermediate_process(int msgLength, char ** preparedMsg, char * message){
	// Prepare Intermediate Array
	char *endptr = NULL;
	int * arr = calloc(msgLength, sizeof(int));
	if (arr == NULL){
		printf("[ERR]: The allocator failed (intermediate_process - arr)\n");
		return -1;
	}
	arr[0] = strtol(strtok(message, "\\x"), &endptr, 16);
	for (int i = 1; i < msgLength; i++){
		arr[i] = strtol(strtok(NULL, "\\x"), &endptr, 16);
	}
	
	// Decryption
	char * arrChar = calloc(msgLength + 1, sizeof(char));
	if (arrChar == NULL){
		printf("[ERR]: The allocator failed (intermediate_process - arrChar)\n");
		return -1;
	}
	for (int i = 0; i < msgLength; i++){
		arrChar[i] = (char)arr[i];
	}
	
	// Cleanup
	free(arr);

	// Result
	*preparedMsg = arrChar;
	return 0;
}

void print_usage(char * argv[]){
        printf("XOR_Crypter - Stable v3.3\n");
        printf("%s [-h], [--help]: Prints this.\n", argv[0]);
        printf("%s [-k <KEY>] [-m <MESSAGE>]: Encrypts message using key.\n", argv[0]);
        printf("%s [-k <KEY>] [-m <HEX>] [-d]: Decrypts message using key.\n", argv[0]);
        printf("%s [--debug] enables debug output (key/message size information).\n", argv[0]);
}

void print_encrypted(char * message, int size){
        for (int i = 0; i < size; i++){
                printf("\\x%02x",message[i]);
        }
        printf("\n");
}
