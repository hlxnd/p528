#include <vector>
#include <algorithm>

#include "p528ex.h"

using namespace std;


#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define PI                                  3.1415926535897932384
#define a_0__km                             6371.0
#define a_e__km                             9257.0
#define N_s                                 341
#define epsilon_r                           15.0
#define sigma                               0.005
#define LOS_EPSILON                         0.00001
#define THIRD                               1.0 / 3.0

// Consts
#define CONST_MODE__SEARCH                  0
#define CONST_MODE__DIFFRACTION             1
#define CONST_MODE__SCATTERING              2

#define CASE_1                              1
#define CASE_2                              2

#define PROP_MODE__NOT_SET                  0
#define PROP_MODE__LOS                      1
#define PROP_MODE__DIFFRACTION              2
#define PROP_MODE__SCATTERING               3

// List of valid polarizations
#define POLARIZATION__HORIZONTAL            0
#define POLARIZATION__VERTICAL              1

#define Y_pi_99_INDEX                       16

//
// RETURN CODES
///////////////////////////////////////////////

#define	SUCCESS                             0
#define ERROR_VALIDATION__D_KM              1
#define ERROR_VALIDATION__H_1               2
#define ERROR_VALIDATION__H_2               3
#define ERROR_VALIDATION__TERM_GEO          4
#define ERROR_VALIDATION__F_MHZ_LOW         5
#define ERROR_VALIDATION__F_MHZ_HIGH        6
#define ERROR_VALIDATION__PERCENT_LOW       7
#define ERROR_VALIDATION__PERCENT_HIGH      8
#define ERROR_VALIDATION__POLARIZATION      9
#define ERROR_HEIGHT_AND_DISTANCE           10
#define SUCCESS_WITH_WARNINGS               11

//
// WARNINGS
///////////////////////////////////////////////

#define WARNING__NO_WARNINGS                0x00
#define WARNING__DFRAC_TROPO_REGION         0x01
#define WARNING__HEIGHT_LIMIT_H_1           0x02
#define WARNING__HEIGHT_LIMIT_H_2           0x04

//
// CLASSES
///////////////////////////////////////////////

class data
{
public:
    const static vector<double> P;          // Percentages for interpolation and data tables

    const static vector<vector<double>> NakagamiRiceCurves;
    const static vector<int> K;
};

//
// FUNCTIONS
///////////////////////////////////////////////

// Private Functions
void GetPathLoss(double psi, Path *path, double f__mhz, double psi_limit, 
    double A_dML__db, double A_d_0__db, int T_pol, LineOfSightParams* params, double *R_Tg);
void RayOptics(Terminal *terminal_1, Terminal *terminal_2, double psi, LineOfSightParams *result);
void TerminalGeometry(double f__mhz, Terminal *terminal);
void Troposcatter(Path *path, Terminal *terminal_1, Terminal *terminal_2, 
    double d__km, double f__mhz, TroposcatterParams *tropo_params);
void TranshorizonSearch(Path* path, Terminal *terminal_1, Terminal *terminal_2, 
    double f__mhz, double A_dML__db, double *M_d, double *A_d0, 
    double* d_crx__km, int* MODE, int* warnings);
double LinearInterpolation(double x1, double y1, double x2, double y2, double x);
void ReflectionCoefficients(double psi, double f__mhz, int T_pol, double* R_g, double* phi_g);
void LineOfSight(Path* path, Terminal* terminal_1, Terminal* terminal_2, LineOfSightParams* los_params, double f__mhz, double A_dML__db,
    double p, double d__km, int T_pol, Result *result, double *K_LOS);
double SmoothEarthDiffraction(double d_1__km, double d_2__km, double f__mhz, double d_0__km, int T_pol);
double InverseComplementaryCumulativeDistributionFunction(double q);
void LongTermVariability(double d_r1__km, double d_r2__km, double d__km, double f__mhz, double time_percentage, 
    double f_theta_h, double PL, double *Y_e__db, double *A_Y);
double CombineDistributions(double A_M, double A_i, double B_M, double B_i, double p);
int ValidateInputs(double d__km, double h_1__meter, double h_2__meter, double f__mhz, 
    int T_pol, double p, int* warnings);


