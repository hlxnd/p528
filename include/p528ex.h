#pragma once

#ifdef P528_EXPORTS
#define DLLEXPORT extern "C" __declspec(dllexport)
#else
#define DLLEXPORT extern "C" __declspec(dllimport)
#endif

//
// DATA STRUCTURES
///////////////////////////////////////////////

struct Path
{
    // Distances
    double d_ML__km;            // Maximum line of sight distance
    double d_0__km;             // Internal param.  See Recommendation text
    double d_d__km;             // Distance where smooth earth diffraction is 0 dB
};

struct Terminal
{
    // Heights
    double h_r__km;             // Real terminal height
    double h_e__km;             // Effective terminal height
    double delta_h__km;         // Internal terminal param.  See Recommendation text

    // Distances
    double d_r__km;             // Ray traced horizon distance
    double a__km;               // Total ray path length to horizon

    // Angles
    double phi__rad;            // Central angle between the terminal and its smooth earth horizon
    double theta__rad;          // Incident angle of the grazing ray at the terminal

    // Losses
    double A_a__db;             // Median atmospheric absorption loss, in dB
};

struct LineOfSightParams
{
    // Heights
    double z__km[2];

    // Distances
    double d__km;               // Path distance between terminals
    double r_0__km;             // Direct ray length
    double r_12__km;            // Indirect ray length
    double D__km[2];

    // Angles
    double theta_h1__rad;       // Take-off angle from low terminal to high terminal, in rad
    double theta_h2__rad;       // Take-off angle from high terminal to low terminal, in rad
    double theta[2];

    // Misc
    double a_a__km;             // Adjusted earth radius
    double delta_r__km;         // Ray length path difference
    double A_LOS__db;           // Loss due to LOS path
};

struct TroposcatterParams
{
    // Distances
    double d_s__km;             // Scattering distance 
    double d_z__km;             // Half the scattering distance

    // Heights
    double h_v__km;             // Height of the common volume cross-over point

    // Angles
    double theta_s;             // Scattering angle
    double theta_A;             // cross-over angle

    // Losses
    double A_s__db;             // Troposcattter Loss
    double A_s_prev__db;        // Troposcatter Loss of Previous Test Point

    // Misc
    double M_s;                 // Troposcatter Line Slope
};

struct Result {
    int propagation_mode;       // Mode of propagation
    int warnings;               // Warning messages

    double d__km;               // Path distance used in calculations
    double A__db;               // Total loss
    double A_fs__db;            // Free space path loss
    double A_a__db;             // Atmospheric absorption loss, in dB

    double theta_h1__rad;	    // Elevation angle of the ray at the low terminal, in rad
};

// Public Functions
DLLEXPORT int __stdcall P528(double d__km, double h_1__meter, double h_2__meter, double f__mhz,
    int T_pol, double p, Result* result);
DLLEXPORT int __stdcall P528_Ex(double d__km, double h_1__meter, double h_2__meter, double f__mhz,
    int T_pol, double p, Result* result, Terminal* terminal_1, Terminal* terminal_2,
    TroposcatterParams* tropo, Path* path, LineOfSightParams* los_params);
DLLEXPORT double __stdcall FindKForYpiAt99Percent(double Y_pi_99__db);
DLLEXPORT double __stdcall NakagamiRice(double K, double q);