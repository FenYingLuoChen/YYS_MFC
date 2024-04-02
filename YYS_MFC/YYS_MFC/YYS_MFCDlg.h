
// YYS_MFCDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "Function.h"

// CYYS_MFCDlg 对话框
class CYYS_MFCDlg : public CDialogEx
{
// 构造
public:
	CYYS_MFCDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_YYS_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	void init_combox();

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	void GetMousePoint(CString type, std::vector<MouseClick> &click_list);
	void SendMousePressed();
	void OpenConSole(CString type);
	void CloseConSole();
	void rememberOption(FILE*file);
	//DWORD WINAPI ThreadProc(LPVOID lpParam);
	//void initwindowpos();
	//BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lparam);
	std::vector<MouseClick> click_list;
	CString m_str_combox;
	BOOL if_read = true;
	BOOL if_reset = false;
	CComboBox m_combox;
	POINT point = { 0 };
	int sleeptime;
	int x, y, width, height;
	CString classname;
	HWND *window = NULL;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	void initwindowpos();
	void rePosWindowpos();
	DWORD WindowFormat[2] = { 0 };
};
