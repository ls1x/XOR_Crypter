#ifndef FUNCTIONS_H
#define FUNCTIONS_H

char * XOR(char * message, char * key, int msgLength, int keyLength);
int get_length(char * message, char * key, int * msgLengthOut, int * keyLengthOut, bool toDecrypt, bool isDebug);
int intermediate_process(int msgLength, char ** preparedMsg, char * message);
void print_usage(char * argv[]);
void print_encrypted(char * message, int size);

#endif
