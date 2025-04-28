#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

unsigned int seed = 0;

const float GRAIN_GROWS_PER_MONTH =	       10.0;
const float ONE_DEER_EATS_PER_MONTH =		1.0;
const float ONE_PREDATOR_EATS_PER_MONTH =		1.0;	// predator eats 2 deer per month

const float AVG_PRECIP_PER_MONTH =		3.0;	// average
const float AMP_PRECIP_PER_MONTH =		2.0;	// plus or minus
const float RANDOM_PRECIP =			2.0;	// plus or minus noise

const float AVG_TEMP =				60.0;	// average
const float AMP_TEMP =				20.0;	// plus or minus
const float RANDOM_TEMP =			10.0;	// plus or minus noise

const float MIDTEMP =				40.0;
const float MIDPRECIP =				10.0;


int	NowYear;		// 2025- 2030
int	NowMonth;		// 0 - 11

float	NowPrecip;		// inches of rain per month
float	NowTemp;		// temperature this month
float	NowHeight;		// grain height in inches
int	NowNumDeer;		// number of deer in the current population
int NowNumPredator;	// number of predators in the current population


omp_lock_t	Lock;
volatile int	NumInThreadTeam;
volatile int	NumAtBarrier;
volatile int	NumGone;

enum BarrierType { B_COMPUTE, B_ASSIGN, B_PRINT };
BarrierType CurrentBarrier = B_COMPUTE;

void	InitBarrier( int );
void	WaitBarrier(BarrierType);
void    Deer();
void    Grain();
void    Watcher();
void    Predator();

float
Ranf( float low, float high )
{
    float r = (float) rand();               // 0 - RAND_MAX
    float t = r  /  (float) RAND_MAX;       // 0. - 1.

    return   low  +  t * ( high - low );
}

int
Ranf( int ilow, int ihigh )
{
    float low = (float)ilow;
    float high = ceil( (float)ihigh );

    return (int) Ranf(low,high);
}

// call this if you want to force your program to use
// a different random number sequence every time you run it:
void
TimeOfDaySeed( )
{
	time_t now;
	time( &now );

	struct tm n;
	struct tm jan01;
#ifdef WIN32
	localtime_s( &n, &now );
	localtime_s( &jan01, &now );
#else
	n =     *localtime(&now);
	jan01 = *localtime(&now);
#endif
	jan01.tm_mon  = 0;
	jan01.tm_mday = 1;
	jan01.tm_hour = 0;
	jan01.tm_min  = 0;
	jan01.tm_sec  = 0;

	double seconds = difftime( now, mktime(&jan01) );
	unsigned int rseed = (unsigned int)( 1000.*seconds );    // milliseconds
	srand( rseed );
}

// specify how many threads will be in the barrier:
//	(also init's the Lock)

void
InitBarrier( int n )
{
    NumInThreadTeam = n;
    NumAtBarrier = 0;
	omp_init_lock( &Lock );
}


// have the calling thread wait here until all the other threads catch up:
void WaitBarrier(BarrierType bt)
{
    omp_set_lock( &Lock );
    {
            NumAtBarrier++;
            if( NumAtBarrier == NumInThreadTeam )
            {
                NumGone = 0;
                NumAtBarrier = 0;
                switch (bt)
                {
                    case B_COMPUTE: 
                        CurrentBarrier = B_ASSIGN; 
                        break;
                    case B_ASSIGN: 
                        CurrentBarrier = B_PRINT; 
                        break;
                    case B_PRINT: 
                        CurrentBarrier = B_COMPUTE;
                        break;
                }
                // let all other threads get back to what they were doing
		        // before this one unlocks, knowing that they might immediately
		        // call WaitBarrier( ) again:
                while( NumGone != NumInThreadTeam-1 );
                omp_unset_lock( &Lock );
                return;
            }
    }
    omp_unset_lock( &Lock );

    while( NumAtBarrier != 0 );	// this waits for the nth thread to arrive

    #pragma omp atomic
    NumGone++;			// this flags how many threads have returned
}

void Deer()
{
    while( NowYear < 2030 )
    {
        // Wait for compute
        if (CurrentBarrier != B_COMPUTE)
            WaitBarrier(CurrentBarrier);

        int nextNumDeer;
        nextNumDeer = NowNumDeer;  // Start from current population
        
        // Deer population growth based on available grain
        float grainPerDeer = NowHeight / (float)(NowNumDeer > 0 ? NowNumDeer : 1);

        if(grainPerDeer >= 3.0)  // Good conditions for population growth
            nextNumDeer += Ranf(2, 8); 
        else if(grainPerDeer >= 1.0)  // Stable conditions
            nextNumDeer += Ranf(-2, 4);
        else  // Scarce food conditions
            nextNumDeer  += Ranf(-4, 0);

        if(NowNumPredator > 0)
            nextNumDeer -= (int)(NowNumPredator * ONE_PREDATOR_EATS_PER_MONTH);
            
        if(nextNumDeer < 0)
            nextNumDeer = 0;
            
        // Done computing - wait for all threads
        WaitBarrier(B_COMPUTE);

        NowNumDeer = nextNumDeer;
        // Done assigning - wait for all threads
        WaitBarrier(B_ASSIGN);
        
        // Wait for the watcher to print
        WaitBarrier(B_PRINT);
    }
}

