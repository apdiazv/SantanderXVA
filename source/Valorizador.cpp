#include "headerFiles.h"
#include "Valorizador.h"


bool Valorizador::instanceFlag = false;
Valorizador* Valorizador::valor = NULL;
clock_t clock_2, clock_3;

Valorizador* Valorizador::getInstance()
{
	if (!instanceFlag)
	{
		valor = new Valorizador;
		instanceFlag = true;
	}
	return valor;
}


Valorizador::Valorizador(void)
{
  //cout <<" Constructing Valorizador "<< "\n";

}

Valorizador::~Valorizador(void)
{
	instanceFlag = false;
    storeCurvas.clear();
	storeHullWhite.clear();
	//cout <<" Destructing Valorizador" << "\n";
}

double Valorizador::valorOperacion(Operacion* op)
{
	if (op->tipo == "FWD")
	{
		Forward* fwd =static_cast<Forward*>(op->oper);
		return Valorizador::valorForward(fwd);
	}
	return 0.0;
}

double Valorizador::valorOperacionScenario(Operation op, const vector<double>& st, vector<vector<double> >& m2m, string moneda)
{
	if (op._type == "FWD")
	{
		return Valorizador::valorForwardScenario(op, st, m2m, moneda);
	}
	else if(op._type == "SWAP")
	{
		
	}
	
	return 0.0;
}

double Valorizador::valorOperacionScenario(Operation op, double st, map<string, double>& sim, vector<double>& m2m, string moneda)
{
    if (op._type == "FWD")
	{
		return Valorizador::valorForwardScenario(op, st, sim, m2m, moneda);
	}
	else if(op._type == "SWAP")
	{
		
	}
	
	return 0.0;
}




double Valorizador::valorForward(Forward* fwd)
{
	Valorizador::addCurvaToStore(fwd->curvaDescuentoCompra);
	Valorizador::addCurvaToStore(fwd->curvaDescuentoVenta);
	double r = interpolations(Valorizador::storeCurvas[fwd->curvaDescuentoCompra].tenors, Valorizador::storeCurvas[fwd->curvaDescuentoCompra].rates, fwd->plazoResidual, 2); // 2 es Clamped Spline
	double vpCompra = (fwd->montoCompra)* exp(-r * fwd->plazoResidual);// /pow(1+r, fwd->plazoResidual);
	r = interpolations(Valorizador::storeCurvas[fwd->curvaDescuentoVenta].tenors, Valorizador::storeCurvas[fwd->curvaDescuentoVenta].rates, fwd->plazoResidual, 2); // 2 es Clamped Spline
	double vpVenta = (fwd->montoVenta)* exp(-r * fwd->plazoResidual);// /pow(1+r, fwd->plazoResidual);
	return Valorizador::aMonedaBase(vpCompra, fwd->monedaCompra) - Valorizador::aMonedaBase(vpVenta, fwd->monedaVenta);
}

double Valorizador::valorSwap(pair<Leg, Leg>& swapLegs) 
{
	//Preparar las curvas
	Valorizador::addHullWhiteToStore(swapLegs.first.getDiscountCurve());
	Valorizador::addHullWhiteToStore(swapLegs.second.getDiscountCurve());
	if(swapLegs.first.getProjectCurve() != swapLegs.first.getDiscountCurve())
	{
		Valorizador::addHullWhiteToStore(swapLegs.first.getProjectCurve());
	}
	if(swapLegs.second.getProjectCurve() != swapLegs.second.getDiscountCurve())
	{
		Valorizador::addHullWhiteToStore(swapLegs.second.getProjectCurve());
	}
	
	//Inicializar el calendario de la operación:
	swapLegs.first.initiateCalendars();
	swapLegs.second.initiateCalendars();
	swapLegs.first.resetAmount();
	swapLegs.second.resetAmount();
	string monedaBase = getMonedaBase();

	double tasaProjCompra = (double)storeHullWhite[swapLegs.first.getProjectCurve()].getR0();
	double tasaDiscCompra = (double)storeHullWhite[swapLegs.first.getDiscountCurve()].getR0();
	double lastFixingCompra = swapLegs.first.getValueRate();
	double valorCompra = valorLegScenario(swapLegs.first, 0 , tasaDiscCompra, tasaProjCompra, lastFixingCompra);

	double tasaProjVenta = (double)storeHullWhite[swapLegs.second.getProjectCurve()].getR0();
	double tasaDiscVenta= (double)storeHullWhite[swapLegs.second.getDiscountCurve()].getR0();
	double lastFixingVenta = swapLegs.second.getValueRate();
	double valorVenta = valorLegScenario(swapLegs.second, 0, tasaDiscVenta, tasaProjVenta, lastFixingVenta);

				
	double vpCompra = aMonedaBase(valorCompra, swapLegs.first.getCurrency());
	double vpVenta = aMonedaBase(valorVenta,  swapLegs.second.getCurrency());
	double m2m = vpCompra - vpVenta;
	return m2m;
}




