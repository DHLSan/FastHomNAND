#include <stdio.h>
#include<time.h>
#include"ntt.h"
#include <stdint.h>
#include<malloc.h>
#include<assert.h>
#include"xntt_ips.h"
#include <stdio.h>
#include "xil_printf.h"
#include "xaxidma.h"
#include"xparameters.h"
#include "xtime_l.h"

XNtt_ips doGain;
XNtt_ips_Config *doGaing_cfg;
XAxiDma axiDMA;
XAxiDma_Config *axiDMA_cfg;

#define MEM_BASE_ADDR 0x01000000
#define TX_BUFFER_BASE (MEM_BASE_ADDR+0x00100000)
#define RX_BUFFER_BASE (MEM_BASE_ADDR+0x00400000)

#define SIZE_ARR 1024
uint64_t inStreamData[SIZE_ARR];

void initPeripherals()
{

   axiDMA_cfg=XAxiDma_LookupConfig(XPAR_AXIDMA_0_DEVICE_ID);
   if(axiDMA_cfg){

	   int status= XAxiDma_CfgInitialize(&axiDMA,axiDMA_cfg);
	   if(status!=XST_SUCCESS){
		   printf("EROR Initializing Dma");
	   }

   }



     doGaing_cfg=XNtt_ips_LookupConfig(XPAR_NTT_IPS_0_DEVICE_ID);
     if(doGaing_cfg){

  	   int status= XNtt_ips_CfgInitialize(&doGain,doGaing_cfg);
  	   if(status!=XST_SUCCESS){
  		   printf("EROR Initializing DoGain");
  	   }

     }
        XAxiDma_IntrDisable(&axiDMA, XAXIDMA_IRQ_ALL_MASK,XAXIDMA_DEVICE_TO_DMA);
         XAxiDma_IntrDisable(&axiDMA, XAXIDMA_IRQ_ALL_MASK,XAXIDMA_DMA_TO_DEVICE);

}




typedef int32_t Torus32;

struct IntPolynomial {
    int32_t N;
    int32_t* coefs;

};


struct TorusPolynomial {
    int32_t N;
    Torus32* coefsT;
};


struct LagrangeHalfCPolynomial
{


    void* data;
    void* precomp;

    struct LagrangeHalfCPolynomial_IMPL
    {
        uint64_t* coefsC;
        int32_t N;

    }b;

};

typedef struct IntPolynomial	   IntPolynomial;
typedef struct TorusPolynomial	   TorusPolynomial;
typedef struct LagrangeHalfCPolynomial	   LagrangeHalfCPolynomial;

void torusPolynomialMultNaive(TorusPolynomial* result, const IntPolynomial* poly1, const TorusPolynomial* poly2);

void torusPolynomialMultNaive_aux(Torus32* __restrict__ result, const int32_t* __restrict__ poly1, const Torus32* __restrict__ poly2, const int32_t N);
void torusPolynomialMultFFT(TorusPolynomial* result, const IntPolynomial* poly1, const TorusPolynomial* poly2);
extern IntPolynomial* new_IntPolynomial(const int32_t N);
extern IntPolynomial* new_IntPolynomial_array(int32_t nbelts, const int32_t N);

//destroys and frees the IntPolynomial structure
//(equivalent of the C++ delete)
extern void delete_IntPolynomial(IntPolynomial* obj);
extern void delete_IntPolynomial_array(int32_t nbelts, IntPolynomial* obj);





//allocates and initialize the TorusPolynomial structure
//(equivalent of the C++ new)
extern TorusPolynomial* new_TorusPolynomial(const int32_t N);
extern TorusPolynomial* new_TorusPolynomial_array(int32_t nbelts, const int32_t N);

//destroys and frees the TorusPolynomial structure
//(equivalent of the C++ delete)
extern void delete_TorusPolynomial(TorusPolynomial* obj);
extern void delete_TorusPolynomial_array(int32_t nbelts, TorusPolynomial* obj);

//allocates and initialize the LagrangeHalfCPolynomial structure
//(equivalent of the C++ new)
extern LagrangeHalfCPolynomial* new_LagrangeHalfCPolynomial(const int32_t N);
extern LagrangeHalfCPolynomial* new_LagrangeHalfCPolynomial_array(int32_t nbelts, const int32_t N);

//destroys and frees the LagrangeHalfCPolynomial structure
//(equivalent of the C++ delete)
extern void delete_LagrangeHalfCPolynomial(LagrangeHalfCPolynomial* obj);
extern void delete_LagrangeHalfCPolynomial_array(int32_t nbelts, LagrangeHalfCPolynomial* obj);





