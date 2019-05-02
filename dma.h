

#ifndef DMA_H_
#define DMA_H_

#include "stdint.h"
#include "MK64F12.h"
#include "Bits.h"
#include "dmamux.h"

#define ARRAY_SIZE (16u)
#define DMA_CH0 (0x01u)
#define DMA_SOURCE_GPIO (51u)
#define NUM_STEPS (1u)

typedef struct
{
	uint8_t *table_init;
	uint8_t next[3];
} State_t;

void DMA_clock_gating(void);

void DMA_init(void);
void DMA_set_transfer_size(uint8_t transfer_size);
void DMA_enable_interrupt_EOML(void);
void DMA_set_source(uint32_t source_pointer, uint8_t source_offset, uint8_t source_last_address);
void DMA_set_destination(uint32_t dest_pointer, uint8_t dest_offset, uint8_t dest_last_address);

void DMA_set_citer_biter(uint8_t num_steps);
void DMA_TCD_ATTR(uint8_t attr_val);

void DMA_enable_request(DMA_channel_t channel, ERQ_channel_t request);

void DMA_set_source_address(DMA_channel_t channel, uint32_t source_address);

boolean_t DMA_isvalidchannel(DMA_channel_t channel);

boolean_t DMA_isvalidrequest(ERQ_channel_t request);

#endif