double Valorizador::valorForwardScenario(Operation op, const vector<double>& st, vector<vector<double> >& m2m, string moneda)
{

	clock_2 = clock();
	cout << " HG "<<clock_2 <<",";
	Valorizador::addHullWhiteToStore(op._discountCurve.first);
	Valorizador::addHullWhiteToStore(op._discountCurve.second);
	clock_3 = clock();
	cout << " HWEnd "<<diffclock(clock_3, clock_2)<<",";
	//Traer el escenario para las dos tasas y las fx que sirvan considerando la pasada a moneda base. Significa
	//hacer una query sobre la tabla de simulación.
	//string monedaBase = getMonedaBase();
	int auxi = st.size();
	int auxj = getMaxSim() + 1;//Corregir
	vector<double> vTemp; //Aqui metemos tiempo, numero de simulacion y m2m
	for (int i = 0; i < auxi; i++)
	{
		//Esto se trae todas las simulaciones disponibles para el st[i]
		//Se guardan en el mapa sim. La llave del mapa de este tipo, si es la simulacion 10 del factor USDCLP la llave
		//es "10-USDCLP" y en el doble viene el valor simulado que corresponde.
		clock_2 = clock();
		//cout << " getSimulationAtT "<<clock_2 <<",";
		map<string, double> sim;
		double x = getSimulationAtT(op._discountCurve.first, op._discountCurve.second, st[i], sim);
		clock_3 = clock();;
		cout << " getSimulationAtTEnd " <<diffclock(clock_3, clock_2)<<",";
		for (int j = 0; j < auxj; j++)
		{
			if ( ((double)st[i] -(op._expiryTime.first / DT)) > TOL)
			{
				vTemp.push_back(st[i]);
				vTemp.push_back((double)j);
				vTemp.push_back(0.0);
				m2m.push_back(vTemp);
				vTemp.clear();
				continue;
			}
				//Estos tres bloques traen los valores de FX de la simulacion
				//Pueden servir pata comvertir a moneda base
			    //USDCLP, EURUSD, USDJPY, GBPUSD, USDMXN, CHFUSD, CLFCLP,
				string auxStr = integerToString(j) + "-USDCLP";
				double usdclp = sim[auxStr];
				if (usdclp == 0) {usdclp = 1.0;}
				
				auxStr = integerToString(j) + "-EURUSD";
				double eurusd = sim[auxStr];
				if (eurusd == 0) {eurusd = 1.0;}

				auxStr = integerToString(j) + "-GBPUSD";
				double gbpusd = sim[auxStr];
				if (gbpusd == 0) {gbpusd = 1.0;}
				
				auxStr = integerToString(j) + "-USDJPY";
				double usdjpy = sim[auxStr];
				if (usdjpy == 0) {usdjpy = 1.0;}
				
				auxStr = integerToString(j) + "-USDMXN";
				double usdmxn = sim[auxStr];
				if (usdmxn == 0) {usdmxn = 1.0;}

				auxStr = integerToString(j) + "-CHFUSD";
				double chfusd = sim[auxStr];
				if (chfusd == 0) {chfusd = 1.0;}

				auxStr = integerToString(j) + "-USDAUD";
				double usdaud = sim[auxStr];
				if (usdaud == 0) {usdaud = 1.0;}

				auxStr = integerToString(j) + "-USDCAD";
				double usdcad = sim[auxStr];
				if (usdcad == 0) {usdcad = 1.0;}

				auxStr = integerToString(j) + "-USDBRL";
				double usdbrl = sim[auxStr];
				if (usdbrl == 0) {usdbrl = 1.0;}

				auxStr = integerToString(j) + "-CLFCLP";
				double clfclp = sim[auxStr];
				if (clfclp == 0) {clfclp = 1.0;}

				//GBPUSD, USDMXN, CHFUSD, CLFCLP, USDAUD, USDCAD
				//Fin bloques que traen FX

				//Traemos la tasa corta de la pata comprada y calculamos la tasa al plazo
				//de la pata comprada.
				auxStr = integerToString(j) + "-" + op._discountCurve.first;
				double tasaCortaCompra = sim[auxStr];
				double dfPlazoCompra = storeHullWhite[op._discountCurve.first].getDiscountFactor(st[i] * DT, op._expiryTime.first, tasaCortaCompra);

				//Traemos la tasa corta de la pata vendida y calculamos la tasa al plazo
				//de la pata vendida.
				auxStr = integerToString(j) + "-" + op._discountCurve.second;
				double tasaCortaVenta = sim[auxStr];
				double dfPlazoVenta = storeHullWhite[op._discountCurve.second].getDiscountFactor(st[i] * DT, op._expiryTime.second, tasaCortaVenta);
				
				double vpCompra = aMoneda(moneda, op._amount.first*dfPlazoCompra, op._currency.first, usdclp, eurusd, usdjpy, clfclp, usdaud, usdcad, usdbrl, gbpusd, chfusd, usdmxn);
				double vpVenta = aMoneda(moneda, op._amount.second*dfPlazoVenta, op._currency.second, usdclp, eurusd, usdjpy, clfclp,  usdaud, usdcad, usdbrl, gbpusd, chfusd, usdmxn);
				vTemp.push_back((double)st[i]);
				vTemp.push_back((double)j);
				vTemp.push_back(vpCompra - vpVenta);
				m2m.push_back(vTemp);
				vTemp.clear();
		}
		sim.clear();
		clock_2 = clock();
		cout << " EndV "<<diffclock(clock_2, clock_3)<<",";
	}

	return 0.0;

}

