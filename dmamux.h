

#ifndef DMAMUX_H_
#define DMAMUX_H_

#include "stdint.h"
#include "MK64F12.h"
#include "Bits.h"
#include "dma.h"
#include <stdio.h>

typedef enum
{
	Disable_Signal,
	_Reserved_,
	UART0_Rx_Signal,
	UART0_Tx_Signal,
	UART1_Rx_Signal,
	UART1_Tx_Signal,
	UART2_Rx_Signal,
	UART2_Tx_Signal,
	UART3_Rx_Signal,
	UART3_Tx_Signal,
	UART4_Signal,
	UART5_Signal,
	I2S0_Rx_Signal,
	I2S0_Tx_Signal,
	SPI0_Rx_Signal,
	SPI0_Tx_Signal,
	SPI1_Signal,
	SPI2_Signal,
	I2C0_Signal,
	I2C1_I2C2_Signal,
	FTM0_Channel0_Signal,
	FTM0_Channel1_Signal,
	FTM0_Channel2_Signal,
	FTM0_Channel3_Signal,
	FTM0_Channel4_Signal,
	FTM0_Channel5_Signal,
	FTM0_Channel6_Signal,
	FTM0_Channel7_Signal,
	FTM1_Channel0_Signal,
	FTM1_Channel1_Signal,
	FTM2_Channel0_Signal,
	FTM2_Channel1_Signal,
	FTM3_Channel0_Signal,
	FTM3_Channel1_Signal,
	FTM3_Channel2_Signal,
	FTM3_Channel3_Signal,
	FTM3_Channel4_Signal,
	FTM3_Channel5_Signal,
	FTM3_Channel6_Signal,
	FTM3_Channel7_Signal,
	ADC0_Signal,
	ADC1_Signal,
	CMP0_Signal,
	CMP1_Signal,
	CMP2_Signal,
	DAC0_Signal,
	DAC1_Signal,
	CMT_Signal,
	PDB_Signal,
	PortA_Signal,
	PortB_Signal,
	PortC_Signal,
	PortD_Signal,
	PortE_Signal,
	IEEE1588Timer0_Signal,
	IEEE1588Timer1_Signal,
	IEEE1588Timer2_Signal,
	IEEE1588Timer3_Signal,
	AlwaysOn58_Signal,
	AlwaysOn59_Signal,
	AlwaysOn60_Signal,
	AlwaysOn61_Signal,
	AlwaysOn62_Signal,
	AlwaysOn63_Signal
} DMAMUX_source_t;

typedef enum
{
	Disabled,
	Normal,
	PeriodicTrigger
} DMAMMUX_mode_t;

void DMAMUX_set_channel_configuration_register(DMA_channel_t channel, boolean_t enable, boolean_t trigger, DMAMUX_source_t source);

void DMAMUX_set_channel_operation_mode(DMA_channel_t channel, DMAMUX_source_t source, DMAMMUX_mode_t mode);

boolean_t DMAMUX_isvalidchannel(DMA_channel_t channel);

boolean_t DMAMUX_isvalidPTchannel(DMA_channel_t channel);

boolean_t DMAMUX_isvalidsource(DMAMUX_source_t source);

#endif
