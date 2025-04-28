#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#ifndef F_PI
#define F_PI		(float)M_PI
#endif

// print debugging messages?
#ifndef DEBUG
#define DEBUG		false
#endif

// setting the number of threads to use:
// (this a default value -- it can also be set from the outside by your script)
#ifndef NUMT
#define NUMT		    8
#endif

// setting the number of trials in the monte carlo simulation:
// (this a default value -- it can also be set from the outside by your script)
#ifndef NUMTRIALS
#define NUMTRIALS	500000
#endif

// how many tries to discover the maximum performance:
#ifndef NUMTRIES
#define NUMTRIES	30
#endif

unsigned int seed = 0;

const float GRAIN_GROWS_PER_MONTH =	       12.0;
const float ONE_DEER_EATS_PER_MONTH =		1.0;

const float AVG_PRECIP_PER_MONTH =		7.0;	// average
const float AMP_PRECIP_PER_MONTH =		6.0;	// plus or minus
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


omp_lock_t	Lock;
volatile int	NumInThreadTeam;
volatile int	NumAtBarrier;
volatile int	NumGone;

void	InitBarrier( int );
void	WaitBarrier( );
void    Deer();
void    Grain();
void    Watcher();
void    MyAgent();

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

// main program:
int
main( int argc, char *argv[ ] )
{
#ifndef _OPENMP
	fprintf( stderr, "No OpenMP support!\n" );
	return 1;
#endif

    

    // starting date and time:
    NowMonth =    0;
    NowYear  = 2025;

    // starting state (feel free to change this if you want):
    NowNumDeer = 2;
    NowHeight =  5.;

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
    		MyAgent( );	// your own
    	}
    }       // implied barrier -- all functions must return in order
    	// to allow any of them to get past here
}

void
Deer()
{
    while( NowYear < 2030 )
    {
        WaitBarrier();
        
        // Deer population growth based on available grain
        float grainPerDeer = NowHeight / (float)(NowNumDeer > 0 ? NowNumDeer : 1);
        
        if(grainPerDeer >= 3.0)  // Good conditions for population growth
            NowNumDeer += Ranf(0, 3); 
        else if(grainPerDeer >= 1.0)  // Stable conditions
            NowNumDeer += Ranf(-1, 2);
        else  // Scarce food conditions
            NowNumDeer += Ranf(-2, 0);
            
        if(NowNumDeer < 0)
            NowNumDeer = 0;
            
        printf("Deer: %d\n", NowNumDeer);
        WaitBarrier();
    }
}

void
Grain( )
{
    while( NowYear < 2030 )
    {
        WaitBarrier( );
        NowHeight += (GRAIN_GROWS_PER_MONTH * NowPrecip) - (NowNumDeer * ONE_DEER_EATS_PER_MONTH);
        if( NowHeight < 0. )
            NowHeight = 0.;
        printf( "Grain: %f\n", NowHeight );
        WaitBarrier( );
    }
}

void
Watcher( )
{
    while( NowYear < 2030 )
    {
        WaitBarrier( );
        float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );	// angle of earth around the sun

        float temp = AVG_TEMP - AMP_TEMP * cos( ang );
        NowTemp = temp + Ranf( -RANDOM_TEMP, RANDOM_TEMP );

        float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
        NowPrecip = precip + Ranf( -RANDOM_PRECIP, RANDOM_PRECIP );
        if( NowPrecip < 0. )
            NowPrecip = 0.;

        printf( "Year: %d Month: %d Temp: %f Precip: %f Height: %f Deer: %d\n",
                NowYear, NowMonth, NowTemp, NowPrecip, NowHeight, NowNumDeer );
        NowMonth++;
        if( NowMonth == 12 )
        {
            NowMonth = 0;
            NowYear++;
        }
        WaitBarrier( );
    }
}

void
MyAgent( )
{
    while( NowYear < 2030 )
    {
        WaitBarrier( );
        printf( "MyAgent: %d\n", NowYear );
        WaitBarrier( );
    }
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

void
WaitBarrier( )
{
    omp_set_lock( &Lock );
    {
            NumAtBarrier++;
            if( NumAtBarrier == NumInThreadTeam )
            {
                    NumGone = 0;
                    NumAtBarrier = 0;
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