double Valorizador::valorForwardScenario(Operation op, double st, map<string, double>& sim, vector<double>& m2m, string moneda)
{

	clock_2 = clock();
	Valorizador::addHullWhiteToStore(op._discountCurve.first);
	Valorizador::addHullWhiteToStore(op._discountCurve.second);
	clock_t clock_1 = clock();
	const int auxj = m2m.size();
	 //cout << "ssim " <<diffclock(clock_1, clock_2)<<",";
	int vcmto = min(getStoppingTimeFromTime(op._expiryTime.first), getStoppingTimeFromTime(op._expiryTime.first));
	if (st > vcmto)
	{
		for (int j = 0; j < auxj; j++)
		{
				m2m.at(j) = 0.0;
		}
	}
	else
	{
		for (int j = 0; j < auxj; j++)
		{
			//Estos tres bloques traen los valores de FX de la simulacion
			//Pueden servir pata comvertir a moneda base
			//USDCLP, EURUSD, USDJPY, GBPUSD, USDMXN, CHFUSD, CLFCLP,
			string auxStr = integerToString(j) + "-USDCLP";
			double usdclp = sim[auxStr];
			if (usdclp == 0) {usdclp = 1.0;}
			
			auxStr = integerToString(j) + "-EURUSD";
			double eurusd = sim[auxStr];
			if (eurusd == 0) {eurusd = 1.0;}

			auxStr = integerToString(j) + "-GBPUSD";
			double gbpusd = sim[auxStr];
			if (gbpusd == 0) {gbpusd = 1.0;}
				
			auxStr = integerToString(j) + "-USDJPY";
			double usdjpy = sim[auxStr];
			if (usdjpy == 0) {usdjpy = 1.0;}
			
			auxStr = integerToString(j) + "-USDMXN";
			double usdmxn = sim[auxStr];
			if (usdmxn == 0) {usdmxn = 1.0;}

			auxStr = integerToString(j) + "-CHFUSD";
			double chfusd = sim[auxStr];
			if (chfusd == 0) {chfusd = 1.0;}

			auxStr = integerToString(j) + "-USDAUD";
			double usdaud = sim[auxStr];
			if (usdaud == 0) {usdaud = 1.0;}

			auxStr = integerToString(j) + "-USDCAD";
			double usdcad = sim[auxStr];
			if (usdcad == 0) {usdcad = 1.0;}

			auxStr = integerToString(j) + "-USDBRL";
			double usdbrl = sim[auxStr];
			if (usdbrl == 0) {usdbrl = 1.0;}

			auxStr = integerToString(j) + "-CLFCLP";
			double clfclp = sim[auxStr];
			if (clfclp == 0) {clfclp = 1.0;}

			//GBPUSD, USDMXN, CHFUSD, CLFCLP, USDAUD, USDCAD
			//Fin bloques que traen FX
			//Traemos la tasa corta de la pata comprada y calculamos la tasa al plazo
			//de la pata comprada.
			auxStr = integerToString(j) + "-" + op._discountCurve.first;
			double tasaCortaCompra = sim[auxStr];
			double dfPlazoCompra = storeHullWhite[op._discountCurve.first].getDiscountFactor(st * DT, op._expiryTime.first, tasaCortaCompra);
				
			//Traemos la tasa corta de la pata vendida y calculamos la tasa al plazo
			//de la pata vendida.
			auxStr = integerToString(j) + "-" + op._discountCurve.second;
			double tasaCortaVenta = sim[auxStr];

			double dfPlazoVenta = storeHullWhite[op._discountCurve.second].getDiscountFactor(st * DT, op._expiryTime.second, tasaCortaVenta);
			double vpCompra = aMoneda(moneda, op._amount.first*dfPlazoCompra, op._currency.first, usdclp, eurusd, usdjpy, clfclp, usdaud, usdcad, usdbrl, gbpusd, chfusd, usdmxn);
			double vpVenta = aMoneda(moneda, op._amount.second*dfPlazoVenta, op._currency.second, usdclp, eurusd, usdjpy, clfclp,  usdaud, usdcad, usdbrl, gbpusd, chfusd, usdmxn);
			//vTemp.push_back((double)st);
			//vTemp.push_back((double)j);
			//vTemp.push_back(vpCompra - vpVenta);
			m2m.at(j) = vpCompra - vpVenta;
			//vTemp.clear();
		}
	}
	clock_3 = clock();
	//cout << "EndLoopMap " <<diffclock(clock_3, clock_1)<<"\n";
	//cout << " EndV "<<diffclock(clock_3, clock_2)<<",";

	return 0.0;
}

