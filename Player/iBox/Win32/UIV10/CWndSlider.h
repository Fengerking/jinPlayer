/*******************************************************************************
	File:		CWndSlider.h

	Contains:	the window view header file

	Written by:	Fenger King

	Change History (most recent first):
	2013-03-28		Fenger			Create file

*******************************************************************************/
#ifndef __CWndSlider_H__
#define __CWndSlider_H__

#include "CWndBase.h"

#define		WM_YYSLD_NEWPOS		WM_APP + 0X2001

class CWndSlider : public CWndBase
{
public:
	CWndSlider(HINSTANCE hInst);
	virtual ~CWndSlider(void);

	virtual bool	CreateWnd (HWND hParent, RECT rcView, COLORREF clrBG, bool bPopup = false);

	virtual bool	SetRange (int nMin, int nMax);
	virtual int		GetPos (void);
	virtual int		SetPos (int nPos);

protected:
	virtual LRESULT	OnReceiveMessage (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void	UpdateThumb (bool bNewPos);

protected:
	HPEN		m_hPenBound;
	HBRUSH		m_hBrushBG;

	RECT		m_rcThumb;
	HBRUSH		m_hBrushTmb;
	long long	m_nThumbPos;

	long long	m_nMinPos;
	long long	m_nMaxPos;
	long long	m_nCurPos;

	RECT		m_rcText;
	TCHAR		m_szDur[32];
	TCHAR		m_szPos[32];
};
#endif //__CWndSlider_H__