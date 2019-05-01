
#include "dma.h"

static uint8_t g_data_source[ARRAY_SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};//defines source data space
static uint8_t g_data_desti[4*ARRAY_SIZE]; //defines destination data space

void DMA0_IRQHandler(void)
{

	uint8_t i;

	DMA0->INT = DMA_CH0;

	for ( i = 0; i < ARRAY_SIZE; ++i)
	{
		printf("%d,",g_data_desti[i]);
	}
	printf("\n");
}

void DMA_clock_gating(void)
{
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
}

//AlwaysOn58_Signal
void DMA_init(void)
{
	DMAMUX_set_channel_operation_mode(DMA_0, PortC_Signal, Normal);
	DMA_enable_request(DMA_0, ERQ_0);
	DMA_set_source((uint32_t)&g_data_source[0], 1, -6);
	DMA_set_destination((uint32_t)&g_data_desti[0], 1, 0);
	DMA_set_citer_biter(NUM_STEPS);
	DMA_set_transfer_size(8);
	DMA_set_attr(0);
	DMA_set_EOML();
}

void DMA_set_transfer_size(uint8_t transfer_size)
{
	DMA0->TCD[0].NBYTES_MLNO = transfer_size;/*byte number*/
}

void DMA_set_attr(uint8_t attr_val)
{
	DMA0->TCD[0].ATTR = attr_val;
}

void DMA_set_EOML(void)
{
	DMA0->TCD[0].CSR = DMA_CSR_INTMAJOR_MASK;/*The end-of-major loop interrupt is enabled*/
}

void DMA_set_citer_biter(uint8_t num_steps)
{
	/*CITER represents the number of minor loops that compose a major loop, every time a minor loop is completed CITTER is decremented by one.
	 * Once CITTER is 0 the DMA copy BITTER into CITTER and adjust SADDR and DADDR with the values specified in SLAST and DLAST_SGA respectively
	 *  SADDR  = SADDR + SLAST and DADDR + DLAST_SGA*/
	DMA0->TCD[0].CITER_ELINKNO = DMA_CITER_ELINKNO_CITER(num_steps);
	/* Once a major loop is completed, BITTER is copy to CITTER*/
	DMA0->TCD[0].BITER_ELINKNO = DMA_BITER_ELINKNO_BITER(num_steps);
}

void DMA_set_source(uint32_t source_pointer, uint8_t source_offset, uint8_t source_last_address)
{
	DMA0->TCD[0].SADDR = (uint32_t) source_pointer;/*defines source data address*/
	DMA0->TCD[0].SOFF = source_offset;/*Source address signed offset;it is expressed in number of bytes*/
	DMA0->TCD[0].SLAST = source_last_address;//restores the source address to the initial value, which is expressed in the amount of bytes to restore*/
}

void DMA_set_destination(uint32_t dest_pointer, uint8_t dest_offset, uint8_t dest_last_address)
{
	DMA0->TCD[0].DADDR = (uint32_t) dest_pointer;/*defines destination data address*/
	DMA0->TCD[0].DOFF = dest_offset;/*destination address signed offset;it is expressed in number of bytes*/
	DMA0->TCD[0].DLAST_SGA = dest_last_address;/*restores the destination address to the initial value, which is expressed in the amount of bytes to restore*/
}

void DMA_enable_request(DMA_channel_t channel, ERQ_channel_t request)
{
	boolean_t valid_requestchannel_flag;

	valid_requestchannel_flag = DMA_isvalidrequest(request);

	if(TRUE == valid_requestchannel_flag)
	{
		switch(request)
		{
		case ERQ_0:
			DMA0->ERQ = DMA_ERQ_ERQ0_MASK;
		break;
		case ERQ_1:
		break;
		case ERQ_2:
		break;
		case ERQ_3:
		break;
		case ERQ_4:
		case ERQ_5:
		break;
		default:
		break;
		}
	}

}

void DMA_set_source_address(DMA_channel_t channel, uint32_t source_address)
{
	switch(channel)
	{
		case DMA_0:
		break;
		case DMA_1:
		break;
		case DMA_2:
		break;
		default:
		break;
	}
}

boolean_t DMA_isvalidchannel(DMA_channel_t channel)
{
	boolean_t boolean_flag;

	/** Verify if channel is between zero and fifteen */
	if((DMA_0 <= channel) && (DMA_15 >= channel))
	{
		boolean_flag = TRUE;
	}
	else
	{
		boolean_flag = FALSE;
	}

	return boolean_flag;
}

boolean_t DMA_isvalidrequest(ERQ_channel_t request)
{
	boolean_t boolean_flag;

	/** Verify if channel is between zero and fifteen */
	if((ERQ_0 <= request) && (ERQ_15 >= request))
	{
		boolean_flag = TRUE;
	}
	else
	{
		boolean_flag = FALSE;
	}

	return boolean_flag;
}
