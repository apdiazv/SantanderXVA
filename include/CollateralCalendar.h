#pragma once

class CollateralCalendar
{
public:
	CollateralCalendar(void);
	CollatelalCalendar(int lastDate, int periodicity);
	int getMarginDate(int stopTime); //!Dado un tiempo t, entrega el tiempo en se calcula garantia

	~CollateralCalendar(void);
private:
    int _lastDate;
	int _nexDate;
	int _periodicity;
};
