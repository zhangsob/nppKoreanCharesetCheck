#ifndef ZNPP_H
#define ZNPP_H

#include "PluginInterface.h"
#include <string>
#include "ZTextFile.h"

class ZNpp : public ZTextLineFile
{
private :
		ZNpp();
public :
#if defined(SCINTILLA_H)
		ZNpp(NppData nppData);
		
		void						NewFile() ;
		int							GetCodePage() const ;
		void						ToAnsi() ;
		void						ToUTF8() ;
		std::string					GetFullCurrentPath() const ;
		int							GetLineCount() const ;
		std::vector<unsigned char>	GetLine(int line) const ;
		void						AddText(const std::string& text) ;
		void						GotoLine(int line) ;
		void						SetSel(int anchor, int caret) ;

		void						AnnotationClearAll() const ;
		void						Annotation(int line, const std::string& annotation) ;
		void						Annotation(COLORREF fore, COLORREF back, int line, const std::string& annotation) ;
		void						Annotation(COLORREF fore, COLORREF back, int line, const std::string& annotation, const std::pair<int, int>& color_indexes) ;
		void						Annotation(COLORREF fore, COLORREF back, int line, const std::string& annotation, const std::vector<std::pair<int, int>>& color_indexes) ;
#endif

#if defined(SCINTILLA_H)
private :
	HWND	GetCurrentScintilta() const ;
	void	ClearCash() const ;

private :
	mutable int		_encoding ;
	mutable int		_line_count ;
	mutable HWND	_scintilla ;
			NppData _nppData;
#endif
};
#endif	//#ifndef ZNPP_H