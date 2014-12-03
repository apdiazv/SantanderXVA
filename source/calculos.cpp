#include "headerFiles.h"
#include "calculos.h"


bool isPositive(double element){ return ((int)element > 0); }
bool isNegative(double element){ return ((int)element < 0); }
bool isCero(double element){ return ((int)element == 0); }

double diffclock(clock_t  clock_1, clock_t clock_2)
{
	double diffticks = clock_1 -clock_2;
	double diffms = diffticks*1000 /CLOCKS_PER_SEC;
	return diffms;

}

string integerToString(int number)
{
   stringstream ss;	//create a stringstream
   ss << number;	//add number to the stream
   return ss.str();	//return a string with the contents of the stream
}

int  index(vector<double> data, double arg )
{ 
	int  inf = 0;
	int	 sup = data.size()-1;
	int  centro = (inf+sup)/2;
	int  indice = centro;
    if (data.size() < 2)
	{
		throw("At least two data points are needed");
		return 1;
	}
	while (inf <= sup)
	{
		if (arg == data[centro])
		{
			indice = centro;
			inf = data.size();
		}
		else
		{
			if (arg < data[centro])
				sup = centro-1;
			else
				inf = centro+1;
		indice = sup;
		}
		centro = (inf+sup)/2;

	}	
	if (indice < 0)
		indice = 0;

    return indice;
}

int  index(vector<int> data, int arg )
{ 
	int  inf = 0;
	int	 sup = data.size()-1;
	int  centro = (inf+sup)/2;
	int  indice = centro;
    if (data.size() < 2)
	{
		//throw("At least two data points are needed");
		return -1;
	}
	while (inf <= sup)
	{
		if (arg == data[centro])
		{
			// correccion SB
			indice = centro - 1;
			inf = data.size();
		}
		else
		{
			if (arg < data[centro])
				sup = centro-1;
			else
				inf = centro+1;
		indice = sup;
		}
		centro = (inf+sup)/2;

	}	
	if (indice < 0)
		indice = 0;

    return indice;
}

vector<double> clampedSpline(vector<double> x, vector<double> y)
{ 
	if (x.size() != y.size())
		throw(" The sizes of the input ranges are different");
	
	const signed long n = x.size()-1;
	double fp1,fpn ;
	
	vector <double> h(n), alpha(n+1);
	vector <double> l(n+1), u(n+1), z(n+1), c(n+1), b(n+1), d(n+1);
    
	fp1 = (y[1] - y[0]) / (x[1] - x[0]);
	fpn = (y[n] - y[n - 1]) / (x[n] - x[n - 1]);
  
	for (int i=0; i < n; i++)
		h.at(i) = x[i + 1] - x[i];
  
    alpha.at(0) = 3 * (y[1] - y[0]) / h[0] - 3 * fp1;
	alpha.at(n) = 3 * fpn - 3 * (y[n] - y[n - 1]) / h[n - 1];

	for (int i=1; i < n ; i++)
		alpha.at(i) = 3 * (y[i + 1] - y[i])/ h[i] - 3  * (y[i] - y[i - 1])/ h[i - 1];    
	
	l.at(0) = 2 * h[0]; 
	u.at(0) = 0.5; 
	z.at(0) = alpha[0] / l[0]; 	
	for (int i=1; i < n ; i++)
    {
		l.at(i) = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * u[i - 1];
		u.at(i)= h[i] / l[i];
		z.at(i) = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
	} 

	l.at(n) = h[n - 1] * (2 - u[n - 1]);
	z.at(n) = (alpha[n] - h[n - 1] * z[n - 1]) / l[n];
	c.at(n) = z[n];
	int i,j;
	for (j=1; j < (n+1) ; j++)
    {	         
		i=n-j;
		c.at(i) = z[i] - u[i] * c[i + 1];
		b.at(i) = (y[i + 1] - y[i]) / h[i] - h[i] * (c[i + 1] + 2 * c[i]) / 3;
		d.at(i) = (c[i + 1] - c[i]) /(3 *h[i]);
	}
	b.at(n) = d.at(n)=0;
	vector <double> _coef(d);

	_coef.insert(_coef.begin(),c.begin(),c.end());
	_coef.insert(_coef.begin(),b.begin(),b.end());
	_coef.insert(_coef.begin(),y.begin(),y.end());
	_coef.insert(_coef.begin(),x.begin(),x.end()); //Incluye x;

	x.clear(),y.clear(),h.clear(), alpha.clear(),l.clear(),u.clear(),z.clear();
	b.clear(),c.clear(),d.clear();
	
	return _coef;
}	