int main() {


    XTime tStart, tEnd;


    const int32_t N = 1024;
    IntPolynomial* a = new_IntPolynomial(N);
    TorusPolynomial* b = new_TorusPolynomial(N);
    TorusPolynomial* resNaive = new_TorusPolynomial(N);
    TorusPolynomial* resFFT = new_TorusPolynomial(N);
    TorusPolynomial* resKaratsuba = new_TorusPolynomial(N);



    	int j=0;
        for ( j = 0; j < 1024; j++) {
            a->coefs[j] =rand();
            b->coefsT[j] = rand();
        }


        XTime_GetTime(&tStart);

        torusPolynomialMultNaive(resNaive, a, b);
        XTime_GetTime(&tEnd);
		printf("%.2f Ms.\n",(1.0*((((tEnd-tStart))))));


        torusPolynomialMultFFT(resFFT, a, b);

             int i=0;
        for ( i = 0; i < N; i++) {
            if (abs((resNaive->coefsT[i] - resFFT->coefsT[i])) > 1) {

            	printf("olmadi :%d\n",i);

            }
            else{
            	printf("oldu :%d\n",i);
            }
        }







    delete_IntPolynomial(a);
    delete_TorusPolynomial(b);
    delete_TorusPolynomial(resNaive);
    delete_TorusPolynomial(resKaratsuba);
    return 0;
}


void torusPolynomialMultNaive(TorusPolynomial* result, const IntPolynomial* poly1, const TorusPolynomial* poly2) {
    const int32_t N = poly1->N;

    torusPolynomialMultNaive_aux(result->coefsT, poly1->coefs, poly2->coefsT, N);
}

void torusPolynomialMultNaive_aux(Torus32* __restrict__ result, const int32_t* __restrict__ poly1, const Torus32* __restrict__ poly2, const int32_t N) {
    Torus32 ri;
    int i=0;
    int j=0;
    for ( i = 0; i < N; i++) {
        ri = 0;
        for ( j = 0; j <= i; j++) {
            ri += poly1[j] * poly2[i - j];
        }
        for ( j = i + 1; j < N; j++) {
            ri -= poly1[j] * poly2[N + i - j];
        }
        result[i] = ri;
    }
}


void torusPolynomialMultFFT(TorusPolynomial* result, const IntPolynomial* poly1, const TorusPolynomial* poly2) {

    const int32_t N = 1024; // N=1024
    uint64_t  modulus = 0xffffffff00000001UL; //

   int i=0;
   uint64_t a1[1024];

    uint64_t* a2 = (uint64_t*)malloc(1024 * sizeof(uint64_t));

    uint64_t* intt_mul_res = (uint64_t*)malloc(N * sizeof(uint64_t));
    uint64_t* ntt_res = (uint64_t*)malloc(N * sizeof(uint64_t));





    for ( i = 0; i < N; i++) {
        if (poly1->coefs[i] < 0) {
            a1[i] = poly1->coefs[i] + modulus;
            uint64_t phi = phi_normal_2[i];
            a1[i] = mod_mul(a1[i], phi, modulus);
        }
        else {
            a1[i] = (uint64_t)poly1->coefs[i];
            uint64_t phi = phi_normal_2[i];
            a1[i] = mod_mul(a1[i], phi, modulus);
        }


        if (poly2->coefsT[i] < 0) {
            a2[i] = poly2->coefsT[i] + modulus;
            uint64_t phi = phi_normal_2[i];//mod_exp(phi, i, modulus);
            a2[i] = mod_mul(a2[i], phi, modulus);
        }
        else {
            a2[i] = (uint64_t)poly2->coefsT[i];
            uint64_t phi = phi_normal_2[i];
            a2[i] = mod_mul(a2[i], phi, modulus);
        }


    }


/*
   	     int *m_dma_buffer_RX = (int *)RX_BUFFER_BASE;


   	     initPeripherals();
   	    	 int gain=5;
   	    	 XNtt_ips_Set_cont(&doGain,gain);
   	    	 XNtt_ips_Start(&doGain);
   	    	 Xil_DCacheFlushRange((u32)inStreamData,SIZE_ARR*sizeof(uint64_t));
   	    	 Xil_DCacheFlushRange((u32)m_dma_buffer_RX,SIZE_ARR*sizeof(uint64_t));


   	 XAxiDma_SimpleTransfer(&axiDMA,(u32)a1,SIZE_ARR*sizeof(uint64_t),XAXIDMA_DMA_TO_DEVICE);
   	 XAxiDma_SimpleTransfer(&axiDMA,(u32)m_dma_buffer_RX,SIZE_ARR*sizeof(uint64_t),XAXIDMA_DEVICE_TO_DMA);
     Xil_DCacheInvalidateRange((u32)m_dma_buffer_RX,SIZE_ARR*sizeof(int));




   */
    printf("asd\n");
   ntt_CT(a1, modulus, N);
    ntt_CT(a2, modulus, N);

    //pragma omp
    for ( i = 0; i < N; i++)
        intt_mul_res[i] = mod_mul(a1[i], a2[i], modulus);



    intt_CT(intt_mul_res, modulus, ntt_res, N);


    uint64_t med = modulus / 2;

    for ( i = 0; i < N; i++) {
        result->coefsT[i] = (Torus32)((ntt_res[i] & 0xffffffff) - (ntt_res[i] > med)); // worked!


    }

    free(a2);
    free(ntt_res);
    free(intt_mul_res);



}
extern IntPolynomial* new_IntPolynomial(const int32_t N) {

    IntPolynomial* obj = (IntPolynomial*)malloc(sizeof(IntPolynomial));
    obj->coefs = (int32_t*)malloc(N * sizeof(int32_t));
    obj->N = N;
    return obj;
}
extern IntPolynomial* new_IntPolynomial_array(int32_t nbelts, const int32_t N) {
	int i=0;
    IntPolynomial* obj = (IntPolynomial*)malloc(nbelts * sizeof(IntPolynomial));
    for ( i = 0; i < nbelts; i++) {
        (obj + i)->coefs = (int32_t*)malloc(N * sizeof(int));
        (obj + i)->N = N;
    }
    return obj;
}
extern void delete_IntPolynomial(IntPolynomial* obj) {
    free(obj);

}
extern void delete_IntPolynomial_array(int32_t nbelts, IntPolynomial* obj) {
	int i=0;
    for ( i = 0; i < nbelts; i++)
        free(obj[i].coefs);

    free(obj);
}


