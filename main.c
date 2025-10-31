#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include "functions.h"

int main(int argc, char * argv[]){
	int c = 0;
	int readFile = 0;
	char * key = NULL;
	char * keyFile = NULL;
	char * msg = NULL;
	char * msgFile = NULL;
	bool isDebug = false;
	bool toDecrypt = false;

	static struct option long_options[] = {
    	{ "debug"    , 0, NULL, 'a' },
    	{ "help"     , 0, NULL, 'h' },
	{ "examples" , 0, NULL, 'e' },
	{ 0, 0, 0, 0}};

	while ((c = getopt_long(argc, argv, "k:m:dhM:K:", long_options, NULL)) != -1){
		switch (c){
			case 'h':
				print_usage(argv);
				return 0;
			case 'k':
				key = optarg;
				break;
			case 'K':
				keyFile = optarg;
				break;
			case 'm':
				msg = optarg;
				break;
			case 'M':
				msgFile = optarg;
				break;
			case 'd':
				toDecrypt = true;
				break;
			case 'a':
				isDebug = true;
				break;
			case 'e':
				print_examples(argv);
				return 0;
			case '?':
				break;
			
			default:
				return -1;
		}
	}

	if ((msg && msgFile) || (key && keyFile)){
		printf("[ERR]: You must select either text or file, but not both.\n");
		printf("[INFO]: Try %s --help.\n", argv[0]);
		return -1;
	}
	if (keyFile){
		readFile = read_file(keyFile, &key);
		/* FILE:
		 * - [X] Abrir arquivo binário
		 * - [X] Ler conteúdo do arquivo
		 * - [ ] Outputar conteúdo pós XOR em um arquivo
		 * 	- [ ] O nome do arquivo deve ser aleatório
		 */	 
	}
	if (msgFile){
		readFile = read_file(msgFile, &msg);
	}
	if (msg && key){
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
			printf("[+] %s\n", decryptedMsg);
			
			// Cleanup 
			free(preparedMsg);
			free(decryptedMsg);
		}
	} else {
		printf("[ERR]: Key and message are required arguments.\n");
		printf("[INFO]: Try %s --help.\n", argv[0]);
		return -1;
	}
	// Cleanup
	if (keyFile){
		free(key);
	}
	if (msgFile){
		free(msg);
	}
	return EXIT_SUCCESS;
}
