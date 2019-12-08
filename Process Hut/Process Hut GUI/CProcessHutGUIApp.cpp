#include "stdafx.h"
#include "CProcessHutGUIApp.h"
#include "CProcessHutGUIDlg.h"

CProcessHutGUIApp::CProcessHutGUIApp()
{

}

CProcessHutGUIApp theApp;

BOOL CProcessHutGUIApp::InitInstance()
{
    CProcessHutGUIDlg myDlg;
    m_pMainWnd = &myDlg;
    myDlg.DoModal();
    return TRUE;
}

