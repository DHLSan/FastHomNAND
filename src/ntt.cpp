#include <stdio.h>
#include <stdint.h>



#include"ntt.h"





#define mod_add(a, b, modulus) ((modulus - a) > b) ? (a + b) : (a + b - modulus)
#define mod_sub(a, b, modulus) (a >= b) ? (a - b) : (modulus - b + a)






extern uint64_t mod_mul(uint64_t x, uint64_t y, uint64_t p) {




    uint32_t x0 = (uint32_t)x;
    uint32_t x1 = (uint32_t)(x >> 32);
    uint32_t y0 = (uint32_t)y;
    uint32_t y1 = (uint32_t)(y >> 32);




    uint64_t x0y0 = (uint64_t)x0 * (uint64_t)y0;
    uint64_t x0y1 = (uint64_t)x0 * (uint64_t)y1;
    uint64_t x1y0 = (uint64_t)x1 * (uint64_t)y0;
    uint64_t x1y1 = (uint64_t)x1 * (uint64_t)y1;



    uint32_t d = (uint32_t)x0y0;
    uint64_t pp1 = (x0y0 >> 32) + (uint32_t)(x1y0)+(uint32_t)(x0y1);
    uint32_t c = (uint32_t)pp1;
    uint64_t pp2 = (x1y0 >> 32) + (x0y1 >> 32) + (uint32_t)(x1y1);
    uint64_t pp3 = (pp1 >> 32) + (uint32_t)(pp2);

    uint32_t a = (pp2 >> 32) + (x1y1 >> 32);

    uint64_t bpc = (uint32_t)pp3 + (uint64_t)c; //1fffffffe max




    bpc = ((bpc + (bpc >> 32)) << 32) - (bpc >> 32); //1fffffffe +

    uint64_t mines = ((uint64_t)a + ((uint64_t)(uint32_t)pp3));
    uint64_t plus = bpc + (uint64_t)d;

    if (plus >= mines)
        return (plus - mines);
    else
        return p - mines + plus;

    /* result = result +p;
     if(result>p)
         result -=p;
    */






}



//////////////////////////////////////////////////////////////////////////


void bitrev_shuffle(uint64_t x[], int N) {

    int j = 0;
    for (int i = 1; i < N; i++) {
        int b = N >> 1;
        while (j >= b) {
            j -= b;
            b >>= 1;
        }
        j += b;
        if (j > i) {
            uint64_t temp = x[j];
            x[j] = x[i];
            x[i] = temp;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////

extern void ntt_CT(uint64_t x[], uint64_t modulus, int N) {
    uint64_t b = 0;
    //uint64_t c=0;

    bitrev_shuffle(x, N);

    int wbarr = 0;
    for (int trans_size = 2; trans_size <= N; trans_size = trans_size * 2) {
        uint64_t wb = 1;
        for (int t = 0; t < (trans_size >> 1); t++) {
            for (int trans = 0; trans < (N / trans_size); trans++) {
                int i = trans * trans_size + t;

                int j = i + (trans_size >> 1);
                uint64_t a = x[i];
                if (wb == 1) {
                    b = x[j];
                }
                else {

                    //c=mod_mul2(x[j], wb, modulus);

                    b = mod_mul(x[j], wb, modulus);




                }
                x[i] = mod_add(a, b, modulus);
                x[j] = mod_sub(a, b, modulus);


            }
            wb = wb_normal_2[wbarr];
            wbarr++;

        }
    }

}




extern void intt_CT(uint64_t x[], uint64_t modulus, uint64_t y[], int N) {
    uint64_t b = 0;
    int inv = 0;

    bitrev_shuffle(x, N);


    for (int trans_size = 2; trans_size <= N; trans_size = trans_size * 2) {
        uint64_t wb = 1;


        for (int t = 0; t < (trans_size >> 1); t++) {
            for (int trans = 0; trans < (N / trans_size); trans++) {
                int i = trans * trans_size + t;
                int j = i + (trans_size >> 1);
                uint64_t a = x[i];


                if (wb == 1)
                    b = x[j];
                else
                    b = mod_mul(x[j], wb, modulus);

                x[i] = mod_add(a, b, modulus);
                x[j] = mod_sub(a, b, modulus);

            }
            wb = wb_inverse_2[inv];
            inv++;
        }
    }



    int i = 0;

    for (i = 0; i < N; i++) {
        y[i] = mod_mul(x[i], scale_2, modulus);    //scale_2*phi inversev, modulus  (phi inverse sclaed)
        uint64_t phi = phi_inverse_2[i];

        y[i] = mod_mul(y[i], phi, modulus);
    }

}

