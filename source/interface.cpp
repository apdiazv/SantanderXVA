
#include "cppinterface.h"
#include "interface.h"
#include "headerFiles.h"

#pragma warning (disable : 4996)


unsigned int cont=0;//1391523783;
unsigned int semilla=1391523783;//(unsigned int)time(NULL);

using namespace std;
typedef std::vector<std::vector<double>> matriz;


CellMatrix testString(CellMatrix input) {
	return input;
}

double getInterpolations(MyArray data1, MyArray data2, double arg, unsigned long type)
{
	//vector<double> data1(data1);
	//vector<double> data2(data2);
	return interpolations(data1, data2, arg, type);
}


std::string convertDouble(double number){
	std::ostringstream ss;//create a stringstream
	ss << number;//add number to the stream
	return ss.str();//return a string with the contents of the stream
}
sqlite3* openDb()
{   //Cambiar Path. C:\\Creasys\\XVA\\cva_data.sqlite
	//"C:\\Debug\\cva_data.sqlite";
	clock_t clock_0, clock_1; //
	clock_0 = clock();
	const char *baseDatos = "C:\\Creasys\\XVA\\cva_data.sqlite";
	sqlite3 *db;
	int rc = 0;
	sqlite3_initialize();
	rc = sqlite3_open_v2(baseDatos, &db, SQLITE_OPEN_READWRITE, NULL);
	if (rc != SQLITE_OK) {
		sqlite3_close(db);
		throw("No se pudo abrir la BBDD");
	}
	clock_1 = clock();
	//cout <<"openDb " <<diffclock(clock_1, clock_0) <<"\n";
	return db;

}

double testInsertData(double whatever)
{
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	std::string qry = "INSERT INTO test (campo1, campo2) VALUES ('11.0', 11.0)";
	int rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		sqlite3_close_v2(db);
		return 2.0;
	}
		
	rc = sqlite3_step(stmt);
	if ((rc != SQLITE_DONE) && (rc != SQLITE_ROW)) {
		sqlite3_close_v2(db);
		return 3.0;
	}

	sqlite3_finalize(stmt);
	
	sqlite3_close(db);
	sqlite3_shutdown();

	return 4.0;
}
double insertFx(CellMatrix valores)
{
	int rc;
	char* errorMessage;
	sqlite3 *db = openDb();
	rc = sqlite3_exec(db, "DELETE FROM Fx", NULL, NULL, &errorMessage);
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMessage);
	sqlite3_stmt *stmt;
	int filas = valores.RowsInStructure();
	std::string qry = "INSERT INTO Fx (nombre, valor, curva_fuerte, curva_debil) VALUES (?, ?, ?, ?)";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		return 2.5;
	}
	for (int i = 0; i < filas; i++)
	{
		std::string input1 = valores(i, 0).StringValue();
		double input2 = valores(i, 1).NumericValue();
		std::string input3 = valores(i, 2).StringValue();
		std::string input4 = valores(i, 3).StringValue();
		rc = sqlite3_bind_text(stmt, 1, input1.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_bind_double(stmt, 2, input2);
		rc = sqlite3_bind_text(stmt, 3, input3.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_bind_text(stmt, 4, input4.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_step(stmt);
		if ((rc != SQLITE_DONE) && (rc != SQLITE_ROW))
		{
			sqlite3_close_v2(db);
			return 3.0;
		}
		sqlite3_reset(stmt);
	}

	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMessage);		
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();

	return 4.0;
}



double insertCurvas(CellMatrix valores)
{
	int rc;
	char* errorMessage;
	sqlite3 *db = openDb();
	rc = sqlite3_exec(db, "DELETE FROM Curva", NULL, NULL, &errorMessage);
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMessage);
	sqlite3_stmt *stmt;
	int filas = valores.RowsInStructure();
	std::string qry = "INSERT INTO Curva (nombre, plazo, valor) VALUES (?, ?, ?)";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		return 2.5;
	}
	for (int i = 0; i < filas; i++)
	{
		std::string input1 = valores(i, 0).StringValue();
		double input2 = valores(i, 1).NumericValue();
		double input3 = valores(i, 2).NumericValue();
		rc = sqlite3_bind_text(stmt, 1, input1.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_bind_double(stmt, 2, input2);
		rc = sqlite3_bind_double(stmt, 3, input3);
		rc = sqlite3_step(stmt);
		if ((rc != SQLITE_DONE) && (rc != SQLITE_ROW))
		{
			sqlite3_close_v2(db);
			return 3.0;
		}
		sqlite3_reset(stmt);
	}

	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMessage);		
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();

	return 4.0;
}

double insertDealNumberNettingSet(CellMatrix valores)
{
	int rc;
	char* errorMessage;
	sqlite3 *db = openDb();
	rc = sqlite3_exec(db, "DELETE FROM DealNumberNettingSet", NULL, NULL, &errorMessage);
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMessage);
	sqlite3_stmt *stmt;
	int filas = valores.RowsInStructure();
	std::string qry = "INSERT INTO DealNumberNettingSet (deal_number, netting_set) VALUES (?, ?)";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		return 2.5;
	}
	for (int i = 0; i < filas; i++)
	{
		string input1 = valores(i, 0).StringValue();
		string input2 = valores(i, 1).StringValue();
		rc = sqlite3_bind_text(stmt, 1, input1.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_bind_text(stmt, 2, input2.c_str(), -1, SQLITE_STATIC);

		rc = sqlite3_step(stmt);
		if ((rc != SQLITE_DONE) && (rc != SQLITE_ROW))
		{
			sqlite3_close_v2(db);
			return 3.0;
		}
		sqlite3_reset(stmt);
	}

	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMessage);		
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();

	return 0.0;
}

double insertNettingSets(CellMatrix valores)
{
	int rc;
	char* errorMessage;
	sqlite3 *db = openDb();
	rc = sqlite3_exec(db, "DELETE FROM NettingSet", NULL, NULL, &errorMessage);
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMessage);
	sqlite3_stmt *stmt;
	int filas = valores.RowsInStructure();
	std::string qry = "INSERT INTO NettingSet (nombre, recovery_rate, default_prob, threshold_curr, threshold_ns, threshold_inst, last_date, initial_margin, periodicity, collateral_adjustment, mta) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		return 2.5;
	}
	for (int i = 0; i < filas; i++)
	{
		string input1 = valores(i, 0).StringValue();
		double input2 = valores(i, 1).NumericValue();
		double input3 = valores(i, 2).NumericValue();
		string input4 = valores(i, 3).StringValue();
		double input5 = valores(i, 4).NumericValue();
		double input6 = valores(i, 5).NumericValue();
		int input7 = (int)valores(i, 6).NumericValue();
		double input8 = valores(i, 7).NumericValue();
		int input9 = (int)valores(i, 8).NumericValue();
		double input10 = valores(i, 9).NumericValue();
		double input11 = valores(i, 10).NumericValue();

		rc = sqlite3_bind_text(stmt, 1, input1.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_bind_double(stmt, 2, input2);
		rc = sqlite3_bind_double(stmt, 3, input3);
		rc = sqlite3_bind_text(stmt, 4, input4.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_bind_double(stmt, 5, input5);
		rc = sqlite3_bind_double(stmt, 6, input6);
		rc = sqlite3_bind_int(stmt, 7, input7);
		rc = sqlite3_bind_double(stmt, 8, input8);
		rc = sqlite3_bind_int(stmt, 9, input9);
		rc = sqlite3_bind_double(stmt, 10, input10);
		rc = sqlite3_bind_double(stmt, 11, input11);

		rc = sqlite3_step(stmt);
		if ((rc != SQLITE_DONE) && (rc != SQLITE_ROW))
		{
			sqlite3_close_v2(db);
			return 3.0;
		}
		sqlite3_reset(stmt);
	}

	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMessage);		
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();

	return 0.0;
}

double getNettingSet(string ns, vector<Operation>& ops)
{
	//ops lo pasamos By Ref para evitarnos cualquier doble consumo y copias desde el método llamado
	//al método que llama. Utilizamos Operacion* porque queremos llamar polimórficamente los métodos
	//de valorización de un FWD o SWAP. Aqui no los estamos heciendo heredar de una clase abstracta
	//si no que Operacion es una clase envoltorio con un puntero a void que es el que trae la
	//operacion y un string que identifica su tipo.

	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	string tempString;
	string qry = "SELECT * FROM Operacion WHERE deal_number IN (SELECT deal_number FROM DealNumberNettingSet WHERE netting_set = ?)"; //Este query trae todas las operaciones del netting set ns

	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		return 1.0;
	}
	
	rc = sqlite3_bind_text(stmt, 1, ns.c_str(), -1, SQLITE_STATIC);

	Operation op;

	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		tempString.assign((const char*)sqlite3_column_text(stmt, 2));
		if (tempString == "FWD")
		{
			op._dealNumber = integerToString(sqlite3_column_int(stmt, 1));
			op._type = tempString;
			(op._pricer).assign((const char*)sqlite3_column_text(stmt, 3));
			(op._fx).assign((const char*)sqlite3_column_text(stmt, 4));
			(op._currency.first).assign((const char*)sqlite3_column_text(stmt, 7));
			(op._currency.second).assign((const char*)sqlite3_column_text(stmt, 24));
			op._amount.first = sqlite3_column_double(stmt, 8);
			op._amount.second = sqlite3_column_double(stmt, 25);
			op._expiryTime.first = sqlite3_column_double(stmt, 6);
			op._expiryTime.second = sqlite3_column_double(stmt, 23);
			(op._discountCurve.first).assign((const char*)sqlite3_column_text(stmt, 20));
			(op._discountCurve.second).assign((const char*)sqlite3_column_text(stmt, 37));
			ops.push_back(op);
		}
		else
		{
			op._type = "SWAP"; //Por ahora el objeto swp no está implementado
			op._dealNumber = integerToString(sqlite3_column_int(stmt, 1));
			(op._pricer).assign((const char*)sqlite3_column_text(stmt, 3));
			op._startTime.first = sqlite3_column_double(stmt, 5);
			op._startTime.second = sqlite3_column_double(stmt, 22);
			op._expiryTime.first = sqlite3_column_double(stmt, 6);
			op._expiryTime.second = sqlite3_column_double(stmt, 23);
			(op._currency.first).assign((const char*)sqlite3_column_text(stmt, 7));
			(op._currency.second).assign((const char*)sqlite3_column_text(stmt, 24));
			op._amount.first = sqlite3_column_double(stmt, 8);
			op._amount.second = sqlite3_column_double(stmt, 25);
			(op._tipoTasa.first).assign((const char*)sqlite3_column_text(stmt, 9));
			(op._tipoTasa.second).assign((const char*)sqlite3_column_text(stmt, 26));
			(op._formaTasa.first).assign((const char*)sqlite3_column_text(stmt, 10));
			(op._formaTasa.second).assign((const char*)sqlite3_column_text(stmt, 27));
			op._valueRate.first = sqlite3_column_double(stmt, 11);
			op._valueRate.second = sqlite3_column_double(stmt, 28);
			(op._periodicity.first).assign((const char*)sqlite3_column_text(stmt, 12));
            (op._periodicity.second).assign((const char*)sqlite3_column_text(stmt, 29));
			(op._stubPeriod.first).assign((const char*)sqlite3_column_text(stmt, 13));
            (op._stubPeriod.second).assign((const char*)sqlite3_column_text(stmt, 30));
			(op._fixingPeriodicity.first).assign((const char*)sqlite3_column_text(stmt, 14));
            (op._fixingPeriodicity.second).assign((const char*)sqlite3_column_text(stmt, 31));
			(op._fixingStubPeriod.first).assign((const char*)sqlite3_column_text(stmt, 15));
            (op._fixingStubPeriod.second).assign((const char*)sqlite3_column_text(stmt, 32));
			op._spread.first = sqlite3_column_double(stmt, 16);
			op._spread.second = sqlite3_column_double(stmt, 33);
			(op._amort.first).assign((const char*)sqlite3_column_text(stmt, 17));
            (op._amort.second).assign((const char*)sqlite3_column_text(stmt, 34));
			(op._includeAmort.first).assign((const char*)sqlite3_column_text(stmt, 18));
            (op._includeAmort.second).assign((const char*)sqlite3_column_text(stmt, 35));
			(op._projectCurve.first).assign((const char*)sqlite3_column_text(stmt, 19));
			(op._projectCurve.second).assign((const char*)sqlite3_column_text(stmt, 36));
			(op._discountCurve.first).assign((const char*)sqlite3_column_text(stmt, 20));
			(op._discountCurve.second).assign((const char*)sqlite3_column_text(stmt, 37));
			op._initialUF.first = sqlite3_column_double(stmt, 21);
			op._initialUF.second = sqlite3_column_double(stmt, 38);
			ops.push_back(op);
		}
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	return 0.0;
}

double cleanValorizacion()
{
	sqlite3 *db = openDb();
	char* errorMessage;
	sqlite3_exec(db, "DELETE FROM Valorizacion", NULL, NULL, &errorMessage);
	sqlite3_close(db);
	sqlite3_shutdown();
	return 0.0;
}

double cleanColateral()
{
	sqlite3 *db = openDb();
	char* errorMessage;
	sqlite3_exec(db, "DELETE FROM Colateral", NULL, NULL, &errorMessage);
	sqlite3_close(db);
	sqlite3_shutdown();
	return 0.0;
}

