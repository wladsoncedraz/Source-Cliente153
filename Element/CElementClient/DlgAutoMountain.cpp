/*
 * FILE: DlgAutoMountain.cpp
 *
 * DESCRIPTION: 
 *
 * CREATED BY: Liyi, 2005/12/2
 *
 * HISTORY: 
 *
 * Copyright (c) 2004 Archosaur Studio, All Rights Reserved.
 */
/*
#include "DlgAutoMountain.h"
#include "DlgAutoBaseMountain.h"
#include "EC_HomeDlgsMgr.h"
#include "DlgCurve.h"
#include "DlgAutoChooseTexture.h"
#include "DlgAutoAllRes.h"

#include "aui/AUILabel.h"
#include "aui/AUIManager.h"
#include "aui/AUIStillImageButton.h"

#include "AutoTerrainCommon.h"
#include "AutoTerrainAction.h"



#include "A3DEngine.h"
#include "A3DViewport.h"

#include "EC_Global.h"
#include "EC_Game.h"
#include "EC_GameRun.h"
#include "EC_World.h"
#include "AutoScene.h"
#include "AutoTerrain.h"
#include "CurvePoint.h"				// Added by jdl, 2006.03.03
#include "AutoHillPoly.h"			// Added by jdl, 2006.03.03
#include "AutoHillLine.h"			// Added by jdl, 2006.03.03
#include "AutoBuildingOperation.h"	// Added by jdl, 2006.03.03
#include "AutoBuildingOperation.h"
#include "AutoTerrainCommon.h"
#include "AutoSelectedArea.h"

#include "windowsx.h"

#include "A3DMacros.h"

#include "DlgAutoSliderBound.h"

AUI_BEGIN_COMMAND_MAP(CDlgAutoMountain, CDlgHomeBase)

AUI_ON_COMMAND("MoveSlider", OnCommandMoveSlider)

AUI_ON_COMMAND("CreateHillPoly", OnCommandCreateHillPoly)
AUI_ON_COMMAND("OpenHeightCurveDlg", OnCommandOpenHeightCurveDlg)

AUI_ON_COMMAND("TurnToBase", OnCommandTurnToBase)

AUI_ON_COMMAND("Save", OnCommandSave)
AUI_ON_COMMAND("SaveAs", OnCommandSaveAs)

AUI_END_COMMAND_MAP()


AUI_BEGIN_EVENT_MAP(CDlgAutoMountain, CDlgHomeBase)

AUI_END_EVENT_MAP()

CDlgAutoMountain::CDlgAutoMountain()
{
	m_pSliderTextureRatio = NULL;
	m_pSliderMainTexture = NULL;
	m_pSliderPatchTexture = NULL;
	m_pSliderPatchDivision = NULL;

	m_nTextureRatio = 0;
	m_nMainTexture = 0;
	m_nPatchTexture = 0;
	m_nPatchDivision = 0;

	m_fTextureRatio = 0.0f;
	m_fMainTexture = 0.0f;
	m_fPatchTexture = 0.0f;
	m_fPatchDivision = 0.0f;

	m_pLabelTextureRatio = NULL;
	m_pLabelMainTexture = NULL;
	m_pLabelPatchTexture = NULL;
	m_pLabelPatchDivision = NULL;

	
	m_pSliderMaxHeightHill = NULL;
	m_pSliderMainSmoothHill = NULL;
	m_pSliderPartSmoothHill = NULL;
	m_pSliderTerrainSeedHill = NULL;
	m_pSliderBridgeScope = NULL;
	m_pSliderBridgeDepth = NULL;
	m_pSliderBorderErode = NULL;
	

	m_pLabelMaxHeightHill = NULL;
	m_pLabelMainSmoothHill = NULL;
	m_pLabelPartSmoothHill = NULL;
	m_pLabelTerrainSeedHill = NULL;
	m_pLabelBridgeScope = NULL;
	m_pLabelBridgeDepth = NULL;
	m_pLabelBorderErode = NULL;
	m_pLabelLineHillWidth = NULL;

	m_nMaxHeightHill = 0;
	m_nMainSmoothHill = 0;
	m_nPartSmoothHill = 0;
	m_nTerrainSeedHill = 0;
	m_nBridgeScope = 0;
	m_nBridgeDepth = 0;
	m_nBorderErode = 0;

	m_fMainSmoothHill = 0.0f;
	m_fPartSmoothHill = 0.0f;	
	m_fBridgeScope = 0.0f;
	m_fBridgeDepth = 0.0f;
	m_fBorderErode = 0.0f;

	m_bCheckHillUp = true;

	m_pCurveHeight = new CCurvePoint;
	

	float fSpriteValues[10];
	fSpriteValues[0] = 1.0f;
	fSpriteValues[1] = 0.94f;
	fSpriteValues[2] = 0.8f;
	fSpriteValues[3] = 0.6f;
	fSpriteValues[4] = 0.40f;
	fSpriteValues[5] = 0.25f;
	fSpriteValues[6] = 0.20f;
	fSpriteValues[7] = 0.30f;
	fSpriteValues[8] = 0.40f;
	fSpriteValues[9] = 0.5f;

	m_pCurveHeight->SetPointValues(7, fSpriteValues);


	//memset(&m_texParamInfo, 0, sizeof(TextureParamInfo_t));


	for( int i = 0; i < BTN_NUM; i++)
	{
		m_pBtn[i] = NULL;
	}

	memset(m_szFileName, 0, MAX_PATH);

	m_pBtnCreate = NULL;
}

CDlgAutoMountain::~CDlgAutoMountain()
{
	if( m_pCurveHeight)
	{
		delete m_pCurveHeight;
		m_pCurveHeight = NULL;
	}

}

bool CDlgAutoMountain::OnInitContext()
{
	SetSliderBound();
	LoadDefault();
	UpdateData(false);
	SetLabelsText();

	return true;
}

void CDlgAutoMountain::OnShowDialog()
{
	CDlgHomeBase::OnShowDialog();

	SetCanMove(false);
}

#define GET_BTN_POINTER(a) DDX_Control( #a, m_pBtn[a]);
void CDlgAutoMountain::DoDataExchange(bool bSave)
{
	DDX_Control("Slider_TextureRatio", m_pSliderTextureRatio);
	DDX_Control("Slider_MainTexture", m_pSliderMainTexture);
	DDX_Control("Slider_PatchTexture", m_pSliderPatchTexture);
	DDX_Control("Slider_PatchDivision", m_pSliderPatchDivision);

	DDX_Control("Label_TextureRatio", m_pLabelTextureRatio);
	DDX_Control("Label_MainTexture", m_pLabelMainTexture);
	DDX_Control("Label_PatchTexture", m_pLabelPatchTexture);
	DDX_Control("Label_PatchDivision", m_pLabelPatchDivision);

	DDX_Slider(bSave, "Slider_TextureRatio", m_nTextureRatio);
	DDX_Slider(bSave, "Slider_MainTexture", m_nMainTexture);
	DDX_Slider(bSave, "Slider_PatchTexture", m_nPatchTexture);
	DDX_Slider(bSave, "Slider_PatchDivision", m_nPatchDivision);

	m_fTextureRatio = float((m_nTextureRatio - 100) * 0.01f);
	m_fMainTexture = float(m_nMainTexture * 0.01f);
	m_fPatchTexture = float(m_nPatchTexture * 0.01f);
	m_fPatchDivision = float(m_nPatchDivision);

	
	DDX_Control("Slider_MaxHeightHill", m_pSliderMaxHeightHill);
	DDX_Control("Slider_MainSmoothHill", m_pSliderMainSmoothHill);
	DDX_Control("Slider_PartSmoothHill", m_pSliderPartSmoothHill);
	DDX_Control("Slider_TerrainSeedHill", m_pSliderTerrainSeedHill);
	DDX_Control("Slider_BridgeScope", m_pSliderBridgeScope);
	DDX_Control("Slider_BridgeDepth", m_pSliderBridgeDepth);
	DDX_Control("Slider_BorderErode", m_pSliderBorderErode);
	

	DDX_Control("Label_MaxHeightHill", m_pLabelMaxHeightHill);
	DDX_Control("Label_MainSmoothHill", m_pLabelMainSmoothHill);
	DDX_Control("Label_PartSmoothHill", m_pLabelPartSmoothHill);
	DDX_Control("Label_TerrainSeedHill", m_pLabelTerrainSeedHill);
	DDX_Control("Label_BridgeScope", m_pLabelBridgeScope);
	DDX_Control("Label_BridgeDepth", m_pLabelBridgeDepth);
	DDX_Control("Label_BorderErode", m_pLabelBorderErode);
	

	DDX_Slider(bSave, "Slider_MaxHeightHill", m_nMaxHeightHill);
	DDX_Slider(bSave, "Slider_MainSmoothHill", m_nMainSmoothHill);
	DDX_Slider(bSave, "Slider_PartSmoothHill", m_nPartSmoothHill);
	DDX_Slider(bSave, "Slider_TerrainSeedHill", m_nTerrainSeedHill);
	DDX_Slider(bSave, "Slider_BridgeScope", m_nBridgeScope);
	DDX_Slider(bSave, "Slider_BridgeDepth", m_nBridgeDepth);
	DDX_Slider(bSave, "Slider_BorderErode", m_nBorderErode);
	
	m_fMainSmoothHill = float(m_nMainSmoothHill * 0.01f);
	m_fPartSmoothHill = float(m_nPartSmoothHill * 0.01f);	
	m_fBridgeScope = float(m_nBridgeScope * 0.01f);
	m_fBridgeDepth = float(m_nBridgeDepth * 0.01f);
	m_fBorderErode = float(m_nBorderErode * 0.01f);
	

	DDX_CheckBox(bSave, "Check_HillUp", m_bCheckHillUp);

	DDX_RadioButton(bSave, 1, m_nUpDownPri);

	DDX_Control("Btn_Create", m_pBtnCreate);

	GET_BTN_POINTER(BTN_SAVE);
	GET_BTN_POINTER(BTN_SAVE_AS);
}

void CDlgAutoMountain::SetSliderBound()
{
	m_pSliderTextureRatio->SetTotal(MAX_TEXTURE_RATIO, MIN_TEXTURE_RATIO);
	m_pSliderMainTexture->SetTotal(MAX_MAIN_TEXTURE, MIN_MAIN_TEXTURE);
	m_pSliderPatchTexture->SetTotal(MAX_PATCH_TEXTURE, MIN_PATCH_TEXTURE);
	m_pSliderPatchDivision->SetTotal(MAX_PATCH_DIVISION, MIN_PATCH_DIVISION);

	
	m_pSliderMaxHeightHill->SetTotal(MAX_HEIGHT_HILL, MIN_HEIGHT_HILL);
	m_pSliderMainSmoothHill->SetTotal(MAX_MAIM_SMOOTH_HILL , MIN_MAIN_SMOOTH_HILL);
	m_pSliderPartSmoothHill->SetTotal(MAX_PART_SMOOTH_HILL, MIN_PART_SMOOTH_HILL);
	m_pSliderTerrainSeedHill->SetTotal(MAX_TERRAIN_SEED_HILL, MIN_TERRAIN_SEED_HILL);
	m_pSliderBridgeScope->SetTotal(MAX_BRIDGE_SCOPE, MIN_BRIDGE_SCOPE);
	m_pSliderBridgeDepth->SetTotal(MAX_BRIDGE_DEPTH, MIN_BRIDGE_DEPTH);
	m_pSliderBorderErode->SetTotal(MAX_BORDER_ERODE, MIN_BORDER_ERODE);
		
}
void CDlgAutoMountain::LoadDefault()
{
	m_nTextureRatio = 120;
	m_nMainTexture = 40;
	m_nPatchTexture = 120;
	m_nPatchDivision = 30;

	
	m_nMaxHeightHill = 150;
	m_nMainSmoothHill = 300;
	m_nPartSmoothHill = 40;
	m_nTerrainSeedHill = 1;
	m_nBridgeScope = 60;
	m_nBridgeDepth = 20;
	m_nBorderErode = 40;


	m_bCheckHillUp = true;

	m_nUpDownPri = 0;

	GetHomeDlgsMgr()->LoadTextureParamInfo(m_texParamInfo, TT_BRIDGE, TT_BRIDGE_PATCH);
}

void CDlgAutoMountain::SetLabelsText()
{
	ACHAR szName[100];
	
	swprintf(szName, _AL("%-4.2f"), m_fTextureRatio);
	m_pLabelTextureRatio->SetText(szName);

	swprintf(szName, _AL("%-4.2f"), m_fMainTexture);
	m_pLabelMainTexture->SetText(szName);

	swprintf(szName, _AL("%-4.2f"), m_fPatchTexture);
	m_pLabelPatchTexture->SetText(szName);

	swprintf(szName, _AL("%f"), m_fPatchDivision);
	m_pLabelPatchDivision->SetText(szName);


	
	swprintf(szName, _AL("%d"), m_nMaxHeightHill);
	m_pLabelMaxHeightHill->SetText(szName);

	swprintf(szName, _AL("%-4.2f"), m_fMainSmoothHill);
	m_pLabelMainSmoothHill->SetText(szName);

	swprintf(szName, _AL("%-4.2f"), m_fPartSmoothHill);
	m_pLabelPartSmoothHill->SetText(szName);

	swprintf(szName, _AL("%d"), m_nTerrainSeedHill);
	m_pLabelTerrainSeedHill->SetText(szName);

	swprintf(szName, _AL("%-4.2f"), m_fBridgeScope);
	m_pLabelBridgeScope->SetText(szName);

	swprintf(szName, _AL("%-4.2f"), m_fBridgeDepth);
	m_pLabelBridgeDepth->SetText(szName);

	swprintf(szName, _AL("%-4.2f"), m_fBorderErode);
	m_pLabelBorderErode->SetText(szName);


}

void CDlgAutoMountain::OnCommandMoveSlider(const char * szCommand)
{
	UpdateData(true);
	SetLabelsText();
}



void CDlgAutoMountain::OnCommandCreateHillPoly(const char* szCommand)
{
	UpdateData(true);

	if( GetOperationType() != OT_HILL_POLY)
	{
		GetAUIManager()->MessageBox("", GetStringFromTable(1001), MB_OK, A3DCOLORRGBA(255, 255, 255, 160));
		return;
	}

	CAutoScene* pScene = GetAutoScene();
	CAutoTexture* pTexture = pScene->GetAutoTerrain()->GetTexture();
	CAutoHillPoly* pAutoHillPoly = pScene->GetAutoHillPoly();
	
	if (NULL == pAutoHillPoly)
		return;

	CAutoSelectedArea* pSelArea = pScene->GetAutoSelectedArea();
	int nNum = pSelArea->GetNumPolyEditPoints();
	POINT_FLOAT* pPoints = pSelArea->GetPolyEditPoints();
	bool bClosed = pSelArea->GetPolyEditAreaClosed();

	pAutoHillPoly->SetAreaPoints(nNum, pPoints);

	if (!bClosed)
	{
		GetAUIManager()->MessageBox("", GetStringFromTable(1002), MB_OK, A3DCOLORRGBA(255, 255, 255, 160));
		return;
	}
	
	CAutoTerrainAction* pAction = pScene->GetAutoTerrainAction();

	 


	// Store action
	CPolygonMountain* pArea = pScene->GetAutoHillPoly()->GetArea();
	if( GetHomeDlgsMgr()->GetModifying())
	{
		int nIdx = GetHomeDlgsMgr()->m_pDlgAutoAllRes->GetTreeViewSelItemIdx();

		if (!pAction->ChangeActionHillPoly(
				(float)m_nMaxHeightHill,
				(float)(m_nMainSmoothHill * 0.01f),
				(float)(m_nPartSmoothHill * 0.01f),
				m_nTerrainSeedHill,
				m_pCurveHeight->GetNumPoints(),
				m_pCurveHeight->GetPointValues(), 
				m_bCheckHillUp,
				m_fTextureRatio,
				m_fMainTexture, 
				m_fPatchTexture,
				m_fPatchDivision,
				(float)(m_nBridgeScope * 0.01f),
				(float)(m_nBridgeDepth * 0.01f),
				pArea->GetNumPoints(),
				pArea->GetFinalPoints(),
				(float)(m_nBorderErode * 0.01f), 
				nIdx))
		{
			GetAUIManager()->MessageBox("", GetStringFromTable(1003), MB_OK, A3DCOLORRGBA(255, 255, 255, 160));
			return;
		}

		GetAutoScene()->RefreshAllHillActions();
	}
	else
	{
				// Create height
		if (!pAutoHillPoly->CreateHillPoly(
				(float)m_nMaxHeightHill,
				(float)(m_nMainSmoothHill * 0.01f),
				(float)(m_nPartSmoothHill * 0.01f),
				m_nTerrainSeedHill,
				m_pCurveHeight->GetNumPoints(),
				m_pCurveHeight->GetPointValues(),
				m_bCheckHillUp,
				(float)(m_nBorderErode * 0.01f)))
		{
			GetAUIManager()->MessageBox("", GetStringFromTable(1004), MB_OK, A3DCOLORRGBA(255, 255, 255, 160));
			return;
		}
		
		if( m_bCheckHillUp)
		{
			if( !pAutoHillPoly->RenderHillTop(
				m_fTextureRatio,
				m_fMainTexture,
				m_fPatchTexture,
				m_fPatchDivision,
				(float)(m_nBridgeScope * 0.01f),
				(float)(m_nBridgeDepth * 0.01f)))
			{
				GetAUIManager()->MessageBox("", GetStringFromTable(1005), MB_OK, A3DCOLORRGBA(255, 255, 255, 160));
				return;
			}
		}

		if (!pAction->AddActionHillPoly(
			(float)m_nMaxHeightHill,
			(float)(m_nMainSmoothHill * 0.01f),
			(float)(m_nPartSmoothHill * 0.01f),
			m_nTerrainSeedHill,
			m_pCurveHeight->GetNumPoints(),
			m_pCurveHeight->GetPointValues(), 
			m_bCheckHillUp,
			m_fTextureRatio,
			m_fMainTexture, 
			m_fPatchTexture,
			m_fPatchDivision,
			(float)(m_nBridgeScope * 0.01f),
			(float)(m_nBridgeDepth * 0.01f),
			pArea->GetNumPoints(),
			pArea->GetFinalPoints(),
			(float)(m_nBorderErode * 0.01f)))
		{
			GetAUIManager()->MessageBox("", GetStringFromTable(1006), MB_OK, A3DCOLORRGBA(255, 255, 255, 160));
			return;
		}
	}
	
	if (m_bCheckHillUp)
	{
		if (!pAction->AddActionHillTextureInfo(
				m_texParamInfo.fMainTextureU,
				m_texParamInfo.fMainTextureV,
				m_texParamInfo.fPatchTextureU,
				m_texParamInfo.fPatchTextureV,
				pTexture->GetTextureID(TT_BRIDGE),
				pTexture->GetTextureID(TT_BRIDGE_PATCH)))
		{
			GetAUIManager()->MessageBox("", GetStringFromTable(1006), MB_OK, A3DCOLORRGBA(255, 255, 255, 160));
			return;
		}
	}

	// Clear hill bridge texture on down area.
	if (2 == m_nUpDownPri)// Down first
	{
		pTexture->ClearBridgeAtDownArea();
	}
	
	GetAutoScene()->RecreateTerrainRender(true);
	// Update buildings
	pScene->GetAutoTerrain()->Tick(0);// Update terrain height
	CAutoBuildingOperation* pBuildingOperation = pScene->GetAutoBuildingOperation();
	pBuildingOperation->AdjustModelsAfterTerrainChange();


	pSelArea->CopyPointsFromPolyEditToView();
	pSelArea->SetViewAreaClosed(bClosed);
	pSelArea->DeleteAllPolyEditPoints();

		//Add Item to TerrainRes Tree View
	if( !GetHomeDlgsMgr()->GetModifying())
	{
		ACHAR szName[100];
		int nCount = GetHomeDlgsMgr()->m_pDlgAutoBaseMountain->GetActionCount();

		a_sprintf( szName, _AL("%s%d"), GetStringFromTable(1007), nCount);

		GetHomeDlgsMgr()->m_pDlgAutoBaseMountain->SetActionCount(nCount+1);
		
		GetHomeDlgsMgr()->m_pDlgAutoAllRes->InsertResTreeChildItem(CDlgAutoAllRes::ARTI_MOUNTAIN_POLY, szName);
	}
	else
	{
		GetHomeDlgsMgr()->SetModifying(false);
		SetBtnModifyToCreate();
		
	}

	//设置纹理操作可用
	GetHomeDlgsMgr()->m_pDlgAutoBaseMountain->SetTexOpEnable(true);
	
	return;
}

void CDlgAutoMountain::OnCommandOpenHeightCurveDlg(const char* szCommand)
{
	GetHomeDlgsMgr()->GetCurveDlg()->Attach(m_pCurveHeight, true);
	GetHomeDlgsMgr()->GetCurveDlg()->Show(true,true);
}


void CDlgAutoMountain::OnCommandOnRadio(const char* szCommand)
{
	UpdateData(true);
	GetAutoScene()->GetAutoTerrain()->SetUpDownPri(m_nUpDownPri);
}

void CDlgAutoMountain::OnCommandTurnToBase(const char* szCommand)
{
	this->Show(false);
	GetHomeDlgsMgr()->SetUnAdvDlgsEnable();

}

void CDlgAutoMountain::SetBtnCreateToModify()
{
	m_pBtnCreate->SetText( GetStringFromTable(1008) );
	return;
}

void CDlgAutoMountain::SetBtnModifyToCreate()
{
	m_pBtnCreate->SetText( GetStringFromTable(1009) );
	return;
}
*/
//void CDlgAutoMountain::InitSettings(HILLINFO &i_HillInfo,
//									bool		i_bSaveEnable /* = false */,
//									const char* i_szFileName /* = NULL */)
/*{
	//确保数据可用
	m_nMaxHeightHill = int(i_HillInfo.fMaxHeightHill);
	m_nMainSmoothHill = int(i_HillInfo.fMainSmoothHill * 100.0f);
	m_nPartSmoothHill = int(i_HillInfo.fPartSmoothHill * 100.0f);
	m_nTerrainSeedHill = i_HillInfo.dwHillSeed;
	m_nBridgeScope = int(i_HillInfo.fBridgeScope * 100.0f);
	m_nBridgeDepth = int(i_HillInfo.fBridgeDepth * 100.0f);
	m_nBorderErode = int(i_HillInfo.fBorderErode * 100.0f);
	

	Clamp(m_nMaxHeightHill, MAX_HEIGHT_HILL, MIN_HEIGHT_HILL);
	Clamp(m_nMainSmoothHill, MAX_MAIM_SMOOTH_HILL, MIN_MAIN_SMOOTH_HILL);
	Clamp(m_nPartSmoothHill, MAX_PART_SMOOTH_HILL, MIN_PART_SMOOTH_HILL);
	Clamp(m_nTerrainSeedHill, MAX_TERRAIN_SEED_HILL, MIN_TERRAIN_SEED_HILL);
	Clamp(m_nBridgeScope, MAX_BRIDGE_SCOPE, MIN_BRIDGE_SCOPE);
	Clamp(m_nBridgeDepth, MAX_BRIDGE_DEPTH, MIN_BRIDGE_DEPTH);
	Clamp(m_nBorderErode, MAX_BORDER_ERODE, MIN_BORDER_ERODE);
	
	

	//纹理相关数据
	int iTextureRatio = int((i_HillInfo.fTextureRatio * 100.0f) + 100.0f);
	Clamp(iTextureRatio, MAX_TEXTURE_RATIO, MIN_TEXTURE_RATIO);
	int iMainTexture = int(i_HillInfo.fMainTexture * 100.0f);
	Clamp(iMainTexture, MAX_MAIN_TEXTURE, MIN_MAIN_TEXTURE);
	int iPatchTexture = int(i_HillInfo.fPatchTexture * 100.0f);
	Clamp(iPatchTexture, MAX_PATCH_TEXTURE, MIN_PATCH_TEXTURE);
	int iPatchDivision = int(i_HillInfo.fPatchDivision);
	Clamp(iPatchDivision, MAX_PATCH_DIVISION, MIN_PATCH_DIVISION);

	//赋值
	m_nTextureRatio = iTextureRatio;
	m_nMainTexture = iMainTexture;
	m_nPatchTexture = iPatchTexture;
	m_nPatchDivision = iPatchDivision;

	//曲线
	m_pCurveHeight->SetPointValues(i_HillInfo.nNumHeightCurve, i_HillInfo.pHeightCurve);
	


	//设置保存和另存
	m_pBtn[BTN_SAVE]->Enable(i_bSaveEnable);
	m_pBtn[BTN_SAVE_AS]->Enable(!i_bSaveEnable);

	UpdateData(false);
	SetLabelsText();

	if( i_bSaveEnable) //如果可以保存，指定文件名
	{
		strcpy(m_szFileName, i_szFileName);
	}
	else				//如果可以另存，指定文件名
	{
		//获取时间
		WORD wYear,wMonth, wDay, wDate, wHour, wMinute, wSecond;
		a_GetSystemTime(&wYear, &wMonth, &wDay, &wDate, &wHour, &wMinute, &wSecond);

		sprintf(m_szFileName, "%d_%d_%d_%d_%d_%d", wYear, wMonth, wDay, wHour, wMinute, wSecond);
		
	}
}

void CDlgAutoMountain::OnCommandSave(const char* szCommand)
{
	UpdateData(true);

	CAutoParameters *pParameters = GetAutoScene()->GetAutoParameters();
	CAutoParameters::HILLINFO param;
	
	param.fMaxHeightHill = float(m_nMaxHeightHill);
	param.fMainSmoothHill = m_fMainSmoothHill;
	param.fPartSmoothHill = m_fPartSmoothHill;
	param.dwHillSeed = m_nTerrainSeedHill;
	param.fBridgeScope = m_fBridgeScope;
	param.fBridgeDepth = m_fBridgeDepth;
	param.fBorderErode = m_fBorderErode;
	

	param.fTextureRatio = m_fTextureRatio;
	param.fMainTexture = m_fMainTexture;
	param.fPatchTexture = m_fPatchTexture;
	param.fPatchDivision = m_fPatchDivision;

	int i;
	param.nNumHeightCurve = m_pCurveHeight->GetNumPoints();
	float* pfValue = m_pCurveHeight->GetPointValues();
	for(i = 0; i < param.nNumHeightCurve; i++)
	{
		param.pHeightCurve[i] = pfValue[i];
	}



	//创建目录
	ACHAR szPath[MAX_PATH];
	a_strcpy(szPath, _AL("userdata\\"));
	_wmkdir(szPath);

	a_strcat(szPath, _AL("home\\"));
	_wmkdir(szPath);

	a_strcat(szPath,_AL("hill\\"));
	_wmkdir(szPath);

	//设置实际文件名
	char szFileName[MAX_PATH];
	strcpy(szFileName, AC2AS(szPath));
	strcat(szFileName, m_szFileName);


	//保存
	if(!pParameters->SaveHillInfo(szFileName, param))
		AutoHomeReport("CDlgAutoMountain::OnCommandSave, Failed to SaveMainHillInfo!");

	this->Show(false);
	GetHomeDlgsMgr()->SetUnAdvDlgsEnable();
}

void CDlgAutoMountain::OnCommandSaveAs(const char* szCommand)
{
	UpdateData(true);
	
	GetHomeDlgsMgr()->m_pDlgAutoBaseMountain->InsertHillSettings(AS2AC(m_szFileName));
	OnCommandSave("");
	
}

*/