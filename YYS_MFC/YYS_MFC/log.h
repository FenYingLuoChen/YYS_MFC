#pragma once
#pragma warinig(disable:4996)

#define LOG_FILE_NAME TEXT("log.txt")

#define LOG_ENABLE

#include <fstream>
#include <string>
#include <ctime>
#include <Windows.h>
#include "tchar.h"

using namespace std;

class Clog
{
public:
	static void GetLogFilePath(CHAR * szPath)
	{
		GetModuleFileNameA(NULL, szPath, MAX_PATH);
		ZeroMemory(strrchr(szPath, _T('\\')), strlen(strrchr(szPath, _T('\\')))*sizeof(CHAR));
		strcat(szPath, "\\");
		char temp[MAX_PATH] = { 0 };
		strcat(szPath, LOG_FILE_NAME);
	}

	static void LOG(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		char buf[1024] = { 0 };
		CHAR szPath[MAX_PATH] = { 0 };
		GetLogFilePath(szPath);
		ofstream fout(szPath, ios::app);
		fout.seekp(ios::end);
		//将format中的占位符替换成args内容  类比sprintf
		vsprintf(buf, format, args);
		va_end(args);
		fout << GetSystemTime() << buf << endl;
		fout.close();
	}

private:
	static string GetSystemTime()
	{
		time_t tNowTime;
		time(&tNowTime);
		tm* tLocalTime = localtime(&tNowTime);
		char szTime[MAX_PATH] = { 0 };
		strftime(szTime, 30, "[%Y-%m-%d %H:%M:%S]", tLocalTime);
		string strTime = szTime;
		return strTime;
	}
};
#ifdef LOG_ENABLE

#define LOG(x,...)  Clog::LOG(x,__VA_ARGS__);

#endif
