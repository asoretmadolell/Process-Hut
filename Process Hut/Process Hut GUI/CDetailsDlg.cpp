// CDetailsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CDetailsDlg.h"
#include "afxdialogex.h"


// CDetailsDlg dialog

IMPLEMENT_DYNAMIC(CDetailsDlg, CDialog)

CDetailsDlg::CDetailsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDetailsDlg::IDD, pParent)
{

}

CDetailsDlg::~CDetailsDlg()
{
}

void CDetailsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
     DDX_Control( pDX, IDC_LIST1, m_listBox );
}

BOOL CDetailsDlg::OnInitDialog()
{
     CDialog::OnInitDialog();

     //m_listBox.SubclassDlgItem( IDC_LIST1, this ); // Same as DDX_Control method

     // Populate the list box with process details
     m_listBox.AddString( _T( "Process Name: " ) + m_processName );
     m_listBox.AddString( _T( "Working Directory: " ) + m_workingDirectory );

     return TRUE;
}



BEGIN_MESSAGE_MAP(CDetailsDlg, CDialog)
END_MESSAGE_MAP()


// CDetailsDlg message handlers
