/*
 *  emsi.h
 *  iemc
 *
 *  Created by Stefan Brueck on 2/13/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef EMSI_H
#define EMSI_H

#include "emath_global.h"
#include <wchar.h>


//! System Internation Unit
struct emsi_entry
{
	long double factor;     //! decimals of a derived unit
	wchar_t     suffix[8];  //! short unit name that is used to suffix numbers
	wchar_t     name[32];   //! full unit name
	int         use;        //! set 0 to disable a derived unit
};

//! System International Unit and Derivates
static const struct emsi_entry EMSI_TABLE_UNIT[] =
{
	{ 1000000000000000000000000.0L, L"Y",       L"yotta", 1 },
	{ 1000000000000000000000.0L,    L"Z",       L"zetta", 1 },
	{ 1000000000000000000.0L,       L"E",       L"exa",   1 },
	{ 1000000000000000.0L,          L"P",       L"peta",  1 },
	{ 1000000000000.0L,             L"T",       L"tera",  1 },
	{ 1000000000.0L,                L"G",       L"giga",  1 },
	{ 1000000.0L,                   L"M",       L"mega",  1 },
	{ 1000.0L,                      L"k",       L"kilo",  1 },
	{ 100.0L,                       L"h",       L"hecto", 0 },
	{ 10.0L,                        L"da",      L"deca",  0 },
	{ 1.0L,                         L"",        L"",      1 },
	{ 0.1L,                         L"d",       L"deci",  0 },
	{ 0.01L,                        L"c",       L"centi", 0 },
	{ 0.001L,                       L"m",       L"milli", 1 },
	{ 0.000001L,                    L"\x03BC",  L"micro", 1 },
	{ 0.000000001L,                 L"n",       L"nano",  1 },
	{ 0.000000000001L,              L"p",       L"pico",  1 },
	{ 0.000000000000001L,           L"f",       L"femto", 1 },
	{ 0.000000000000000001L,        L"a",       L"atto",  1 },
	{ 0.000000000000000000001L,     L"z",       L"zepto", 1 },
	{ 0.000000000000000000000001L,  L"y",       L"yocto", 1 }
};

#define EMSI_TABLE_UNIT_SIZE (sizeof(EMSI_TABLE_UNIT)/ sizeof(struct emsi_entry))


//! find SI scaling where scaling divided by value is greater than level
EMATHSHARED_EXPORT
		const struct emsi_entry* emsi_find_scale(double value, double level);

//! find 1:1 scaling
EMATHSHARED_EXPORT
	const struct emsi_entry* emsi_find_11();

#endif
