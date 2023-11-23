
// demo3.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "demo3.h"
#include "demo3Dlg.h"
#include <Windows.h>
#include <iphlpapi.h>
#include<sstream>
#include"CLcokDlg.h"
#pragma comment(lib, "iphlpapi.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cdemo3App

BEGIN_MESSAGE_MAP(Cdemo3App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Cdemo3App 构造
#include<string>
CString Cdemo3App::GetPcinfoCode()
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
		resultStr +=temp;
	}
	return resultStr;
}

CString Cdemo3App::GetKey(CString pcInfoCode)
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

Cdemo3App::Cdemo3App()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 Cdemo3App 对象

Cdemo3App theApp;


// Cdemo3App 初始化

BOOL Cdemo3App::InitInstance()
{
	

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CString keyPath = _T("Software\\YourCompany\\YourApp");

	CString savedKey;

	HKEY hKey;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\myApp", 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
	{
		DWORD dataSize = 0;
		if (RegQueryValueEx(hKey, "Key", NULL, NULL, NULL, &dataSize) == ERROR_SUCCESS)
		{
			TCHAR* buffer = new TCHAR[dataSize / sizeof(TCHAR)];
			if (RegQueryValueEx(hKey, "Key", NULL, NULL, (LPBYTE)buffer, &dataSize) == ERROR_SUCCESS)
			{
				savedKey = buffer;
			}
			delete[] buffer;
		}

		RegCloseKey(hKey);
	}
	

	INT_PTR nResponse = 0;
	CString pcInfoCode=GetPcinfoCode();
	if (savedKey != pcInfoCode)
	{
		CLcokDlg lockDlg;
		m_pMainWnd = &lockDlg;
		INT_PTR nResponse = lockDlg.DoModal();
	}
	else
	{
		Cdemo3Dlg dlg;
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
	}

	
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

