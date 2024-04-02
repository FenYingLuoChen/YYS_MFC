#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>

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