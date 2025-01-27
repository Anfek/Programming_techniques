class Magma{
    #define BLOCK_SIZE 4
    typedef uint8_t vect[BLOCK_SIZE];

    static unsigned char Pi[8][16]={
        {1,7,14,13,0,5,8,3,4,15,10,6,9,12,11,2},
        {8,14,2,5,6,9,1,12,15,4,11,0,13,10,3,7},
        {5,13,15,6,9,2,12,10,11,7,8,1,4,3,14,0},
        {7,15,5,10,8,1,6,13,0,9,3,14,11,4,2,12},
        {12,8,2,1,13,4,15,6,7,0,10,5,3,14,9,11},
        {11,3,5,8,2,15,10,13,14,1,7,4,12,9,6,0},
        {6,8,2,3,9,10,5,12,1,14,4,7,11,13,0,15},
        {12,4,6,2,10,5,11,9,14,8,13,7,0,3,15,1}
    };

    static void add_32(const uint8_t *a, const uint8_t *b, uint8_t *c){
        for (int i = 0; i < BLOCK_SIZE; i++)
            c[i] = a[i]^b[i];
    }

    static void magma_T(const uint8_t *in_data, uint8_t *out_data){
        uint8_t first_part_byte, sec_part_byte;
        int i;
        for (i = 0; i < 4; i++){
            first_part_byte = (in_data[i] & 0xf0) >> 4;
            sec_part_byte = (in_data[i] & 0x0f);
            first_part_byte = Pi[i * 2][first_part_byte];
            sec_part_byte = Pi[i * 2 + 1][sec_part_byte];
            out_data[i] = (first_part_byte << 4) | sec_part_byte;
        }
    }

    static void magma_g(const uint8_t *k, const uint8_t *A, uint8_t *out_data){
        uint8_t buf[4];
        uint32_t buf_32 = 0;
        
        add_32(A, k, buf);
        magma_T(internal, internal);
        
        for(int i=0; i<BLOCK_SIZE; i++){
            buf_32 = (buf_32 << 8) + buf[i];
        }

        buf_32 = (buf_32 << 11)|(buf_32 >> 21);
        
        for(int i=0; i<BLOCK_SIZE; i++){
            out_data[i] = buf_32 >> 8*(3-i);
        }
    }

    static void round_crypt(uint8_t **A, uint8_t **round_key, bool mode){
        uint8_t buf_A1[BLOCK_SIZE];
        for(int i=0; i<32; i++){
            for(int i=0; i<BLOCK_SIZE; i++){
                buf_A1[i] = A[1][i];
            }

            if(mode)
                magma_g(round_key[i], A[1], A[1]);//шифрование
            else
                magma_g(round_key[31-i], A[1], A[1]);//расшифрование

            
            add_32(A[0], A[1], A[1]);

            for(int i=0; i<BLOCK_SIZE; i++){
                A[0][i] = buf_A1[i];
            }
        }

        for(int i=0; i<BLOCK_SIZE; i++){
            A[0][i] = A[1][i];
            A[1][i] = buf_A1[i];
        }
    }

    static void Magma_crypt(const uint8_t *text, const uint8_t *key){//text[8] - 64bit = 8elem*8bit, key[32] - 256bit = 32elem*8bit
        uint8_t A[2][BLOCK_SIZE], round_key[32][BLOCK_SIZE], result[BLOCK_SIZE];
        for(int i=0; i<BLOCK_SIZE; i++){
            A[0][i] = text[i];
            A[1][i] = text[i+BLOCK_SIZE];
        }

        for(int i=0; i<3; i++){
            for(int j=0; j<8; j++){
                for(int k=0; k<BLOCK_SIZE; k++)
                    round_key[i*8 + j][k] = key[j*BLOCK_SIZE + k];
            }
        }
        for(int j=0; j<8; j++){
            for(int k=0; k<BLOCK_SIZE; k++)
                round_key[3*8 + j][k] = key[32-j*BLOCK_SIZE-k-1];
        }

        round_crypt(A, round_key, true);
        

    }
}