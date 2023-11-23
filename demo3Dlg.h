
// demo3Dlg.h: 头文件
//

#pragma once
#include<vector>
#include<string>
#include<map>
using std::map;
using std::vector;
// Cdemo3Dlg 对话框
class Cdemo3Dlg : public CDialogEx
{
// 构造
public:
	Cdemo3Dlg(CWnd* pParent = nullptr);	// 标准构造函数
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEMO3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
private:
	std::vector<double>getNums(CString str);
	BOOL m_IsInitialized;
	int m_nOldCx, m_nOldCy; // 变量需要在类的构造函数中初始化
	CRect m_rect;
	map<int, vector<double>> tar;				//存储所有控件比例信息    key = 控件ID  value = 控件比例
	map<int, vector<double>>::iterator key;		//迭代器查找结果
	map<int, vector<double>>::iterator end;		//存储容器的最后一个元素

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	void ReSize(int cx, int cy);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit4();
	CListCtrl m_listCtrl;
	afx_msg void OnNMClickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