double Valorizador::valorSwapScenario(pair<Leg, Leg>& swapLegs, double st, map<string, double>& sim, vector<double>& m2m, string moneda)
{
	//Preparar las curvas
	Valorizador::addHullWhiteToStore(swapLegs.first.getDiscountCurve());
	Valorizador::addHullWhiteToStore(swapLegs.second.getDiscountCurve());
	if(swapLegs.first.getProjectCurve() != swapLegs.first.getDiscountCurve())
	{
		Valorizador::addHullWhiteToStore(swapLegs.first.getProjectCurve());
	}
	if(swapLegs.second.getProjectCurve() != swapLegs.second.getDiscountCurve())
	{
		Valorizador::addHullWhiteToStore(swapLegs.second.getProjectCurve());
	}
	
	//Inicializar el calendario de la operación:
	swapLegs.first.initiateCalendars();
	swapLegs.second.initiateCalendars();		
		
	//const int auxi = st.size();
	const int auxj = m2m.size();
	//vector<double> vTemp; 
	//Si él tiempo de parada es mayor que el tiempo de vencimiento de la operación completa con 0.0
    int vcmto = min(swapLegs.first.getCalendarCoupon().back(), swapLegs.second.getCalendarCoupon().back());
	if ( st > vcmto)
	{ 
		for (int j = 0; j < auxj; j++)
		{
			//vTemp.push_back(st);
			//vTemp.push_back((double)j);
			//vTemp.push_back(0.0);
			//m2m.push_back(vTemp);
			//vTemp.clear();
			m2m.at(j) = 0;
			continue;
		}
	} 
	else
	{
		//Reset a calendario vigente 
	    swapLegs.first.resetCalendars((int)st);
		swapLegs.second.resetCalendars((int)st);
		swapLegs.first.resetAmount();
		swapLegs.second.resetAmount();
		pair<vector<double>, vector<double>> fixSim;
		if(swapLegs.first.getFlagFixing() == true)
		{
			fixSim.first.reserve(auxj);
			double x = getSimulationAtT(swapLegs.first.getProjectCurve(), swapLegs.first.getLastFixing(), fixSim.first);
		}
		if(swapLegs.second.getFlagFixing() == true)
		{
			fixSim.second.reserve(auxj);
			double x = getSimulationAtT(swapLegs.second.getProjectCurve(), swapLegs.second.getLastFixing(), fixSim.second);
		}
			//map<string, double> simFirst;
			//double x = getSimulationAtT(swapLegs.first.getDiscountCurve(), swapLegs.first.getProjectCurve(), st[i], simFirst);
			//map<string, double> simSecond;
			//x = getSimulationAtT(swapLegs.second.getDiscountCurve(), swapLegs.second.getProjectCurve(), st[i], simSecond);

		
		for (int j = 0; j < auxj; j++)
		{
			
			//Estos tres bloques traen los valores de FX de la simulacion
			string auxStr = integerToString(j) + "-USDCLP";
			double usdclp = sim[auxStr];
			if (usdclp == 0) {usdclp = 1.0;}
				
			auxStr = integerToString(j) + "-EURUSD";
			double eurusd = sim[auxStr];
			if (eurusd == 0) {eurusd = 1.0;}
				
			auxStr = integerToString(j) + "-USDJPY";
			double usdjpy = sim[auxStr];
			if (usdjpy == 0) {usdjpy = 1.0;}

			auxStr = integerToString(j) + "-CLFCLP";
			double clfclp = sim[auxStr];
			if (clfclp == 0) {clfclp = 1.0;}
			//Fin bloques que traen FX

			//Valorización pata compra.				
			auxStr = integerToString(j) + "-" + swapLegs.first.getDiscountCurve();
			double tasaDiscCompra = sim[auxStr];
			auxStr = integerToString(j) + "-" + swapLegs.first.getProjectCurve();
			double tasaProjCompra = sim[auxStr];
			//LastFixing
			double lastFixingCompra = 0.0;
			if(!fixSim.first.empty())
			{
				lastFixingCompra = fixSim.first[j];
			}
			double valorCompra = valorLegScenario(swapLegs.first,(int) st, tasaDiscCompra, tasaProjCompra, lastFixingCompra);

			//Valorización pata Venta.				
			auxStr = integerToString(j) + "-" + swapLegs.second.getDiscountCurve();
			double tasaDiscVenta = sim[auxStr];
			auxStr = integerToString(j) + "-" + swapLegs.second.getProjectCurve();
			double tasaProjVenta = sim[auxStr];
			//LastFixing
			double lastFixingVenta = 0.0;
			if(!fixSim.second.empty())
			{
				lastFixingVenta = fixSim.second[j];
			}
			double valorVenta = valorLegScenario(swapLegs.second, (int) st, tasaDiscVenta, tasaProjVenta, lastFixingVenta);
				
			double vpCompra = aMoneda(moneda, valorCompra,  swapLegs.first.getCurrency(), usdclp, eurusd, usdjpy, clfclp);
			double vpVenta = aMoneda(moneda, valorVenta,  swapLegs.second.getCurrency(), usdclp, eurusd, usdjpy, clfclp);//aMoneda(moneda, op._amount.second*dfPlazoVenta, op._currency.second, usdclp, eurusd, usdjpy);
			//vTemp.push_back((double)st);
			//vTemp.push_back((double)j);
			//vTemp.push_back(vpCompra - vpVenta);
			//m2m.push_back(vTemp);
			//vTemp.clear();
			m2m.at(j) = vpCompra - vpVenta;
		}
		//pair<vector<double>, vector<double>> fixSim;
		fixSim.first.clear();
		fixSim.second.clear();
		//simFirst.clear();
		//simSecond.clear();
	}
	
	return 0.0;
}

