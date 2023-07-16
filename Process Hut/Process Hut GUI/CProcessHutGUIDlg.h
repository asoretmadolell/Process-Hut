#pragma once
#include "afxcmn.h"

#include "resource.h"

// CProcessHutGUIDlg dialog
class CProcessHutGUIDlg : public CDialog
{
// Construction
public:
    CProcessHutGUIDlg( CWnd* pParent = NULL );  // standard constructor
    
// Dialog Data
    enum { IDD = IDD_EXAMPLE_DLG };

protected:
    virtual void DoDataExchange( CDataExchange* pDX );	// DDX/DDV support

// Implementation
protected:
     virtual BOOL OnInitDialog();

     DECLARE_MESSAGE_MAP()

public:    
    CString m_strTree;
    CTreeCtrl m_treeCtrl;


private:
     CButton m_btnDetails;
     HTREEITEM m_selectedProcessItem;

     afx_msg void OnBnClickedDetails();
     //afx_msg LRESULT CProcessHutGUIDlg::OnTreeSelectionChanged( WPARAM wParam, LPARAM lParam, LRESULT* pResult );
     afx_msg void OnTreeSelectionChanged( NMHDR* pNMHDR, LRESULT* pResult );


};