//allocates and initialize the TorusPolynomial structure
//(equivalent of the C++ new)
extern TorusPolynomial* new_TorusPolynomial(const int32_t N) {
    TorusPolynomial* obj = (TorusPolynomial*)malloc(sizeof(TorusPolynomial));
    obj->coefsT = (Torus32*)malloc(1024 * sizeof(Torus32));
    obj->N = 1024;
    return obj;
}
extern TorusPolynomial* new_TorusPolynomial_array(int32_t nbelts, const int32_t N) {
    TorusPolynomial* obj = (TorusPolynomial*)malloc(nbelts * sizeof(TorusPolynomial));
    int i=0;
    for ( i = 0; i < nbelts; i++) {
        obj[i].coefsT = (Torus32*)malloc(N * sizeof(Torus32));
        obj[i].N = N;
    }

    return obj;
}
extern void delete_TorusPolynomial(TorusPolynomial* obj) {
    free(obj);
}
extern void delete_TorusPolynomial_array(int32_t nbelts, TorusPolynomial* obj) {

    for (int i = 0; i < nbelts; i++)
        free(obj->coefsT);

    free(obj);


}


//allocates and initialize the LagrangeHalfCPolynomial structure
//(equivalent of the C++ new)
extern LagrangeHalfCPolynomial* new_LagrangeHalfCPolynomial(const int32_t N) {
    LagrangeHalfCPolynomial* obj = (LagrangeHalfCPolynomial*)malloc(sizeof(LagrangeHalfCPolynomial));
    obj->b.N = N;
    obj->b.coefsC = (uint64_t*)malloc(1024 * sizeof(uint64_t));
    return obj;
}
extern LagrangeHalfCPolynomial* new_LagrangeHalfCPolynomial_array(int32_t nbelts, const int32_t N) {
    LagrangeHalfCPolynomial* obj = (LagrangeHalfCPolynomial*)malloc(N * sizeof(LagrangeHalfCPolynomial));
    int i=0;
    for ( i = 0; i < nbelts; i++) {
        obj[i].b.N = N;
        obj[i].b.coefsC = (uint64_t*)malloc(1024 * sizeof(uint64_t));
    }
    return obj;
}
extern void delete_LagrangeHalfCPolynomial(LagrangeHalfCPolynomial* obj) {

    free(obj->b.coefsC);
    free(obj);

}
extern  void delete_LagrangeHalfCPolynomial_array(int32_t nbelts, LagrangeHalfCPolynomial* obj) {
	int i=0;
    for ( i = 0; i < nbelts; i++)
        free(obj[i].b.coefsC);

    free(obj);


}


