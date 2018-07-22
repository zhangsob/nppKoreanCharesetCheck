#include "ZTextFile.h"

ZTextFile::ZTextFile(const std::string& file)
	: fp(nullptr), filepath(file)
{
	fopen_s(&fp, file.c_str(), "rb") ;
}

ZTextFile::~ZTextFile()
{
	if(fp)	fclose(fp) ;
}

bool ZTextFile::isOK()
{
	return fp ? true : false ;
}

bool ZTextFile::isEOF()
{
	if(fp == nullptr)	return true ;
	return feof(fp) ? true : false ;
}

std::vector<unsigned char> ZTextFile::GetLine()
{
	std::vector<unsigned char> ret ;
	if(fp == nullptr)	return ret ;

	for (int ch = 0;(ch = fgetc(fp)) >= 0;) {
		ret.push_back((unsigned char)ch) ;
		if(ch == 0x0A)	break ;
	}

	return ret ;
}

std::string ZTextFile::GetFullCurrentPath() const
{
	return filepath ;
}

/**
	�� ���� ���
	@return �� ������ 1, 0x0A 1 Byte��� 2�̴�. (��, �� �ٵ� ���̸� EOL(End Of Line) �Ǵ� EOF(End Of File)���� ���� �ȴ�.)
*/
int ZTextFile::GetLineCount() const
{
	if (line_positions.empty() && fp) {
		fseek(fp, 0, SEEK_SET) ;
		line_positions.push_back(ftell(fp)) ;
		for(int ch = 0;(ch = fgetc(fp)) >= 0;) {
			if(ch == 0x0A)
				line_positions.push_back(ftell(fp)) ;		
		}
	}

	return (int)line_positions.size() ;
}

std::vector<unsigned char> ZTextFile::GetLine(int line) const
{
	std::vector<unsigned char> ret ;
	if(fp == nullptr)	return ret ;
	if(line < 0)		return ret ;

	if(line_positions.empty())	GetLineCount() ;

	if((size_t)line >= line_positions.size())	return ret ;

	fseek(fp, line_positions[line], SEEK_SET) ;
	for (int ch = 0;(ch = fgetc(fp)) >= 0;) {
		ret.push_back((unsigned char)ch) ;
		if(ch == 0x0A)	break ;
	}

	return ret ;
}
