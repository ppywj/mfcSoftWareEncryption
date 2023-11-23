#pragma once


// CLcokDlg 对话框

class CLcokDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLcokDlg)

public:
	CLcokDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLcokDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif
private:
	CString GetKey(CString pcInfoCode);
	CString GetPcinfoCode();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedButton1();
	CString registerCode;
	CString keyCode;
	CEdit registerCodeEdit;
	CEdit keyEdit;

	afx_msg void OnEnChangeEdit1();
};
