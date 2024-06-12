// DialogBK.cpp : 实现文件
//

#include "stdafx.h"
#include "YYS_MFC.h"
#include "DialogBK.h"
#include "afxdialogex.h"


// DialogBK 对话框

IMPLEMENT_DYNAMIC(DialogBK, CDialogEx)

DialogBK::DialogBK(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

DialogBK::~DialogBK()
{
}

void DialogBK::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogBK, CDialogEx)
END_MESSAGE_MAP()


// DialogBK 消息处理程序
