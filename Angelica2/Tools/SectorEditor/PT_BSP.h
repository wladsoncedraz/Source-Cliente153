/*
 * FILE: PT_BSP.h
 *
 * DESCRIPTION: BSP for sectors routines
 *
 * CREATED BY: Duyuxin, 2003/8/12
 *
 * HISTORY:
 *
 * Copyright (c) 2001 Archosaur Studio, All Rights Reserved.	
 */

#ifndef	_PT_BSP_H_
#define _PT_BSP_H_

#include "PT_Internal.h"

/////////////////////////////////////////////////////////////////////////
//
//	Constants and Macros
//
/////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////
//
//	Types and Global variables
//
/////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////
//
//	Global functions
//
/////////////////////////////////////////////////////////////////////////

namespace PORTAL
{
	bool ProcessBSP();
	void ReleaseBSPNodes(s_PTBSPNODE* pNode);
}

/////////////////////////////////////////////////////////////////////////
//
//	Inline functions
//
/////////////////////////////////////////////////////////////////////////


#endif	//	_PT_BSP_H_