double Valorizador::valorSwapScenario(pair<Leg, Leg>& swapLegs, const vector<double>& st, vector<vector<double> >& m2m, string moneda)
{
	//Preparar las curvas
	Valorizador::addHullWhiteToStore(swapLegs.first.getDiscountCurve());
	Valorizador::addHullWhiteToStore(swapLegs.second.getDiscountCurve());
	if(swapLegs.first.getProjectCurve() != swapLegs.first.getDiscountCurve())
	{
		Valorizador::addHullWhiteToStore(swapLegs.first.getProjectCurve());
	}
	if(swapLegs.second.getProjectCurve() != swapLegs.second.getDiscountCurve())
	{
		Valorizador::addHullWhiteToStore(swapLegs.second.getProjectCurve());
	}
	
	//Inicializar el calendario de la operación:
	swapLegs.first.initiateCalendars();
	swapLegs.second.initiateCalendars();		
		
	const int auxi = st.size();
	const int auxj = getMaxSim() + 1;
	vector<double> vTemp; 
	//Si él tiempo de parada es mayor que el tiempo de vencimiento de la operación completa con 0.0
    int vcmto = min(swapLegs.first.getCalendarCoupon().back(), swapLegs.second.getCalendarCoupon().back());
	for (int i = 0; i < auxi; i++)
	{
		if ( st[i] > vcmto)
		{ 
			for (int j = 0; j < auxj; j++)
			{
				vTemp.push_back(st[i]);
				vTemp.push_back((double)j);
				vTemp.push_back(0.0);
				m2m.push_back(vTemp);
				vTemp.clear();
				continue;
			}
		} 
		else
		{
			//Reset a calendario vigente 
	        swapLegs.first.resetCalendars((int) st[i]);
			swapLegs.second.resetCalendars((int) st[i]);
			swapLegs.first.resetAmount();
			swapLegs.second.resetAmount();
			pair<vector<double>, vector<double>> fixSim;
			if(swapLegs.first.getFlagFixing() == true)
			{
				fixSim.first.reserve(auxj);
				double x = getSimulationAtT(swapLegs.first.getProjectCurve(), swapLegs.first.getLastFixing(), fixSim.first);
			}
			if(swapLegs.second.getFlagFixing() == true)
			{
				fixSim.second.reserve(auxj);
				double x = getSimulationAtT(swapLegs.second.getProjectCurve(), swapLegs.second.getLastFixing(), fixSim.second);
			}
			map<string, double> simFirst;
			double x = getSimulationAtT(swapLegs.first.getDiscountCurve(), swapLegs.first.getProjectCurve(), st[i], simFirst);
			map<string, double> simSecond;
			x = getSimulationAtT(swapLegs.second.getDiscountCurve(), swapLegs.second.getProjectCurve(), st[i], simSecond);

		
			for (int j = 0; j < auxj; j++)
			{
			
				//Estos tres bloques traen los valores de FX de la simulacion
				string auxStr = integerToString(j) + "-USDCLP";
				double usdclp = simFirst[auxStr];
				if (usdclp == 0) {usdclp = 1.0;}
				
				auxStr = integerToString(j) + "-EURUSD";
				double eurusd = simFirst[auxStr];
				if (eurusd == 0) {eurusd = 1.0;}
				
				auxStr = integerToString(j) + "-USDJPY";
				double usdjpy = simFirst[auxStr];
				if (usdjpy == 0) {usdjpy = 1.0;}

				auxStr = integerToString(j) + "-CLFCLP";
				double clfclp = simFirst[auxStr];
				if (clfclp == 0) {clfclp = 1.0;}
				//Fin bloques que traen FX

				//Valorización pata compra.				
				auxStr = integerToString(j) + "-" + swapLegs.first.getDiscountCurve();
				double tasaDiscCompra = simFirst[auxStr];
				auxStr = integerToString(j) + "-" + swapLegs.first.getProjectCurve();
				double tasaProjCompra = simFirst[auxStr];
				//LastFixing
				double lastFixingCompra = 0.0;
				if(!fixSim.first.empty())
				{
					lastFixingCompra = fixSim.first[j];
				}
				double valorCompra = valorLegScenario(swapLegs.first, (int)st[i], tasaDiscCompra, tasaProjCompra, lastFixingCompra);

				//Valorización pata Venta.				
				auxStr = integerToString(j) + "-" + swapLegs.second.getDiscountCurve();
				double tasaDiscVenta = simSecond[auxStr];
				auxStr = integerToString(j) + "-" + swapLegs.second.getProjectCurve();
				double tasaProjVenta = simSecond[auxStr];
				//LastFixing
				double lastFixingVenta = 0.0;
				if(!fixSim.second.empty())
				{
					lastFixingVenta = fixSim.second[j];
				}
				double valorVenta = valorLegScenario(swapLegs.second, (int)st[i], tasaDiscVenta, tasaProjVenta, lastFixingVenta);

				
				double vpCompra = aMoneda(moneda, valorCompra,  swapLegs.first.getCurrency(), usdclp, eurusd, usdjpy, clfclp);
				double vpVenta = aMoneda(moneda, valorVenta,  swapLegs.second.getCurrency(), usdclp, eurusd, usdjpy, clfclp);//aMoneda(moneda, op._amount.second*dfPlazoVenta, op._currency.second, usdclp, eurusd, usdjpy);
				vTemp.push_back((double)st[i]);
				vTemp.push_back((double)j);
				vTemp.push_back(vpCompra - vpVenta);
				m2m.push_back(vTemp);
				vTemp.clear();
			}
			simFirst.clear();
			simSecond.clear();
		}
	}
	return 0.0;
}


