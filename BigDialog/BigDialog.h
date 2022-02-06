#pragma once

//---------------------------------------------------------------------
// Define

#define DECLARE_INTERNAL_PROC(resultType, callType, procName, args) \
	typedef resultType (callType *Type_##procName) args; \
	Type_##procName procName = NULL

#define DECLARE_HOOK_PROC(resultType, callType, procName, args) \
	typedef resultType (callType *Type_##procName) args; \
	extern Type_##procName true_##procName; \
	resultType callType hook_##procName args

#define IMPLEMENT_HOOK_PROC(resultType, callType, procName, args) \
	Type_##procName true_##procName = procName; \
	resultType callType hook_##procName args

#define IMPLEMENT_HOOK_PROC_NULL(resultType, callType, procName, args) \
	Type_##procName true_##procName = NULL; \
	resultType callType hook_##procName args

#define GET_INTERNAL_PROC(module, procName) \
	procName = (Type_##procName)::GetProcAddress(module, #procName)

#define GET_HOOK_PROC(module, procName) \
	true_##procName = (Type_##procName)::GetProcAddress(module, #procName)

#define ATTACH_HOOK_PROC(name) DetourAttach((PVOID*)&true_##name, hook_##name)

//---------------------------------------------------------------------
// Api Hook

DECLARE_HOOK_PROC(HRSRC, WINAPI, FindResourceA, (HMODULE module, LPCSTR name, LPCSTR type));
DECLARE_HOOK_PROC(INT_PTR, WINAPI, DialogBoxParamA, (HINSTANCE instance, LPCSTR templateName, HWND parent, DLGPROC dialogFunc, LPARAM initParam));
DECLARE_HOOK_PROC(HWND, WINAPI, CreateDialogParamA, (HINSTANCE instance, LPCSTR templateName, HWND parent, DLGPROC dialogFunc, LPARAM initParam));
DECLARE_HOOK_PROC(BOOL, WINAPI, GetOpenFileNameA, (LPOPENFILENAMEA ofn));
DECLARE_HOOK_PROC(BOOL, WINAPI, GetSaveFileNameA, (LPOPENFILENAMEA ofn));

//---------------------------------------------------------------------
