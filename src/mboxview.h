//
//////////////////////////////////////////////////////////////////
//
//  Windows Mbox Viewer is a free tool to view, search and print mbox mail archives.
//
// Source code and executable can be downloaded from
//  https://sourceforge.net/projects/mbox-viewer/  and
//  https://github.com/eneam/mboxviewer
//
//  Copyright(C) 2019  Enea Mansutti, Zbigniew Minciel
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the version 3 of GNU Affero General Public License
//  as published by the Free Software Foundation; 
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU
//  Library General Public License for more details.
//
//  You should have received a copy of the GNU Library General Public
//  License along with this program; if not, write to the
//  Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
//  Boston, MA  02110 - 1301, USA.
//
//////////////////////////////////////////////////////////////////
//

// mboxview.h : main header file for the mboxview application
//

#if !defined(AFX_mboxview_H__01D75A85_01DB_4CC8_A34E_AC20E309168D__INCLUDED_)
#define AFX_mboxview_H__01D75A85_01DB_4CC8_A34E_AC20E309168D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include <string>
#include "mainfrm.h"       // main symbols
#include "TextUtilities.h"

extern const char *sz_Software_mboxview;

/////////////////////////////////////////////////////////////////////////////
// CmboxviewApp:
// See mboxview.cpp for the implementation of this class
//

#define MAPPING_SIZE 268435456

class CmboxviewApp : public CWinApp
{
public:
	CmboxviewApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CmboxviewApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CmboxviewApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	afx_msg void MyMRUFileHandler(UINT i);
	DECLARE_MESSAGE_MAP()
};


extern CmboxviewApp theApp;

char *findOneOf(char *beg, char *end, char *charList);
BOOL isEmptyLine(const char* p, const char* e);
char* strnstrUpper2Lower(char *any, char *end, const char *lower, int lowerlength);
int strncmpUpper2Lower(char *any, char *end, const char *lower, int lowerlength);
char *strchar(char *beg, char *end, char c);
BOOL isNumeric(CString &str);
BOOL Str2Wide(CString &res, UINT CodePage, CStringW &m_strW);
UINT charset2Id(const char *char_set);
BOOL id2charset(UINT id, std::string &charset);
void ShellExecuteError2Text(UINT errorCode, CString &errorText);
void AppendMenu(CMenu *menu, int commandId, const char *commandName);
int AttachIcon(CMenu* Menu, LPCTSTR MenuName, int resourceId, CBitmap  &cmap);
BOOL BrowseToFile(LPCTSTR filename);
void CheckShellExecuteResult(HINSTANCE  result, HWND h = 0);
void Com_Initialize();

inline char *SkipWhite(char *p) {
	while ((*p == ' ') || (*p == '\t')) p++;
	return p;
}

inline char *SkipWhitePlus(char *p) {
	while ((*p == ' ') || (*p == '\t') || (*p == '"')) p++;
	return p;
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_mboxview_H__01D75A85_01DB_4CC8_A34E_AC20E309168D__INCLUDED_)