double insertValorizacion(string ns, string dealNum, const matriz& m2m)
{
	int rc;
	char* errorMessage;
	sqlite3 *db = openDb();
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMessage);
	sqlite3_stmt *stmt;
	int filas = m2m.size();
	std::string qry = "INSERT INTO Valorizacion (netting_set, num_operacion, tiempo, num_simulacion, valor) VALUES (?, ?, ?, ?, ?)";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		return 2.5;
	}
	for (int i = 0; i < filas; i++)
	{
		string input1 = ns;
		string input2 = dealNum;
		double input3 = m2m[i][0];
		double input4 = m2m[i][1];
		double input5 = m2m[i][2];

		rc = sqlite3_bind_text(stmt, 1, input1.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_bind_text(stmt, 2, input2.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_bind_double(stmt, 3, input3);
		rc = sqlite3_bind_double(stmt, 4, input4);
		rc = sqlite3_bind_double(stmt, 5, input5);
		rc = sqlite3_step(stmt);
		if ((rc != SQLITE_DONE) && (rc != SQLITE_ROW))
		{
			sqlite3_close_v2(db);
			return 3.0;
		}
		sqlite3_reset(stmt);
	}

	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMessage);		
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();

	return 0.0;
}

double insertValorizacion(vector<ResultadoValorizacion> & resultados, tablas type)
{
	int rc;
	char* errorMessage;
	sqlite3 *db = openDb();
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMessage);
	sqlite3_stmt *stmt;
	int filas = resultados.size();
	std::string qry;
	if (type == tblValorizacion)
	{
		qry = "INSERT INTO Valorizacion (netting_set, num_operacion, tiempo, num_simulacion, valor) VALUES (?, ?, ?, ?, ?)";
	}
	else
	{
		qry = "INSERT INTO Colateral (netting_set, num_operacion, tiempo, num_simulacion, valor) VALUES (?, ?, ?, ?, ?)";
	}

	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		return 2.5;
	}
	int numSim = resultados.begin()->_mtm.size();
	for (int i = 0; i < filas; i++)
	{
		//string input1 = resultados[i]._netting_set;
		//string input2 = resultados[i]._deal_number;
		//double input3 = resultados[i]._time;//m2m[i][0];
		for(int j = 0; j < numSim; j++)
		{
			//int input4 = j;
			//double input5 = resultados[i]._mtm[j];
			rc = sqlite3_bind_text(stmt, 1, resultados[i]._netting_set.c_str(), -1, SQLITE_STATIC);
			rc = sqlite3_bind_text(stmt, 2, resultados[i]._deal_number.c_str(), -1, SQLITE_STATIC);
			rc = sqlite3_bind_double(stmt, 3,resultados[i]._time);
			rc = sqlite3_bind_int(stmt, 4, j);
			rc = sqlite3_bind_double(stmt, 5, resultados[i]._mtm[j]);
			rc = sqlite3_step(stmt);
			if ((rc != SQLITE_DONE) && (rc != SQLITE_ROW))
			{
				sqlite3_close_v2(db);
				return 3.0;
			}
			sqlite3_reset(stmt);
		}
	}

	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMessage);		
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();

	return 0.0;
}

double getThresholdInfoFromNettingSet(NettingSet& ns)
{
	int rc;
	sqlite3 *db = openDb();

	sqlite3_stmt *stmt;
	std::string qry = "SELECT threshold_curr, threshold_inst, threshold_ns, periodicity, last_date FROM NettingSet WHERE nombre = ?";
	string tempString(ns.getName());
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	rc = sqlite3_bind_text(stmt, 1, tempString.c_str(), -1, SQLITE_STATIC);

	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		return 2.5;
	}
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		const char* temp = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		string result(temp);
		ns.setThresholdCurrency(result);
		ns.setThresholdInstitution(sqlite3_column_double(stmt, 1));
		ns.setThresholdCounterparty(sqlite3_column_double(stmt, 2));
		ns.setPeriodicity(sqlite3_column_int(stmt, 3));
		ns.setLastMarginDate(sqlite3_column_int(stmt, 4));

		sqlite3_finalize(stmt);
		sqlite3_close(db);
		sqlite3_shutdown();
		return 0.0;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	return 2.0;
}

double insertColateral(string dealNum, const matriz& collateral, NettingSet& ns)
{
	int rc;
	char* errorMessage;
	sqlite3 *db = openDb();

	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMessage);
	sqlite3_stmt *stmt;
	int filas = collateral.size();
	std::string qry = "INSERT INTO Colateral (netting_set, num_operacion, tiempo, num_simulacion, valor) VALUES (?, ?, ?, ?, ?)";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		return 2.5;
	}
	for (int i = 0; i < filas; i++)
	{
		string input1 = ns.getName();
		string input2 = dealNum;
		int periodicity = ns.getPeriodicity();
		double input3 = collateral[i][0] + periodicity;
		double input4 = collateral[i][1];
		//Este numero hay que procesarlo un poco mas. Voy a crear una clase NettingSet que tenga los thresholds
		//por lado y lado y la frecuencia de revalorizacion.
		//Ademas tendra un metodito que calcule el colateral que debe haber dado un m2m.
		//Entonces en la linea siguiente escribire myNettingSet.collateral(collateral[i][2])
		double input5 = collateral[i][2]; //ns.collateral(collateral[i][2]);



		rc = sqlite3_bind_text(stmt, 1, input1.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_bind_text(stmt, 2, input2.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_bind_double(stmt, 3, input3);
		rc = sqlite3_bind_double(stmt, 4, input4);
		rc = sqlite3_bind_double(stmt, 5, input5);
		rc = sqlite3_step(stmt);
		if ((rc != SQLITE_DONE) && (rc != SQLITE_ROW))
		{
			sqlite3_close_v2(db);
			return 3.0;
		}
		sqlite3_reset(stmt);
	}

	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMessage);		
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();

	return 0.0;
}