double Valorizador::valorLegScenario(Leg& leg, int stopTime, double discRate, double projRate, double nextFixing)
{
	double pvLeg = 0.0;
	if(!leg.getCalendarCoupon().empty())
	{
		//Cupones Vigentes == leg.getCalendarCoupon()
		size_t numCoupons = leg.getCalendarCoupon().size();
		//La primera fecha de cupon es anterior al stopTime, el primer discfactor es cero.
		vector<double> discFactors(numCoupons, 1.0);
		for (unsigned int i = 1; i < numCoupons; i++)
		{
			discFactors.at(i) = storeHullWhite[leg.getDiscountCurve()].getDiscountFactor(stopTime*DT, (leg.getCalendarCoupon()[i])*DT, discRate);
		}

		if(leg.tipoPata == "FIX")
		{
			pvLeg = valueLegFixScenario(&leg, discFactors);
		}
		else if(leg.tipoPata == "FLOAT")
		{
			//nextFixing
			if(leg.getFlagFixing() == false)
			{
				nextFixing = leg.getValueRate();
			}
			else
			{
				double firstDisc = storeHullWhite[leg.getProjectCurve()].getDiscountFactor((leg.getLastFixing())*DT, (leg.getCalendarCoupon()[1])*DT, nextFixing);
				nextFixing =(1/firstDisc - 1)/(double)((leg.getCalendarCoupon()[1]- leg.getLastFixing())*DT);//- log(firstDisc)/(double)((leg.getCalendarCoupon()[1]- leg.getLastFixing())*DT);
			}

			//forwardRates si fechas de coupon!= Fechas de Fixing y/o curva de proyección diferente.
			vector<double> forwardRates;
			if(leg.getFlagProj() == true)
			{
				//discFactorsProj.reserve(numCoupons);
				//discFactorsProj.assign(discFactors.begin(), discFactors.end());
				//forwardRates.reserve(numCoupons);
				forwardRates.assign(numCoupons, 0.0);
				double x = getForwardRateFromDiscountFactors(stopTime, leg.getCalendarCoupon(), discFactors, forwardRates);
			}
			else
			{	
				size_t numFixing = leg.getCalendarFixing().size();
				vector<double> discFactorsProj(numFixing, 1.0);
				for (unsigned int i = 1; i < numFixing; i++)
				{
					discFactorsProj.at(i) = storeHullWhite[leg.getProjectCurve()].getDiscountFactor(stopTime*DT, (leg.getCalendarFixing()[i])*DT, projRate);
				}
				//forwardRates.reserve(numFixing);
				forwardRates.assign(numFixing, 0.0);
				double x = getForwardRateFromDiscountFactors(stopTime, leg.getCalendarFixing(), discFactorsProj, forwardRates);
				discFactorsProj.clear();
			}
			vector<double> fixingRates;
            double y = getFixingRatesForLeg(leg.getCalendarCoupon(),leg.getCalendarFixing(), forwardRates, nextFixing, fixingRates);
			pvLeg = valueLegFloatScenario(&leg, discFactors,fixingRates);
			// double valueLegFloatScenario(Leg* leg, vector<double> discFactors, vector<double> discFactorsProj, double firstFix);
		}
		else if(leg.tipoPata == "FLOATCAM")
		{
			//nextFixing
			if(leg.getFlagFixing() == false)
			{
				nextFixing = leg.getValueRate();
			}
			else
			{
				double firstDisc = storeHullWhite[leg.getProjectCurve()].getDiscountFactor((leg.getLastFixing())*DT, stopTime*DT, nextFixing);
				nextFixing =(1/firstDisc - 1)/(double)((stopTime - leg.getLastFixing())*DT);//- log(firstDisc)/(double)((leg.getCalendarCoupon()[1]- leg.getLastFixing())*DT);
			}
			double auxInterest = leg.getAmount()*leg.getInterest(leg.getLastFixing(), stopTime, nextFixing);
			//forwardRates asume que fechas de coupon == Fechas de Fixing y curva de proyección= descuento
			vector<double> forwardRates;
			forwardRates.assign(numCoupons, 0.0);
			// Corregido el 30/10 la primera tasa fwd no consideraba el stopTime
			double x = getForwardRateFromDiscountFactors(stopTime, leg.getCalendarCoupon(), discFactors, forwardRates);
			//corregido el 30/09 Se estaban multiplicando los intereses
			double nextInterest = leg.getAmount()*leg.getInterest(stopTime, leg.getCalendarCoupon()[1], forwardRates[1]);
			pvLeg = valueLegFloatCamScenario(&leg, discFactors, forwardRates, nextInterest)+auxInterest;
			// double valueLegFloatScenario(Leg* leg, vector<double> discFactors, vector<double> discFactorsProj, double firstFix);
		}
	}
	return pvLeg;
}

