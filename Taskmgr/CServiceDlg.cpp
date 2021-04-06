// CServiceDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProcessExlpore.h"
#include "CServiceDlg.h"
#include "afxdialogex.h"
#include<windows.h>
#include<winsvc.h>


// CServiceDlg 对话框

IMPLEMENT_DYNAMIC(CServiceDlg, CDialogEx)

CServiceDlg::CServiceDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SERVICE, pParent)
{

}

CServiceDlg::~CServiceDlg()
{
}

void CServiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SERVICE, m_ListCtrlService);
}


BEGIN_MESSAGE_MAP(CServiceDlg, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_SERVICE, &CServiceDlg::OnNMRClickListService)
	ON_COMMAND(ID_32778, &CServiceDlg::OnStartService)
	ON_COMMAND(ID_32779, &CServiceDlg::OnCloseService)
END_MESSAGE_MAP()


// CServiceDlg 消息处理程序
void CServiceDlg::InitService()
{
	CString str;
	SC_HANDLE HSCM = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	DWORD dwServiceNum = 0;
	DWORD dwSize = 0;
	EnumServicesStatusEx(HSCM, SC_ENUM_PROCESS_INFO,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,
		NULL,
		0,
		&dwSize,
		&dwServiceNum,
		NULL,
		NULL);

	LPENUM_SERVICE_STATUS_PROCESS pEnumService = (LPENUM_SERVICE_STATUS_PROCESS) new char[dwSize];

	bool bStatus = FALSE;
	bStatus = EnumServicesStatusEx(HSCM,
		SC_ENUM_PROCESS_INFO,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,
		(PBYTE)pEnumService,
		dwSize,
		&dwSize,
		&dwServiceNum,
		NULL, NULL);

	for (DWORD i = 0; i < dwServiceNum; i++)
	{
		//pEnumService[i].lpServiceName;
		//pEnumService[i].ServiceStatusProcess.dwCurrentState;
		//pEnumService[i].ServiceStatusProcess.dwServiceType;
		str = pEnumService[i].lpServiceName;
		m_ListCtrlService.InsertItem(i, str);
		m_vecSerName.push_back(str);
		if (SERVICE_STOPPED == pEnumService[i].ServiceStatusProcess.dwCurrentState)
			str = "服务已停止";
		else if (SERVICE_START_PENDING == pEnumService[i].ServiceStatusProcess.dwCurrentState)
			str = "服务正在启动";
		else if (SERVICE_STOP_PENDING == pEnumService[i].ServiceStatusProcess.dwCurrentState)
			str = "服务正在停止";
		else if (SERVICE_RUNNING == pEnumService[i].ServiceStatusProcess.dwCurrentState)
			str = "服务正在运行";
		else if (SERVICE_CONTINUE_PENDING == pEnumService[i].ServiceStatusProcess.dwCurrentState)
			str = "该服务将继续";
		else if (SERVICE_PAUSE_PENDING == pEnumService[i].ServiceStatusProcess.dwCurrentState)
			str = "服务正在暂停";
		else if (SERVICE_PAUSED == pEnumService[i].ServiceStatusProcess.dwCurrentState)
			str = "服务已暂停";
		m_ListCtrlService.SetItemText(i, 1, str);

		if (SERVICE_KERNEL_DRIVER == pEnumService[i].ServiceStatusProcess.dwServiceType)
			str = "设备驱动程序";
		else if (SERVICE_FILE_SYSTEM_DRIVER == pEnumService[i].ServiceStatusProcess.dwServiceType)
			str = "文件系统驱动程序";
		else if (SERVICE_WIN32_OWN_PROCESS == pEnumService[i].ServiceStatusProcess.dwServiceType)
			str = "该服务在其自己的进程中运行";
		else if (SERVICE_WIN32_SHARE_PROCESS == pEnumService[i].ServiceStatusProcess.dwServiceType)
			str = "该服务与其他服务共享一个过程";
		else
			str = "其他服务";
		m_ListCtrlService.SetItemText(i, 2, str);

		SC_HANDLE hService = OpenService(HSCM,
			pEnumService[i].lpServiceName,
			SERVICE_QUERY_CONFIG);
		
		QueryServiceConfig(hService, NULL, 0, &dwSize);
		LPQUERY_SERVICE_CONFIG pServiceConfig = (LPQUERY_SERVICE_CONFIG) new char[dwSize];
		QueryServiceConfig(hService, pServiceConfig, dwSize, &dwSize);
		 int j = 0;
		//pServiceConfig->dwStartType;
		m_ListCtrlService.SetItemText(i, 3, pServiceConfig->lpBinaryPathName);
		//pServiceConfig->lpBinaryPathName;
		delete[] pServiceConfig;
	}
	delete[] pEnumService;
}

BOOL CServiceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListCtrlService.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListCtrlService.InsertColumn(1, L"名称", LVCFMT_CENTER, 100);
	m_ListCtrlService.InsertColumn(2, L"状态", LVCFMT_CENTER, 100);
	m_ListCtrlService.InsertColumn(3, L"服务类型", LVCFMT_CENTER, 100);
	m_ListCtrlService.InsertColumn(4, L"路径信息", LVCFMT_CENTER, 300);

	InitService();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CServiceDlg::OnNMRClickListService(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CMenu menu;
	menu.LoadMenuW(IDR_MENU3);
	CMenu* pSub = menu.GetSubMenu(0);
	POINT pi;
	GetCursorPos(&pi);
	pSub->TrackPopupMenu(TPM_RIGHTALIGN, pi.x, pi.y, this);
	*pResult = 0;
}


void CServiceDlg::OnStartService()
{
	// TODO: 在此添加命令处理程序代码
	CString str;
	str = "正在运行";
	DWORD dwIndex = m_ListCtrlService.GetSelectionMark();
	CString szSerName = m_vecSerName[dwIndex];

	SC_HANDLE scmHandle = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	

	auto serviceHandle = OpenServiceW(scmHandle,
		szSerName,
		SERVICE_ALL_ACCESS);
	

	SERVICE_STATUS serviceStatus;
	QueryServiceStatus(serviceHandle, &serviceStatus);
	if (serviceStatus.dwCurrentState == SERVICE_RUNNING)
	{
		MessageBox(L"服务已启动,不能再启动!");
		return;
	}
	StartServiceW(serviceHandle, 0, NULL);

	m_ListCtrlService.SetItemText(dwIndex, 1, str);
	CloseServiceHandle(scmHandle);
	CloseServiceHandle(serviceHandle);
}


void CServiceDlg::OnCloseService()
{
	// TODO: 在此添加命令处理程序代码
	CString str;
	str = "已停止";
	DWORD dwIndex = m_ListCtrlService.GetSelectionMark();
	CString szSerName = m_vecSerName[dwIndex];
	//QueryServiceStatus
	SC_HANDLE scmHandle = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);


	auto serviceHandle = OpenServiceW(scmHandle,
		szSerName,
		SERVICE_ALL_ACCESS | SERVICE_STOP);


	SERVICE_STATUS serviceStatus;
	QueryServiceStatus(serviceHandle, &serviceStatus);
	if (serviceStatus.dwCurrentState == SERVICE_STOPPED)
	{
		MessageBox(L"服务已关闭，不能再关闭!");
		return;
	}
	ControlService(serviceHandle, SERVICE_CONTROL_STOP, &serviceStatus);

	m_ListCtrlService.SetItemText(dwIndex, 1, str);

	CloseServiceHandle(scmHandle);
	CloseServiceHandle(serviceHandle);
}