double insertOperationIntoDb(vector<Operation>& vecOps)
{
	int rc;
	char* errorMessage;
	sqlite3 *db = openDb();
	rc = sqlite3_exec(db, "DELETE FROM Operacion", NULL, NULL, &errorMessage);
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMessage);
	sqlite3_stmt *stmt;
	int filas = vecOps.size();
	string qry = "INSERT INTO Operacion (deal_number, type, pricer, fx, bStartTime, bExpiryTime, bCurrency, bAmount, bTipoTasa, bFormaTasa, bValueRate, bPeriodicity, bStubPeriod, bFixPeriodicity, bFixStubPeriod, bSpread, bAmort, bIncludeAmort, bProjCurve, bDiscountCurve, bInitialUF, sStartTime, sExpiryTime, sCurrency, sAmount, sTipoTasa, sFormaTasa, sValueRate, sPeriodicity, sStubPeriod, sFixPeriodicity, sFixStubPeriod, sSpread, sAmort, sIncludeAmort, sProjCurve, sDiscountCurve, sInitialUF) VALUES (?1, ?2, ?3, ?4, ?5, ?6, ?7, ?8, ?9, ?10, ?11, ?12, ?13, ?14, ?15, ?16, ?17, ?18, ?19, ?20, ?21, ?22, ?23, ?24, ?25, ?26, ?27, ?28, ?29, ?30, ?31, ?32, ?33, ?34, ?35, ?36, ?37, ?38)";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		return 2.5;
	}
	for (int i = 0; i < filas; i++)
	{
		//Se capturan los datos básicos de la operación
		string input1 = vecOps[i]._dealNumber;
		if (input1.empty()) continue;			//Si viene vacío pasamos al próximo registro
		string input2 = vecOps[i]._type;
		if (input2.empty()) continue;			//Si viene vacío pasamos al próximo registro
		string input3 = vecOps[i]._pricer;
		if (input3.empty()) continue;			//Si viene vacío pasamos al próximo registro
		string input4 = vecOps[i]._fx;

		//Los datos de la pata activa
		double input5 = vecOps[i]._startTime.first;
		double input6 = vecOps[i]._expiryTime.first;
		string input7 = vecOps[i]._currency.first;
		double input8 = vecOps[i]._amount.first;
		string input9 = vecOps[i]._tipoTasa.first;
		string input10 = vecOps[i]._formaTasa.first;
		double input11 = vecOps[i]._valueRate.first;
		string input12 = vecOps[i]._periodicity.first;
		string input13 = vecOps[i]._stubPeriod.first;
		string input14 = vecOps[i]._fixingPeriodicity.first;
		if (input14.empty()) input14 = "";
		string input15 = vecOps[i]._fixingStubPeriod.first;
		if (input15.empty()) input15 = "";
		double input16 = vecOps[i]._spread.first;
		string input17 = vecOps[i]._amort.first;
		if (input17.empty()) input17 = "";
		string input18 = vecOps[i]._includeAmort.first;
		string input19 = vecOps[i]._projectCurve.first;
		if (input19.empty()) input19 = "";
		string input20 = vecOps[i]._discountCurve.first;
		double input21 = vecOps[i]._initialUF.first;

		//Los datos de la pata pasiva
		double input22 = vecOps[i]._startTime.second;
		double input23 = vecOps[i]._expiryTime.second;
		string input24 = vecOps[i]._currency.second;
		double input25 = vecOps[i]._amount.second;
		string input26 = vecOps[i]._tipoTasa.second;
		string input27 = vecOps[i]._formaTasa.second;
		double input28 = vecOps[i]._valueRate.second;
		string input29 = vecOps[i]._periodicity.second;
		string input30 = vecOps[i]._stubPeriod.second;
		string input31 = vecOps[i]._fixingPeriodicity.second;
		if (input31.empty()) input31 = "";
		string input32 = vecOps[i]._fixingStubPeriod.second;
		if (input32.empty()) input32 = "";
		double input33 = vecOps[i]._spread.second;
		string input34 = vecOps[i]._amort.second;
		if (input34.empty()) input34 = "";
		string input35 = vecOps[i]._includeAmort.second;
		string input36 = vecOps[i]._projectCurve.second;
		if (input36.empty()) input36 = "";
		string input37 = vecOps[i]._discountCurve.second;
		double input38 = vecOps[i]._initialUF.second;

		//Hacemos el binding de los primeros 4 parámetros
		rc = sqlite3_bind_text(stmt, 1, input1.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_bind_text(stmt, 2, input2.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_bind_text(stmt, 3, input3.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_bind_text(stmt, 4, input4.c_str(), -1, SQLITE_STATIC);

		//Binding de los parámetros de la pata activa
		rc = sqlite3_bind_double(stmt, 5, input5);							//double 
		rc = sqlite3_bind_double(stmt, 6, input6);							//double 
		rc = sqlite3_bind_text(stmt, 7, input7.c_str(), -1, SQLITE_STATIC);	//string 
		rc = sqlite3_bind_double(stmt, 8, input8);							//double 
		rc = sqlite3_bind_text(stmt, 9, input9.c_str(), -1, SQLITE_STATIC);	//string 
		rc = sqlite3_bind_text(stmt, 10, input10.c_str(), -1, SQLITE_STATIC);//string 
		rc = sqlite3_bind_double(stmt, 11, input11);							//double 
		rc = sqlite3_bind_text(stmt, 12, input12.c_str(), -1, SQLITE_STATIC);//string
		rc = sqlite3_bind_text(stmt, 13, input13.c_str(), -1, SQLITE_STATIC);//string 
		rc = sqlite3_bind_text(stmt, 14, input14.c_str(), -1, SQLITE_STATIC);//string 
		rc = sqlite3_bind_text(stmt, 15, input15.c_str(), -1, SQLITE_STATIC);//string 
		rc = sqlite3_bind_double(stmt, 16, input16);							//double
		rc = sqlite3_bind_text(stmt, 17, input17.c_str(), -1, SQLITE_STATIC);//string
		rc = sqlite3_bind_text(stmt, 18, input18.c_str(), -1, SQLITE_STATIC);//string 
		rc = sqlite3_bind_text(stmt, 19, input19.c_str(), -1, SQLITE_STATIC);//string
		rc = sqlite3_bind_text(stmt, 20, input20.c_str(), -1, SQLITE_STATIC);//string
		rc = sqlite3_bind_double(stmt, 21, input21);							//double

		//Binding de los parámetros de la pata pasiva
		rc = sqlite3_bind_double(stmt, 22, input22);							//double 
		rc = sqlite3_bind_double(stmt, 23, input23);							//double 
		rc = sqlite3_bind_text(stmt, 24, input24.c_str(), -1, SQLITE_STATIC);//string 
		rc = sqlite3_bind_double(stmt, 25, input25);							//double 
		rc = sqlite3_bind_text(stmt, 26, input26.c_str(), -1, SQLITE_STATIC);//string 
		rc = sqlite3_bind_text(stmt, 27, input27.c_str(), -1, SQLITE_STATIC);//string 
		rc = sqlite3_bind_double(stmt, 28, input28);							//double 
		rc = sqlite3_bind_text(stmt, 29, input29.c_str(), -1, SQLITE_STATIC);//string
		rc = sqlite3_bind_text(stmt, 30, input30.c_str(), -1, SQLITE_STATIC);//string 
		rc = sqlite3_bind_text(stmt, 31, input31.c_str(), -1, SQLITE_STATIC);//string 
		rc = sqlite3_bind_text(stmt, 32, input32.c_str(), -1, SQLITE_STATIC);//string 
		rc = sqlite3_bind_double(stmt, 33, input33);							//double
		rc = sqlite3_bind_text(stmt, 34, input34.c_str(), -1, SQLITE_STATIC);//string
		rc = sqlite3_bind_text(stmt, 35, input35.c_str(), -1, SQLITE_STATIC);//string 
		rc = sqlite3_bind_text(stmt, 36, input36.c_str(), -1, SQLITE_STATIC);//string
		rc = sqlite3_bind_text(stmt, 37, input37.c_str(), -1, SQLITE_STATIC);//string
		rc = sqlite3_bind_double(stmt, 38, input38);							//double

		//Se ejecuta el stmt y se controla si está ok
		rc = sqlite3_step(stmt);
		if ((rc != SQLITE_DONE) && (rc != SQLITE_ROW))	//Si hay problemas
		{
			sqlite3_close_v2(db);						//Cierra la conexión
			return 3.0;									//Retorna 3.0
		}
		sqlite3_reset(stmt);							//Se resetea el stmt para pasar al siguiente registro
	}

	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMessage);	//Se hace el COMMIT

	//Se cierra la BBDD
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	
	return 0.0;			//Retorna el código de éxito
}

double insertOperations(CellMatrix valores)
{
	int filas = valores.RowsInStructure();	//Indica el número de operaciones a insertar en la BBDD
	vector<Operation> ops;					//En este vector recogeremos todos los registros a insertar
	Operation auxOp;						//Objeto temporal que empujaremos en ops

	//Recorremos todas las operaciones (filas de valores)
	for (int i = 0; i < filas; i++)
	{
		//Son los datos comunes a ambas patas de la operación
		auxOp._dealNumber = valores(i, 0).StringValue();
		auxOp._type	= valores(i, 1).StringValue();
		auxOp._pricer = valores(i, 2).StringValue();
		if (valores(i, 3).IsEmpty())
		{
			auxOp._fx = "";
		}
		else
		{
			auxOp._fx = valores(i, 3).StringValue();
		}

		//Comenzamos el ingreso de los datos por pata. Notar que .first = activo
		auxOp._startTime.first = valores(i, 4).NumericValue();
		auxOp._expiryTime.first = valores(i, 5).NumericValue();
		auxOp._currency.first = valores(i, 6).StringValue();
		auxOp._amount.first = valores(i, 7).NumericValue();
		if (valores(i, 8).IsEmpty())
		{
			auxOp._tipoTasa.first = "";
		}
		else
		{
			auxOp._tipoTasa.first = valores(i, 8).StringValue();
		}
		if (valores(i, 9).IsEmpty())
		{
			auxOp._formaTasa.first = "";
		}
		else
		{
			auxOp._formaTasa.first = valores(i, 9).StringValue();
		}
		if (valores(i, 10).IsEmpty())
		{
			auxOp._valueRate.first = 0.0;
		}
		else
		{
			auxOp._valueRate.first = valores(i, 10).NumericValue();
		}
		if (valores(i, 11).IsEmpty())
		{
			auxOp._periodicity.first = "";
		}
		else
		{
			auxOp._periodicity.first = valores(i, 11).StringValue();
		}
		if (valores(i, 12).IsEmpty())
		{
			auxOp._stubPeriod.first = "";
		}
		else
		{
			auxOp._stubPeriod.first = valores(i, 12).StringValue();
		}
		if (valores(i, 13).IsEmpty())
		{
			auxOp._fixingPeriodicity.first = "";
		}
		else
		{
			auxOp._fixingPeriodicity.first = valores(i, 13).StringValue();			
		}
		if (valores(i, 14).IsEmpty())
		{
			auxOp._fixingStubPeriod.first = "";
		}
		else
		{
			auxOp._fixingStubPeriod.first = valores(i, 14).StringValue();
		}
		if (valores(i, 15).IsEmpty())
		{
			auxOp._spread.first = 0.0;
		}
		else
		{
			auxOp._spread.first = valores(i, 15).NumericValue();
		}
		if (valores(i, 16).IsEmpty())
		{
			auxOp._amort.first = "";
		}
		else
		{
			auxOp._amort.first = valores(i, 16).StringValue();
		}
		if (valores(i, 17).IsEmpty())
		{
			auxOp._includeAmort.first = "";
		}
		else
		{
			auxOp._includeAmort.first = valores(i, 17).StringValue();
		}
		if (valores(i, 18).IsEmpty())
		{
			auxOp._projectCurve.first = "";
		}
		else
		{
			auxOp._projectCurve.first = valores(i, 18).StringValue();
		}
		auxOp._discountCurve.first = valores(i, 19).StringValue();
		if (valores(i, 20).IsEmpty())
		{
			auxOp._initialUF.first = 0.0;
		}
		else
		{
			auxOp._initialUF.first = valores(i, 20).NumericValue();
		}

		//y .second = pasivo
		auxOp._startTime.second = valores(i, 21).NumericValue();
		auxOp._expiryTime.second = valores(i, 22).NumericValue();
		auxOp._currency.second = valores(i, 23).StringValue();
		auxOp._amount.second = valores(i, 24).NumericValue();
		if (valores(i, 25).IsEmpty())
		{
			auxOp._tipoTasa.second = "";
		}
		else
		{
			auxOp._tipoTasa.second = valores(i, 25).StringValue();
		}
		if (valores(i, 26).IsEmpty())
		{
			auxOp._formaTasa.second = "";
		}
		else
		{
			auxOp._formaTasa.second = valores(i, 26).StringValue();
		}
		if (valores(i, 27).IsEmpty())
		{
			auxOp._valueRate.second = 0.0;
		}
		else
		{
			auxOp._valueRate.second = valores(i, 27).NumericValue();
		}
		if (valores(i, 28).IsEmpty())
		{
			auxOp._periodicity.second = "";
		}
		else
		{
			auxOp._periodicity.second = valores(i, 28).StringValue();
		}
		if (valores(i, 29).IsEmpty())
		{
			auxOp._stubPeriod.second = "";
		}
		else
		{
			auxOp._stubPeriod.second = valores(i, 29).StringValue();
		}
		if (valores(i, 30).IsEmpty())
		{
			auxOp._fixingPeriodicity.second = "";
		}
		else
		{
			auxOp._fixingPeriodicity.second = valores(i, 30).StringValue();			
		}
		if (valores(i, 31).IsEmpty())
		{
			auxOp._fixingStubPeriod.second = "";
		}
		else
		{
			auxOp._fixingStubPeriod.second = valores(i, 31).StringValue();
		}
		if (valores(i, 32).IsEmpty())
		{
			auxOp._spread.second = 0.0;
		}
		else
		{
			auxOp._spread.second = valores(i, 32).NumericValue();
		}
		if (valores(i, 33).IsEmpty())
		{
			auxOp._amort.second = "";
		}
		else
		{
			auxOp._amort.second = valores(i, 33).StringValue();
		}
		if (valores(i, 34).IsEmpty())
		{
			auxOp._includeAmort.second = "";
		}
		else
		{
			auxOp._includeAmort.second = valores(i, 34).StringValue();
		}
		if (valores(i, 35).IsEmpty())
		{
			auxOp._projectCurve.second = "";
		}
		else
		{
			auxOp._projectCurve.second = valores(i, 35).StringValue();
		}

		auxOp._discountCurve.second = valores(i, 36).StringValue();

		if (valores(i, 37).IsEmpty())
		{
			auxOp._initialUF.second = 0.0;
		}
		else
		{
			auxOp._initialUF.second = valores(i, 37).NumericValue();
		}

		//Empujamos auxOp al vector ops
		ops.push_back(auxOp);
	}
	double result = insertOperationIntoDb(ops); //Se insertan las operaciones en ela BBDD
	ops.clear();						//Se vacía el vector de operaciones
	ops.swap(vector<Operation> (ops));	//Swap trick para liberar la memoria del vector
	return result;
}

double getOperationFromDealNumber(int numero, Operacion* op)
{
	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	Forward* fwd = new Forward;
	std::string tempString;
	
	std::string qry = "SELECT * FROM Operacion WHERE deal_number = ?";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		return 1.0;
	}
	
	rc = sqlite3_bind_int(stmt, 1, numero);

	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		tempString.assign((const char*)sqlite3_column_text(stmt, 2));
		if (tempString == "FWD")
		{
			fwd->dealNumber = numero;
			fwd->tipoInstrumento = tempString;
			(fwd->pricer).assign((const char*)sqlite3_column_text(stmt, 3));
			(fwd->fxPair).assign((const char*)sqlite3_column_text(stmt, 4));
			(fwd->monedaCompra).assign((const char*)sqlite3_column_text(stmt, 7));
			(fwd->monedaVenta).assign((const char*)sqlite3_column_text(stmt, 24));
			fwd->montoCompra = sqlite3_column_double(stmt, 8);
			fwd->montoVenta = sqlite3_column_double(stmt, 25);
			fwd->plazoResidual = sqlite3_column_double(stmt, 6);
			(fwd->curvaDescuentoCompra).assign((const char*)sqlite3_column_text(stmt, 20));
			(fwd->curvaDescuentoVenta).assign((const char*)sqlite3_column_text(stmt, 37));
			op->tipo = "FWD";
			op->oper = fwd;
		}
		else
		{
			//Esto se implementa para los swaps

		}
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	return 0.0;
}



double getOperationFromDealNumber(string dn, Operation* op)
//(int numero, Operacion* op)
{
	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	//Forward* fwd = new Forward;
	std::string tempString;
	
	std::string qry = "SELECT * FROM Operacion WHERE deal_number = ?";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		return 1.0;
	}
	
	rc = sqlite3_bind_text(stmt, 1, dn.c_str(), -1, SQLITE_STATIC);	
	//rc = sqlite3_bind_int(stmt, 1, numero);

	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		tempString.assign((const char*)sqlite3_column_text(stmt, 2));
		if (tempString == "FWD")
		{
			/*fwd->dealNumber = numero;
			fwd->tipoInstrumento = tempString;
			(fwd->pricer).assign((const char*)sqlite3_column_text(stmt, 3));
			(fwd->fxPair).assign((const char*)sqlite3_column_text(stmt, 4));
			(fwd->monedaCompra).assign((const char*)sqlite3_column_text(stmt, 7));
			(fwd->monedaVenta).assign((const char*)sqlite3_column_text(stmt, 24));
			fwd->montoCompra = sqlite3_column_double(stmt, 8);
			fwd->montoVenta = sqlite3_column_double(stmt, 25);
			fwd->plazoResidual = sqlite3_column_double(stmt, 6);
			(fwd->curvaDescuentoCompra).assign((const char*)sqlite3_column_text(stmt, 20));
			(fwd->curvaDescuentoVenta).assign((const char*)sqlite3_column_text(stmt, 37));
			op->tipo = "FWD";
			op->oper = fwd;
			*/
		}
		else if (tempString == "SWP")
		{
			//Esto se implementa para los swaps
			op->_type = "SWAP"; 
			op->_dealNumber = integerToString(sqlite3_column_int(stmt, 1));
			(op->_pricer).assign((const char*)sqlite3_column_text(stmt, 3));
			op->_startTime.first = sqlite3_column_double(stmt, 5);
			op->_startTime.second = sqlite3_column_double(stmt, 22);
			op->_expiryTime.first = sqlite3_column_double(stmt, 6);
			op->_expiryTime.second = sqlite3_column_double(stmt, 23);
			(op->_currency.first).assign((const char*)sqlite3_column_text(stmt, 7));
			(op->_currency.second).assign((const char*)sqlite3_column_text(stmt, 24));
			op->_amount.first = sqlite3_column_double(stmt, 8);
			op->_amount.second = sqlite3_column_double(stmt, 25);
			(op->_tipoTasa.first).assign((const char*)sqlite3_column_text(stmt, 9));
			(op->_tipoTasa.second).assign((const char*)sqlite3_column_text(stmt, 26));
			(op->_formaTasa.first).assign((const char*)sqlite3_column_text(stmt, 10));
			(op->_formaTasa.second).assign((const char*)sqlite3_column_text(stmt, 27));
			op->_valueRate.first = sqlite3_column_double(stmt, 11);
			op->_valueRate.second = sqlite3_column_double(stmt, 28);
			(op->_periodicity.first).assign((const char*)sqlite3_column_text(stmt, 12));
            (op->_periodicity.second).assign((const char*)sqlite3_column_text(stmt, 29));
			(op->_stubPeriod.first).assign((const char*)sqlite3_column_text(stmt, 13));
            (op->_stubPeriod.second).assign((const char*)sqlite3_column_text(stmt, 30));
			(op->_fixingPeriodicity.first).assign((const char*)sqlite3_column_text(stmt, 14));
            (op->_fixingPeriodicity.second).assign((const char*)sqlite3_column_text(stmt, 31));
			(op->_fixingStubPeriod.first).assign((const char*)sqlite3_column_text(stmt, 15));
            (op->_fixingStubPeriod.second).assign((const char*)sqlite3_column_text(stmt, 32));
			op->_spread.first = sqlite3_column_double(stmt, 16);
			op->_spread.second = sqlite3_column_double(stmt, 33);
			(op->_amort.first).assign((const char*)sqlite3_column_text(stmt, 17));
            (op->_amort.second).assign((const char*)sqlite3_column_text(stmt, 34));
			(op->_includeAmort.first).assign((const char*)sqlite3_column_text(stmt, 18));
            (op->_includeAmort.second).assign((const char*)sqlite3_column_text(stmt, 35));
			(op->_projectCurve.first).assign((const char*)sqlite3_column_text(stmt, 19));
			(op->_projectCurve.second).assign((const char*)sqlite3_column_text(stmt, 36));
			(op->_discountCurve.first).assign((const char*)sqlite3_column_text(stmt, 20));
			(op->_discountCurve.second).assign((const char*)sqlite3_column_text(stmt, 37));
			op->_initialUF.first = sqlite3_column_double(stmt, 21);
			op->_initialUF.second = sqlite3_column_double(stmt, 38);
		}
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	return 0.0;
}










