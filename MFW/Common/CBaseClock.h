/*******************************************************************************
	File:		CBaseClock.h

	Contains:	The audio dec header file.

	Written by:	Fenger King

	Change History (most recent first):
	2013-09-02		Fenger			Create file

*******************************************************************************/
#ifndef __CBaseClock_H__
#define __CBaseClock_H__

#include "CBaseObject.h"
#include "CMutexLock.h"

#include "yyData.h"

class CBaseClock : public CBaseObject
{
public:
	CBaseClock(void);
	virtual ~CBaseClock(void);

	virtual long long	GetTime (void);
	virtual int			SetTime (long long llTime);

	virtual int			Start (void);
	virtual int			Pause (void);

	virtual int			SetErrAdj (int nError);
	virtual int			GetErrAdj (void);

	virtual int			SetSpeed (float fSpeed);
	virtual float		GetSpeed (void);
	
	virtual int			SetOffset (int nOffset);
	virtual int			GetOffset (void);

	virtual bool		IsPaused (void);

protected:
	CMutexLock			m_mtTime;
	bool				m_bRun;

	int					m_nErrAdj;
	int					m_nOldAdj;
	long long			m_llStart;
	long long			m_llSystem;

	long long			m_llLast;
	long long			m_llNow;

	float				m_fSpeed;
	int					m_nOffset;
};

#endif // __CBaseClock_H__
