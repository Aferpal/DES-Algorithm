#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"./DES.h"

//s tables
static short s_tables[8][64] = {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7, 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8, 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0, 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
                                {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10, 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5, 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15, 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
                                {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8, 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1, 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7, 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
                                {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15, 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9, 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4, 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
                                {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9, 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6, 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14, 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
                                {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11, 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8, 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6, 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
                                {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1, 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6, 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2, 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
                                {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7, 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2, 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8, 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
                                };


unsigned long permutate(unsigned long value, short* perm_table, int length, int or_length){
    unsigned long res = 0;
    for( int i = 0; i < length; i++){
        res = res << 1;
        res = res | ( 0x1 & ( value >> ( or_length - perm_table[i] ) ) );
    } 
    return res;
}

void generateKeys(unsigned long key, unsigned long keys[16]){

    short pc_1_list[] = {57, 48, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};
    short pc_2_list[] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};
    short left_rotation[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
    
    //initial permutation pc-1
    unsigned long pc1 = permutate(key, pc_1_list, 56, 64);
    
    //split key into two 28 bits
    unsigned long l0 = (pc1 >> 28) & 0xfffffff;
    unsigned long r0 = pc1 & 0xfffffff;


    for( int i = 0; i < 16; i++){
        //right and left rot
        
        l0 = ( ( l0 >> ( 28 - left_rotation[i] ) ) & ( 2*left_rotation[i] - 1 ) ) | ( l0 << left_rotation[i] ) & ( 0xfffffff - 2*left_rotation[i] + 1 );
        
        r0 = ( ( r0 >> ( 28 - left_rotation[i] ) ) & ( 2*left_rotation[i] - 1 ) ) | ( r0 << left_rotation[i] ) & ( 0xfffffff - 2*left_rotation[i] + 1 );
        
        //permutation with PC2 to generate i key
        keys[i] = permutate(( ( l0 << 28 ) | r0 ), pc_2_list, 48, 56);    
    
    }

}

unsigned long feistel(unsigned long value, unsigned long key){

    short e_table[] = {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};
    
    //expand the value with e_table
    unsigned long e_value = permutate(value, e_table, 48, 32);

    //xor with the key
    e_value = e_value ^ key;


    short temp_s = 0;
    unsigned long s_value = 0;

    for( int i = 0; i<8; i++){

        temp_s = ( e_value >> ( 42 - 6*i ) ) & 0x03f; //get the corresponding sextet

        short position = ((temp_s&0x1) | ((temp_s>>4)&0x2)) * 16 + ((temp_s>>1)&0xf); //calculate row/column position in buffer

        temp_s = s_tables[i][position];

        s_value = s_value << 4;

        s_value = s_value | (temp_s & 0x0f);
    }


    short p_table[] = {16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};
    
    //return the permutation with p table
    return permutate(s_value, p_table, 32, 32);
}


unsigned long code_64_bits(unsigned long value, unsigned long key){

    //generate the sub_keys from the given key
    unsigned long keys[16];
    generateKeys(key, keys);

    short ip_table[] =     {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};
    short ip_table_inv[] = {40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31, 38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29, 36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};
    
    //initial permutation of the input
    value = permutate(value, ip_table, 64, 64);

    //split the values
    unsigned long l = (value >> 32) & 0xffffffff, r = value & 0xffffffff;

    unsigned long aux = 0;

    //16 rounds
    for( int i = 0; i < 16; i++){

        aux = feistel(r, keys[i]) ^ l; //calculate xor and f

        //twist values
        l = r;

        r = aux;
    }

    //twist values again to reverse last twist and rearange them
    value =  (r << 32) | (l&0xffffffff);

    //permutate to inverse the inital permutation
    return permutate(value, ip_table_inv, 64, 64);

}



unsigned long decode_64_bits(unsigned long value, unsigned long key){

    //generate the sub_keys from the given key
    unsigned long keys[16];
    generateKeys(key, keys);

    short ip_table[] =     {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};
    short ip_table_inv[] = {40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31, 38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29, 36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};
    
    //initial permutation
    value = permutate(value, ip_table, 64, 64);

    //split the values
    unsigned long l = (value >> 32) & 0xffffffff, r = value & 0xffffffff;
    
    unsigned long aux = 0;
    
    //16 rounds in reverse order to decode
    for( int i = 15; i >= 0; i--){

        unsigned long aux = feistel(r, keys[i]) ^ l; //calculate xor and f

        //twist values
        l = r;
        
        r = aux;
    }

    //twist values again to reverse last twist and rearange them
    value =  (r << 32) | (l&0xffffffff);

    //permutate to inverse the inital permutation
    return permutate(value, ip_table_inv, 64, 64);

}

void store_long_to_char_arr_big_endian(unsigned long val, char* arr){
    for( int j = 0; j<8; j++){

        *arr = ((val >> (56-8*j))&0xff);

        arr++;

    }
}


char* code_string(char* string, unsigned long key){

    int len = strlen(string);

    char* res = (char*)malloc(sizeof(char)*( len + 8 - len%8 + 1 )); //we allocate enough chars to round to next 8 multiple
    
    char* res_r = res; //res runner to traverse and update the res array
    
    unsigned long value = 0;
    
    int i = 0;
    
    //we traverse the string
    while(*string != 0){
        
        //load the chars into a unsigned long value
        value = (value << 8) | (unsigned char)*string;

        i++;string++;

        if( i == 8 ){ //in case the unsigned long is fully allocated with 64 bits

            value = code_64_bits(value, key); //we store the coded value

            //save the value into char array (big endian)
            store_long_to_char_arr_big_endian(value, res_r);

            //update res_r to store next unsigned long
            res_r+=8;

            //reset values
            value = 0;
            i = 0;

        }
        
    }

    if( value != 0){ //in case there was still data

        value = value << 8*(8-i); //add padding 

        value = code_64_bits(value, key);

        store_long_to_char_arr_big_endian(value, res_r);

        res_r+=8;

        value = 0;
        i = 0;
    }

    *res_r = 0; //add final 0 to form c string

    return res;
}

char* decode_string(char* string, unsigned long key){
    int len = strlen(string);

    char* res = (char*)malloc(sizeof(char)*( len + 8 - len%8 + 1 )); //we allocate enough chars to round to next 8 multiple
    
    char* res_r = res; //res runner to traverse and update the res array
    
    unsigned long value = 0;
    
    int i = 0;
    
    //we traverse the string
    while(*string != 0){
        
        //load the chars into a unsigned long value
        value = (value << 8) | (unsigned char)*string;

        i++;string++;

        if( i == 8 ){ //in case the unsigned long is fully allocated with 64 bits

            value = decode_64_bits(value, key); //we store the coded value

            //save the value into char array (big endian)
            store_long_to_char_arr_big_endian(value, res_r);

            //update res_r to store next unsigned long
            res_r+=8;

            //reset values
            value = 0;
            i = 0;

        }
        
    }

    if( value != 0){ //in case there was still data

        value = value << 8*(8-i); //add padding 

        value = decode_64_bits(value, key);

        store_long_to_char_arr_big_endian(value, res_r);

        res_r+=8;

        value = 0;
        i = 0;
    }
    
    *res_r = 0; //add final 0 to form c string

    return res;
}

int main(){
    unsigned long key = 0x0123456789ABCDEF;
    char* encrypted_str = code_string("Hello World!", key);
    printf("%s\n", encrypted_str);
    char* decrypted_str = decode_string(encrypted_str, key);
    printf("%s\n", decrypted_str);

    //responses must be freed
    free(encrypted_str);
    free(decrypted_str);
    return 0;
}