/*
 * FILE: A3DSurface.h
 *
 * DESCRIPTION: A storage class for any system memory based surface
 *
 * CREATED BY: Hedi, 2001/12/4
 *
 * HISTORY:
 *
 * Copyright (c) 2001 Archosaur Studio, All Rights Reserved.	
 */

#ifndef _A3DSURFACE_H_
#define _A3DSURFACE_H_

#include "A3DPlatform.h"
#include "A3DTypes.h"
#include "A3DEngine.h"
#include "A3DDevice.h"
#include "A3DTexture.h"

class A3DSurface : public A3DObject
{
private:
	A3DDevice *				m_pA3DDevice;
	char					m_szSurfaceMap[MAX_PATH];
	bool					m_bHWISurface;

	IDirect3DSurface8 *		m_pDXSurface;

	A3DFORMAT				m_format;

	int						m_nWidth;
	int						m_nHeight;

public:
	A3DSurface();
	~A3DSurface();

	bool Init(A3DDevice * pA3DDevice, IDirect3DSurface8 * pDXSurface, const char * szMapFile);
	bool Release();

	bool Create(A3DDevice* pDevice, int iWidth, int iHeight, A3DFORMAT Format);
	bool LockRect(RECT* pRect, void** ppData, int* iPitch, DWORD dwFlags);
	bool UnlockRect();

	bool CopyRects(A3DSurface * pSrcSurface, const RECT * pSourceRectsArray, int nNumRects, const POINT * pDestPointsArray);
	bool SaveToFile(const char * szFileName);

	bool DrawToBack(int x, int y);

	inline int GetWidth() { return m_nWidth; }
	inline int GetHeight() { return m_nHeight; }
	inline A3DFORMAT GetFormat() { return m_format; } 

	inline IDirect3DSurface8 * GetDXSurface() { return m_pDXSurface; }
};

typedef A3DSurface * PA3DSurface;
#endif