void covarianza (vector<double> sigma, matriz & rho)
{
	size_t n = rho.size();	
	for (unsigned int i=0; i< n;i++)
	{
		for(unsigned int j=0;j<n;j++)
		{
			rho.at(i).at(j)=sigma[i]*sigma[j]*rho[i][j];
		}
	}
}

void cholesky(matriz & sigma)
{
    size_t n = sigma.size();
    std::vector<double> p;
    double sum;
    double a;
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = i; j < n; j++)
        {
            sum = sigma[i][j];
            for (unsigned int k = 0; k < i; k++)
            {
                sum = sum - sigma[i][k] * sigma[j][k];
            }
            if (i == j)
            {
                if (sum <= 0) throw "Error";
                p.push_back(sqrt(sum));
            }
            else
            {
                sigma[j][i] = sum / p[i];

            }
        }
    }
    
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = i; j < n; j++)
        {
            if (i == j)
            {
                a = p[i];
            }
            else
            {
                a = 0;
            }
            sigma[i][j] = a;

        }
    }
	p.clear();
}

vector<double> mmult(matriz sigma, vector<double> z)
{
	size_t n = sigma.size();
	vector<double> _z(n);
	for (unsigned int i = 0; i < n; i++)
	{
		double suma = 0;
		for (unsigned int j = 0; j < n; j++)
		{
		suma = (sigma[i][j]) * z[j] + suma;
		}
		_z.at(i) = suma;
	}
	return _z;
}

vector<double> getErroresNoCorrelacionados(size_t n)
{
	vector<double> z(n);
	for(unsigned int i = 0; i < n; i++)
    {
		z.at(i) = gauss();
	}
	return z;
}

matriz covarianza(vector<pair <string, string>> _factoresParaSimular, map<string, double> _sigma, map<string, Rho> _rho)
{
	string auxStr;
	size_t n = _factoresParaSimular.size();
	matriz result(n, n);	
	for (unsigned int i = 0; i < n; i++)
	{
		for (unsigned int j = i + 1; j < n; j++)
		{
			auxStr = _factoresParaSimular[i].first + "$" + _factoresParaSimular[j].first;
			result.at(i).at(j) = _sigma[_factoresParaSimular[i].first] * _sigma[_factoresParaSimular[j].first] * _rho[auxStr].valor();
		}
		
		for (unsigned int j = 0; j < i; j++)
		{
			result.at(i).at(j) = result[j][i];
		}

		result.at(i).at(i) = _sigma[_factoresParaSimular[i].first] * _sigma[_factoresParaSimular[i].first];
	}
	
	return result;
}

double getInterpolationRate(Curva* curva, double t)
{
   Interpola* _result = new Interpola(curva);
  _result->getIndice(t);
  double _r = _result->getRate();
  delete _result;
  return _r;
}

double mean(vector<double> v)
{
	double result = 0;
	for (unsigned int i = 0; i < v.size(); i++)
	{
		result= v[i]+result;
	}
	return result/v.size();
}

double percentil(std::vector<double> x, double z)
{
    long n;
    long LowPos;
    long UppPos;
    double LowScore;
    double UppScore;
    double LowPerc;
    double UppPerc;
    
    std::sort(x.begin(), x.end());
    /*for (int i = 0; i < x.size(); i++)
    {
        std::cout << "input " << i << " es: " << x[i] << std::endl;
    }
    */
    n = x.size();
    
    if (floor(z * n + 0.5) == 0)
    {

        return x[0];
    }
    else if (floor(z * n + 0.5) == n)
    {
        return x[n - 1];
    }
    else
    {
        LowPos = (long) floor(z * n + 0.5);
        //std::cout << LowPos << std::endl;
        
        UppPos = (long) floor(z * n + 0.5) + 1;
        //std::cout << UppPos << std::endl;
        
        LowScore = x[LowPos - 1];
        //std::cout << LowScore << std::endl;
        
        UppScore = x[UppPos - 1];
        //std::cout << UppScore << std::endl;
        
        LowPerc = (double(LowPos) - 0.5) / double(n);
        //std::cout << LowPerc << std::endl;
        
        UppPerc = (double(UppPos) - 0.5) / double(n);
        //std::cout << UppPerc << std::endl;

		double result = (LowScore * (UppPerc - z) + UppScore * (z - LowPerc)) / (UppPerc -LowPerc);


        return  result;
    }
}


