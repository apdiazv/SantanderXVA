//
// DESCRIPTION: ResultadoValorizacion
//

#ifndef RESULTADOVALORIZACION_H
#define RESULTADOVALORIZACION_H

#include <vector>

using namespace std;

struct ResultadoValorizacion
{
	string _netting_set;
	string _deal_number;
	int _time;
	//vector<vector<double>> _mtm;
	vector<double> _mtm;

	ResultadoValorizacion()	{	}
	ResultadoValorizacion(const ResultadoValorizacion& copyValorizacion)	
	{	
		_netting_set =  copyValorizacion._netting_set;
		_deal_number = copyValorizacion._deal_number;
        _time =  copyValorizacion._time; 
		_mtm = copyValorizacion._mtm;

	}

	ResultadoValorizacion(string netting_set, string deal_number, int time, vector<double> mtm)
	{		
		_netting_set =  netting_set;
		_deal_number = deal_number;
		_time = time;
		_mtm = mtm;
	}
};

#endif