//this file is part of notepad++
//Copyright (C)2003 Don HO <donho@altern.org>
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifndef PLUGINDEFINITION_H
#define PLUGINDEFINITION_H

//
// All difinitions of plugin interface
//
#include "PluginInterface.h"

#define TITLE "Korean Charset Check"
#define NPP_UNKOWN_CHARSET_DEFAULT_UTF8_BUG_FIX	// EUC-KR(MS949)�� UTF-8(Default)ó���ϴ� Bug Fix�� �־� FileBase�� ����ó���ϴ� Logic�߰�.
#ifdef NPP_UNKOWN_CHARSET_DEFAULT_UTF8_BUG_FIX
#define NUM_FUNC	17
#else
#define NUM_FUNC	14
#endif

//-------------------------------------//
//-- STEP 1. DEFINE YOUR PLUGIN NAME --//
//-------------------------------------//
// Here define your plugin name
//
const TCHAR NPP_PLUGIN_NAME[] = TEXT(TITLE);

//-----------------------------------------------//
//-- STEP 2. DEFINE YOUR PLUGIN COMMAND NUMBER --//
//-----------------------------------------------//
//
// Here define the number of your plugin commands
//
const int nbFunc = NUM_FUNC;


//
// Initialization of your plugin data
// It will be called while plugin loading
//
void pluginInit(HANDLE hModule);

//
// Cleaning of your plugin
// It will be called while plugin unloading
//
void pluginCleanUp();

//
//Initialization of your plugin commands
//
void commandMenuInit();

//
//Clean up your plugin commands allocation (if any)
//
void commandMenuCleanUp();

//
// Function which sets your command 
//
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk = NULL, bool check0nInit = false);

//
// Your plugin command functions
//
void KoreanCharsetCheck();

void AsciiCheck();
void EUCKRCheck();
void CP949Check();
void UTF8_Check();

#if defined(NPP_UNKOWN_CHARSET_DEFAULT_UTF8_BUG_FIX)
void FileBaseEUCKRCheck();
void FileBaseCP949Check();
void FileBaseUTF8_Check();
#endif

void AsciiTable();
void EUCKRTable();
void CP949Table();
void UnicodeTable();
void UTF8Table();

void KCC_About() ;
//void hello();
//void helloDlg();

#endif //PLUGINDEFINITION_H
