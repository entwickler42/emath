/*
 *  emath.h
 *  iemc
 *
 *  Created by Stefan Brueck on 2/13/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef EMATH_H
#define EMATH_H

#include "emath_global.h"

#include <math.h>
#include <wchar.h>

#ifdef WIN32
typedef signed __int64 int64_t;
typedef unsigned __int64 uint64_t; 
#else
#include <stdint.h>
#endif 

/* reminder only ... */
#define UTF8_MICRO    "\x03BC"
#define UTF8_SQUARE   "\x00B2"

// Error codes
#define EM_OK                0 //! All good
#define EM_ERR_UNKNOWNCONV  -1 //! Convertion for the given units is not defined
#define EM_ERR_ARGC2NULL    -2 //! Function convert2() is not defined
#define EM_ERR_ARGC3NULL    -3 //! Function convert3() is not defined
#define EM_ERR_ARGC4NULL    -4 //! Function convert4() is not defined
#define EM_ERR_UNKNOWNARGC  -5 //! Undefined number of arguments

// Base identifiers
#define EMF_NONE  0 //! Unspezific Field
#define EMF_E     1 //! Electric Field
#define EMF_MAGB  2 //! Magnetic Flux Density 
#define EMF_MAGH  4 //! Magnetic Power Density
#define EMF_POWER 8 //! Power
#define EMF_ALL   (EMF_E|EMF_MAGB|EMF_MAGH|EMF_POWER) //! Any defined EM Field

#define EM_NOTDB   0 //! no decibel
#define EM_DB10    1 //! current / voltage decibel
#define EM_DB20    2 //! power decibel

// Base Convertions
#define dtodb20(x) (20.0 * log10((double)x)) //! convert current / voltage to decibel  
#define dtodb10(x) (10.0 * log10((double)x)) //! convert power to decibel

#define db20tod(x) (pow(10.0, ((double)x) / 20.0)) //! convert decibel to current / voltage
#define db10tod(x) (pow(10.0, ((double)x) / 10.0)) //! convert decibel to power

#define tesla2gauss(x) ((double)x * 10000.0) //! convert Tesla to Gauss
#define gauss2tesla(x) ((double)x * 0.001) //! convert Gauss to Tesla

// Supported E/H/B Field / Power Units
#define EMU_DBM     0 //! db milliwatt
#define EMU_DBV     1 //! db Volt
#define EMU_DBVM    2 //! db Volt per Meter
#define EMU_DBT     3 //! dB Tesla 
#define EMU_WATT    4 //! Watt   (P)
#define EMU_VOLT    5 //! Volt   (U)
#define EMU_AMPERE  6 //! Ampere (I)
#define EMU_AM      7 //! Magnetic Power Density (H) in Ampere per Meter
#define EMU_VM      8 //! Electic Field in Volt per Meter
#define EMU_WM2     9 //! Heat Flux Density (E) in W/m^2
#define EMU_WCM2   10 //! Head Flux Density (E) in W/cm^2

#define EMU_DBUV   11
#define EMU_DBUVM  12
#define EMU_DBUT   13

#define EMU_TESLA  14 //! Magnetic Flux Density (B) in Tesla
#define EMU_GAUSS  15 //! Magnetic Flux Density (B) in Gauss
#define EMU_COUNT  16 //! Total number of supported units of measuremnt


// General purpose unit Convertion; return 0 on successfull Convertion
EMATHSHARED_EXPORT
int emconv(double src, int unit_src, double* dest, int unit_dest, double impedanz, double db, uint64_t hz);
EMATHSHARED_EXPORT 
int emconv6(double src, int unit_src, double* dest, int unit_dest, double db, uint64_t hz);
EMATHSHARED_EXPORT 
int emconv5(double src, int unit_src, double* dest, int unit_dest, double impedanz);
EMATHSHARED_EXPORT 
int emconv4(double src, int unit_src, double* dest, int unit_dest);

