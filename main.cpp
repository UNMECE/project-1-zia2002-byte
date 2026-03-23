#include <iostream>
#include <iomanip>


// Structure to store capacitor data over time
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
// Given constants from assignment
	const double timestep = 1e-10;
	const double stoptime = 5e-6;
	const double resistance = 1000.0;
	const double capacitance = 100e-12;
	const double srccurrent = 1e-2;
	const double srcvoltage = 10.0;    

// Total number of timesteps
	int nsteps = static_cast<int>(stoptime / timestep);

// Capacitor objects for both cases
	Capacitor constcurrent;
	Capacitor constvoltage;

	constcurrent.C = capacitance;
	constvoltage.C = capacitance;

// Including timestep 0
	int arraysize = nsteps + 1;

// constant current
	constcurrent.time = new double[arraysize];
	constcurrent.voltage = new double[arraysize];
	constcurrent.current = new double[arraysize];

// constant voltage
	constvoltage.time = new double[arraysize];
	constvoltage.voltage = new double[arraysize];
	constvoltage.current = new double[arraysize];

//filling time arrays
	for (int i = 0; i < arraysize; i++)
{
		constcurrent.time[i] = i * timestep;
		constvoltage.time[i] = i * timestep;
}

constcurrent.voltage[0] = 0.0;
constcurrent.current[0] = srccurrent;

constvoltage.voltage[0] = 0.0;
constvoltage.current[0] = srcvoltage / resistance;

for (int i = 1; i < arraysize; i++)
{
        constcurrent.current[i] = constcurrent.current[i - 1];

        constcurrent.voltage[i] =
        constcurrent.voltage[i - 1] +
        constcurrent.current[i - 1] * timestep / constcurrent.C;
}
	for (int i = 1; i < arraysize; i++)
{
		constvoltage.current[i] =
        	constvoltage.current[i - 1] -
        	(constvoltage.current[i - 1] / (resistance * constvoltage.C)) * timestep;

    		constvoltage.voltage[i] =
        	srcvoltage - constvoltage.current[i] * resistance;
}

//Setting up formatting for printing
	std::cout << std::scientific << std::setprecision(6);
	
//Printing every 200 steps
	std::cout << "Constant Current Source Results\n";
	
std::cout << "Step\tTime(s)\t\tVoltage(V)\tCurrent(A)\n";

for (int i = 0; i < arraysize; i += 200)
{
    std::cout << i << "\t"
              << constcurrent.time[i] << "\t"
              << constcurrent.voltage[i] << "\t"
              << constcurrent.current[i] << "\n";
}

	std::cout << "\nConstant Voltage Source Results\n";
std::cout << "Step\tTime(s)\t\tVoltage(V)\tCurrent(A)\n";

for (int i = 0; i < arraysize; i += 200)
{
    std::cout << i << "\t"
              << constvoltage.time[i] << "\t"
              << constvoltage.voltage[i] << "\t"
              << constvoltage.current[i] << "\n";
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

//Freeing up memory
delete[] constcurrent.time;
delete[] constcurrent.voltage;
delete[] constcurrent.current;

delete[] constvoltage.time;
delete[] constvoltage.voltage;
delete[] constvoltage.current;

	return 0;

}