double getCurvaFromNombre(std::string nombre, Curva* curvaOut)
{
	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	
	std::string qry = "SELECT plazo, valor FROM Curva WHERE nombre = ? ORDER BY plazo ASC";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		return 1.0;
	}
	
	rc = sqlite3_bind_text(stmt, 1, nombre.c_str(), -1, SQLITE_STATIC);

	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		(curvaOut->tenors).push_back(sqlite3_column_double(stmt, 0));
		(curvaOut->rates).push_back(sqlite3_column_double(stmt, 1));
	}
	
	curvaOut->nombre = nombre;
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	return 0.0;
}
	//falta get curva en linea 500 se saca del cppinterface.h
double valueFwd(int number) //Esta es una función para llamar desde Excel
{
	double result;
	Operacion* operacion = new Operacion;
	Valorizador* miValorizador = Valorizador::getInstance();
	double x = getOperationFromDealNumber(number, operacion);
	if (x == 0)
	{
		result = miValorizador->valorOperacion(operacion);
	}
	delete operacion;
	delete miValorizador;
	return result;
}

double insertMonedaBase(std::string monedaBase)
{
	int rc;
	char* errorMessage;
	sqlite3 *db = openDb();
	rc = sqlite3_exec(db, "DELETE FROM FxBase", NULL, NULL, &errorMessage);
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMessage);
	sqlite3_stmt *stmt;
	std::string qry = "INSERT INTO FxBase (moneda_base) VALUES (?)";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		return 2.5;
	}
	
	rc = sqlite3_bind_text(stmt, 1, monedaBase.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_step(stmt);
	if ((rc != SQLITE_DONE) && (rc != SQLITE_ROW))
	{
		sqlite3_finalize(stmt);
		sqlite3_close_v2(db);
		sqlite3_shutdown();
		return 3.0;
	}
	
	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMessage);		
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();

	return 4.0;
}

double insertValorPercentil(double valorPercentil)
{
	int rc;
	char* errorMessage;
	sqlite3 *db = openDb();
	rc = sqlite3_exec(db, "DELETE FROM ValorPercentil", NULL, NULL, &errorMessage);
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMessage);
	sqlite3_stmt *stmt;
	std::string qry = "INSERT INTO ValorPercentil (valor) VALUES (?)";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		return 1.0;
	}
	
	rc = sqlite3_bind_double(stmt, 1, valorPercentil);
	rc = sqlite3_step(stmt);
	if ((rc != SQLITE_DONE) && (rc != SQLITE_ROW))
	{
		sqlite3_finalize(stmt);
		sqlite3_close_v2(db);
		sqlite3_shutdown();
		return 2.0;
	}
	
	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMessage);		
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();

	return 0.0;
}
double getInstitutionDefaultProbability()
{
	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	
	std::string qry = "SELECT default_prob FROM Institution";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		throw("Error al preparar el statement");
	}
	
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		double result = sqlite3_column_double(stmt, 0);
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		sqlite3_shutdown();
		return result;
	}
	
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	throw("Error al ejecutar la consulta");	
}

double getStoppingTimes(vector<int>& st)
{
	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	
	std::string qry = "SELECT DISTINCT tiempo FROM Colateral";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		throw("Error al preparar el statement");
	}
	
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		st.push_back(sqlite3_column_int(stmt, 0));
	}
	
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	return 0.0;
}

double getInstitutionRecoveryRate()
{
	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	
	std::string qry = "SELECT recovery_rate FROM Institution";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		throw("Error al preparar el statement");
	}
	
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		double result = sqlite3_column_double(stmt, 0);
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		sqlite3_shutdown();
		return result;
	}
	
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	throw("Error al ejecutar la consulta");	
}

double getDefaultProbabilityFromNettingSet(string ns)
{
	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	
	std::string qry = "SELECT default_prob FROM NettingSet WHERE nombre = ?";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	rc = sqlite3_bind_text(stmt, 1, ns.c_str(), -1, SQLITE_STATIC);
	
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		throw("Error al preparar el statement");
	}
	
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		double result = sqlite3_column_double(stmt, 0); //Esta linea se corrigió. Se estaba tomando como int y por eso te devolvía 0.
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		sqlite3_shutdown();
		return result;
	}
	
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	throw("Error al ejecutar la consulta.");	
}

double getRecoveryRateFromNettingSet(string ns)
{
	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	
	std::string qry = "SELECT recovery_rate FROM NettingSet WHERE nombre = ?";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	rc = sqlite3_bind_text(stmt, 1, ns.c_str(), -1, SQLITE_STATIC);
	
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		throw("Error al preparar el statement");
	}
	
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		//int result = sqlite3_column_int(stmt, 0);
		double result = sqlite3_column_double(stmt, 0); //Esta linea se corrigió. Se estaba tomando como int y por eso te devolvía 0.
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		sqlite3_shutdown();
		return result;
	}
	
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	throw("Error al ejecutar la consulta.");	
}

int getPeriodicityFromNettingSet(string ns)
{
	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	
	std::string qry = "SELECT periodicity FROM NettingSet WHERE nombre = ?";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	rc = sqlite3_bind_text(stmt, 1, ns.c_str(), -1, SQLITE_STATIC);
	
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		throw("Error al preparar el statement");
	}
	
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		int result = sqlite3_column_int(stmt, 0);
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		sqlite3_shutdown();
		return result;
	}
	
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	throw("Error al ejecutar la consulta");	
}

std::string getMonedaBase()
{
	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	
	std::string qry = "SELECT moneda_base FROM FxBase";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		return "Error al preparar el statement";
	}
	
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		const char* temp = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		std::string result(temp);
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		sqlite3_shutdown();
		return result;
	}
	
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	return "Error";
}

FxRate* getFX(string nombreFX)
{
	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	
	std::string qry = "SELECT valor, curva_fuerte, curva_debil FROM Fx WHERE nombre = ?";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	
	rc = sqlite3_bind_text(stmt, 1, nombreFX.c_str(), -1, SQLITE_STATIC);

	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		throw("1.0");
	}
	
	FxRate* result;
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		string curvaFuerte;
		string curvaDebil;
		result = new FxRate(nombreFX, sqlite3_column_double(stmt, 0), curvaDebil.assign((const char*)sqlite3_column_text(stmt, 2)), curvaFuerte.assign((const char*)sqlite3_column_text(stmt, 1)));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		sqlite3_shutdown();
		return result;
	}
	
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();

}

double getSigma(string nombreFactor)
{
	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	
	string qry = "SELECT valor FROM Sigma WHERE nombre = ?";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	
	rc = sqlite3_bind_text(stmt, 1, nombreFactor.c_str(), -1, SQLITE_STATIC);

	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		return 1.0;
	}
	
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		double result = sqlite3_column_double(stmt, 0);
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		sqlite3_shutdown();
		return result;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	return 2.0;
}

double getGamma(string nombreFactor)
{
	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	
	string qry = "SELECT valor FROM Gamma WHERE nombre = ?";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	
	rc = sqlite3_bind_text(stmt, 1, nombreFactor.c_str(), -1, SQLITE_STATIC);

	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		return 1.0;
	}
	
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		double result = sqlite3_column_double(stmt, 0);
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		sqlite3_shutdown();
		return result;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	return 2.0;
}

double getSimulationAtT(string curva, long int t, vector<double>& sim)
//El doble (double t) debiera pasar a Long: Revisar plis
{
	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;

	string qry = "SELECT valor FROM Simulacion WHERE tiempo = ? AND factor = ? ORDER BY num_simulacion";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);

	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		return 1.0;
	}
	
	rc = sqlite3_bind_int(stmt, 1, t);
	rc = sqlite3_bind_text(stmt, 2, curva.c_str(), -1, SQLITE_STATIC);

	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		double valor = sqlite3_column_double(stmt, 0);
		sim.push_back(valor);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	return 0.0;
}

double getSimulationAtT(string curva1, string curva2, double t, map<string, double>& sim)
{
	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
    //USDCLP, EURUSD, USDJPY, GBPUSD, USDMXN, CHFUSD, CLFCLP, CLP_CAM, EURUSDFX, USD_LIB_3M
	//factor = 'USDCLP' OR factor = 'EURUSD' OR factor = 'USDJPY' OR factor = 'GBPUSD' OR factor = 'USDMXN' OR factor = 'CHFUSD' OR factor = 'CLFCLP' OR factor = ''
	string qry = "SELECT num_simulacion || '-'|| factor AS tag, valor FROM Simulacion WHERE tiempo = ? AND (factor = 'USDCLP' OR factor = 'EURUSD' OR factor = 'USDJPY' OR factor = 'GBPUSD' OR factor = 'USDMXN' OR factor = 'CHFUSD' OR factor = 'CLFCLP' OR factor = ? OR factor = ?) ORDER BY tag";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);

	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		return 1.0;
	}
	
	rc = sqlite3_bind_int(stmt, 1, (int)t);
	rc = sqlite3_bind_text(stmt, 2, curva1.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_text(stmt, 3, curva2.c_str(), -1, SQLITE_STATIC);

	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		string aux;
		aux.assign((const char*)sqlite3_column_text(stmt, 0));
		double valor = sqlite3_column_double(stmt, 1);
		sim[aux] = valor;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	return 0.0;
}

double getSimulationAtT(long int t, map<string, double>& sim)
{
    int rc;
    sqlite3 *db = openDb();
    sqlite3_stmt *stmt;
 
    string qry = "SELECT num_simulacion || '-'|| factor AS tag, valor FROM Simulacion WHERE tiempo = ? ORDER BY tag";
    rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
 
    if (rc != SQLITE_OK)
    {
        sqlite3_close_v2(db);
        const char* a = sqlite3_errmsg(db);
        return 1.0;
    }
     
    rc = sqlite3_bind_int(stmt, 1, t);
 
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        string aux;
        aux.assign((const char*)sqlite3_column_text(stmt, 0));
        double valor = sqlite3_column_double(stmt, 1);
        sim[aux] = valor;
    }
 
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    sqlite3_shutdown();
    return 0.0;
}

int getMaxSim()
{
	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	
	string qry = "SELECT max(num_simulacion) FROM Simulacion";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		return 1;
	}
	
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		int result = sqlite3_column_int(stmt, 0);
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		sqlite3_shutdown();
		return result;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	return 2;
}


map<string, Rho> getRho(vector<pair <string, string>> inFactores)
{
	int rc;
	string auxStr;
	map<string, Rho> result;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	
	string qry = "SELECT nombre, valor FROM Rho WHERE nombre = ?";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		throw("Problema");
	}
	for (unsigned int i = 0; i < inFactores.size(); i++)
	{
		for (unsigned int j = i + 1; j < inFactores.size(); j++)
		{
			auxStr = inFactores[i].first + "$" + inFactores[j].first;
			rc = sqlite3_bind_text(stmt, 1, auxStr.c_str(), -1, SQLITE_STATIC);
			if (rc == SQLITE_OK)
			{
				if (sqlite3_step(stmt) == SQLITE_ROW)
				{
					string mNombre;
					mNombre.assign((const char*)sqlite3_column_text(stmt, 0));
					double mValor = sqlite3_column_double(stmt, 1);
					Rho* mRho = new Rho(mNombre, mValor);
					result[mNombre] = *mRho;
					delete mRho;
					rc = sqlite3_clear_bindings(stmt);
					rc = sqlite3_reset(stmt);
				}
				else
				{
					rc = sqlite3_clear_bindings(stmt);
					rc = sqlite3_reset(stmt);
					auxStr = inFactores[j].first + "$" + inFactores[i].first;
					rc = sqlite3_bind_text(stmt, 1, auxStr.c_str(), -1, SQLITE_STATIC);
					if (rc == SQLITE_OK)
					{
						if (sqlite3_step(stmt) == SQLITE_ROW)
						{
							string mNombre;
							mNombre = inFactores[i].first + "$" + inFactores[j].first; //.assign((const char*)sqlite3_column_text(stmt, 0));
							double mValor = sqlite3_column_double(stmt, 1);
							Rho* mRho = new Rho(mNombre, mValor);
							result[mNombre] = *mRho;
							delete mRho;
							rc = sqlite3_clear_bindings(stmt);
							rc = sqlite3_reset(stmt);
						}
					}
				}
			}
		}
	}
	
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	return result;
}

double insertVector(CellMatrix valores, std::string destino)
{
	int rc;
	char* errorMessage;
	sqlite3 *db = openDb();
	std::string qry ="DELETE FROM " + destino;
	rc = sqlite3_exec(db, qry.c_str(), NULL, NULL, &errorMessage);
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMessage);
	sqlite3_stmt *stmt;
	int filas = valores.RowsInStructure();
	qry = "INSERT INTO " + destino +" (nombre, valor) VALUES (?, ?)";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		return 2.5;
	}
	for (int i = 0; i < filas; i++)
	{
		std::string input1 = valores(i, 0).StringValue();
		double input2 = valores(i, 1).NumericValue();
		rc = sqlite3_bind_text(stmt, 1, input1.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_bind_double(stmt, 2, input2);
		rc = sqlite3_step(stmt);
		if ((rc != SQLITE_DONE) && (rc != SQLITE_ROW))
		{
			sqlite3_close_v2(db);
			return 3.0;
		}
		sqlite3_reset(stmt);
	}

	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMessage);		
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();

	return 4.0;
}