//! Convert Voltage and Current to dB
EMATHSHARED_EXPORT 
void emconv_dtodb20(double d, double* db20);
//! Convert dB to Voltage and Current
EMATHSHARED_EXPORT 
void emconv_db20tod(double db20, double* d);
//! Convert Watt to dBm (Power P)
EMATHSHARED_EXPORT 
void emconv_watt2dbm(double watt, double* dbm);
//! Convert dBm to Watt (Power P)
EMATHSHARED_EXPORT 
void emconv_dbm2watt(double dbm, double* watt);
//! Convert Volt to dBm (Power P)
EMATHSHARED_EXPORT 
void emconv_volt2dbm(double volt, double* dbm, double impedanz);
//! Convert dBm to Volt (Voltage U)
EMATHSHARED_EXPORT 
void emconv_dbm2volt(double dbm, double* volt, double impedanz);
//! Convert dBm to W/m^2 (Heat Flux Density E)
EMATHSHARED_EXPORT 
void emconv_dbm2wm2(double dbm, double* wm2, double db, uint64_t hz);
//! Convert dBm to W/cm^2 (Heat Flux Density E)
EMATHSHARED_EXPORT
void emconv_dbm2wcm2(double dbm, double* wcm2, double db, uint64_t hz);
//! Convert W/m^2 to dBm
EMATHSHARED_EXPORT
void emconv_wm22dbm(double wm2, double* dbm, double db, uint64_t hz);
//! Convert W/cm^2 to dBm
EMATHSHARED_EXPORT
void emconv_wcm22dbm(double wcm2, double* dbm, double db, uint64_t hz);
//! Convert W/m^2 to V/m (Electric Field Strength E) 
EMATHSHARED_EXPORT 
void emconv_wm22vm(double wm2, double* vm);
//! Convert dBm to V/m (Electric Field Strength E)
EMATHSHARED_EXPORT 
void emconv_dbm2vm(double dbm, double* vm, double db, uint64_t hz);
//! Convert W/m^2 to A/m (Magnetic Field H)
EMATHSHARED_EXPORT 
void emconv_wm22am(double wm2, double* am);
//! Convert dBm to A/m (Magnetic Field H)
EMATHSHARED_EXPORT 
void emconv_dbm2am(double dbm, double* am, double db, uint64_t hz);
//! Convert dBm to dBV (Voltage U)
EMATHSHARED_EXPORT 
void emconv_dbm2dbv(double dbm, double* dbv, double impedanz);
//! Convert dBm to dBuV (Voltage U)
EMATHSHARED_EXPORT
void emconv_dbm2dbuv(double dbm, double* dbuv, double impedanz);
//! Convert dBm to dBV/m (Electric Field Strength E)
EMATHSHARED_EXPORT 
void emconv_dbm2dbvm(double dbm, double* dbvm, double db, uint64_t hz);
//! Convert dBm to dBuV/m (Electric Field Strength E)
EMATHSHARED_EXPORT
void emconv_dbm2dbuvm(double dbm, double* dbuvm, double db, uint64_t hz);
//! Convert Power to A/m (Magnetic Field H)
EMATHSHARED_EXPORT 
void emconv_watt2am(double p, double* am);
//! Convert Power to V/m (Electric Field Strength E)
EMATHSHARED_EXPORT 
void emconv_watt2vm(double p, double* vm);
//! Convert Power to W/m^2 (Heat Flux Density E)
EMATHSHARED_EXPORT 
void emconv_watt2wm2(double p, double* wm2);
//! Convert Power to W/cm^2 (Heat Flux Density E)
EMATHSHARED_EXPORT 
void emconv_watt2wcm2(double p, double* wcm2);
//! Convert Tesla to Gauss (Magnetic Field B) (?)
EMATHSHARED_EXPORT 
void emconv_tesla2gauss(double tesla, double* gauss);
//! Convert Gauss to Tesla (Magnetic Field B)
EMATHSHARED_EXPORT 
void emconv_gauss2tesla(double gauss, double* tesla);
//! Convert Tesla to A/m (Magnetic Field H)
EMATHSHARED_EXPORT 
void emconv_tesla2am(double tesla, double* am);
//! Convert Tesla to dBuT
EMATHSHARED_EXPORT 
void emconv_tesla2dbut(double tesla, double* dbut);
//! Convert V/m to Watt
EMATHSHARED_EXPORT
void emconv_vm2watt(double vm, double* watt, double db, uint64_t hz);
//! Convert V/m to dBuV/m
EMATHSHARED_EXPORT
void emconv_vm2dbuvm(double vm, double* dbuv);
//! Convert V/m to A/m
EMATHSHARED_EXPORT
void emconv_vm2am(double vm, double* am);
//! Convert V/m to W/m^2
EMATHSHARED_EXPORT
void emconv_vm2wm2(double vm, double* wm2);
//! Convert V/m to W/cm^2
EMATHSHARED_EXPORT
void emconv_vm2wcm2(double vm, double* wcm2);