double getProbDefaultAtStopTime(map<int, pair<double, double> > probDefault, double stopTime, string nombre)
{
    map<int, pair<double, double> > ::iterator it;// = ;
	double result = 0;
	double auxProb = 1.0;
	it = probDefault.begin();
	if (nombre == "inst")
	{
		result = it->second.first;
		auxProb = (1 - it->second.first);

		while (it != probDefault.end() && it->first != stopTime)
		{
			++it; // Corregido el 26/11 
			result = result + auxProb * (it->second.first);
			auxProb = auxProb * (1 - it->second.first);
			//++it; 
		}
	}
	else if (nombre == "cont")
	{
		result = it->second.second;
		auxProb = (1 - it->second.second);
		while (it != probDefault.end() && it->first != stopTime)
		{
			++it; 
			result = result + auxProb * (it->second.second);
			auxProb = auxProb * (1 - it->second.second);
			//++it;
		}
	}
	
	return result;
}

int getStoppingTimeFromTime(double time)
{
	double param, fractpart, intpart;
	param = time/DT;
	fractpart = abs(modf(param , &intpart));
	if (0.5 < fractpart || 0.5 == fractpart)
	{
		if(intpart >= 0)
		{
			intpart = intpart + 1;
		}
		else
		{
			intpart = intpart - 1;
		}
	}
	return (int)intpart;
}


void calendar(int startTime, int expiryTime, int period, string stubPeriod, vector<int>&times)
{
	double param = (double)(expiryTime - startTime)/period ;
	double fractpart, intpart;
	fractpart = modf (param , &intpart);
	bool flag = false;
	int numPeriods = (int)intpart;	
	if ( 0.5 < fractpart || 0.5 == fractpart)
	flag = true; 
	//  Un StubPeriod  corto acepta un periodo un poco más largo pero no al revés.
	//  StubPeriod Default == CortoAlInicio
	if ( stubPeriod == "CortoAlFinal")
	{
		int i = 1;
		int auxDate = startTime;
		if (flag)
		numPeriods = numPeriods + 1;
		while (auxDate < expiryTime && i < (numPeriods + 1)) 
		{
			times.push_back(auxDate);
			auxDate = startTime + i * period;					
				i++;
		}
			times.push_back(expiryTime);
			sort(times.begin(), times.end());
	}
	else if(stubPeriod == "LargoAlInicio")
	{
		int i = 1;
		int auxDate = expiryTime;
		//if (flag)
		//numPeriods = numPeriods + 1;					
		while (auxDate > startTime && i < (numPeriods + 1)) 
		{
			times.push_back(auxDate);
			auxDate = expiryTime - i * period;					
			i++;
		}
			times.push_back(startTime);
			sort(times.begin(), times.end());
	}
	else if ( stubPeriod == "LargoAlFinal")
	{
		int i = 1;
		int auxDate = startTime;
		//if (flag)
		//numPeriods = numPeriods + 1;
		while (auxDate < expiryTime && i < (numPeriods + 1)) 
		{
			times.push_back(auxDate);
			auxDate = startTime + i * period;					
			i++;
		}
			times.push_back(expiryTime);
			sort(times.begin(), times.end());
	}
	else
	{
		int i = 1;
		int auxDate = expiryTime;
		if (flag)
		numPeriods = numPeriods + 1;					
		while (auxDate > startTime && i < (numPeriods + 1)) 
		{
			times.push_back(auxDate);
			auxDate = expiryTime - i * period;					
			i++;
		}
		times.push_back(startTime);
		sort(times.begin(), times.end());
	}
	
}


double amortization(string type, int timeC, int expiryTime, double valueRate ,int numPeriods)
{
	// BULLET is default case.
    double result = 0.0;
	if (type == "GERMAN")
	{
		if (timeC < expiryTime || timeC  == expiryTime)
				result = (double)(1.0 / numPeriods );
	} 
	else if (type == "FRENCH")
	{ //Implementar
		
	}
	else if (type == "CUSTOM")
	{//Implementar
	}
	else
	{
		if (timeC  == expiryTime)
		result = 1.0;
	}
	return result;
}

double amortization(string type, const vector<int>& couponTimes, double valueRate, vector<double>& percAmor)
{
	return valueRate;
}


