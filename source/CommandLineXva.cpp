//
// DESCRIPTION: Main access
//

#include "headerFiles.h"

#include "cppinterface.h"
#include "Interface.h"

using namespace std;

int main(int argc, char* argv[])
{
	string pausa;

	vector<string> auxNettingSets;
	vector<double> stopTimes;
	double aux = getNettingSetsAndStopTimes(auxNettingSets, stopTimes);
	CellMatrix nettingSets(auxNettingSets.size(),2);

	for (unsigned int i = 0; i < auxNettingSets.size(); i++)
	{
		nettingSets(i, 0) = auxNettingSets[i].c_str();
		nettingSets(i, 1) = "Si";
		cout << auxNettingSets[i] << "\n";
	}

	cout << " Start Valorizacion \n";
	cout << " Numero Ns: " << auxNettingSets.size() << endl;
	cout << " Numero St: " << stopTimes.size() << endl;
	aux = startValorizacion(nettingSets, stopTimes);
	cout << aux << " Valorizacion OK \n";
	aux = startMetricas(nettingSets);
	cout << aux << " Metricas  OK \n";
	aux = startExposicionCrediticia(nettingSets);
	cout << aux << " Xva Ok \n";
	cin >> pausa;

	return 0;
}

