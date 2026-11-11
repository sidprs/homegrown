#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define N 1024
#define M 1024
#define K 1024
#define BL 32
#define MIN(a, b) ((a) < (b)) ? (a) : (b)


void gemm_ikj(const float* A, const float* B, float* C){
  float rA = 0;  
  for(int i = 0; i < M; i++){
    for(int k = 0; k < K; k++){
      rA = A[i*K+k];
      for(int j = 0; j < N; j++){
        C[i*N+j] += rA * B[k*N+j]; 
      }
    }
  }
}

void gemm_ikj_tiled(const float* A, const float* B,  float* C){
  for(int si = 0; si < M; si+=BL){
    for(int sk = 0; sk < K; sk+=BL){
      for(int sj = 0; sj < N; sj+=BL){
        int i_min = MIN(si + BL, M); 
        int k_min = MIN(sk + BL, K); 
        int j_min = MIN(sj + BL, N); 
        for(int i = si; i < i_min; i++){
          for(int k = sk; k < k_min; k++){
            float rA = A[i*K+k];
            for(int j = sj; j < j_min; j++){
              C[i*N+j] += rA * B[k*N+j]; 
            }
          }
        }
      }
    }
  }
}