double interest(string formaTasa, int t0, int t1, double valueRate, double spread)
{
	double result = 0.0;
	//el Caso default es "Lin"
	if ( formaTasa == "Com" )
	{
		result = pow((1 + valueRate + spread), (t1 - t0)*DT) - 1 ;
	}
	else
	{ 
		result = (t1 - t0)*DT*(valueRate + spread) ;
	}
	return result;
}







/*Interpolations.h*/

 double qcLinInterpol(vector<double> data1, vector<double> data2,  double arg,  int type )
{
	// std::
	short indice;
	const short TAM = data1.size()-1;
	double RetVal;
	double slope = 0.0;
    if (data1.size() != data2.size())
        throw(" The sizes of the input ranges are different");
    
    indice = index(data1, arg);

	if (arg <= data1[0] || indice == TAM)
		RetVal = data2[indice];
	else
	{   
		slope = (data2[indice+1]-data2[indice])/(data1[indice+1]-data1[indice]);
		RetVal = slope*(arg-data1[indice])+data2[indice];
	}

	/*if (type=="d")
		return slope;
	else
		return RetVal;*/

	switch (type)
	{
	case 1:return slope;//first derivative
		break;
	case 2:return 0;//second derivative
		break;
	default:return RetVal;// interpolation
		break;
	}
}

 
double qcCubicSpline(vector<double> x, vector<double> y, double arg, int type)
{ 
	if (x.size() != y.size())
        throw(" The sizes of the input ranges are different");

	const unsigned long n = x.size()-1;
	//double fp1, fpn ;
	vector<double> h(n), alpha(n+1);
	vector<double> l(n+1), u(n+1), z(n+1), c(n+1), b(n+1), d(n+1);
    
	//fp1 = (y[1] - y[0]) / (x[1] - x[0]);
	//fpn = (y[n] - y[n - 1]) / (x[n] - x[n - 1]);
  
	for (unsigned int i = 0; i < n; i++)
		h[i] = x[i + 1] - x[i];
  
    alpha[0] = 0; //3 * (y[1] - y[0]) / h[0] - 3 * fp1;
	alpha[n] = 0;//3 * fpn - 3 * (y[n] - y[n - 1]) / h[n - 1];	
	for (unsigned int i = 1; i < n ; i++)
		alpha[i] = 3 * (y[i + 1] - y[i])/ h[i] - 3  * (y[i] - y[i - 1])/ h[i - 1];    
	
	l[0] = 2 * h[0]; 
	u[0] = 0;// En Clamped 0.5; 
	z[0] = alpha[0] / l[0]; 	
	for (unsigned int i = 1; i < n ; i++)
    {
		l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * u[i - 1];
		u[i] = h[i] / l[i];
		z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
	}  
	l[n] = 1;//h[n - 1] * (2 - u[n - 1]);
	z[n] = 0;//(alpha[n] - h[n - 1] * z[n - 1]) / l[n];
	c[n] = z[n];
	unsigned int  i, j;
	for (j = 1; j < (n+1) ; j++)
    {	         
		i = n-j;
		c[i] = z[i] - u[i] * c[i + 1];
		b[i] = (y[i + 1] - y[i]) / h[i] - h[i] * (c[i + 1] + 2 * c[i]) / 3;
		d[i] = (c[i + 1] - c[i]) /(3 *h[i]);
	}
	b[n] = d[n]=0;
    /*MyMatrix Aux(n+1, 5);
	for (i=0; i < (n+1) ; i++)
	{
		Aux(i, 0)=x[i];
		Aux(i, 1)=y[i];
		Aux(i, 2)=b[i];
		Aux(i, 3)=c[i];
		Aux(i, 4)=d[i];
	}*/		
	unsigned int k = index(x, arg);
	if (k < n)
		k = k;
	else
		k = k-1;
	//vector<double> h(n), alpha(n+1);
	//vector<double> l(n+1), u(n+1), z(n+1), c(n+1), b(n+1), d(n+1);
	h.clear();
	alpha.clear();
	l.clear();
	u.clear();
	z.clear();

	switch (type)
	{
	case 1:return b[k] + 2*c[k] * (arg - x[k]) + 3*d[k] * (arg - x[k])*(arg - x[k]);//first derivative
		break;
	case 2:return 2*c[k]+ 6*d[k] * (arg - x[k]);//second derivative
		break;
	default:return y[k] + (arg - x[k])* (b[k] + c[k] * (arg - x[k]) + d[k] * (arg - x[k])*(arg - x[k]));// interpolation
		break;
	}
	
}


