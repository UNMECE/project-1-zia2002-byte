#include <iostream>
#include <iomanip>

struct _capacitor
{
 	double *time;
	double *voltage;
 	double *current;
	double C;
};

typedef struct _capacitor Capacitor;

int main()
{

	const double timestep = 1e-10;
	const double stoptime = 5e-6;
	const double resistance = 1000.0;
	const double capacitance = 100e-12;
	const double srccurrent = 1e-2;
	const double srcvoltage = 10.0;    

	int nsteps = static_cast<int>(stoptime / timestep);

	Capacitor constcurrent;
	Capacitor constvoltage;

	constcurrent.C = capacitance;
	constvoltage.C = capacitance;

	int arraysize = nsteps + 1;

// constant current
	constcurrent.time = new double[arraysize];
	constcurrent.voltage = new double[arraysize];
	constcurrent.current = new double[arraysize];

// constant voltage
	constvoltage.time = new double[arraysize];
	constvoltage.voltage = new double[arraysize];
	constvoltage.current = new double[arraysize];

	for (int i = 0; i < arraysize; i++)
{
		constcurrent.time[i] = i * timestep;
		constvoltage.time[i] = i * timestep;
}

// constant current case
	constcurrent.voltage[0] = 0.0;
	constcurrent.current[0] = srccurrent;

// constant voltage case
	constvoltage.voltage[0] = 0.0;
	constvoltage.current[0] = srcvoltage / resistance;

for (int i = 1; i < arraysize; i++)
{
    constcurrent.current[i] = constcurrent.current[i - 1];

    constcurrent.voltage[i] =
        constcurrent.voltage[i - 1] +
        constcurrent.current[i - 1] * timestep / constcurrent.C;
}
	return 0;

}
