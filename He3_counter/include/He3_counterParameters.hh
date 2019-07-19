#ifndef He3_counterParameters_h
#define He3_counterParameters_h 1

#define RAD  .48	   	//Detector radius in cm
//#define RAD  .14	   	//Detector radius in cm


#define WIDTH  6.2   	//width of detector from 4th counters in cm
//#define WIDTH  1.2   	//width of detector from 4th counters in cm

#define RAD_wire  .01	   	//Detector radius in cm
//#define LENGTH  0.01 		//Detector length in cm
#define LENGTH  1.0 		//Detector length in cm

#define FACTOR 1		// Multiplying factor
//#define FACTOR 1		// Multiplying factor
//#define pAr 1.0*FACTOR		// Ar partial pressure in bar

#define pAr 0.0*FACTOR		// Ar partial pressure in bar
#define pCO2 0.0*FACTOR	//CO2 partial pressure in bar
#define pCF4 0.0*FACTOR	//CF4 partial pressure in bar
#define pHe3 0.5*FACTOR		//He3 partial pressure in bar

#define POSITION 100		//in mm
//#define POSITION 200		//in mm

#define OUTPUTFILE1	"./results/ReactionPositions.txt"
#define OUTPUTFILE2	"./results/DepositedEnergy.txt"

#endif
