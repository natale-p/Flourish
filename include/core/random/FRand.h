//-*-Mode: C++;-*-
#ifndef _FRand_h_
#define _FRand_h_


#include <stddef.h>
#include <QDataStream>

double		URand(int *);
double		Sen3a(void);
double		Crusk(void);
double		Exponencial(int *, double);
double		ShifExp(int *, double, double);
double		Normal(int *, double, double);
double		Normal_Mm(int *, double, double, double, double);
double		HWay(int *, double, double, double, double);
double		Erlang(int *, double, int);
double		Poisson(int *, double, double, double);
double		Uniform(int *, double, double);
int			Bernoulli(int *, double);
int			Binomial(int *, int, double);
int			Binomial(double, int, double);
int			RandomClass(int * seed, int n); // returns a number between 0 and n-1

double GetHeadway(int headwayType, double timeBetweenVehs, double shiftfactor, int *seed);

class ARandomGenerator
{
public:
	ARandomGenerator();
	ARandomGenerator(const ARandomGenerator & otherRNG);
	ARandomGenerator(int aseed);
	virtual ~ARandomGenerator();

    ARandomGenerator &operator=(ARandomGenerator const & other);


	void setSeed(int aseed);
	int getSeed() const;

	int * getRefSeed();

	virtual double random01();

	double uniform(double a, double b);
	static double uniform(double value01, double a, double b);

	double normal(double mu, double sigma);
	double normalfull(double mu, double sigma);
	/*! firstRandomNum and secondRandomNum can be externally specified and also returned. When they are not null and their value is > 0 they will be used instead of generating them using the random01() function.
	 *	If they are not null, the random numbers used will be returned. */
	double normal_mt(double mu, double sigma, double amin, double amax, double * firstRandomNum = NULL, double * secondRandomNum = NULL );
	double lognormal_mt(double mu, double sigma, double min, double max);
	double exponential(double lambda);
	double getHeadway(int headwayType, double timeBetweenVehs, double shiftfactor);
	int randomClass(int n);
	int getNewSeed();

    void storeState(QDataStream & stream);
    void restoreState(QDataStream & stream);
protected:
	int seed;
};




#endif