EMATHSHARED_EXPORT
void emconv_vm2dbm(double vm, double* dbm, double db, uint64_t hz);

EMATHSHARED_EXPORT
void emconv_dbvm2dbm(double dbvm, double* dbm, double db, uint64_t hz);

EMATHSHARED_EXPORT
void emconv_dbuvm2dbm(double dbuvm, double* dbm, double db, uint64_t hz);

EMATHSHARED_EXPORT
void emconv_dbv2dbm(double dbv, double* dbm, double impedanz);

EMATHSHARED_EXPORT
void emconv_dbuv2dbm(double dbuv, double* dbm, double impedanz);

//! calculate lambda for a given frequency
EMATHSHARED_EXPORT 
double lambda(uint64_t frequency);

//! return the emu_entry entry for a given uid; return NULL if the uid was not found
EMATHSHARED_EXPORT
const struct emu_entry* emu_find(int emu);


//! Structure a unit of measurement
struct emu_entry
{
	int emu;
	int quantity;
	int db_type;
	int precision;
	wchar_t suffix[32];
	wchar_t symbol[8];
};

//! Structure a unit of measurement Convertion
struct em_conv
{
	int unit_src;
	int unit_dst;
	int argc;
	void (*convert2)(double, double*);
	void (*convert3)(double, double*, double);
	void (*convert4)(double, double*, double, uint64_t);
};

//! Define the properties for all supported units of measurement
static const struct emu_entry EMU_TABLE_UNITS[] =
{
	{ EMU_DBM,    EMF_ALL,             EM_DB10,   2,   L"dBm",        L""  },
	{ EMU_DBV,    EMF_E,               EM_DB20,   2,   L"dBV",        L""  },
	{ EMU_DBUV,   EMF_E,               EM_DB20,   2,   L"dB\x03BCV",  L""  }, // X == FAKE
	{ EMU_DBVM,   EMF_E,               EM_DB20,   2,   L"dBVm",       L""  },
	{ EMU_DBUVM,  EMF_E,               EM_DB20,   2,   L"dB\x03BCVm", L""  }, // X
	{ EMU_DBT,    EMF_MAGB|EMF_MAGH,   EM_DB20,   2,   L"dBT",        L""  },
	{ EMU_DBUT,   EMF_MAGB|EMF_MAGH,   EM_DB20,   2,   L"dB\x03BCT",  L""  }, // X
	{ EMU_WATT,   EMF_POWER,           EM_NOTDB,  16,  L"W",          L"P" },
	{ EMU_VOLT,   EMF_E,               EM_NOTDB,  16,  L"V",          L"U" },
	{ EMU_AMPERE, EMF_POWER,           EM_NOTDB,  16,  L"A",          L""  },
	{ EMU_AM,     EMF_POWER|EMF_MAGB,  EM_NOTDB,  16,  L"A/m",        L""  },
	{ EMU_VM,     EMF_E,               EM_NOTDB,  16,  L"V/m",        L"E" },
	{ EMU_WM2,    EMF_POWER,           EM_NOTDB,  16,  L"W/m\x00B2",  L"H" },
	{ EMU_WCM2,   EMF_POWER,           EM_NOTDB,  16,  L"W/cm\x00B2", L"H" }, // X
	{ EMU_TESLA,  EMF_MAGB|EMF_MAGH,   EM_NOTDB,  16,  L"T",          L"B" },
	{ EMU_GAUSS,  EMF_MAGB|EMF_MAGH,   EM_NOTDB,  16,  L"G",          L"B" }
};
//! Number of elements in the unit properties table
#define EMU_TABLE_UNITS_SIZE (sizeof(EMU_TABLE_UNITS) / sizeof(struct emu_entry))

