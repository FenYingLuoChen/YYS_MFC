#pragma once
#include "Function.h"
#include "YYS_MFCDlg.h"
class MyPicture
{
public:
	MyPicture(char* filename);
	~MyPicture();

	//初始化
	void Init();
	//从主窗口指定位置获取图片保存
	void SaveBmpFromPointToFile(char * filename, POINT point, HWND hwnd, int width = 10, int height = 10);
	//更新背景图片
	void UpdateBackGround();
	//获取图片位置
	BOOL GetBmpPos();
	//点击
	BOOL Click();
	//结算
	void EndClick();
	//设置主次窗口
	void MainSubWnd();
	//移动视图
	static void MouseDrag();

	//主窗口
	static HWND HwndMain;
	//次窗口
	static HWND HwndSub;
	//背景图片
	static char* BackGround;
	//主次窗口区分标识 0 主窗口 1 次窗口
	static int type;
	//窗口类
	static HWND * window;

	//当前图片
	char * Bitmap;
	//当前图片位置
	POINT BmpPos;
	//是否初始化图片
	BOOL IfInit;

};

