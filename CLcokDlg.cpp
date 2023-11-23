// CLcokDlg.cpp: 实现文件
//

#include "pch.h"
#include "demo3.h"
#include "CLcokDlg.h"
#include "afxdialogex.h"
#include<sstream>
#include<string>
#include <iphlpapi.h>
#include"CLcokDlg.h"
#include"demo3Dlg.h"
#pragma comment(lib, "iphlpapi.lib")
// CLcokDlg 对话框

IMPLEMENT_DYNAMIC(CLcokDlg, CDialogEx)

CLcokDlg::CLcokDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, registerCode(_T(""))
	, keyCode(_T(""))
{

}

CLcokDlg::~CLcokDlg()
{
}

CString CLcokDlg::GetKey(CString pcInfoCode)
{
	CString str = "3214569872021041520024925592652165";

	CString result;
	for (int i = 0; i < pcInfoCode.GetLength() && i < str.GetLength(); i++)
	{
		TCHAR ch = (TCHAR)((pcInfoCode[i] - '0') ^ (str[i] - '0')) + '0';
		result += ch;
	}
	return result;
}

CString CLcokDlg::GetPcinfoCode()
{
	std::string macAddress;
	IP_ADAPTER_INFO adapterInfo[16];
	DWORD bufferSize = sizeof(adapterInfo);
	DWORD result = GetAdaptersInfo(adapterInfo, &bufferSize);

	if (result == ERROR_SUCCESS)
	{
		PIP_ADAPTER_INFO pAdapterInfo = adapterInfo;
		std::stringstream ss;
		for (DWORD i = 0; i < pAdapterInfo->AddressLength; i++)
		{
			if (i > 0)
				ss << ":";
			ss << std::hex << (int)pAdapterInfo->Address[i];
		}
		macAddress = ss.str();
	}

	// 将 MAC 地址进行异或操作，得到全数字的结果
	std::string numericMacAddress;
	for (int i = 0; i < macAddress.length(); i++)
	{
		char numericChar = (char)(macAddress[i] ^ '0');
		numericMacAddress += numericChar;
	}
	CString pcInfo;
	pcInfo.Format(_T("%s"), numericMacAddress.c_str());
	CString resultStr, temp;
	for (int i = 0; i < pcInfo.GetLength(); i++)
	{
		temp.Format("%d", (int)pcInfo[i]);
		resultStr += temp;
	}
	return resultStr;
}

void CLcokDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, registerCode);
	DDX_Text(pDX, IDC_EDIT2, keyCode);
	DDX_Control(pDX, IDC_EDIT1, registerCodeEdit);
	DDX_Control(pDX, IDC_EDIT2, keyEdit);
}

BOOL CLcokDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	registerCodeEdit.SetWindowText(GetKey(GetPcinfoCode()));
	return true;
}


BEGIN_MESSAGE_MAP(CLcokDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLcokDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CLcokDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// 解锁按钮响应
void CLcokDlg::OnBnClickedButton1()
{
	CString registerCode, key;
	GetDlgItemText(IDC_EDIT1, registerCode);
	GetDlgItemText(IDC_EDIT2,key);
	if (GetKey(registerCode) == key)
	{
		//写注册表
		CString registerCode, key;
		GetDlgItemText(IDC_EDIT1, registerCode);
		GetDlgItemText(IDC_EDIT2, key);

		if (GetKey(registerCode) == key)
		{
			// 写入注册表
			HKEY hKey;
			if (RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\myApp", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &hKey, NULL) == ERROR_SUCCESS)
			{
				RegSetValueEx(hKey, "Key", 0, REG_SZ, (LPBYTE)(LPCTSTR)key, (key.GetLength() + 1) * sizeof(TCHAR));
				RegCloseKey(hKey);
			}

			// 隐藏当前对话框并显示主对话框
			ShowWindow(SW_HIDE);
			Cdemo3Dlg mainDlg;
			mainDlg.DoModal();
		}
		ShowWindow(SW_HIDE);
		Cdemo3Dlg mainDlg;
		mainDlg.DoModal();
	}
	
}


void CLcokDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