//! Define Convertion function for pairs of units ( count 2=IO, 3=IOR, 4=IODF )
static const struct em_conv EM_TABLE_CONV[] =
{
	{ EMU_DBM,    EMU_WATT,   2,  &emconv_dbm2watt,      NULL,              NULL },
	{ EMU_DBM,    EMU_WM2,    4,  NULL,                  NULL,              &emconv_dbm2wm2   },
	{ EMU_DBM,    EMU_WCM2,   4,  NULL,                  NULL,              &emconv_dbm2wcm2  },
	{ EMU_DBM,    EMU_AM,     4,  NULL,                  NULL,              &emconv_dbm2am    },
	{ EMU_DBM,    EMU_DBVM,   4,  NULL,                  NULL,              &emconv_dbm2dbvm  },
	{ EMU_DBM,    EMU_DBUVM,  4,  NULL,                  NULL,              &emconv_dbm2dbuvm },
	{ EMU_DBM,    EMU_VM,     4,  NULL,                  NULL,              &emconv_dbm2vm    },
	{ EMU_DBM,    EMU_VOLT,   3,  NULL,                  &emconv_dbm2volt,  NULL },
	{ EMU_DBM,    EMU_DBV,    3,  NULL,                  &emconv_dbm2dbv,   NULL },
	{ EMU_DBM,    EMU_DBUV,   3,  NULL,                  &emconv_dbm2dbuv,  NULL },
	{ EMU_WATT,   EMU_DBM,    2,  &emconv_watt2dbm,      NULL,              NULL },
	{ EMU_VOLT,   EMU_DBM,    3,  NULL,                  &emconv_volt2dbm,  NULL },
	{ EMU_DBUV,   EMU_DBM,    3,  NULL,                  &emconv_dbuv2dbm,  NULL,              },
	{ EMU_DBV,    EMU_DBM,    3,  NULL,                  &emconv_dbv2dbm,   NULL               },
	{ EMU_WM2,    EMU_DBM,    4,  NULL,                  NULL,              &emconv_wm22dbm   },
	{ EMU_WCM2,   EMU_DBM,    4,  NULL,                  NULL,              &emconv_wcm22dbm  },
	{ EMU_DBUVM,  EMU_DBM,    4,  NULL,                  NULL,              &emconv_dbuvm2dbm  },
	{ EMU_DBVM,   EMU_DBM,    4,  NULL,                  NULL,              &emconv_dbvm2dbm   },
	{ EMU_VM,     EMU_DBM,    4,  NULL,                  NULL,              &emconv_vm2dbm     },

	{ EMU_VM,     EMU_DBVM,   2,  &emconv_dtodb20,       NULL,              NULL },
	{ EMU_VM,     EMU_WATT,   4,  NULL,                  NULL,              &emconv_vm2watt },
	{ EMU_VM,     EMU_DBUVM,  2,  &emconv_vm2dbuvm,      NULL,              NULL },
	{ EMU_VM,     EMU_AM,     2,  &emconv_vm2am,         NULL,              NULL },
	{ EMU_VM,     EMU_WM2,    2,  &emconv_vm2wm2,        NULL,              NULL },
	{ EMU_VM,     EMU_WCM2,   2,  &emconv_vm2wcm2,       NULL,              NULL },

	{ EMU_WATT,   EMU_AM,     2,  &emconv_watt2am,       NULL,              NULL },
	{ EMU_WATT,   EMU_VM,     2,  &emconv_watt2vm,       NULL,              NULL },
	{ EMU_WATT,   EMU_WM2,    2,  &emconv_watt2wm2,      NULL,              NULL }, // wrong result!
	{ EMU_WATT,   EMU_WCM2,   2,  &emconv_watt2wcm2,     NULL,              NULL }, // wrong result!
	{ EMU_WM2,    EMU_VM,     2,  &emconv_wm22vm,        NULL,              NULL },
	{ EMU_WM2,    EMU_AM,     2,  &emconv_wm22am,        NULL,              NULL },
	{ EMU_VOLT,   EMU_DBV,    2,  &emconv_dtodb20,       NULL,              NULL },
	{ EMU_DBV,    EMU_VOLT,   2,  &emconv_db20tod,       NULL,              NULL },
	{ EMU_DBVM,   EMU_VM,     2,  &emconv_db20tod,       NULL,              NULL },
	{ EMU_DBT,    EMU_TESLA,  2,  &emconv_db20tod,       NULL,              NULL },
	{ EMU_TESLA,  EMU_AM,     2,  &emconv_tesla2am,      NULL,              NULL },
	{ EMU_TESLA,  EMU_GAUSS,  2,  &emconv_tesla2gauss,   NULL,              NULL },
	{ EMU_GAUSS,  EMU_TESLA,  2,  &emconv_gauss2tesla,   NULL,              NULL },
	{ EMU_TESLA,  EMU_DBT,    2,  &emconv_dtodb20,       NULL,              NULL },
	{ EMU_TESLA,  EMU_DBUT,   2,  &emconv_tesla2dbut,    NULL,              NULL }

};
//! Number of elements in the unit Convertion table
#define EM_TABLE_CONV_SIZE (sizeof(EM_TABLE_CONV) / sizeof(struct em_conv))

#endif
