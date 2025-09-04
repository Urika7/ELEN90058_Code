#include "SPWS2.h"

#define PI 3.14159265359
#define SAMPLE_RATE	8000


#define BUFFER_LENGTH 80 // 8000Hz * 10ms
#define ALPHA 0.7
#define FSR 1.0


static float delayBuffer[BUFFER_LENGTH+1];
static float delayBuffer1[BUFFER_LENGTH+1];
static float delayBuffer2[BUFFER_LENGTH+1];
static int n = 0;
static unsigned long sampledCount = 0;


// Input samples
float LeftInput;
float RightInput;

// Output samples
float LeftOutput;
float RightOutput;


// Declare any global variables you need



void Flanging(void)
{

int d = floor(0.5 * BUFFER_LENGTH * (1.0-cosf(2*PI*FSR*sampledCount/SAMPLE_RATE)));


	int n_delayed = n - d;
	if (n_delayed < 0)
		n_delayed += (BUFFER_LENGTH+1);

	LeftOutput = LeftInput + ALPHA*delayBuffer[n];//Apply Filter

    delayBuffer[n_delayed] = LeftInput;//Assign next input into buffer

    //Increase index
    n++;

    //If reached end of buffer size, start writing over buffer
    if(n > BUFFER_LENGTH){
    	n = 0;
    	sampledCount++;
    }

}

void Chorusing(void)
{
	int d1 = floor(2.5 * BUFFER_LENGTH * (1.0-cosf(2*PI*FSR*sampledCount/SAMPLE_RATE)));
	int d2 = floor(2.5 * BUFFER_LENGTH * (1.0+cosf(2*PI*FSR*sampledCount/SAMPLE_RATE)));


		int n_delayed1 = n - d1;
		if (n_delayed1 < 0)
			n_delayed1 += (BUFFER_LENGTH+1);


	    //Delay2
		int n_delayed2 = n - d2;
		if (n_delayed2 < 0)
			n_delayed2 += (BUFFER_LENGTH+1);


		LeftOutput = LeftInput + ALPHA*delayBuffer1[n] + ALPHA*delayBuffer2[n];//Apply Filter

	    delayBuffer1[n_delayed1] = LeftInput;//Assign next input into buffer

	    delayBuffer2[n_delayed2] = LeftInput;//Assign next input into buffer

	    //If reached end of buffer size, start writing over buffer
	    if(n > BUFFER_LENGTH){
	    	n = 0;
	    	sampledCount++;
	    }

	    //Increase index
	    n++;
}

void Phasing(void)
{
	float gamma = 0.75;
	float a = gamma*gamma;
	float omega = 4*PI/SAMPLE_RATE;
	float A = PI/4;
	// TODO: Implement Phasing

	//Notch frequency
	float w01 = PI/20.0f + (9.0f*PI/20.0f-PI/20.0f)/2.0f * (1.0f+sinf(2.0f*PI*(n/SAMPLE_RATE)));
	float w02 = 3.0f*PI/10.0f + (7.0f*PI/10.0f-3.0f*PI/10.0f)/2.0f * (1.0f+sinf(4.0f*PI*(n/SAMPLE_RATE)));
	float B1 = cosf(w01);
	float B2 = cosf(w02);
	static float x1[3] = {0}, y1[3] = {0};
	static float x2[3] = {0}, y2[3] = {0};

	x1[2] = x1[1]; x1[1]=x1[0]; x1[0] = LeftInput;
	y1[2]=y1[1]; y1[1]=y1[0];
	y1[0] = 2.0f*B1*y1[1]-y1[2]+(2.0f/(1.0f+a))*(x1[0]-B1*(1.0f+a)*x1[1]+a*x1[2]);

	x2[2] = x2[1]; x2[1]=x2[0]; x2[0] = LeftInput;
	y2[2]=y2[1]; y2[1]=y2[0];
	y2[0] = 2.0f*B2*y2[1]-y2[2]+(2.0f/(1.0f+a))*(x2[0]-B2*(1.0f+a)*x2[1]+a*x2[2]);

	LeftOutput = LeftInput+y2[0]*y1[0];
}
