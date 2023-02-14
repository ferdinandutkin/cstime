// pch.h: это предварительно скомпилированный заголовочный файл.
// Перечисленные ниже файлы компилируются только один раз, что ускоряет последующие сборки.
// Это также влияет на работу IntelliSense, включая многие функции просмотра и завершения кода.
// Однако изменение любого из приведенных здесь файлов между операциями сборки приведет к повторной компиляции всех(!) этих файлов.
// Не добавляйте сюда файлы, которые планируете часто изменять, так как в этом случае выигрыша в производительности не будет.

#ifndef PCH_H
#define PCH_H

// Добавьте сюда заголовочные файлы для предварительной компиляции
#include "framework.h"

#endif //PCH_H
#pragma once
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#else
#ifndef LINUX
#define LINUX
#endif
#ifndef linux
#define linux
#endif
#endif

#ifdef _WIN32
// Used for dll exporting and importing
#define  DLLEXPORT   extern "C" __declspec( dllexport ) 
#define  DLLIMPORT   extern "C" __declspec( dllimport )

// Can't use extern "C" when DLL exporting a class
#define  DLL_CLASS_EXPORT   __declspec( dllexport ) 
#define  DLL_CLASS_IMPORT   __declspec( dllimport )

// Can't use extern "C" when DLL exporting a global
#define  DLL_GLOBAL_EXPORT   extern __declspec( dllexport ) 
#define  DLL_GLOBAL_IMPORT   extern __declspec( dllimport )
#elif defined _LINUX

// Used for dll exporting and importing
#define  DLLEXPORT   extern "C" 
#define  DLLIMPORT   extern "C" 

// Can't use extern "C" when DLL exporting a class
#define  DLL_CLASS_EXPORT   
#define  DLL_CLASS_IMPORT  

// Can't use extern "C" when DLL exporting a global
#define  DLL_GLOBAL_EXPORT   extern
#define  DLL_GLOBAL_IMPORT   extern 
#else
#error "Unsupported Platform."
#endif


#include <wrect.h>
#include <cl_dll.h>
#include <in_defs.h> 
#include <cdll_int.h>
#include <cl_entity.h>
#include <com_model.h>
#include <cvardef.h>
#include <entity_state.h>
#include <entity_types.h>
#include <event_args.h>
#include <net_api.h>
#include <r_studioint.h>
#include <pm_defs.h>
#include <r_efx.h>
#include <com_model.h>
#include <ref_params.h>
#include <studio_event.h>
#include <event_api.h>
#include <screenfade.h>
#include <demo_api.h>
#include <triangleapi.h>
#include <ivoicetweak.h>
#include <con_nprint.h>
//Interfaces
#include <interface.h>
#include <APIProxy.h>