double insertInstitution(double probDefault, double recovRate, double spreadCap, double spreadCol)
{
	int rc;
	char* errorMessage;
	sqlite3 *db = openDb();
	string qry ="DELETE FROM Institution";
	rc = sqlite3_exec(db, qry.c_str(), NULL, NULL, &errorMessage);
 
	sqlite3_stmt *stmt;
	qry = "INSERT INTO Institution (default_prob, recovery_rate, spread_cap, spread_col) VALUES (?, ?, ?, ?)";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		return 1.0;
	}
 
	rc = sqlite3_bind_double(stmt, 1, probDefault);
	rc = sqlite3_bind_double(stmt, 2, recovRate);
	rc = sqlite3_bind_double(stmt, 3, spreadCap);
	rc = sqlite3_bind_double(stmt, 4, spreadCol);

	 rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE)
	{
		sqlite3_close_v2(db);
		return 1.0;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
 
	return 0.0;
}

double insertCustomAmort(CellMatrix valores)
{
	int rc;
	char* errorMessage;
	sqlite3 *db = openDb();
	rc = sqlite3_exec(db, "DELETE FROM CustomAmortization", NULL, NULL, &errorMessage);
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMessage);
	sqlite3_stmt *stmt;
	int filas = valores.RowsInStructure();
	std::string qry = "INSERT INTO CustomAmortization (deal_number, leg, amort_time, amort_percent) VALUES (?, ?, ?, ?)";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		return 2.5;
	}
	for (int i = 0; i < filas; i++)
	{
		std::string input1 = valores(i, 0).StringValue();
		std::string input2 = valores(i, 1).StringValue();
		double input3 = valores(i, 2).NumericValue();
		double input4 = valores(i, 3).NumericValue();
		rc = sqlite3_bind_text(stmt, 1, input1.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_bind_text(stmt, 2, input2.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_bind_double(stmt, 3, input3);
		rc = sqlite3_bind_double(stmt, 4, input4);
		rc = sqlite3_step(stmt);
		if ((rc != SQLITE_DONE) && (rc != SQLITE_ROW))
		{
			sqlite3_close_v2(db);
			return 3.0;
		}
		sqlite3_reset(stmt);
	}

	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMessage);		
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();

	return 4.0;
}
//Modificar
double insertXVA(const vector<Risk>& auxRisk)
{
	time_t time_0, time_1;
	time(&time_0);
	int rc;
	char* errorMessage;
	sqlite3 *db = openDb();
	string qry ="DELETE FROM Xva";
	rc = sqlite3_exec(db, qry.c_str(), NULL, NULL, &errorMessage);
 
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMessage);
	sqlite3_stmt *stmt;
	int filas = auxRisk.size();
	qry = "INSERT INTO Xva (netting_set, unilateral_cva, value_cva, unilateral_dva, value_dva, bilateral_cva, value_fva, value_pfe_max, value_epe) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		return 1.0;
	}
	for (int i = 0; i < filas; i++)
	{
		string input1 = auxRisk[i].nettingSet;
		int input2 = (int) auxRisk[i].unilateralCVA;
		double input3 = auxRisk[i].valueCVA;
		double input4 = auxRisk[i].unilateralDVA;
		double input5 = auxRisk[i].valueDVA;
		double input6 = auxRisk[i].bilateralCVA;
		double input7 = auxRisk[i].valueFVA;
		double input8 = auxRisk[i].pFEMax;
		double input9 = auxRisk[i].expPosExp;

		rc = sqlite3_bind_text(stmt, 1, input1.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_bind_int(stmt, 2, input2);
		rc = sqlite3_bind_double(stmt, 3, input3);
		rc = sqlite3_bind_double(stmt, 4, input4);
		rc = sqlite3_bind_double(stmt, 5, input5);
		rc = sqlite3_bind_double(stmt, 6, input6);
		rc = sqlite3_bind_double(stmt, 7, input7);
		rc = sqlite3_bind_double(stmt, 8, input8);
		rc = sqlite3_bind_double(stmt, 9, input9);

		rc = sqlite3_step(stmt);
		if ((rc != SQLITE_DONE) && (rc != SQLITE_ROW))
		{
			sqlite3_close_v2(db);
			return 2.0;
		}
		sqlite3_reset(stmt);
	}

	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMessage);  
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	time(&time_1);

	return 0.0;
}

double insertMetrics(const vector<Metrics>& metrics)
{
	time_t time_0, time_1;
	time(&time_0);
	int rc;
	char* errorMessage;
	sqlite3 *db = openDb();
	string qry ="DELETE FROM ExposureMetrics";
	rc = sqlite3_exec(db, qry.c_str(), NULL, NULL, &errorMessage);
	//rc = sqlite3_exec(db, "VACUUM", NULL, NULL, &errorMessage);
	
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMessage);
	sqlite3_stmt *stmt;
	int filas = metrics.size();
	qry = "INSERT INTO ExposureMetrics (netting_set, stop_time, expected_exposure, negative_expected_exposure, max_exposure, potential_future_exposure, expected_future_value) VALUES (?, ?, ?, ?, ?, ?, ?)";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		return 1.0;
	}
	for (int i = 0; i < filas; i++)
	{
		/*string input1 = metrics[i].nettingSet;
		int input2 = metrics[i].stopTime;
		double input3 = metrics[i].expExp;
		double input4 = metrics[i].negExpExp;
		double input5 = metrics[i].maxExp;
		double input6 = metrics[i].potFutExp;
		double input7 = metrics[i].expFutVal;*/

		rc = sqlite3_bind_text(stmt, 1, metrics[i].nettingSet.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_bind_int(stmt, 2, metrics[i].stopTime);
		rc = sqlite3_bind_double(stmt, 3, metrics[i].expExp);
		rc = sqlite3_bind_double(stmt, 4, metrics[i].negExpExp);
		rc = sqlite3_bind_double(stmt, 5, metrics[i].maxExp);
		rc = sqlite3_bind_double(stmt, 6, metrics[i].potFutExp);
		rc = sqlite3_bind_double(stmt, 7, metrics[i].expFutVal);

		rc = sqlite3_step(stmt);
		if ((rc != SQLITE_DONE) && (rc != SQLITE_ROW))
		{
			sqlite3_close_v2(db);
			return 2.0;
		}
		sqlite3_reset(stmt);
	}

	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMessage);		
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	time(&time_1);

	return 0.0;
}

double insertSimulation(const vector<Simulador::_simulacion>& sim)
{
	time_t time_0, time_1;
	time(&time_0);
	int rc;
	char* errorMessage;
	sqlite3 *db = openDb();
	std::string qry ="DELETE FROM Simulacion";
	rc = sqlite3_exec(db, qry.c_str(), NULL, NULL, &errorMessage);
	rc = sqlite3_exec(db, "VACUUM", NULL, NULL, &errorMessage);
	
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMessage);
	
	sqlite3_stmt *stmt;
	int filas = sim.size();
	qry = "INSERT INTO Simulacion (factor, num_simulacion, tiempo, valor) VALUES (?, ?, ?, ?)";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		return 2.5;
	}
	for (int i = 0; i < filas; i++)
	{
		std::string input1 = sim[i].factor;
		int input2 = sim[i].numSimulacion;
		double input3 = floor(sim[i].tiempo * 100000000.0 + .5) / 100000000.0;
		double input4 = sim[i].valor;

		rc = sqlite3_bind_text(stmt, 1, input1.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_bind_int(stmt, 2, input2);
		rc = sqlite3_bind_double(stmt, 3, input3);
		rc = sqlite3_bind_double(stmt, 4, input4);

		rc = sqlite3_step(stmt);
		if ((rc != SQLITE_DONE) && (rc != SQLITE_ROW))
		{
			sqlite3_close_v2(db);
			return 3.0;
		}
		sqlite3_reset(stmt);
	}

	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMessage);		
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	time(&time_1);

	return (double)(time_1 - time_0);
}

double insertSimulation(std::list<Simulador::_simulacion>& sim)
{
	time_t time_0, time_1;
	time(&time_0);
	int rc;
	char* errorMessage;
	sqlite3 *db = openDb();
	std::string qry ="DELETE FROM Simulacion";
	rc = sqlite3_exec(db, qry.c_str(), NULL, NULL, &errorMessage);
	rc = sqlite3_exec(db, "VACUUM", NULL, NULL, &errorMessage);
	
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMessage);
	
	sqlite3_stmt *stmt;
	int filas = sim.size();
	qry = "INSERT INTO Simulacion (factor, num_simulacion, tiempo, valor) VALUES (?, ?, ?, ?)";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		return 2.5;
	}
	//for (int i = 0; i < filas; i++)
	for (std::list<Simulador::_simulacion>::iterator it = sim.begin(); it != sim.end(); it++)
	{
		
		//std::string input1 = it -> factor;
		//int input2 = it -> numSimulacion;
		double input3 = floor(it -> tiempo * 100000000.0 + .5) / 100000000.0;
		//double input4 = it -> valor;

		rc = sqlite3_bind_text(stmt, 1, it->factor.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_bind_int(stmt, 2, it->numSimulacion);
		rc = sqlite3_bind_double(stmt, 3, input3);
		rc = sqlite3_bind_double(stmt, 4, it->valor);

		rc = sqlite3_step(stmt);
		if ((rc != SQLITE_DONE) && (rc != SQLITE_ROW))
		{
			sqlite3_close_v2(db);
			return 3.0;
		}
		sqlite3_reset(stmt);
	}
	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMessage);		
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	time(&time_1);

	return (double)(time_1 - time_0);
}


double startSimulation(CellMatrix queFactores, double horizonte, unsigned long iteraciones)
{
	time_t time_0, time_1;
	time(&time_0);
	pair <string, string> factor;
	vector<pair <string, string>> factores;
	map<string, FxRate> mapFx;
	map<string, Curva> mapCurva;
	map<string, double> mapSigma;
	map<string, double> mapGamma;
	map<string, Rho> mapRho;
	int filas = queFactores.RowsInStructure();
	for (int i = 0; i < filas; i++)
	{
		if (queFactores(i, 2).StringValue() == "Si")
		{
			factor = std::make_pair(queFactores(i, 0).StringValue(), queFactores(i, 1).StringValue());
			factores.push_back(factor);
		}
	}

	Simulador* simulator = new Simulador(horizonte, iteraciones, factores);

	for (unsigned int i = 0; i < factores.size(); i++)
	{
		if (factores[i].second == "FX")
		{
			FxRate* mFx = getFX(factores[i].first);
			mapFx[factores[i].first] = *mFx;
			delete mFx;
			mapSigma[factores[i].first] = getSigma(factores[i].first);
		}
		else if (factores[i].second == "IR")
		{
			Curva* mCurva = new Curva;
			getCurvaFromNombre(factores[i].first, mCurva);
			mapCurva[factores[i].first] = *mCurva;
			delete mCurva;
			mapSigma[factores[i].first] = getSigma(factores[i].first);
			mapGamma[factores[i].first] = getGamma(factores[i].first);
		}
	}

	//Si tengo en el vector de factores 1: USDCLP 2: EURUSD
	//Busca primero USDCLP$EURUSD
	//Si no busca EURUSD$USDCLP. Y en este caso le asigna el nombre USDCLP$EURUSD

	mapRho = getRho(factores);

	simulator->fx(mapFx);
	simulator->curva(mapCurva);
	simulator->sigma(mapSigma);
	simulator->gamma(mapGamma);
	simulator->rho(mapRho);
	simulator->setModels();
	simulator->getSeed(time(0));
	simulator->Cholesky();

	//Inicializar semilla
	if (cont==0)
	{	
		srand(semilla);
		cont++;
	}

	//Liberar Memoria
	mapFx.clear();
	mapCurva.clear();
	mapSigma.clear();
	mapGamma.clear();
	mapRho.clear();

	
	//Notar que ahora runSimulacion() ya no es void si no que devuelve un vector
	//de structs Simulador::_simulacion. Esta struct tiene la misma estructura que 
	//una fila de la tabla de la BBDD donde se guarda la simulacion.
	//Recordar que la tabla es (factor, num_simulacion, tiempo, valor)
	size_t auxTam = (unsigned int) (iteraciones * (horizonte * 264 + 1) * factores.size());
	factores.clear();
	//vector<Simulador::_simulacion> vec_sim;//(iteraciones);
	std::list<Simulador::_simulacion> vec_sim;
	try 
	{
		// vector throws a bad alloc if resized
		//vec_sim.resize(auxTam);
	}
	catch (const std::bad_alloc& bad) 
	{
		std::cerr << "Bad allocation: " << bad.what() << '\n';
		if (simulator != 0)
			delete simulator;
		throw("Problema, bad allocation ");
	}

	simulator->runSimulacion(vec_sim);


	//Este método es el que inserta los datos en la BBDD.
	//El doble que retorna es el tiempo que se demora en hacer la inserción.
	//double tt = insertSimulation(sim);
	double tt = insertSimulation(vec_sim);
	vec_sim.clear();
	vec_sim.swap(std::list <Simulador::_simulacion> (vec_sim));

	if (simulator != 0)
		delete simulator;
	//vec_sim.swap(auxSim);
	//vec_sim.clear();
	//vec_sim.erase( remove( vec_sim.begin(), vec_sim.end(), 0), vec_sim.end() );
	//vector<Simulador::_simulacion> (sim).;


	time(&time_1);
	return difftime(time_1, time_0);
}

