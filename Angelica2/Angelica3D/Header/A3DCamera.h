/*
 * FILE: A3DCamera.h
 *
 * DESCRIPTION: Class representing a camera
 *
 * CREATED BY: Hedi, 2001/12/3
 *
 * HISTORY:
 *
 * Copyright (c) 2001 Archosaur Studio, All Rights Reserved.	
 */

#ifndef _A3DCAMERA_H_
#define _A3DCAMERA_H_

#include "A3DCameraBase.h"

class A3DCamera	: public A3DCameraBase
{
public:		//	Types

public:		//	Constructor and Destructor

	A3DCamera();
	virtual ~A3DCamera() {}

public:		//	Attributes

public:		//	Operations

	//	Initlaize object
	bool Init(A3DDevice* pA3DDevice, FLOAT vFov=DEG2RAD(65.0f), FLOAT vFront=1.0f, FLOAT vBack=2000.0f, FLOAT vRatio=1.3333333f);
	//	Release object
	virtual void Release();

	//	Apply camera to device
	virtual bool Active();
	//	Update function is called in Active()
	bool Update();

	//	Set / Get FOV
	void SetFOV(FLOAT vFOV) { m_vFOV = vFOV; UpdateProjectTM(); }
	FLOAT GetFOV() const { return m_vFOV; }
	void SetFOVSet(FLOAT vFOVSet) { m_vFOVSet = vFOVSet; }
	float GetRatio() const { return m_vRatio; }

	//	Set / Get projection parameters
	bool SetProjectionParam(FLOAT fFOV, FLOAT fFront, FLOAT fBack, FLOAT fRatio);
	void GetProjectionParam(FLOAT* pvFOV, FLOAT* pvFront, FLOAT* pvBack, FLOAT* pvRatio)
	{ 
		*pvFOV	 = m_vFOV;
		*pvFront = m_vFront; 
		*pvBack	 = m_vBack; 
		*pvRatio = m_vRatio;
	}

protected:	//	Attributes

	FLOAT	m_vFOV;
	FLOAT	m_vFOVSet;
	FLOAT	m_vRatio;

protected:	//	Operations

	//	Update project TM
	virtual bool UpdateProjectTM();
	//	Create view frustum
	virtual bool CreateViewFrustum();
	//	Update world frustum
	virtual bool UpdateWorldFrustum();
};


#endif
