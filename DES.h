#ifndef __DES_H_
#define __DES_H_

void generateKeys(unsigned long key, unsigned long keys[16]);

unsigned long feistel(unsigned long value, unsigned long key);

unsigned long code_64_bits(unsigned long value, unsigned long key);

unsigned long decode_64_bits(unsigned long value, unsigned long key);

char* code_string(char* string, unsigned long key);

char* decode_string(char* string, unsigned long key);

#endif