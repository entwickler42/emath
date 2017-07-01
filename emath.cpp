/*
 *  emath.c
 *  iemc
 *
 *  Created by Stefan Brueck on 2/13/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "emath.h"

#ifdef WIN32
#include <stdio.h>
#endif

// Base constants
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_4PI
#define M_4PI 12.5663706144
#endif

#define MU0 0.0000012566370614359172953850573533118 //! Magnetic Field Constant = 4 * PI * 10E-7
#define EFS_Z0 376.7304 //! Freiwellenwiderstand

// 
#define MIN(X,Y)  ( (X) < (Y) ? (X) : (Y) )
#define MAX(X,Y)  ( (X) > (Y) ? (X) : (Y) )
#define LAMBDA(X) ( 300000000.0 / MAX(0.01, (double)X) )

static bool debug_mode = false;

// generic convert function; internal use only! 
int p_emconv(double src, int unit_src, double* dest, int unit_dest, double impedanz, double db, uint64_t hz)
{
	size_t i;
	
	if( unit_src == unit_dest ){
		*dest = src;
		return EM_OK;
	}
	
	for (i=0; i<EM_TABLE_CONV_SIZE; i++){
		const struct em_conv* conv = EM_TABLE_CONV + i;
		// forward towards desired Convertion		
		if( conv->unit_src != unit_src || conv->unit_dst != unit_dest )
			continue;
		// call related convert method with the proper number of arguments
		switch(conv->argc)
		{
		case 2:
			if( conv->convert2 == NULL ) // convert2 not defined
				return EM_ERR_ARGC2NULL;
			conv->convert2(src, dest);
			return EM_OK;
		case 3:
			if( conv->convert3 == NULL ) // convert3 not defined
				return EM_ERR_ARGC3NULL;
			conv->convert3(src, dest, impedanz);
			return EM_OK;
		case 4:
			if( conv->convert4 == NULL ) // convert4 not defined
				return EM_ERR_ARGC4NULL;
			conv->convert4(src, dest, db, hz);
			return EM_OK;	
		default:
			// invalid number or arguments
			return EM_ERR_UNKNOWNARGC;
		}
	}	
	return EM_ERR_UNKNOWNCONV;
}

int emconv(double src, int unit_src, double* dest, int unit_dest, double impedanz, double db, uint64_t hz)
{
	int r = p_emconv(src, unit_src, dest, unit_dest, impedanz, db, hz);
	if( r != EM_OK && debug_mode ){
		qDebug("%s: ERROR %i: %i => %i", Q_FUNC_INFO, r, unit_src, unit_dest);
	}
	return r;
}

int emconv6(double src, int unit_src, double* dest, int unit_dest, double db, uint64_t hz)
{
	int r = p_emconv(src, unit_src, dest, unit_dest, 0.0, db, hz);
	if( r != EM_OK && debug_mode ){
		qDebug("%s: ERROR %i: %i => %i", Q_FUNC_INFO, r, unit_src, unit_dest);
	}
	return r;
}

int emconv5(double src, int unit_src, double* dest, int unit_dest, double impedanz)
{
	int r = p_emconv(src, unit_src, dest, unit_dest, impedanz, 0.0, 0);
	if( r != EM_OK && debug_mode ){
		qDebug("%s: ERROR %i: %i => %i", Q_FUNC_INFO, r, unit_src, unit_dest);
	}
	return r;
}

int emconv4(double src, int unit_src, double* dest, int unit_dest)
{	
	int r = p_emconv(src, unit_src, dest, unit_dest, 0.0, 0.0, 0);
	if( r != EM_OK && debug_mode ){
		qDebug("%s: ERROR %i: %i => %i", Q_FUNC_INFO, r, unit_src, unit_dest);
	}
	return r;
}

void emconv_watt2dbm(double watt, double* dbm)
{
	*dbm = dtodb10(watt) + 30.0;
}

void emconv_dbm2watt(double dbm, double* watt)
{
	*watt = db10tod(dbm - 30.0);
}

void emconv_dbm2wm2(double dbm, double* wm2, double db, uint64_t hz)
{
	*wm2 = M_4PI / pow(LAMBDA(hz), 2.0) * db10tod(dbm - 30.0 - db);
}

void emconv_dbm2wcm2(double dbm, double* wcm2, double db, uint64_t hz)
{
	emconv_dbm2wm2(dbm, wcm2, db, hz);
	*wcm2 /= 10000.0;
}

void emconv_wm22dbm(double wm2, double* dbm, double db, uint64_t hz)
{
	*dbm = dtodb10(wm2 / (M_4PI / pow(LAMBDA(hz), 2.0))) + 30.0 + db;
}

void emconv_wcm22dbm(double wcm2, double* dbm, double db, uint64_t hz)
{
	emconv_wm22dbm(wcm2 * 10000.0, dbm, db, hz);
}

void emconv_wm22vm(double wm2, double* vm)
{
	*vm = sqrt(EFS_Z0 * wm2); 
}

void emconv_dbm2volt(double dbm, double* volt, double impedanz)
{
	// U = sqrt(P * R)
	*volt = sqrt(db10tod(dbm - 30.0) * impedanz);
}

void emconv_volt2dbm(double volt, double *dbm, double impedanz)
{
	// P = U^2 / R
	*dbm = dtodb10(pow(volt, 2.0) / impedanz) + 30.0;
}

void emconv_dbm2vm(double dbm, double* vm, double db, uint64_t hz)
{
	double wm2;
	emconv_dbm2wm2(dbm, &wm2, db, hz);	
	emconv_wm22vm(wm2, vm);
}

void emconv_dbm2am(double dbm, double* am, double db, uint64_t hz)
{
	double wm2;
	emconv_dbm2wm2(dbm, &wm2, db, hz);
	emconv_wm22am(wm2, am);
}

void emconv_wm22am(double wm2, double* am)
{
	*am = sqrt(wm2 / EFS_Z0);
}

void emconv_dbm2dbv(double dbm, double* dbv, double impedanz)
{
	*dbv = dtodb20(sqrt(db10tod(dbm-30.0) * impedanz));
}

void emconv_dbm2dbuv(double dbm, double* dbuv, double impedanz)
{
	emconv_dbm2dbv(dbm, dbuv, impedanz);
	*dbuv += 120.0;
}

void emconv_dbm2dbvm(double dbm, double* dbvm, double db, uint64_t hz)
{
	double vm;
	emconv_dbm2vm(dbm, &vm, db, hz);
	*dbvm = dtodb20(vm);
}

void emconv_dbm2dbuvm(double dbm, double* dbuvm, double db, uint64_t hz)
{
	emconv_dbm2dbvm(dbm, dbuvm, db, hz);
	*dbuvm += 120.0;
}

void emconv_dtodb20(double d, double* db20)
{
	*db20 = dtodb20(d);
}

void emconv_db20tod(double db20, double* d)
{
	*d = db20tod(db20);
}

void emconv_watt2am(double p, double* am)
{
	*am = sqrt(p / EFS_Z0);
}

void emconv_watt2vm(double p, double* vm)
{
	*vm = sqrt(p / EFS_Z0) * EFS_Z0;
}

void emconv_watt2wm2(double p, double* wm2)
{
	*wm2 = p;
}

void emconv_watt2wcm2(double p, double* wcm2)
{
	*wcm2 = p / 10000.0;
}

void emconv_tesla2gauss(double tesla, double* gauss)
{
	*gauss = tesla * 10000.0;
}

void emconv_gauss2tesla(double gauss, double* tesla)
{
	*tesla =  gauss * 0.0001;
}

void emconv_tesla2am(double tesla, double* am)
{
	*am = tesla / MU0;	
}

void emconv_tesla2dbut(double tesla, double* dbut)
{
	*dbut = dtodb20(tesla) + 120.0;
}

void emconv_vm2dbm(double vm, double* dbm, double db, uint64_t hz)
{
	double wm2 = pow(vm, 2.0) / EFS_Z0;
	emconv_wm22dbm(wm2, dbm, db, hz);
}

void emconv_dbvm2dbm(double dbvm, double* dbm, double db, uint64_t hz)
{
	emconv_vm2dbm( db20tod(dbvm), dbm, db, hz);
}

void emconv_dbuvm2dbm(double dbuvm, double* dbm, double db, uint64_t hz)
{
	emconv_vm2dbm( db20tod(dbuvm - 120.0), dbm, db, hz);
}

void emconv_dbv2dbm(double dbv, double* dbm, double impedanz)
{
	*dbm = dtodb10(pow(db20tod(dbv), 2.0) / impedanz) + 30.0;
}

void emconv_dbuv2dbm(double dbuv, double* dbm, double impedanz)
{
	*dbm = dtodb10(pow(db20tod(dbuv - 120.0), 2.0) / impedanz) + 30.0;
}

void emconv_vm2watt(double vm, double* watt, double db, uint64_t hz)
{
	emconv_vm2dbm(vm, watt, db, hz);
	*watt = db10tod(*watt - 30.0);
}

void emconv_vm2dbuvm(double vm, double* dbuv)
{
	emconv_dtodb20(vm, dbuv);
	*dbuv += 120.0;
}

void emconv_vm2am(double vm, double* am)
{
	*am = vm / EFS_Z0;
}

void emconv_vm2wm2(double vm, double* wm2)
{
	*wm2 = pow(vm, 2.0) / EFS_Z0;
}

void emconv_vm2wcm2(double vm, double* wcm2)
{
	*wcm2 = pow(vm, 2.0) / EFS_Z0 / 10000.0;
}

double lambda(uint64_t hz)
{
	return LAMBDA(hz);
}

const struct emu_entry* emu_find(int emu)
{
	unsigned int i;
	for(i=0; i<EMU_TABLE_UNITS_SIZE; i++)
		if( EMU_TABLE_UNITS[i].emu == emu )
			return EMU_TABLE_UNITS + i;
	return 0;
}