MyMatrix getSimulaciones(string factor, int cuantasSim, double horizonte)
{
	//Este método retorna las primeras int cuantasSim simulaciones del factor 
	//string factor a un horizonte de tiempo igual a double horizonte.
	//Es una matriz de tres columnas con la estructura (num_simulacion, tiempo, valor)
	MyMatrix result(1, 1);
	result.resize((size_t)( cuantasSim * ceil(horizonte / DT) + 1 ), 3);
	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	
	std::string qry = "SELECT num_simulacion, tiempo, valor FROM Simulacion WHERE factor = ? AND num_simulacion <= ? AND tiempo <= ? ORDER BY num_simulacion, tiempo";

	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		throw("Hubo un problema al preparar la consulta (sqlite3_prepare_v2)");
	}
	
	rc = sqlite3_bind_text(stmt, 1, factor.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_int(stmt, 2, cuantasSim - 1);
	rc = sqlite3_bind_double(stmt, 3, horizonte);

	int i;
	i = 0;
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		double temp = 3.14;
		result(i, 0) = sqlite3_column_int(stmt, 0);
		temp = result(i, 0);
		result(i, 1) = sqlite3_column_double(stmt, 1);
		temp = result(i, 1);
		result(i, 2) = sqlite3_column_double(stmt, 2);
		temp = result(i, 2);
		i++;
		std::cout << i;
		if (i >= cuantasSim * ceil(horizonte / DT))
		{
			std::cin.get();
		}
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	return result;
}

double getCustomAmortForDealnumberAndLeg(string dealNumber, string leg, vector<double>& cAmort)
{
	//Va a buscar el calendario de customAmort a la base dado el número de operación y la pata (“b” o “s”).
	int rc;
	sqlite3 *db = openDb();

	sqlite3_stmt *stmt;
	std::string qry = "SELECT amort_percent FROM CustomAmortization WHERE deal_number = ? AND leg = ?";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	rc = sqlite3_bind_text(stmt, 1, dealNumber.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_bind_text(stmt, 2, leg.c_str(), -1, SQLITE_STATIC);

	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		return 2.5;
	}

	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		cAmort.push_back(sqlite3_column_double(stmt, 0));
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	return 0.0;
}


double getSwapFromOperation(const Operation & op, pair<Leg, Leg>& swapLegs)
{
	if (op._dealNumber != "")
	{
		swapLegs.first.tipoPata = op._tipoTasa.first;
		swapLegs.first.setNotionalAmount(op._amount.first, op._currency.first);
		swapLegs.first.setCalendars(op._startTime.first, op._expiryTime.first, op._periodicity.first, op._stubPeriod.first, op._fixingPeriodicity.first, op._fixingStubPeriod.first);
		swapLegs.first.setInterest(op._formaTasa.first, op._valueRate.first, op._spread.first);
		swapLegs.first.setPricingParameters(op._projectCurve.first, op._discountCurve.first, op._includeAmort.first);
		if( op._amort.first == "CUSTOM")
		{
			vector<double> cAmort;
			double x = getCustomAmortForDealnumberAndLeg(op._dealNumber, "b", cAmort);
			swapLegs.first.setCalendarAmortize(cAmort);			
		}
		else
		{
			swapLegs.first.setCalendarAmortize(op._amort.first);
		}
		swapLegs.second.tipoPata = op._tipoTasa.second;
		swapLegs.second.setNotionalAmount(op._amount.second, op._currency.second);
		swapLegs.second.setCalendars(op._startTime.second, op._expiryTime.second, op._periodicity.second, op._stubPeriod.second, op._fixingPeriodicity.second, op._fixingStubPeriod.second);
		swapLegs.second.setInterest(op._formaTasa.second, op._valueRate.second, op._spread.second);
		swapLegs.second.setPricingParameters(op._projectCurve.second, op._discountCurve.second, op._includeAmort.second);
		if( op._amort.second == "CUSTOM")
		{
			vector<double> cAmort;
			double x = getCustomAmortForDealnumberAndLeg(op._dealNumber, "s", cAmort);
			swapLegs.second.setCalendarAmortize(cAmort);			
		}
		else
		{
			swapLegs.second.setCalendarAmortize(op._amort.second);
		}
		return 0;
	}
	else
		return 1;
	
}

double startValorizacion(CellMatrix nettingSets, MyArray stopTimes)
{
	clock_t clock_0, clock_1, clock_ini, clock_fin, clock_3, clock_4;
	clock_ini = clock();
	cleanValorizacion();
	cleanColateral();	
	int filas = nettingSets.RowsInStructure();
	int operaciones;
	const int auxj = getMaxSim() + 1;
	//vector<double> collateralStopTimes(stopTimes.size());
	sort(stopTimes.begin(), stopTimes.end());	//Just in case.
    clock_1 = clock();
	Valorizador* miValorizador = Valorizador::getInstance();
	for (unsigned int k = 0; k < stopTimes.size(); k++)
	{
		map<string, double> sim;
		//Buscamos para un stopTime todas las simulaciones
		double x = getSimulationAtT((int)stopTimes[k], sim);
		clock_0 = clock();
		//cout << (int)stopTimes[k] <<" "<< diffclock(clock_0, clock_1) <<"\n";
		for (int i = 0; i < filas; i++)
		{
			if (nettingSets(i, 1).StringValue() == "Si")
			{
				//Buscamos el netting set en BBDD. Obtenemos vector<Operation> ops
				//Ademas buscamos la periodicidad de reevaluacion del NS
				vector<Operation> ops;
				map<string, double> simCol;
				NettingSet netSet(nettingSets(i, 0).StringValue(), "CLP", 0, 0, 0, 0, 0);
				getThresholdInfoFromNettingSet(netSet);
				//int periodicity = netSet.getPeriodicity();
				//collateralStopTimes.at(j)=(stopTimes[j] - periodicity);//collateralStopTimes.push_back(stopTimes[j] - periodicity);
				//int collateralStopTime = (int)(stopTimes[k] - periodicity);
				int collateralStopTime = netSet.getMarginDate(stopTimes[k]);
				x = getSimulationAtT(collateralStopTime, simCol);
				double r = getNettingSet(nettingSets(i, 0).StringValue(), ops); //esto trae las ops del ns
				operaciones = ops.size();
				//Calculamos el valor de cada operación del ns en cada stopping time.
				//Además calculamos el valor de cada operacion
				//en cada stopping time obtenemos un vector de valores cuyo size depende del número
				//de simulaciones que esté registrado en la BBDD
				vector<ResultadoValorizacion> auxResultVal(ops.size());
				vector<ResultadoValorizacion> auxResultCol(ops.size());
				for (unsigned int j = 0; j < ops.size(); j++)
				{
					//vector<vector<double>> m2m;
					//vector<vector<double>> collateral;
					vector<double> m2m(auxj);
					vector<double> collateral(auxj);
					double result;
					if( ops[j]._type == "FWD")
					{
						clock_3 = clock();
						result = miValorizador->valorOperacionScenario(ops[j], stopTimes[k], sim, m2m, netSet.getThresholdCurrency());
						result = miValorizador->valorOperacionScenario(ops[j], collateralStopTime, simCol, collateral, netSet.getThresholdCurrency());
						//result = insertValorizacion(netSet.getName(), ops[j]._dealNumber, m2m);
						//result = insertColateral(ops[j]._dealNumber, collateral, netSet);
						ResultadoValorizacion temp(netSet.getName(), ops[j]._dealNumber, (int)stopTimes[k], m2m);
						m2m.clear();
						m2m.swap(m2m);
						auxResultVal.at(j) = temp;
						temp._mtm = collateral;
						collateral.clear();
					    collateral.swap(collateral);
						auxResultCol.at(j) = temp;
						clock_4 = clock();
						//cout <<"EndOp "<< diffclock(clock_4, clock_3) <<"\n";
					}
					else if( ops[j]._type == "SWAP")
					{
						clock_3 = clock();
						pair<Leg, Leg> swapLegs;
						double x = getSwapFromOperation(ops[j], swapLegs);
						result = miValorizador->valorSwapScenario(swapLegs, stopTimes[k], sim, m2m, netSet.getThresholdCurrency());	
						result = miValorizador->valorSwapScenario(swapLegs, collateralStopTime, simCol, collateral, netSet.getThresholdCurrency());	
						ResultadoValorizacion temp(netSet.getName(), ops[j]._dealNumber, (int)stopTimes[k], m2m);
						m2m.clear();
						m2m.swap(m2m);
						auxResultVal.at(j) = temp;
						temp._mtm = collateral;
						collateral.clear();
					    collateral.swap(collateral);
						auxResultCol.at(j) = temp;
						clock_4 = clock();
						//cout <<"EndOp "<< diffclock(clock_4, clock_3) <<"\n";
						
					}
				}

				ops.clear();
				simCol.clear();
				tablas type = tblValorizacion;
				double xx = insertValorizacion(auxResultVal, type);
				auxResultVal.clear();
				auxResultVal.swap(auxResultVal);
				type = tblColateral;
				xx = insertValorizacion(auxResultCol, type);
				auxResultCol.clear();
				auxResultCol.swap(auxResultCol);
			}
		}
		sim.clear();
		clock_1 = clock();
		cout <<(int)stopTimes[k] <<" End "<< diffclock(clock_1, clock_0)<<" ms \n";
	}
	if (miValorizador!= 0)
	{
			delete miValorizador;
	}
	//collateralStopTimes.clear();
	clock_fin = clock();
	return diffclock(clock_fin, clock_ini);
}

double getNettingSetObjectFromName(string name, NettingSet& nettingSet)
{
	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
    //threshold_curr, threshold_ns, threshold_inst, last_date, initial_margin, periodicity, collateral_adjustment, mta
	std::string qry = "SELECT threshold_curr, threshold_ns, threshold_inst, periodicity, collateral_adjustment, mta, last_date, initial_margin FROM NettingSet WHERE nombre = ?";
	  
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	rc = sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
 
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		throw("Error al preparar el statement");
	}
 
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		nettingSet.setName(name);
		const char* temp = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		string result(temp);
		nettingSet.setThresholdCurrency(result);
		nettingSet.setThresholdCounterparty(sqlite3_column_double(stmt, 1));
		nettingSet.setThresholdInstitution(sqlite3_column_double(stmt, 2));
		nettingSet.setPeriodicity(sqlite3_column_int(stmt, 3));
		nettingSet.setCollateralAdjustment(sqlite3_column_double(stmt, 4));
		nettingSet.setMTA(sqlite3_column_double(stmt, 5));
		nettingSet.setLastMarginDate(sqlite3_column_int(stmt, 6));
		nettingSet.setInitialCollateral(sqlite3_column_double(stmt, 7));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		sqlite3_shutdown();
		return 0.0;
	}
	// Agregado por SB: el 18/11 revisar si aplica
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	return 1.0;
}

double getCollateralForNettingSet(string ns, map<int, vector<double>>& collateral)
{
	//valor lo pasamos By Ref para evitarnos cualquier doble consumo y copias desde el método llamado
	//al método que llama. Para el netting set consultado, el mapa registra para cada (stopping time - menos
	//la periodicidad de revalorizacion del ns) el vector con los colaterales en todas las 
	//simulaciones de este netting set.

	int rc;
	char* errorMessage;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	string tempString;
	vector<int> st;
	vector<double> valores;
	NettingSet netSet; //ESTO ES NUEVO
	double x = getNettingSetObjectFromName(ns, netSet); //ESTO ES NUEVO
	rc = sqlite3_prepare_v2(db, "SELECT DISTINCT tiempo FROM Colateral", -1, &stmt, NULL);
	if (rc == SQLITE_OK)
	{
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			st.push_back(sqlite3_column_int(stmt, 0));
		}
	}
	sqlite3_finalize(stmt);

	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMessage);
	for (unsigned int i = 0; i < st.size(); i++)
	{
		//Este query trae todas los colaterales del netting set ns para un stopping time (menos la
		//periodicidad de valorizacion).
		string qry = "SELECT SUM(valor) FROM Colateral WHERE tiempo = ? AND netting_set = ? GROUP BY num_simulacion" ;
		rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
		if (rc != SQLITE_OK)
		{
			sqlite3_close_v2(db);
			const char* a = sqlite3_errmsg(db);
			return 1.0;
		}
  
		rc = sqlite3_bind_int(stmt, 1, st[i]);
		rc = sqlite3_bind_text(stmt, 2, ns.c_str(), -1, SQLITE_STATIC); 

		int marginDate =  netSet.getMarginDate(st[i]); // Agregado para poder incorporar una garantía inicial;

		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			valores.push_back(netSet.collateral(sqlite3_column_double(stmt, 0), marginDate)); //AQUI ADENTRO ES NUEVO
			//valores.push_back(netSet.collateralWithCSA(sqlite3_column_double(stmt, 0))); //NUEVO
			
		}
		collateral.insert(pair<int, vector<double>>(st[i], valores));
		valores.clear();
		sqlite3_reset(stmt);
	}

	st.clear();
	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMessage);  

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	return 0.0;
}

