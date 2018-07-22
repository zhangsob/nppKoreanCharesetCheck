#include "ZNpp.h"
#include <windows.h>
#ifdef _DEBUG
#	include "zutil.h"
#endif

#if defined(SCINTILLA_H)
#include "menuCmdID.h"

ZNpp::ZNpp(NppData nppData)
	: _nppData(nppData), _scintilla(nullptr), _line_count(0), _encoding(0)
{
}

void ZNpp::NewFile()
{
	::SendMessage(_nppData._nppHandle, NPPM_MENUCOMMAND, 0, IDM_FILE_NEW);
	ClearCash() ;
}

std::string ZNpp::GetFullCurrentPath() const
{
	TCHAR path[MAX_PATH] ;
	::SendMessage(_nppData._nppHandle, NPPM_GETFULLCURRENTPATH, 0, (LPARAM)path);	// 얻기.... 다음은.. 현재창의 내용물.. Logging하기..

#ifdef UNICODE
	int encoding = (int)::SendMessage(GetCurrentScintilta(), SCI_GETCODEPAGE, 0, 0);
	char pathA[MAX_PATH];
	WideCharToMultiByte(encoding, 0, path, -1, pathA, MAX_PATH, NULL, NULL);
	return static_cast<std::string>(pathA) ;
#else
	return static_cast<std::string>(path) ;
#endif
}

void ZNpp::ClearCash() const
{
	_scintilla = nullptr ;
	_encoding = 0 ;
	_line_count = 0 ;
}

HWND ZNpp::GetCurrentScintilta() const
{
	if(_scintilla == nullptr) {
		int currentEdit;
		::SendMessage(_nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&currentEdit);
		_scintilla = (currentEdit == 0) ? _nppData._scintillaMainHandle : _nppData._scintillaSecondHandle ;
	}
	return _scintilla ;
}

int ZNpp::GetCodePage() const
{
	if (_encoding == 0) {
		_encoding = (int)::SendMessage(GetCurrentScintilta(), SCI_GETCODEPAGE, 0, 0);
	}
	return _encoding ;
}

void ZNpp::ToAnsi()
{
	::SendMessage(_nppData._nppHandle, NPPM_MENUCOMMAND, 0, IDM_FORMAT_ANSI);
	_encoding = 0 ;
}

void ZNpp::ToUTF8()
{
	::SendMessage(_nppData._nppHandle, NPPM_MENUCOMMAND, 0, IDM_FORMAT_UTF_8);
	_encoding = 0 ;
}

int ZNpp::GetLineCount() const
{
	if(_line_count == 0) {
		_line_count = (int)::SendMessage(GetCurrentScintilta(), SCI_GETLINECOUNT, 0, 0) ;
	}
	return _line_count ;
}

std::vector<unsigned char> ZNpp::GetLine(int line) const
{
	std::vector<unsigned char> ret ;
	if(line < 0)	return ret ;

	if(line < GetLineCount()) {
		int line_text_count = (int)::SendMessage(GetCurrentScintilta(), SCI_LINELENGTH, line, 0);
		if(line_text_count > 0) {
			ret.resize(line_text_count) ;
			::SendMessage(_scintilla, SCI_GETLINE, line, (LPARAM)&ret[0]);
		}
	}

	return ret ;
}

void ZNpp::AddText(const std::string& text)
{
	::SendMessage(GetCurrentScintilta(), SCI_ADDTEXT, text.length(), (LPARAM)text.data()) ;
	_line_count = 0 ;
}

void ZNpp::GotoLine(int line)
{
	::SendMessage(GetCurrentScintilta(), SCI_GOTOLINE, line, 0) ;
}

void ZNpp::SetSel(int anchor, int caret)
{
	::SendMessage(GetCurrentScintilta(), SCI_SETSEL, anchor, caret) ;
}

void ZNpp::AnnotationClearAll() const
{
	::SendMessage(GetCurrentScintilta(), SCI_ANNOTATIONCLEARALL, 0, 0);
}

void ZNpp::Annotation(int line, const std::string& annotation)
{
	if(annotation.length() == 0)	return ;

	::SendMessage(GetCurrentScintilta(), SCI_ANNOTATIONSETVISIBLE, ANNOTATION_BOXED, 0);
	::SendMessage(GetCurrentScintilta(), SCI_ANNOTATIONSETTEXT, line, (LPARAM)annotation.c_str());
}

void ZNpp::Annotation(COLORREF fore, COLORREF back, int line, const std::string& annotation)
{
	if(annotation.length() == 0)	return ;
	Annotation(line, annotation) ;

	::SendMessage(GetCurrentScintilta(), SCI_STYLESETFORE, STYLE_LASTPREDEFINED + 1, fore);
	::SendMessage(GetCurrentScintilta(), SCI_STYLESETBACK, STYLE_LASTPREDEFINED + 1, back);

	std::vector<char> styles ;
	//styles.resize(annotation.length(), STYLE_DEFAULT) ;
	styles.resize(annotation.length(), STYLE_LASTPREDEFINED + 1) ;
	::SendMessage(GetCurrentScintilta(), SCI_ANNOTATIONSETSTYLES, line, (LPARAM)&styles[0]) ;
}

void ZNpp::Annotation(COLORREF fore, COLORREF back, int line, const std::string& annotation, const std::pair<int, int>& color_indexes)
{
	std::vector<std::pair<int, int>> indexes ;
	indexes.push_back(color_indexes) ;
	Annotation(fore, back, line, annotation, indexes) ;
}

void ZNpp::Annotation(COLORREF fore, COLORREF back, int line, const std::string& annotation, const std::vector<std::pair<int, int>>& color_indexes)
{
	if(annotation.length() == 0)	return ;
	Annotation(line, annotation) ;

	::SendMessage(GetCurrentScintilta(), SCI_STYLESETFORE, STYLE_LASTPREDEFINED + 1, fore);
	::SendMessage(GetCurrentScintilta(), SCI_STYLESETBACK, STYLE_LASTPREDEFINED + 1, back);

	std::vector<char> styles ;
	styles.resize(annotation.length(), STYLE_DEFAULT) ;

	for(const auto& indexes : color_indexes) {
		if(indexes.first >= indexes.second)		continue ;
		if(indexes.first >= (int)styles.size())	continue ;
		if(indexes.second > (int)styles.size())	continue ;

		for(int i = indexes.first; i < indexes.second; ++i)
			styles[i] = STYLE_LASTPREDEFINED + 1 ;
	}

	::SendMessage(GetCurrentScintilta(), SCI_ANNOTATIONSETSTYLES, line, (LPARAM)&styles[0]) ;
}
#endif