void Valorizador::addCurvaToStore(string nombreCurva)
{
	std::map<std::string, Curva>::iterator it = storeCurvas.find(nombreCurva);
	if(it == storeCurvas.end())
	{
		Curva* newCurva = new Curva;
		double x = getCurvaFromNombre(nombreCurva, newCurva);
		if (x == 0)
		{
			storeCurvas.insert(std::pair<std::string, Curva>(nombreCurva, *newCurva));
		}
		delete newCurva;
	} 
}


void Valorizador::addHullWhiteToStore(string nombreCurva)
{
	int s = storeHullWhite.count(nombreCurva);
	if(s == 0)
	{
		Curva* newCurva = new Curva;
		double x = getCurvaFromNombre(nombreCurva, newCurva);
		if (x == 0)
		{
			double gamma = getGamma(nombreCurva);
			double sigma = getSigma(nombreCurva);
			HullWhite newHullWhite = HullWhite(newCurva, gamma, sigma);
			storeHullWhite.insert(pair<string, HullWhite>(nombreCurva, newHullWhite));  
			//storeHullWhite[nombreCurva] = newHullWhite;
			//delete newHullWhite;
		}
		delete newCurva;
	} 

}
double Valorizador::aMonedaBase(double monto, string moneda)
{
	if (getMonedaBase() == "CLP")
	{
		if (moneda == "CLP") { return monto; }
		if (moneda == "USD") { return monto * getFX("USDCLP")->valor(); }
		if (moneda == "EUR") { return monto * getFX("EURUSD")->valor()* getFX("USDCLP")->valor() ;}
		if (moneda == "JPY") { return monto / getFX("USDJPY")->valor() * getFX("USDCLP")->valor(); }
		if (moneda == "CLF") { return monto * getFX("CLFCLP")->valor(); }
		if (moneda == "AUD") { return monto / getFX("USDAUD")->valor() * getFX("USDCLP")->valor(); }
		if (moneda == "CAD") { return monto / getFX("USDCAD")->valor() * getFX("USDCLP")->valor(); }
		if (moneda == "BRL") { return monto / getFX("USDBRL")->valor() * getFX("USDCLP")->valor(); }
		if (moneda == "MXN") { return monto / getFX("USDMXN")->valor() * getFX("USDCLP")->valor(); }
		if (moneda == "GBP") { return monto * getFX("GBPUSD")->valor() * getFX("USDCLP")->valor(); }
		if (moneda == "CHF") { return monto * getFX("CHFUSD")->valor() * getFX("USDCLP")->valor(); }
	}
	else if (getMonedaBase() == "USD")
	{
		if (moneda == "USD") { return monto; }
		if (moneda == "CLP") { return monto / getFX("USDCLP")->valor(); }
		if (moneda == "EUR") { return monto * getFX("EURUSD")->valor(); }
		if (moneda == "JPY") { return monto / getFX("USDJPY")->valor(); }
		if (moneda == "CLF") { return ( monto * getFX("CLFCLP")->valor())/ getFX("USDCLP")->valor(); }
		if (moneda == "AUD") { return monto / getFX("USDAUD")->valor(); }
		if (moneda == "CAD") { return monto / getFX("USDCAD")->valor(); }
		if (moneda == "BRL") { return monto / getFX("USDBRL")->valor(); }
		if (moneda == "MXN") { return monto / getFX("USDMXN")->valor(); }
		if (moneda == "GBP") { return monto * getFX("GBPUSD")->valor(); }
		if (moneda == "CHF") { return monto * getFX("CHFUSD")->valor(); }
	}
	return 1.0;
}

