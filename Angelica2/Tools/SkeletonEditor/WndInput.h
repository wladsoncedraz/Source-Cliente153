#if !defined(AFX_WNDINPUT_H__C4DC2D61_7BF1_4F15_8355_5DB8A941E175__INCLUDED_)
#define AFX_WNDINPUT_H__C4DC2D61_7BF1_4F15_8355_5DB8A941E175__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WndInput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWndInput window

class CWndInput : public CWnd
{
public:		//	Types

	enum
	{
		ID_EDITWINDOW = 101,	//	Edit window ID
	};

	//	Data type
	enum
	{
		DATA_INTEGER = 0,		//	Integer
		DATA_FLOAT,				//	Float
		DATA_STRING,			//	String
	};

// Construction
public:
	CWndInput();

public:		//	Attributes

public:		//	Operations

	//	Popup window, begin to input data
	bool Popup(int iOwnWndID, int iDataType, void* pIniData, const RECT& rc);
	//	Close window, end inputing data
	void Close();

	//	Get owner window's ID
	int GetOwnerWindowID() { return m_iOwnWndID; }

	int GetDataType() { return m_iDataType; }
	const CString& GetResultString() { return m_strResult; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWndInput)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWndInput();

protected:	//	Attributes

	CEdit	m_EditWnd;
	CFont	m_Font;
	int		m_iDataType;	//	Data type
	CString	m_strResult;	//	Result string
	int		m_iOwnWndID;	//	ID of own window

	bool	m_bEditing;		//	Edit flag

protected:	//	Operations

	void EndEditing(bool bCancel, bool bClickEnd, const POINT* pPoint);

	// Generated message map functions
protected:
	//{{AFX_MSG(CWndInput)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WNDINPUT_H__C4DC2D61_7BF1_4F15_8355_5DB8A941E175__INCLUDED_)
