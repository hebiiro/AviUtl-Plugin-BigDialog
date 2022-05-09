#pragma once

//---------------------------------------------------------------------

DECLARE_HOOK_PROC(HRSRC, WINAPI, FindResourceA, (HMODULE module, LPCSTR name, LPCSTR type));
DECLARE_HOOK_PROC(INT_PTR, WINAPI, DialogBoxParamA, (HINSTANCE instance, LPCSTR templateName, HWND parent, DLGPROC dialogFunc, LPARAM initParam));
DECLARE_HOOK_PROC(HWND, WINAPI, CreateDialogParamA, (HINSTANCE instance, LPCSTR templateName, HWND parent, DLGPROC dialogFunc, LPARAM initParam));
DECLARE_HOOK_PROC(BOOL, WINAPI, GetOpenFileNameA, (LPOPENFILENAMEA ofn));
DECLARE_HOOK_PROC(BOOL, WINAPI, GetSaveFileNameA, (LPOPENFILENAMEA ofn));

//---------------------------------------------------------------------