double Valorizador::aMonedaBase(double monto, string moneda, double usdclp, double eurusd, double usdjpy, double clfclp)
{
	if (getMonedaBase() == "CLP")
	{
		if (moneda == "CLP") { return monto; }
		if (moneda == "USD") { return monto * usdclp; }
		if (moneda == "EUR") { return monto * eurusd * usdclp; }
		if (moneda == "JPY") { return monto / usdjpy * usdclp; }
		if (moneda == "CLF") { return monto * clfclp; }

	}
	else if (getMonedaBase() == "USD")
	{
		if (moneda == "USD") { return monto; }
		if (moneda == "CLP") { return monto / usdclp; }
		if (moneda == "EUR") { return monto * eurusd; }
		if (moneda == "JPY") { return monto / usdjpy; }
		if (moneda == "CLF") { return monto * clfclp / usdclp ; }
	}
	return 0.0;
}

double Valorizador::aMoneda(string queMoneda, double monto, string monedaMonto, double usdclp, double eurusd, double usdjpy, double clfclp, double usdaud, double usdcad, double usdbrl, double gbpusd, double chfusd, double usdmxn)
{
	if (queMoneda == "CLP")
	{
		if (monedaMonto == "CLP") { return monto; }
		if (monedaMonto == "USD") { return monto * usdclp; }
		if (monedaMonto == "EUR") { return monto * eurusd * usdclp; }
		if (monedaMonto == "JPY") { return monto / usdjpy * usdclp; }
		if (monedaMonto == "CLF") { return monto * clfclp; }
		if (monedaMonto == "AUD") { return monto / usdaud * usdclp; }
		if (monedaMonto == "CAD") { return monto / usdcad * usdclp; }
		if (monedaMonto == "BRL") { return monto / usdbrl * usdclp; }
		if (monedaMonto == "MXN") { return monto / usdmxn * usdclp; }
		if (monedaMonto == "GBP") { return monto * gbpusd * usdclp; }
		if (monedaMonto == "CHF") { return monto * chfusd * usdclp; }

	}
	else if (queMoneda == "USD")
	{
		if (monedaMonto == "USD") { return monto; }
		if (monedaMonto == "CLP") { return monto / usdclp; }
		if (monedaMonto == "EUR") { return monto * eurusd; }
		if (monedaMonto == "JPY") { return monto / usdjpy; }
		if (monedaMonto == "CLF") { return monto * clfclp / usdclp; }
		if (monedaMonto == "AUD") { return monto / usdaud; }
		if (monedaMonto == "CAD") { return monto / usdcad;}
		if (monedaMonto == "BRL") { return monto / usdbrl; }
		if (monedaMonto == "MXN") { return monto / usdmxn; }
		if (monedaMonto == "GBP") { return monto * gbpusd; }
		if (monedaMonto == "CHF") { return monto * chfusd; }
	}
	return 0.0;
}