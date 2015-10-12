/*
 * TRG_Trigger.c
 *
 * Created: 13.04.2015 21:49:35
 *  Author: Squirrel
 */ 


#include <asf.h>
#include "TRG_Trigger.h"
#include "IO_Discretes.h"
#include "IO_SysTickTimer.h"
#include "GBL_Defines.h"

typedef struct {
	uint32_t State;
	uint32_t PreviousState;
	uint32_t DebounceCounter;
	uint32_t IsDebounced;
	uint32_t PullTimestampTicks;
	uint32_t ReleaseTimestampTicks;
	uint32_t Edge;
	
} TRG_Trigger_Context_Type;

static TRG_Trigger_Context_Type TRG_Trigger_Context;



void TRG_Trigger_Initialize(void) {
	TRG_Trigger_Context.State                 = TRG_TRIGGER_RELEASED;
	TRG_Trigger_Context.PreviousState         = TRG_TRIGGER_RELEASED;
	
	TRG_Trigger_Context.IsDebounced           = true;
	TRG_Trigger_Context.DebounceCounter       = 0;
	
	TRG_Trigger_Context.PullTimestampTicks    = MAX_UINT_32;
	TRG_Trigger_Context.ReleaseTimestampTicks = MAX_UINT_32;
	
	TRG_Trigger_Context.Edge                  = TRG_TRIGGER_EDGE_NONE;
}


void TRG_Trigger_Update(void) {
	
	bool ActTriggerPulled;
	uint32_t ActTimerTicks;
	
	ActTriggerPulled = IO_Discretes_GetInputIsSet(IO_DISCRETES_CHANNEL_TRIGGER);
	ActTimerTicks    = IO_SysTickTimer_GetTicks();
	
	if (TRG_Trigger_Context.IsDebounced) {
		
		if (ActTriggerPulled) {
			// trigger actually pulled
			if (TRG_Trigger_Context.State != TRG_TRIGGER_PULLED) {
				TRG_Trigger_Context.State                 = TRG_TRIGGER_PULLED;
				TRG_Trigger_Context.DebounceCounter       = ActTimerTicks;
				TRG_Trigger_Context.PullTimestampTicks    = ActTimerTicks;
				TRG_Trigger_Context.IsDebounced           = false;
			}
		
		} else {
			// trigger actually not pulled
			if (TRG_Trigger_Context.State != TRG_TRIGGER_RELEASED) {
				TRG_Trigger_Context.State                 = TRG_TRIGGER_RELEASED;
				TRG_Trigger_Context.DebounceCounter       = ActTimerTicks;
				TRG_Trigger_Context.ReleaseTimestampTicks = ActTimerTicks;
				TRG_Trigger_Context.IsDebounced           = false;
			}
		
		}
	}
	
	if (TRG_Trigger_Context.DebounceCounter + TRG_TRIGGER_DEBOUNCE_TICKS <= ActTimerTicks ) {
		TRG_Trigger_Context.IsDebounced = true;
	} 
	

	// edge detection
	if (TRG_Trigger_Context.State != TRG_Trigger_Context.PreviousState) {
		if (TRG_Trigger_Context.State == TRG_TRIGGER_PULLED) {
			TRG_Trigger_Context.Edge = TRG_TRIGGER_EDGE_PULL;
		} else {
			TRG_Trigger_Context.Edge = TRG_TRIGGER_EDGE_RELEASE;
		}
	}
	
	TRG_Trigger_Context.PreviousState = TRG_Trigger_Context.State;
	
}

void TRG_Trigger_ClearEdge(void) {
	TRG_Trigger_Context.Edge = TRG_TRIGGER_EDGE_NONE;
}

uint32_t TRG_Trigger_GetEdge(void) {
	return TRG_Trigger_Context.Edge;
}

uint32_t TRG_Trigger_GetReleaseTimestampTicks(void) {
	return TRG_Trigger_Context.ReleaseTimestampTicks;
}

uint32_t TRG_Trigger_GetPullTimestampTicks(void) {
	return TRG_Trigger_Context.PullTimestampTicks;
}

uint32_t TRG_Trigger_GetState(void) {
	return TRG_Trigger_Context.State;
}
