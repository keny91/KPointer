
#ifndef _KEYPOINTERSEGMENT_H_
#define _KEYPOINTERSEGMENT_H_

/* 	Includes */

#include <stdlib.h>
#include <stdio.h>

/*	Is	Debugging mode active	*/
#if (defined DEBUG_SEGMENT) || (defined DEBUG_ALL)
int Debug_Segment_Enabled = 1;
#else
int Debug_Segment_Enabled = 0;
#endif

/*	Defined Values 	*/

// can be changed to other types to remain compatibility
#define Time_t float

#define VideoSource vlcFormat;

// KPointerSegment operations return Values
#define KPOINTER_SEGMENT_RETURN_OK 					1
#define KPOINTER_SEGMENT_ILLEGAL_NULL_POINTER  		2
#define KPOINTER_SEGMENT_ILLEGAL_ELEMENT_1 			3
#define KPOINTER_SEGMENT_NOT_FOUND 					4
#define KPOINTER_SEGMENT_NOT_FOUND 					5
#define KPOINTER_SEGMENT_INTERNAL_ERROR 			6


// TimeStampEvent Message
#define TS_EVENT_LOAD_SUCCESS 					10
#define TS_EVENT_LOAD_UNKNOWN_FAILURE 			11	
#define TS_EVENT_TRIGGERED  					12
#define TS_EVENT_NOT_TRIGGERED  				13
#define TS_EVENT_NONE_LEFT		  				14
#define TS_EVENT_ERROR_INVALID_CALLBACK		  	15

#define TS_MINIMUM_TIME_BETWEEN_EVENTS 		5.0f // X seconds in between events



/*	Maximum lenght of array type extensions	*/

//  Define maximum extension of strings
#define MAX_CHARS_REGISTRATION_NUMBER 20
#define MAX_CHARS_COUNTRY 10
#define MAX_NR_IMAGES 20


typedef struct KPointerSegmentObject *KPSegment;
typedef struct TimeStampEventStruct TimeStampEvent;
//typedef void(*CBfunction)(IntradaLiveData result); // not going to compile with this.
												   // typedef void (*functionName)(RequiredParams);


typedef class KPointerSegmentObject
{
public:
	KPointerSegmentObject();
	~KPointerSegmentObject();

	// Sets and gets
	int SetPreviousSegment(KPSegment the_segment);
	int GetPreviousSegment(KPSegment the_segment);
	int PrepareNextTimeStampEvent();
	int AddTimeStampEvent(float TimeStamp, TimeStampEvent event, void* CBfunction);   // Must bechecked first - valid Operation? - valid TS?
	int ReallocateEventInTimeLine();

	int SetCallbackOnEnd(void* CBfunction);
	int SetCallbackOnStart(void* CBfunction);

private:
	KPSegment nextSegment;
	KPSegment previousSegment;
	TimeStampEvent * TimeStampEventList;  // Array or list of Events

	int IsValidOperation();   // Check if the type of operation is among the acepted
	Time_t StartTime;
	Time_t EndTime;

};





// Should this be an array or a linked list?
// Probably this structure will have multiple childs creating a variety of Events with different parameters
struct TimeStampEventStruct {

private:
	void * Callback;  // what happens when trigger
	Time_t TimeStamp;
	int EventType;
	//VideoSource ContentSource;
	// next
	// prev

	int CallBackOperationType;
	int TriggerOnTimeStampReached();  // Contains internal callback when set	
	static int * ValidOperations;	// This is set for every type/child and can be access globally TimeStampEventStruct
	static int * IsValidOperation(int OperationType);



public:
	Time_t GetTimeStamp();
	int SetTimeStamp();
	int SetCallbackOnTrigger();
	int CheckTrigger(float currentTime);
	int DeleteThisEvent();  // also relink LinkedList or Update array

};








#endif  // end _KEYPOINTERSEGMENT_H_