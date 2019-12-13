#include "stdafx.h"
#include "CProcessHutGUIDlg.h"
#include "CProcessHutGUIApp.h"
#include <psapi.h>
#include <string>

// CProcessHutGUIDlg dialog

CProcessHutGUIDlg::CProcessHutGUIDlg( CWnd* pParent /*=NULL*/ )
    :CDialog( CProcessHutGUIDlg::IDD, pParent )
    , m_strTree( _T( "" ) )
{

}

void CProcessHutGUIDlg::DoDataExchange( CDataExchange* pDX )
{
    CDialog::DoDataExchange( pDX );
    //DDX_Text( pDX, IDC_STATIC_TXT, m_strTree );
    DDX_Control( pDX, IDC_TREE1, m_treeCtrl );
}

// CProcessHutGUIDlg message handlers

BOOL CProcessHutGUIDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Get the list of process identifiers.
    DWORD aProcesses[ 1024 ], cbNeeded, cProcesses;
    unsigned int i;

    if( !EnumProcesses( aProcesses, sizeof( aProcesses ), &cbNeeded ) )
    {
        return 1;
    }

    // Calculate how many process identifiers were returned.
    cProcesses = cbNeeded / sizeof( DWORD );
    ShowWindow( SW_MINIMIZE );

    HTREEITEM hItem, hProcess;
    hItem = m_treeCtrl.InsertItem( L"Processes", TVI_ROOT );

    for( i = 0; i < cProcesses; i++ )
    {
        if( aProcesses[ i ] != 0 )
        {
            CString str;
            str.Format( TEXT( "Process %d" ), aProcesses[ i ] );
            m_treeCtrl.InsertItem( str, hItem );
        }
    }

    return TRUE;  // return TRUE  unless you set the focus to a control
}