double getValorizacionForNettingSet(string ns, map<int, vector<double>>& valor)
{
	//valor lo pasamos By Ref para evitarnos cualquier doble consumo y copias desde el metodo llamado
	//al metodo que llama. Para el netting set consultado, el mapa registra para cada stopping time el vector
	//con las valorizaciones en todas las simulaciones de este netting set.

	int rc;
	char* errorMessage;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	string tempString;
	vector<int> st;
	vector<double> valores;
	rc = sqlite3_prepare_v2(db, "SELECT DISTINCT tiempo FROM Valorizacion", -1, &stmt, NULL);
	if (rc == SQLITE_OK)
	{
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			st.push_back(sqlite3_column_int(stmt, 0));
		}
	}
	sqlite3_finalize(stmt);

	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMessage);
	for (unsigned int i = 0; i < st.size(); i++)
	{
		//string qry = "SELECT valor FROM Valorizacion WHERE tiempo = ? AND netting_set = ?"; //Este query trae todas las valorizaciones del netting set ns para un stopping time
		string qry = "SELECT SUM(valor) FROM Valorizacion WHERE tiempo = ? AND netting_set = ? GROUP BY num_simulacion" ;
		rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
		if (rc != SQLITE_OK)
		{
			sqlite3_close_v2(db);
			const char* a = sqlite3_errmsg(db);
			return 1.0;
		}
		
		rc = sqlite3_bind_int(stmt, 1, st[i]);
		rc = sqlite3_bind_text(stmt, 2, ns.c_str(), -1, SQLITE_STATIC);	

		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			valores.push_back(sqlite3_column_double(stmt, 0));
		}
		valor.insert(pair<int, vector<double>>(st[i], valores));
		valores.clear();
		sqlite3_reset(stmt);
	}

	st.clear();
	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMessage);		

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	return 0.0;
}

double getExposureMetricsForNettingSet(string ns, map<int, vector<double>>& metrics)
{
	//Dado el nombre del ns y valor, completar el mapa con las métricas asociadas.
	//En el mapa vienen: stopTime y vector ={EE, NEE, ME, PFE, EFV}={0,1,2,3,4}

	int rc;
	char* errorMessage;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	string tempString;
	vector<int> st;
	vector<double> valores;
	rc = sqlite3_prepare_v2(db, "SELECT DISTINCT tiempo FROM Valorizacion", -1, &stmt, NULL);
	if (rc == SQLITE_OK)
	{
		 while (sqlite3_step(stmt) == SQLITE_ROW)
		{
		 st.push_back(sqlite3_column_int(stmt, 0));
		}
	}
	sqlite3_finalize(stmt);

	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMessage);
	for (unsigned int i = 0; i < st.size(); i++)
	{
		//string qry = "SELECT valor FROM Valorizacion WHERE tiempo = ? AND netting_set = ?"; //Este query trae todas las valorizaciones del netting set ns para un stopping time
		string qry = "SELECT expected_exposure, negative_expected_exposure, max_exposure, potential_future_exposure, expected_future_value FROM ExposureMetrics WHERE netting_set = ? AND stop_time = ?" ;
		rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
		if (rc != SQLITE_OK)
		{
			sqlite3_close_v2(db);
			const char* a = sqlite3_errmsg(db);
			return 1.0;
		}
  
		rc = sqlite3_bind_text(stmt, 1, ns.c_str(), -1, SQLITE_STATIC); 
		rc = sqlite3_bind_int(stmt, 2, st[i]);

		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
		valores.push_back(sqlite3_column_double(stmt, 0));
		valores.push_back(sqlite3_column_double(stmt, 1));
		valores.push_back(sqlite3_column_double(stmt, 2));
		valores.push_back(sqlite3_column_double(stmt, 3));
		valores.push_back(sqlite3_column_double(stmt, 4));
		}
		metrics.insert(pair<int, vector<double>>(st[i], valores));
		valores.clear();
		sqlite3_reset(stmt);
	}

	st.clear();
	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMessage);  

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	return 0.0;
}

double getPercentil(string ns)
{
	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	
	std::string qry = "SELECT valor FROM ValorPercentil";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		throw("Error al preparar el statement");
	}
	
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		double result = sqlite3_column_double(stmt, 0);
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		sqlite3_shutdown();
		return result;
	}
	
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	throw("Error al ejecutar la consulta");
}	


MyMatrix getValorizaciones(string nombreNS, int cuantasVal)
{
	//Este método retorna las primeras int cuantasVal valorizaciones del string nombreNS
	//Es una matriz de cuatro columnas con la estructura (num_simulacion, tiempo, MTM, colateral)
	MyMatrix result(1, 1);
	vector<int> st;
	double  x = getStoppingTimes(st); 
	int  cuantosTimes = st.size();
	result.resize(cuantasVal * cuantosTimes, 4);
	map<int, vector<double>> valor;
	map<int, vector<double>> colateral;
    x = getValorizacionForNettingSet(nombreNS, valor);
	x = getCollateralForNettingSet(nombreNS, colateral);
	for (int i = 0; i < cuantasVal; i++)
	{
		for (int j = 0; j < cuantosTimes; j++)
		{
			result(j + i * cuantosTimes, 0) = (double) i;
			result(j + i * cuantosTimes, 1) = st[j];
			result(j + i * cuantosTimes, 2) = valor[st[j]][i];
			result(j + i * cuantosTimes, 3) = colateral[st[j]][i];
		}
	}
	st.clear();
	valor.clear();
	colateral.clear();
    return result;
}

double startMetricasDeExposicion(vector<string> nettingSets)
{
	clock_t clock_ini, clock_fin;
	clock_ini = clock();
	// Esta función cálcula las métricas de exposición dado un vector de nettingSets
	int numNettingSets = nettingSets.size(); 
	// La clase ExposureMetrics se encarga de calcular todas las métricas de exposición.
	// Estas son : EE, NEE, ME, PFE, EFV.
	ExposureMetrics* exposures = new ExposureMetrics();
	// La struct Metrics contiene las métricas para un netting set.
	// El vector auxMetricas se guardará en la base de datos.
	vector<Metrics> auxMetricas; 
	for (int i = 0; i < numNettingSets; i++)
	{
		string nombreNS = nettingSets[i]; 
		map<int, vector<double>> valor;
		map<int, vector<double>> colateral;
        double x = getValorizacionForNettingSet(nombreNS, valor);
		x = getCollateralForNettingSet(nombreNS, colateral);
		double auxPer = getPercentil(nombreNS);
		exposures->setNumeroSimulaciones(valor.begin()->second.size());	
		for (map<int, vector<double>>::iterator it = valor.begin(); it != valor.end(); ++it)
		{
			int stopTime = it->first;
			//exposures->setValor(it->second);
			//exposures->setColateral(colateral[stopTime]);
			exposures->setMtmAndColateral(it->second, colateral[stopTime]);
			exposures->calculateExposicion();
			exposures->claculateExposicionNegativa();
			double auxEE = exposures->getExposicionEsperada();
			double auxNEE = exposures->getExposicionNegativaEsperada();
			double auxME = exposures->getExposicionMaxima();
			double auxPFE = exposures->getExposicionPotencialFutura(auxPer);
			double auxEFV = exposures->getValorFuturoEsperado();
			Metrics tempMetricas(nombreNS, stopTime,auxEE, auxNEE, auxME, auxPFE, auxEFV);
			// Se guarda tempMetricas en el vector de métricas.
			auxMetricas.push_back(tempMetricas);
		}
		valor.clear();
		colateral.clear();	}
	if (exposures != 0)
		delete exposures;	

    //Insertar vector auxMetricas en BBDD.
	double x = insertMetrics(auxMetricas);
	if (x != 0)
	{
		auxMetricas.clear();
		vector<Metrics>().swap(auxMetricas);
		return 1.0;
	}
	
	//Eliminar vector de metricas.
    auxMetricas.clear();
	vector<Metrics>().swap(auxMetricas);

	clock_fin = clock();

	return diffclock(clock_fin, clock_ini);
}

double getCurvaFromMonedaBase(Curva* curvaBase)
{
	// Dado curvaBase extraer desde la BBDD la curva de descuento que corresponde a la moneda base.
	// Implementar el código correcto.
	string nombre;
	if (getMonedaBase() == "CLP")
	{
		nombre = "CLP_CAM";
	}
	else if (getMonedaBase() == "USD")
	{
		nombre = "USD_LIB_3M";
	}	
	return getCurvaFromNombre(nombre, curvaBase);
}

string getMonedaThresholdForNettingSet(string ns)
{
	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;
	
	std::string qry = "SELECT threshold_curr FROM NettingSet WHERE nombre = ?";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	rc = sqlite3_bind_text(stmt, 1, ns.c_str(), -1, SQLITE_STATIC);
	
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		throw("Error al preparar el statement");
	}
	
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		const char* temp = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		string result(temp);
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		sqlite3_shutdown();
		return result;
	}
	
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	throw("Error al ejecutar la consulta.");	
}

double getCurvaFromMonedaThreshold(Curva* curvaBase, string moneda)
{
	//Para calcular los XVA hay que usar la curva de la moneda del threshold, no la curva de 
	//la moneda base.
	//Esta función te está dando la curva que corresponde en duro.
	//Despues le hacemos un arreglo adicional.
	string nombre;
	if (moneda == "CLP")
	{ 
		nombre = "ZEROCLP";//"CLPSWPCCLC";//
	}
	else if (moneda == "USD")
	{
		nombre = "ZEROUSD";//"USDSWAPCLC";//
	}	
	return getCurvaFromNombre(nombre, curvaBase);
}


double getLGDFromNettinSet(string ns, pair<double, double>& valueLGD)
{
	// Dado el nombre del ns y  valueLGD completar el par valueLGD, donde:
	// first = Institución y Second = Contraparte.
	valueLGD.first = 1 - getInstitutionRecoveryRate();
	valueLGD.second = 1 - getRecoveryRateFromNettingSet(ns);
	return  0.0;
}

double getProbDeDefaultFromNettinSet(string ns, map<int, pair<double, double>>& probDefault)
{
	// Dado el nombre del ns y probDefault, completar el mapa con las probabilidades asociadas.
	// En el mapa vienen: stopTime y pares de probabilidad, donde: first = Institución, Second = Contraparte.
	// Al stop time ti corresponde la probabilidad PD(ti-1,ti).	
	double dpInst = getInstitutionDefaultProbability();
	double dpNS = getDefaultProbabilityFromNettingSet(ns);
	vector<int> st;
	double  x = getStoppingTimes(st); 
	for (unsigned int i = 0; i < st.size(); i++)
	{
		double aux;
		if (i == 0)
		{
			aux = 0.0;
		}
		else
		{
			aux = (double)st[i-1];
		}
		aux = (double)(st[i]-aux)*DT;
		double dpInstPlazo = 1 - pow(1 - dpInst, aux);
		double dpNSPlazo = 1 - pow(1 - dpNS, aux);

		//Lógica del cálculo: Por ejemplo a = pow(1 - dpNS, aux) es la probabilidad de supervivencia en un intervalo de tiempo
		//igual a la distincia entre dos stop times consecutivos. La distancia la mide aux. Por lo tanto, 1 - a es la probabilidad de 
		//default en este mismo intervalo.

		probDefault.insert(pair<int, pair<double, double>>(st[i], pair<double, double>(dpInstPlazo, dpNSPlazo))); 
	}

	/*
	for (vector<int>::iterator it = st.begin(); it != st.end(); ++it)
	{
		int stopTime = *it;
		double exponent = (double)stopTime/264.0;
		double dpInstPlazo = 1 - pow(1 - dpInst, exponent);
		double dpNSPlazo = 1 - pow(1 - dpNS, exponent); 
		probDefault.insert(pair<int, pair<double, double>>(stopTime, pair<double, double>(dpInstPlazo, dpNSPlazo))); 
	}*/
	st.clear();
	return 0.0;
}

double getSpreadsFromNettingSets(map<int, pair<double, double>>& spread)
{
  // Dado ns y spread, el mapa se debe completar conforforme a: stopTime y pares de spread, donde: first = cap, Second = col.
 
	int rc;
	sqlite3 *db = openDb();
 
	double spreadCap = 0.0;
	double spreadCol = 0.0;

	sqlite3_stmt *stmt;
	std::string qry = "SELECT spread_cap, spread_col FROM Institution";
	//string tempString(ns.getName());
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);

	if (rc != SQLITE_OK)
	{
	sqlite3_close_v2(db);
	return 2.5;
	}
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
	spreadCap = sqlite3_column_double(stmt, 0);
	spreadCol = sqlite3_column_double(stmt, 1);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	vector<int> st;
	double  x = getStoppingTimes(st);
	double auxTime = 0.0;
    for (unsigned int i = 0; i < st.size(); i++)
    {
	auxTime = ((double)st[i] - auxTime)*DT;
	spread.insert(pair<int, pair<double, double>>(st[i], pair<double, double>(spreadCap * auxTime, spreadCol * auxTime)));
	auxTime = (double)st[i];
	}

	return 0.0;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	throw("Error al ejecutar la consulta"); 
}


