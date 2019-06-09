//MonteCarlo is a method of solving problem using statistics.
//Lets say probability of an event to occure when certain conditions generated in given samples is P.
//P=N/M, where N is total no of samples and M is number of event generated.
//To calculate value of pi, it can be used as out of N points within a square of  edges 2R size M number of points comes inside circle of radius R.
//So, N/M = (2R)^2/pR^2
//N/M = 4/p
//and p = 4M/N -- pi calculated as probability here.
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>

using namespace std;

int main()
{

int sq_point = 0; 
int cr_point =0;
const int RADIUS = 1;
srand(unsigned(time(0))); //initialise random  no generator

for(int i=0 ; i< 1000; i++)
{
      double x = double(rand()%1000)/1000;
      double y = double(rand()%1000)/1000;

      double distanceFrmCntr = (x*x)+(y*y);
      if (distanceFrmCntr < 1)
         cr_point++;
      sq_point++;
}

double pi = double(4*cr_point)/sq_point;
cout << pi << endl;

return 0;
}
