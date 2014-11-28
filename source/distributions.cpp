
#include "headerFiles.h"
#include "distributions.h"

double cumNormalDist(double x)
{
   // Cumulative Normal Distribution
	double build;
	double absX;
	double aux;

	if (x < 0)
	{
		absX = -x;
	}
	else
	{
		absX = x;
	}
	
	if (absX > 37)
	{
		if (x < 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		double exponential = exp(-.5 * absX * absX);
		if (absX < 7.07106781186547)
		{
			build = 3.52624965998911E-02 * absX + 0.700383064443688;
			build = build * absX + 6.37396220353165;
			build = build * absX + 33.912866078383;
			build = build * absX + 112.079291497871;
			build = build * absX + 221.213596169931;
			build = build * absX + 220.206867912376;
			aux = exponential * build;
			build = 8.83883476483184E-02 * absX + 1.75566716318264;
			build = build * absX + 16.064177579207;
			build = build * absX + 86.7807322029461;
			build = build * absX + 296.564248779674;
			build = build * absX + 637.333633378831;
			build = build * absX + 793.826512519948;
			build = build * absX + 440.413735824752;
			aux = aux / build;
		}
		else
		{
			build = absX + 0.65;
			build = absX + 4 / build;
			build = absX + 3 / build;
			build = absX + 2 / build;
			build = absX + 1 / build;
			aux = exponential / build / 2.506628274631;
		}
	}

	if (x > 0)
	{
		aux = 1 - aux;
	}

	return aux;

}

double invCumNormalDist(double u)
{ 
	double a[]={2.50662823884, -18.61500062529, 41.39119773534, -25.44106049637};
	double b[]={-8.4735109309, 23.08336743743, -21.06224101826, 3.13082909833};
	double c[]={0.337475482272615, 0.976169019091719, 0.160797971491821, 0.0276438810333863, 0.0038405729373609, 0.0003951896511919, 0.0000321767881768, 0.0000002888167364, 0.0000003960315187};
    
	double x;
	double r;

	x=u-0.5;
		if ((abs(x)-0.42)<=TOL )//x<=0.42
		  {
             r=x*x;
			 r=x*(a[0]+r*(a[1]+r*(a[2]+r*a[3])))/(1+r*(b[0]+r*(b[1]+r*(b[2]+r*b[3]))));
		  }
		else
		  {
			  r=u;
			  if (x> TOL )//x>0
				r=1-u;

			  r=log(-log(r));
			  r=c[0] + r * (c[1] + r * (c[2] + r * (c[3] + r * (c[4] + r * (c[5] + r * (c[6] + r * (c[7] + r * c[8])))))));
				
			  if (x< TOL )//x<0
			    r=-r;			      
		  }
	return r;
}

double uniforme()
{
	return  ((double)(rand()+0.5) / (RAND_MAX+1.0));
}

double gauss ()
{
	return invCumNormalDist(uniforme());
}
