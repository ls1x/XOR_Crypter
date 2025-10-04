#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

char * XOR(char * message, char * key, int * size){
	char * enc = NULL;
	int msgLength = strlen(message);
	int keyLength = strlen(key);

	enc = calloc(msgLength,sizeof(char));

	for (int i = 0; i < msgLength; i++){
		enc[i] = message[i] ^ key[i % keyLength];
	}
	*size = msgLength;
	return enc;
}

void print_usage(char * argv[]){
	printf("%s -k <KEY> -m <Message>\n", argv[0]);
}

int main(int argc, char * argv[]){
	int c = 0;
	char * key = NULL;
	char * msg = NULL;

	while ((c = getopt(argc,argv,"k:m:")) != -1){
		switch (c){
			case 'k':
				key = optarg;
				break;
			case 'm':
				msg = optarg;
				break;
			case '?':
				break;
			default:
				return -1;
		}
	}

	if (key && msg){
		char * encMsg = NULL;
		int size = 0;
		encMsg = XOR(msg, key, &size);
		for (int i = 0; i < size; i++){
			printf("0x%x ",encMsg[i]);
		}
		printf("\n");
	} else {
		printf("Key and message are required arguments.\n");
		print_usage(argv);
	}

	return EXIT_SUCCESS;
}
