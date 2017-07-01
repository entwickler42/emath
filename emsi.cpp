/*
 *  emsi.c
 *  iemc
 *
 *  Created by Stefan Brueck on 2/13/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "emsi.h"


const struct emsi_entry* emsi_find_scale(double value, double level)
{	
	size_t i;
	
	for( i=0; i<EMSI_TABLE_UNIT_SIZE; i++ ){
		if( EMSI_TABLE_UNIT[i].use == 1 && value / EMSI_TABLE_UNIT[i].factor >= level ){
			return &EMSI_TABLE_UNIT[i];
		}
	}
	return 0;
}

const struct emsi_entry* emsi_find_11()
{ 
	return emsi_find_scale(1.0, 1.0); 
}
