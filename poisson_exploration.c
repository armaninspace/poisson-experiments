#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

// globals 
static const gsl_rng_type * T;
static gsl_rng * r;
// end

void init();
double rnorm(double mu, double sd);
double runif(double a, double b);
unsigned int rpoisson(double mu);

int main (int argc, char **argv) {
  init();
  long numruns=100000000;
  double a1=0.1;
  double a2=0.2;
  double b1=0.4;
  double b2=0.6;
  int RES_MX=20;
  long resa[RES_MX];
  long resa_bar[RES_MX];
  long resb[RES_MX];
  long resaorb[RES_MX];
  long double lambda=1.;
  for (int i=0; i<RES_MX; i++) {
    resa[i]=0;
    resa_bar[i]=0;
    resb[i]=0;
    resaorb[i]=0;
  }
  for (long i=0; i<numruns; i++) {
    int n=rpoisson(lambda);
    int ina=0;
    int ina_bar=0;
    int inb=0;
    int inab=0;
    for (int j=0; j<n; j++) {
      double x=runif(0.,1.);
      if (a1<x && x<a2) {
	ina++;
      } else ina_bar++;
      if (b1<x && x<b2) {
	inb++;
      }
      if ((a1<x && x<a2) || (b1<x && x<b2)) {
	inab++;
      }
    }
    resa[ina]++;
    resa_bar[ina_bar]++;
    resb[inb]++;
    resaorb[inab]++;
  }
  printf("total number of runs = %ld\n", numruns);
  printf("lambda=%Lf\n",lambda);
  printf("the a region is (%f,%f)\n",a1,a2);
  printf("the a_bar region is (%f,%f)'\n",a1,a2);
  printf("the b region is (%f,%f)\n",b1,b2);
  printf("region,times_in_the_region,number_of_runs,proportion_of_runs\n");
  for (int i=0; i<RES_MX; i++) printf("a,%d,%ld,%lf\n", i, resa[i],(1.*resa[i]/numruns));
  for (int i=0; i<RES_MX; i++) printf("a_bar,%d,%ld,%lf\n", i, resa_bar[i],(1.*resa_bar[i]/numruns));
  for (int i=0; i<RES_MX; i++) printf("b,%d,%ld,%lf\n", i, resb[i],(1.*resb[i]/numruns));
  for (int i=0; i<RES_MX; i++) printf("a_or_b,%d,%ld,%lf\n", i, resaorb[i],(1.*resaorb[i]/numruns));
}

void init() {  
  T = gsl_rng_default;
  r = gsl_rng_alloc (T);
}

double rnorm(double mu, double sd) {
  return gsl_ran_gaussian(r, sd) + mu;
}

double runif(double a, double b) {
  return gsl_ran_flat(r, a, b);
}

unsigned int rpoisson(double mu) {
  return gsl_ran_poisson(r, mu);
}