double  qcClampedSpline(vector<double> x, vector<double> y, double arg, int type)
{ 
	if (x.size() != y.size())
        throw(" The sizes of the input ranges are different");

	const unsigned long n = x.size()-1;
	double fp1, fpn ;
	vector<double> h(n), alpha(n+1);
	vector<double> l(n+1), u(n+1), z(n+1), c(n+1), b(n+1), d(n+1);
    
	fp1 = (y[1] - y[0]) / (x[1] - x[0]);
	fpn = (y[n] - y[n - 1]) / (x[n] - x[n - 1]);
  
	for (unsigned int i = 0; i < n; i++)
		h[i] = x[i + 1] - x[i];
  
    alpha[0] = 3 * (y[1] - y[0]) / h[0] - 3 * fp1;
	alpha[n] = 3 * fpn - 3 * (y[n] - y[n - 1]) / h[n - 1];	
	for (unsigned int i = 1; i < n ; i++)
		alpha[i] = 3 * (y[i + 1] - y[i])/ h[i] - 3  * (y[i] - y[i - 1])/ h[i - 1];    
	
	l[0] = 2 * h[0]; 
	u[0] = 0.5; 
	z[0] = alpha[0] / l[0]; 	
	for (unsigned int i = 1; i < n ; i++)
    {
		l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * u[i - 1];
		u[i] = h[i] / l[i];
		z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
	} 

	l[n] = h[n - 1] * (2 - u[n - 1]);
	z[n] = (alpha[n] - h[n - 1] * z[n - 1]) / l[n];
	c[n] = z[n];
	unsigned int i, j;
	for (j = 1; j < (n+1) ; j++)
    {	         
		i = n-j;
		c[i] = z[i] - u[i] * c[i + 1];
		b[i] = (y[i + 1] - y[i]) / h[i] - h[i] * (c[i + 1] + 2 * c[i]) / 3;
		d[i] = (c[i + 1] - c[i]) /(3 *h[i]);
	}
	b[n] = d[n] = 0;
	
	unsigned int k = index(x, arg);
	if (k < n)
		k = k;
	else
		k=k-1;

	h.clear();
	alpha.clear();
	l.clear();
	u.clear();
	z.clear();
	
	switch (type)
	{
	case 1:return b[k] + 2*c[k] * (arg - x[k]) + 3*d[k] * (arg - x[k])*(arg - x[k]);//first derivative
		break;
	case 2:return 2*c[k]+ 6*d[k] * (arg - x[k]);//second derivative
		break;
	default:return y[k] + (arg - x[k])* (b[k] + c[k] * (arg - x[k]) + d[k] * (arg - x[k])*(arg - x[k]));// interpolation
		break;
	}
}
 
 double interpolations(vector<double> data1, vector<double> data2,  double arg,  int type )
 {
	double result=0.0;
	switch (type)
	{
	//Cubic Spline Interpolation
	case 1:result = qcCubicSpline(data1, data2, arg, 0);
		break;
	//Clamped Spline Interpolation
	case 2:result = qcClampedSpline(data1, data2, arg,0);
		break;
	// Lineal Interpolation
	default:result = qcLinInterpol(data1, data2, arg, 0);
		break;
	}
	return result;
 }

 double derivatives(vector<double> data1, vector<double> data2, double arg, int type )
 {
	double result = 0.0;
	switch (type)
	{
	//Cubic Spline Interpolation
	case 1:result = qcCubicSpline(data1, data2, arg, 1);
		break;
	//Clamped Spline Interpolation
	case 2:result = qcClampedSpline(data1, data2, arg, 1);
		break;
	// Lineal Interpolation
	default:result = qcLinInterpol(data1, data2, arg, 1);
		break;
	}
	return result;
 }

  double seconderivatives(vector<double> data1, vector<double> data2,  double arg, int type )
 {
	double result = 0.0;
	switch (type)
	{
	//Cubic Spline Interpolation
	case 1:result = qcCubicSpline(data1, data2, arg, 2);
		break;
	//Clamped Spline Interpolation
	case 2:result = qcClampedSpline(data1, data2, arg,  2);
		break;
	// Lineal Interpolation
	default:result = qcLinInterpol(data1, data2, arg, 2);
		break;
	}
	return result;
 }

/*Pointer to map
    map<string, Curva> _curva;
	map<string, double> _gamma;
	map<string, double> _sigma;
	map<string, Rho> _rho;
	matriz _cholesky;
	map<string, vector<double>> _thetas;
*/	