double startCreditValueAdjustment(vector<string> nettingSets)
{
	clock_t clock_fin, clock_ini, clock_1, clock_2;
	clock_ini = clock();
	// Dado un vector de nettingSets esta función cálcula: Unilateral CVA, CVA, DVA, BilateralCVA, FVA  Ademas de: PFEMaxima y EPE.
	int numNettingSets = nettingSets.size(); 
	pair<double, double> valueLGD;//first = Institución, Second = Contraparte
	Curva* curvaBase = new Curva();
	// La struct Risk contiene los cálculos de exposición para un netting set.
	// El vector auxRisk se debe guardar en la base de datos.
	vector<Risk> auxRisk(numNettingSets);
	map<int, pair<double, double>> spread; //first = Cap, Second = Col
	double z = getSpreadsFromNettingSets(spread);
	for (int i = 0; i < numNettingSets; i++)
	{
		string nombreNS = nettingSets[i];
		map<int, vector<double>> metricas; 
		map<int, pair<double, double>> probDefault;//first = Institución, Second = Contraparte
		double v = getProbDeDefaultFromNettinSet(nombreNS, probDefault);
		double w  = getLGDFromNettinSet(nombreNS, valueLGD);		
		double x =  getCurvaFromMonedaThreshold(curvaBase, getMonedaThresholdForNettingSet(nombreNS));	
        double y = getExposureMetricsForNettingSet(nombreNS, metricas);
		// La clase CreditExposure realiza todos los cálculos 
		CreditExposure* results = new CreditExposure(metricas, probDefault, valueLGD, curvaBase);
		metricas.clear();
		probDefault.clear();
		double unilateralCVA = results->getUnilateralCVA();
		double valueCVA = results->getCVA();
		double valueDVA = results->getDVA();
		double bilateralCVA = results->getBilateralCVA();
		double valueFVA = results->getFVA(spread);
		double valuePFEMax = results->getPFEMaxima();
		double valueEPE = results->getExposicionPossitivaEsperada();
		double unilateralDVA = results->getUnilateralDVA();
		Risk tempRisk(nombreNS, unilateralCVA, valueCVA,  valueDVA, bilateralCVA, valueFVA, valuePFEMax, valueEPE, unilateralDVA);
		// Se guarda tempRisk en el vector de riesgos.
		auxRisk.at(i) = tempRisk;
		delete results;
	}
	
	delete curvaBase;
	spread.clear();
	
	clock_2 = clock();
	//cout <<"StarInserttXva "<< diffclock(clock_2, clock_ini) <<"\n";	
	//Insertar vector auxMetricas en base de datos;
	double x = insertXVA(auxRisk);
	clock_1 = clock();
	//cout <<"EndInsertXva"<< diffclock(clock_1, clock_2) <<"\n";
	auxRisk.clear();

	//Eliminar vector de metricas.	
    vector<Risk>().swap(auxRisk);
    clock_fin = clock();
	return diffclock(clock_fin, clock_ini);
}


double startMetricas(CellMatrix nettingSets)
{
	int numNettingSets = nettingSets.RowsInStructure();
	vector<string> auxNettingSets;
	for (int i = 0; i < numNettingSets; i++)
	{
		if (nettingSets(i, 1).StringValue() == "Si")
		{
			auxNettingSets.push_back(nettingSets(i, 0).StringValue());
		}
	}
	//double x1 = getNettingSetsValorizados(auxNettingSets);
	double x2 = startMetricasDeExposicion(auxNettingSets);
	return x2;
}

double startExposicionCrediticia(CellMatrix nettingSets)
{
	int numNettingSets = nettingSets.RowsInStructure();
	vector<string> auxNettingSets;
	for (int i = 0; i < numNettingSets; i++)
	{
		if (nettingSets(i, 1).StringValue() == "Si")
		{
			auxNettingSets.push_back(nettingSets(i, 0).StringValue());
		}
	}
	//double x1 = getNettingSetsForCVA(auxNettingSets);
	double x2 = startCreditValueAdjustment(auxNettingSets);
	
    return x2;
}

double getDiscountFactorFromCurva(string nombreCurva , double t)
{
	Curva* curva = new Curva();
	double x = getCurvaFromNombre(nombreCurva, curva);
	double r = getInterpolationRate(curva, t);
	delete curva;
	double discFactor = exp(-r*t);

	return discFactor;

}


MyMatrix getMetricas(string nombreNS)
{
	//Este método retorna las métricas EE, NEE, ME, PFE, EFV={0,1,2,3,4} para cada stopTime
	MyMatrix result(1, 1);
	map<int, vector<double>> metricas;
	double x = getExposureMetricsForNettingSet(nombreNS, metricas);
	int  cuantosTimes = metricas.size();
	result.resize(cuantosTimes, 6);
	int j = 0;
	for (map<int, vector<double>>::iterator it = metricas.begin(); it != metricas.end(); ++it)
	{
			result(j, 0) = it->first;
			result(j, 1) = it->second[0];
			result(j, 2) = it->second[1];
			result(j, 3) = it->second[2];
			result(j, 4) = it->second[3];
			result(j, 5) = it->second[4];
			j++;
	}
	metricas.clear();
    return result;

}

double getXvaForNettingSet(Risk& risk)
{
	int rc;
	sqlite3 *db = openDb();

	sqlite3_stmt *stmt;
	std::string qry = "SELECT unilateral_cva, value_cva, unilateral_dva, value_dva, bilateral_cva, value_fva, value_pfe_max, value_epe FROM Xva WHERE netting_set = ?";
	string tempString(risk.nettingSet);
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	rc = sqlite3_bind_text(stmt, 1, tempString.c_str(), -1, SQLITE_STATIC);

	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		return 2.5;
	}
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		 risk.unilateralCVA = sqlite3_column_double(stmt, 0);
		 risk.valueCVA = sqlite3_column_double(stmt, 1);
		 risk.unilateralDVA= sqlite3_column_double(stmt, 2);
		 risk.valueDVA = sqlite3_column_double(stmt, 3);
		 risk.bilateralCVA = sqlite3_column_double(stmt, 4);
		 risk.valueFVA = sqlite3_column_double(stmt, 5);
		 risk.pFEMax = sqlite3_column_double(stmt, 6);
		 risk.expPosExp = sqlite3_column_double(stmt, 7);
		 //risk.bilateralCVA = sqlite3_column_int(stmt, 3);
		 //risk.valueFVA = sqlite3_column_int(stmt, 4);
		 //risk.pFEMax = sqlite3_column_int(stmt, 5);
		 //risk.expPosExp = sqlite3_column_int(stmt, 6);

		sqlite3_finalize(stmt);
		sqlite3_close(db);
		sqlite3_shutdown();
		return 0.0;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	sqlite3_shutdown();
	return 2.0;
}


MyMatrix getCreditExposureResults(string nombreNS)
{
	//Este método retorna los resultados de: Unilateral CVA, CVA, Unilateral DVA,DVA, BilateralCVA, FVA  Ademas de: PFEMaxima y EPE.
	MyMatrix result(1, 8);//result es una matriz de ceros.
	//Risk* risk = new Risk();
	Risk risk;
	risk.nettingSet = nombreNS;
	if (nombreNS != "")
	{
		int x =	(int)getXvaForNettingSet(risk);
		if( x == 0)
		{
			result(0, 0) = risk.unilateralCVA;
			result(0, 1) = risk.valueCVA;
			result(0, 2) = risk.unilateralDVA;
			result(0, 3) = risk.valueDVA;
			result(0, 4) = risk.bilateralCVA;
			result(0, 5) = risk.valueFVA;
			result(0, 6) = risk.pFEMax;
			result(0, 7) = risk.expPosExp;
		}
	}
	return result;
}


double legSwaps(string nombreNS, MyArray stopTimes)
{
	assert(nombreNS != "");
	vector<Operation> ops;
	getNettingSet(nombreNS, ops);
	
	for( unsigned int i = 0; i < ops.size(); i ++)
	{
		if (ops[i]._type == "SWAP")
		{
			//pair<Leg, Leg> storeLegs;(ops[i]._tipoTasa.first, ops[i]._tipoTasa.second);
			Leg myLeg = Leg();
			myLeg.tipoPata = ops[i]._tipoTasa.first;
			myLeg.setNotionalAmount(ops[i]._amount.first, ops[i]._currency.first);
			myLeg.setCalendars(ops[i]._startTime.first, ops[i]._expiryTime.first, ops[i]._periodicity.first, ops[i]._stubPeriod.first, ops[i]._fixingPeriodicity.first, ops[i]._fixingStubPeriod.first);
			myLeg.setCalendarAmortize(ops[i]._amort.first);
			myLeg.setInterest(ops[i]._formaTasa.first, ops[i]._valueRate.first, ops[i]._spread.first);
			myLeg.setPricingParameters(ops[i]._projectCurve.first, ops[i]._discountCurve.first, ops[i]._includeAmort.first);
			myLeg.initiateCalendars();
			for (unsigned int j = 0; j < stopTimes.size(); j++)
			{
				myLeg.resetCalendars((int)stopTimes[j]);

				if(!myLeg.getCalendarCoupon().empty())
				{
					int auxCupon = myLeg.getCalendarCoupon()[0];
					double result = myLeg.getInterest(auxCupon, auxCupon, 0.0);
					result = myLeg.getAmortize(auxCupon);
				}
			}

			myLeg.initiateCalendars();
			/*for (int j = 0; j < stopTimes.size(); j++)
			{
				int aux = (int)stopTimes[j]-DM;
				myLeg.resetCalendars(aux);
			}*/
			
		}
	}
	ops.clear();
	ops.swap(vector<Operation> (ops));
	
	return 0.0;
  
}

double insertParamDeValorizacion(CellMatrix nettingSets, MyArray stopTimes)
{
	//Se guardan los nettingSets conforme a la siguiente estructura:
	//Netting Set: Nombre netting_set
	//Valorizar: Si/No conforme si valoriza o no

	//Los stopping times se guardan como pasos de simulación, (tipo long int)
	int rc;
	char* errorMessage;
	sqlite3 *db = openDb();
	rc = sqlite3_exec(db, "DELETE FROM ParamValorizacion", NULL, NULL, &errorMessage);
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMessage);
	sqlite3_stmt *stmt;
	int filas = nettingSets.RowsInStructure();
	string qry = "INSERT INTO ParamValorizacion (netting_set, se_valoriza) VALUES (?, ?)";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		return 2.5;
	}
	for (int i = 0; i < filas; i++)
	{
		string input1 = nettingSets(i, 0).StringValue();
		string input2 = nettingSets(i, 1).StringValue();

		rc = sqlite3_bind_text(stmt, 1, input1.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_bind_text(stmt, 2, input2.c_str(), -1, SQLITE_STATIC);

		rc = sqlite3_step(stmt);
		if ((rc != SQLITE_DONE) && (rc != SQLITE_ROW))
		{
			sqlite3_close_v2(db);
			return 3.0;
		}
		sqlite3_reset(stmt);
	}

	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMessage);		
	sqlite3_finalize(stmt);

	rc = sqlite3_exec(db, "DELETE FROM StopTimesParaValorizacion", NULL, NULL, &errorMessage);
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMessage);
	filas = stopTimes.size();
	qry = "INSERT INTO StopTimesParaValorizacion (stopping_time) VALUES (?)";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		return 2.5;
	}
	for (int i = 0; i < filas; i++)
	{
		double input1 = stopTimes.at(i);

		rc = sqlite3_bind_double(stmt, 1, input1);

		rc = sqlite3_step(stmt);
		if ((rc != SQLITE_DONE) && (rc != SQLITE_ROW))
		{
			sqlite3_close_v2(db);
			return 3.0;
		}
		sqlite3_reset(stmt);
	}

	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMessage);		
	sqlite3_finalize(stmt);

	sqlite3_close(db);
	sqlite3_shutdown();

	return 0.0;
}


double getNettingSetsAndStopTimes(vector<string>& nettingSets, vector<double>& stopTimes)
{
	int rc;
	sqlite3 *db = openDb();
	sqlite3_stmt *stmt;

	string qry = "SELECT netting_set FROM ParamValorizacion WHERE se_valoriza = \'Si\'";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);

	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		return 1.0;
	}
	//string txtValor;
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		//tempString.assign((const char*)sqlite3_column_text(stmt, 1));
		//txtValor.assign((const char*)sqlite3_column_text(stmt, 1));
		const char* temp = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		//std::string txtValor(temp);
		nettingSets.push_back(temp);
	}

	sqlite3_finalize(stmt);

	qry = "SELECT stopping_time FROM StopTimesParaValorizacion";
	rc = sqlite3_prepare_v2(db, qry.c_str(), -1, &stmt, NULL);

	if (rc != SQLITE_OK)
	{
		sqlite3_close_v2(db);
		const char* a = sqlite3_errmsg(db);
		return 1.0;
	}
	
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		int txtValor = sqlite3_column_int(stmt, 0);
		stopTimes.push_back(txtValor);
	}

	sqlite3_finalize(stmt);

	sqlite3_close(db);
	sqlite3_shutdown();
	return 0.0;
}



double startValorizacionExe()
{
	vector<string> auxNettingSets;
	vector<double> stopTimes;
	double x = getNettingSetsAndStopTimes(auxNettingSets, stopTimes);
	CellMatrix nettingSets(auxNettingSets.size(),2);

	for (unsigned int i = 0; i < auxNettingSets.size(); i++)
	{
		nettingSets(i, 0) = auxNettingSets[i].c_str();
		nettingSets(i, 1) = "Si";
	}

	x = startValorizacion(nettingSets, stopTimes);
	return x;
	
}

double getValueSwapFromDealNumber(CellMatrix  dealNumber)
{
	//nettingSets(i, 1).StringValue()
	string dn(dealNumber(0,0).StringValue());
	Operation op;
	double x = getOperationFromDealNumber(dn, & op);
	pair<Leg, Leg> swapLegs;
	x = getSwapFromOperation(op,swapLegs);
	Valorizador* miValorizador = Valorizador::getInstance();
	double result = miValorizador->valorSwap(swapLegs);

	if (miValorizador!= 0)
	{
		delete miValorizador;
	}
	return result;

}
