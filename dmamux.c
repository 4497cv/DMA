
#include "dmamux.h"

void DMAMUX_set_channel_configuration_register(DMA_channel_t channel, boolean_t enable, boolean_t trigger, DMAMUX_source_t source)
{
	boolean_t channel_flag;
	boolean_t source_flag;
	uint16_t mask_val = 0;

	/* Verify if all arguments are valid */
	channel_flag = DMAMUX_isvalidchannel(channel);
	source_flag = DMAMUX_isvalidsource(source);

	if((TRUE == channel_flag) && (TRUE == source_flag))
	{
		DMAMUX->CHCFG[channel] = 0;

		if(TRUE == enable)
		{
			/* DMA channel is enabled */
			mask_val |= DMAMUX_CHCFG_ENBL_MASK;
		}
		else
		{
		}


		if(TRUE == trigger)
		{
			/* Triggering is enabled: the DMAMUX is in Periodic Trigger mode. */
			mask_val |= DMAMUX_CHCFG_TRIG_MASK;
		}
		else
		{
		}

		/* Route DMA Source to DMA Channel */
		mask_val |= DMAMUX_CHCFG_SOURCE(source);
		DMAMUX->CHCFG[channel] = mask_val;
	}
}

void DMAMUX_set_channel_operation_mode(DMA_channel_t channel, DMAMUX_source_t source, DMAMMUX_mode_t mode)
{
	boolean_t PeriodicTriggerChannel_flag;

	if(PeriodicTrigger == mode)
	{
		PeriodicTriggerChannel_flag = DMAMUX_isvalidPTchannel(channel);
	}
	else
	{
	}


	switch(mode)
	{
		case Disabled:
			DMAMUX_set_channel_configuration_register(channel, FALSE, FALSE, Disable_Signal);
		break;
		case Normal:
			DMAMUX_set_channel_configuration_register(channel, TRUE, FALSE, source);
		break;
		case PeriodicTrigger:
			if(PeriodicTriggerChannel_flag)
			{
				DMAMUX_set_channel_configuration_register(channel, TRUE, TRUE, source);
			}
			else
			{
				/* ERROR WHILE CONFIGURING PERIODIC TRIGGER */	
			}	
		break;
		default:
		break;
	}
}

boolean_t DMAMUX_isvalidchannel(DMA_channel_t channel)
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

boolean_t DMAMUX_isvalidPTchannel(DMA_channel_t channel)
{
	boolean_t boolean_flag;

	/** Verify if channel is between zero and fifteen */
	if((DMA_0 <= channel) && (DMA_3 >= channel))
	{
		boolean_flag = TRUE;
	}
	else
	{
		boolean_flag = FALSE;
	}

	return boolean_flag;
}

boolean_t DMAMUX_isvalidsource(DMAMUX_source_t source)
{
	boolean_t boolean_flag;

	/** Verify if channel is between zero and fifteen */
	if((Disable_Signal <= source) && (AlwaysOn63_Signal >= source))
	{
		boolean_flag = TRUE;
	}
	else
	{
		boolean_flag = FALSE;
	}

	return boolean_flag;
}
