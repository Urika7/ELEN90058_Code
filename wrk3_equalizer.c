#include "SPWS3.h"
#include <math.h>

#define PI 3.14159265359
#define SAMPLE_RATE	24000.0

// Input samples
float LeftInput;
float RightInput;

// Output samples
float LeftOutput;
float RightOutput;

// Command Gains (GL, GM, and GH) which are changed by push-button switches 4-6
float GainL = 1.0;
float GainM = 1.0;
float GainH = 1.0;

// Declare any global variables you need

void Equalizer(void)
{
	static float wcL = 2*PI*2840/SAMPLE_RATE;
	static float wcM = 2*PI*4000/SAMPLE_RATE;
	static float wcH = 2*PI*5680/SAMPLE_RATE;

	float ol = tan(wcL/2);
	float oH = tan(wcH/2);
	float B = (wcH-wcL);
	float gl = GainL;
	float gH = GainH;
	float gm = GainM;

	float a1L= gl*pow(ol,2) + pow(ol,1/2)*pow(gl,3/4) + sqrt(gl);
	float a2L = 2*(gl*pow(ol,2)-sqrt(gl));
	float a3L = gl*pow(ol,2)-sqrt(2)*ol*pow(gl,3/4)+sqrt(gl);
	float b1L = sqrt(gl)+sqrt(2)*ol*pow(gl,1/4)+pow(ol,2);
	float b2L = 2*(pow(ol,2)-sqrt(gl));
	float b3L = sqrt(gl)-sqrt(2)*ol*pow(gl,1/4) + pow(ol,2);

	float a1H = gH + sqrt(2)*oH*pow(gH,3/4)+pow(oH,2)*sqrt(gH);
	float a2H = -2*(gH-pow(oH,2)*sqrt(gH));
	float a3H = gH-sqrt(2)*oH*pow(gH,3/4) + pow(oH,2)*(sqrt(gH));
	float b1H = sqrt(gH)*pow(oH,2)+sqrt(2)*oH*pow(gH,1/4) + 1;
	float b2H = 2*(sqrt(gH)*pow(oH,2)-1);
	float b3H = sqrt(gH)*pow(oH,2)-sqrt(2)*oH*pow(gH,1/4)+1;

	float a1M = sqrt(gm)+gm*tan(B/2);
	float a2M = -2*sqrt(gm)*cos(B);
	float a3M = sqrt(gm)-gm*tan(B/2);
	float b1M = sqrt(gm)+tan(B/2);
	float b2M = -2*sqrt(gm)*cos(B);
	float b3M = sqrt(gm)-tan(B/2);

	static float x[3] = {0}, y[3] = {0}, yH[3] = {0}, yM[3] = {0};
	x[0]=LeftInput;
	x[1]=x[0], x[2]=x[1];
	y[2]=y[1], y[1]=y[0];
	yH[2]=yH[1], yH[1]=yH[0];
	yM[2]=yM[1], yM[1]=yM[0];

	y[0] = 1/b1L*((a1L*x[0]+a2L*x[1]+a3L*x[2])-(b3L*y[2]+b2L*y[1]));
	yH[0] = 1/b1H*((a1H*y[0]+a2H*y[1]+a3H*y[2])-(b2H*yH[1]+b3H*yH[2]));
	yM[0] = 1/b1M*((a1M*x[0]+a2M*x[1]+a3M*x[2])-(b2M*yM[1]+b3M*yM[2]));
	// TODO: Implement your three band Equalizer containing two Shelving filter
	// and one peaking/notch filter. Use GainL, GainM, and GainH
	// as command gains of first, second, and third band respectively.

	LeftOutput = (GainL)*yM[0];
}
