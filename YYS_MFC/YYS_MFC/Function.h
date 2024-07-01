#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <GdiPlus.h>
#include <atlstr.h>
#include <windows.h>
#pragma comment(lib,"GdiPlus.lib")
using namespace Gdiplus;
typedef struct mouse_click
{
	POINT point;
	int sleep_time;
}MouseClick;

//vector<mouse_click> click_list;
//获取需要点击的鼠标位置
void GetMousePoint(std::vector<MouseClick> &click_list);
void SendMousePressed(std::vector<MouseClick> &click_list);
void GetYYSWindow(CString  classname, HWND *window);
void widechar2char(wchar_t * wide_str,char * char_str);
void char2widechar(char * wide_str, wchar_t * char_str);
void Debug(const char* format,...);
int getRand(int min,int max);