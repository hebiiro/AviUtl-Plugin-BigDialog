#include "pch.h"
#include "BigDialog.h"

//---------------------------------------------------------------------

// デバッグ用コールバック関数。デバッグメッセージを出力する
void ___outputLog(LPCTSTR text, LPCTSTR output)
{
	::OutputDebugString(output);
}

//---------------------------------------------------------------------

HINSTANCE g_instance = 0;

void initHook()
{
	MY_TRACE(_T("initHook()\n"));

	HMODULE user32 = ::GetModuleHandle(_T("user32.dll"));
	GET_HOOK_PROC(user32, DialogBoxParamA);
	GET_HOOK_PROC(user32, CreateDialogParamA);

	MY_TRACE_HEX(true_DialogBoxParamA);
	MY_TRACE_HEX(true_CreateDialogParamA);

	DetourTransactionBegin();
	DetourUpdateThread(::GetCurrentThread());

	ATTACH_HOOK_PROC(DialogBoxParamA);
	ATTACH_HOOK_PROC(CreateDialogParamA);
	ATTACH_HOOK_PROC(GetOpenFileNameA);
	ATTACH_HOOK_PROC(GetSaveFileNameA);

	if (DetourTransactionCommit() == NO_ERROR)
	{
		MY_TRACE(_T("API フックに成功しました\n"));
	}
	else
	{
		MY_TRACE(_T("API フックに失敗しました\n"));
	}
}

void termHook()
{
	MY_TRACE(_T("termHook()\n"));
}

//---------------------------------------------------------------------

EXTERN_C BOOL APIENTRY DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		{
			// ロケールを設定する。
			// これをやらないと日本語テキストが文字化けするので最初に実行する。
			_tsetlocale(LC_ALL, _T(""));

			MY_TRACE(_T("DLL_PROCESS_ATTACH\n"));

			// この DLL のハンドルをグローバル変数に保存しておく。
			g_instance = instance;
			MY_TRACE_HEX(g_instance);

			// この DLL の参照カウンタを増やしておく。
			WCHAR moduleFileName[MAX_PATH] = {};
			::GetModuleFileNameW(g_instance, moduleFileName, MAX_PATH);
			::LoadLibraryW(moduleFileName);

			initHook();

			break;
		}
	case DLL_PROCESS_DETACH:
		{
			MY_TRACE(_T("DLL_PROCESS_DETACH\n"));

			termHook();

			break;
		}
	}

	return TRUE;
}

//---------------------------------------------------------------------

IMPLEMENT_HOOK_PROC_NULL(INT_PTR, WINAPI, DialogBoxParamA, (HINSTANCE instance, LPCSTR templateName, HWND parent, DLGPROC dialogFunc, LPARAM initParam))
{
	if ((DWORD)templateName <= 0x0000FFFF || ::IsBadReadPtr(templateName, 1))
	{
		MY_TRACE(_T("DialogBoxParamA(0x%08X, %d)\n"), instance, templateName);
	}
	else
	{
		MY_TRACE(_T("DialogBoxParamA(0x%08X, %hs)\n"), instance, templateName);
		if (instance == ::GetModuleHandle(_T("exedit.auf")) ||
			instance == ::GetModuleHandle(0))
		{
			MY_TRACE(_T("ダイアログを置き換えます\n"));
			instance = g_instance;
		}
	}

	return true_DialogBoxParamA(instance, templateName, parent, dialogFunc, initParam);
}

IMPLEMENT_HOOK_PROC_NULL(HWND, WINAPI, CreateDialogParamA, (HINSTANCE instance, LPCSTR templateName, HWND parent, DLGPROC dialogFunc, LPARAM initParam))
{
	if ((DWORD)templateName <= 0x0000FFFF || ::IsBadReadPtr(templateName, 1))
	{
		MY_TRACE(_T("CreateDialogParamA(0x%08X, %d)\n"), instance, templateName);
	}
	else
	{
		MY_TRACE(_T("CreateDialogParamA(0x%08X, %hs)\n"), instance, templateName);
		if (instance == ::GetModuleHandle(_T("exedit.auf")) ||
			instance == ::GetModuleHandle(0))
		{
			MY_TRACE(_T("ダイアログを置き換えます\n"));
			instance = g_instance;
		}
	}

	return true_CreateDialogParamA(instance, templateName, parent, dialogFunc, initParam);
}

IMPLEMENT_HOOK_PROC(BOOL, WINAPI, GetOpenFileNameA, (LPOPENFILENAMEA ofn))
{
	MY_TRACE(_T("GetOpenFileNameA()\n"));

	if (ofn->hInstance == ::GetModuleHandle(0))
	{
		MY_TRACE(_T("ダイアログを置き換えます\n"));
		ofn->hInstance = g_instance;
	}

	return true_GetOpenFileNameA(ofn);
}

IMPLEMENT_HOOK_PROC(BOOL, WINAPI, GetSaveFileNameA, (LPOPENFILENAMEA ofn))
{
	MY_TRACE(_T("GetSaveFileNameA()\n"));

	if (ofn->hInstance == ::GetModuleHandle(0))
	{
		MY_TRACE(_T("ダイアログを置き換えます\n"));
		ofn->hInstance = g_instance;
	}

	return true_GetSaveFileNameA(ofn);
}

//---------------------------------------------------------------------
