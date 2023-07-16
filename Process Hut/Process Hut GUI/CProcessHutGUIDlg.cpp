#include "stdafx.h"
#include "CProcessHutGUIDlg.h"
#include "CProcessHutGUIApp.h"
#include <psapi.h>
#include <string>
#include <TlHelp32.h>
#include "afxwin.h"
#include "afxmsg_.h"
#include "afxcmn.h"
#include "CDetailsDlg.h"

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

    // Create the "Details" button
    //m_btnDetails.Create( L"Details", WS_CHILD | WS_VISIBLE | WS_DISABLED, CRect( 10, 10, 100, 30 ), this, IDC_DETAILS_BUTTON );
    m_btnDetails.SubclassDlgItem( IDC_DETAILS_BUTTON, this );

    // Get the list of process identifiers.
    DWORD aProcesses[ 1024 ], cbNeeded, cProcesses;
    unsigned int i;

    if( !EnumProcesses( aProcesses, sizeof( aProcesses ), &cbNeeded ) )
    {
        return 1;
    }

    // Calculate how many process identifiers were returned.
    cProcesses = cbNeeded / sizeof( DWORD );
    //ShowWindow( SW_MINIMIZE );

    HTREEITEM hProcessItem = m_treeCtrl.InsertItem( L"Processes", TVI_ROOT );

    for( i = 0; i < cProcesses; i++ )
    {
        if( aProcesses[ i ] != 0 )
        {
             // Insert process item
            CString str;
            str.Format( TEXT( "Process %d" ), aProcesses[ i ] );
            HTREEITEM hProcess = m_treeCtrl.InsertItem( str, hProcessItem );

            // Insert threads as child items for the process
            HANDLE hProcessHandle = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[ i ] );
            if( hProcessHandle != NULL )
            {
                 THREADENTRY32 threadEntry;
                 threadEntry.dwSize = sizeof( THREADENTRY32 );

                 HANDLE hThreadSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPTHREAD, 0 );
                 if( hThreadSnapshot != INVALID_HANDLE_VALUE )
                 {
                      if( Thread32First( hThreadSnapshot, &threadEntry ) )
                      {
                           do
                           {
                                if( threadEntry.th32OwnerProcessID == aProcesses[ i ] )
                                {
                                     CString threadStr;
                                     threadStr.Format( TEXT( "Thread %d" ), threadEntry.th32ThreadID );
                                     m_treeCtrl.InsertItem( threadStr, hProcess );
                                }
                           }
                           while( Thread32Next( hThreadSnapshot, &threadEntry ) );
                      }
                 }
                 CloseHandle( hThreadSnapshot );
            }
            CloseHandle( hProcessHandle );
        }
    }

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CProcessHutGUIDlg::OnBnClickedDetails()
{
     // Ensure a process item is selected
     if( m_selectedProcessItem != NULL )
     {
          // Retrieve the process ID from the selected item's text
          CString processText = m_treeCtrl.GetItemText( m_selectedProcessItem );
          int processID = _ttoi( processText.Mid( 8 ) );

          // Open the process with necessary access rights
          HANDLE hProcess = OpenProcess( PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processID );
          if( hProcess != NULL )
          {
               // Query the process information
               TCHAR path[ MAX_PATH ];
               DWORD pathSize = MAX_PATH;
               if( QueryFullProcessImageName( hProcess, 0, path, &pathSize ) != 0 )
               {
                    // Get the working directory of the process
                    TCHAR workingDir[ MAX_PATH ];
                    _tcscpy_s( workingDir, path );
                    PathRemoveFileSpec( workingDir );

                    // Create a dialog to display process details
                    CDetailsDlg dlg;

                    // Pass the process details to the dialog
                    dlg.m_processName = path;
                    dlg.m_workingDirectory = workingDir;

                    dlg.DoModal();
               }

               // Close the process handle
               CloseHandle( hProcess );
          }
     }
}

void CProcessHutGUIDlg::OnTreeSelectionChanged( NMHDR* pNMHDR, LRESULT* pResult )
{
     LPNMTREEVIEW pNMTV = reinterpret_cast<LPNMTREEVIEW>( pNMHDR );

     // Enable/disable the "Details" button based on the selection
     if( pNMTV->itemNew.hItem != NULL && m_treeCtrl.GetParentItem( pNMTV->itemNew.hItem ) == m_treeCtrl.GetRootItem() )
     {
          m_selectedProcessItem = pNMTV->itemNew.hItem;
          m_btnDetails.EnableWindow( TRUE );
     }
     else
     {
          m_selectedProcessItem = NULL;
          m_btnDetails.EnableWindow( FALSE );
     }

     *pResult = 0;
}


BEGIN_MESSAGE_MAP( CProcessHutGUIDlg, CDialog )
     // Other message map entries...
     ON_BN_CLICKED( IDC_DETAILS_BUTTON, &CProcessHutGUIDlg::OnBnClickedDetails )
     //ON_NOTIFY_REFLECT( TVN_SELCHANGED, &CProcessHutGUIDlg::OnTreeSelectionChanged )
     ON_NOTIFY( TVN_SELCHANGED, IDC_TREE1, &CProcessHutGUIDlg::OnTreeSelectionChanged )


END_MESSAGE_MAP()

