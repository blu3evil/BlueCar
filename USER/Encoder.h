#ifndef ENCODER_H__
#define ENCODER_H__

#include "stdint.h"

void Encoderinit(void);
void GetEncoderPulse(void);
void Encoder_combinationread(void);
void Encoder_Update_Count(void);
void speedcaculate(void);

#endif