void Grain( )
{
    while( NowYear < 2030 )
    {
        if (CurrentBarrier != B_COMPUTE)
            WaitBarrier(CurrentBarrier);

        float nextHeight;
        nextHeight = NowHeight;

        float tempFactor = 1.0 - (0.05 * fabs(NowTemp - MIDTEMP));
        if(tempFactor < 0.0)
            tempFactor = 0.0;

        nextHeight += ((GRAIN_GROWS_PER_MONTH * NowPrecip) * tempFactor) - 
        (NowNumDeer * ONE_DEER_EATS_PER_MONTH);
        if(nextHeight < 0.)
            nextHeight = 0.;
        
        // Done computing - wait for all threads
        WaitBarrier(B_COMPUTE);

        NowHeight = nextHeight;
        // Done assigning - wait for all threads
        WaitBarrier(B_ASSIGN);
        
        // Wait for the watcher to print
        WaitBarrier(B_PRINT);
    }
}

void Predator( )
{
    while( NowYear < 2030 )
    {
        if (CurrentBarrier != B_COMPUTE)
            WaitBarrier(CurrentBarrier);

        // Compute next value in local variable
        int nextNumPredator;
        nextNumPredator = NowNumPredator;

        // Predator population growth based on available deer
        float deerPerPredator = NowNumDeer / (float)(NowNumPredator > 0 ? NowNumPredator : 1);

        if(deerPerPredator >= 4.0)  // Good conditions for predator growth
            nextNumPredator += Ranf(0, 2); 
        else if(deerPerPredator >= 2.0)  // Stable conditions
            nextNumPredator += Ranf(-1, 1);
        else  // Scarce food conditions
            nextNumPredator += Ranf(-2, 0);

        if(nextNumPredator < 0)
            nextNumPredator = 0;

        // Done computing - wait for all threads
        WaitBarrier(B_COMPUTE);

        NowNumPredator = nextNumPredator;
        // Done assigning - wait for all threads
        WaitBarrier(B_ASSIGN);
        
        // Wait for the watcher to print
        WaitBarrier(B_PRINT);
    }
}

void Watcher( )
{
    while( NowYear < 2030 )
    {
        // Wait for compute
        if (CurrentBarrier != B_COMPUTE)
            WaitBarrier(CurrentBarrier);
            
        // Wait for compute
        WaitBarrier(B_COMPUTE);
        
        // Wait for assignment
        WaitBarrier(B_ASSIGN);

        float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );	// angle of earth around the sun

        float temp = AVG_TEMP - AMP_TEMP * cos( ang );
        NowTemp = temp + Ranf( -RANDOM_TEMP, RANDOM_TEMP );

        float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
        NowPrecip = precip + Ranf( -RANDOM_PRECIP, RANDOM_PRECIP );
        if( NowPrecip < 0. )
            NowPrecip = 0.;

        int Months = 0;
        Months = (NowYear - 2025) * 12 + NowMonth;

        #define CSV_OUTPUT
        #ifdef CSV_OUTPUT

        printf( "%d,%f,%f,%f,%d,%d\n",
                Months, NowTemp, NowPrecip, NowHeight, NowNumDeer, NowNumPredator );
        #else
        printf( "Year: %d Month: %d Temp: %f Precip: %f GrainHeight: %f Deer: %d Predators: %d\n",
            NowYear, NowMonth, NowTemp, NowPrecip, NowHeight, NowNumDeer, NowNumPredator );
        #endif
        NowMonth++;
        if( NowMonth == 12 )
        {
            NowMonth = 0;
            NowYear++;
        }
        // Done printing
        WaitBarrier(B_PRINT);
    }
}

// main program:
int main( int argc, char *argv[ ] )
{
#ifndef _OPENMP
	fprintf( stderr, "No OpenMP support!\n" );
	return 1;
#endif
    // starting date and time:
    NowMonth =    0;
    NowYear  = 2025;

    // starting state (feel free to change this if you want):
    NowNumDeer =  50;
    NowHeight =  1000.;
    NowNumPredator = 6;

    omp_set_num_threads( 4 );	// same as # of sections
    InitBarrier( 4 );
    #pragma omp parallel sections
    {
    	#pragma omp section
    	{
    		Deer( );
    	}

    	#pragma omp section
    	{
    		Grain( );
    	}

    	#pragma omp section
    	{
    		Watcher( );
    	}

    	#pragma omp section
    	{
    		Predator( );	// your own
    	}
    }       // implied barrier -- all functions must return in order
    	// to allow any of them to get past here
}