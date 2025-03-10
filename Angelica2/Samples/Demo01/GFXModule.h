/*
 * FILE: GFXModule.h
 *
 * DESCRIPTION: 
 *
 * CREATED BY: Duyuxin, 2009/5/25
 *
 * HISTORY: 
 *
 * Copyright (c) 2009 Archosaur Studio, All Rights Reserved.
 */

#ifndef _GFXMODULE_H_
#define _GFXMODULE_H_

#include <AList2.h>
#include <A3DVector.h>

///////////////////////////////////////////////////////////////////////////
//	
//	Define and Macro
//	
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//	
//	Types and Global variables
//	
///////////////////////////////////////////////////////////////////////////

class A3DGFXExMan;
class A3DGFXEx;
class A3DViewport;

///////////////////////////////////////////////////////////////////////////
//	
//	Declare of Global functions
//	
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//	
//	Class CGFXModule
//	
///////////////////////////////////////////////////////////////////////////

class CGFXModule
{
public:		//	Types

public:		//	Constructor and Destructor

	CGFXModule();
	virtual ~CGFXModule();

public:		//	Attributes

public:		//	Operations

	//	Initialize game
	bool Init();
	//	Release game
	void Release();

	//	Tick routine
	bool Tick(DWORD dwDeltaTime);
	//	Render routine
	bool Render(A3DViewport* pViewport);

	//	Play a GFX
	bool PlayGFX(const char* szFile, const A3DVECTOR3& vPos, const A3DVECTOR3& vDir, const A3DVECTOR3& vUp, float fScale=0.0f);

	//	Get interface
	A3DGFXExMan* GetA3DGFXExMan() { return m_pA3DGFXExMan; }

protected:	//	Attributes

	A3DGFXExMan*	m_pA3DGFXExMan;		//	GFX object manager

	APtrList<A3DGFXEx*>		m_GFXList;	//	GFX list

protected:	//	Operations

};

///////////////////////////////////////////////////////////////////////////
//	
//	Inline functions
//	
///////////////////////////////////////////////////////////////////////////

#endif	//	_GFXMODULE_H_
