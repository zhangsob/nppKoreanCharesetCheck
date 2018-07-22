#ifndef ZTEXTFILE_H
#define ZTEXTFILE_H

#include "ZTextLineFile.h"
#include <string>

class ZTextFile : public ZTextLineFile
{
public :
	ZTextFile(const std::string& file) ;
	~ZTextFile() ;

private : 
	ZTextFile(const ZTextFile& file) ;
	ZTextFile& operator=(const ZTextFile& file);

public :	// ZTextLineFile
	std::string GetFullCurrentPath() const ;
	int GetLineCount() const ;
	std::vector<unsigned char> GetLine(int line) const ;

public :
	bool isOK() ;
	bool isEOF() ;
	std::vector<unsigned char> GetLine() ;

private :
	std::string filepath ;
	FILE *fp ;
	mutable std::vector<long> line_positions ;
};
#endif	//ZTEXTFILE_H
