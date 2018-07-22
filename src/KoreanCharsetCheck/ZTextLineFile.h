#ifndef ZTEXTLINEFILE_H
#define ZTEXTLINEFILE_H

#include <vector>
#include <map>

struct ZTextLineFile
{
	enum ZCharSetBytes {
		UnknownCharset	= 0x00,

		Ascii_Charset	= 0x10,
		EUCKR_Charset	= 0x20,
		CP949_Charset	= 0x40,
		UTF8_Charset	= 0x80,

		Ascii_Binary	= 0x10,
		Ascii_1Byte		= (UTF8_Charset | CP949_Charset | EUCKR_Charset | Ascii_Charset | 0x01),
		EUCKR_2Byte		= (CP949_Charset | EUCKR_Charset | 0x02),	// 0xA1 ~ 0xAC, 0xB0 ~ 0xC8, 0xCA ~ 0xFD
		EUCKR_1Byte		= (CP949_Charset | EUCKR_Charset | 0x01),	// 0xA1 ~ 0xFE
		CP949_2Byte		= (CP949_Charset | 0x02),	// 0x81 ~ 0xC6
		CP949_1Byte		= (CP949_Charset | 0x01),	// 0x41 ~ 0x5A, 0x61 ~ 0x7A, 0x81 ~ 0xA0
		UTF8_3Byte		= (UTF8_Charset | 0x03),
		UTF8_2Byte		= (UTF8_Charset | 0x02),
		UTF8_1Byte		= (UTF8_Charset | 0x01),
	};
	static std::string GetName(ZCharSetBytes charset) ;

	virtual std::string	GetFullCurrentPath() const = 0 ;
	virtual int GetLineCount() const = 0 ;
	virtual std::vector<unsigned char> GetLine(int line) const = 0 ;
	
#ifdef _DEBUG
static	std::vector<unsigned char>	GetKoreanCharset(const std::vector<unsigned char>& bytes, unsigned char& checkCharset, bool isLogging) ;
#else
static	std::vector<unsigned char>	GetKoreanCharset(const std::vector<unsigned char>& bytes, unsigned char& checkCharset) ;
#endif
static	std::vector<unsigned char>	GetAscii(const std::vector<unsigned char>& bytes) ;
static	std::vector<unsigned char>	GetEUCKR(const std::vector<unsigned char>& bytes) ;
static	std::vector<unsigned char>	GetCP949(const std::vector<unsigned char>& bytes) ;
static	std::vector<unsigned char>	GetUTF_8(const std::vector<unsigned char>& bytes) ;
static	std::vector<unsigned char>	GetCharset(ZCharSetBytes charset, const std::vector<unsigned char>& bytes) ;

static	std::map<unsigned int, std::string>	GetAsciiTable() ;
static	std::map<unsigned int, std::string>	GetEUCKRTable() ;
static	std::map<unsigned int, std::string>	GetCP949Table() ;
static	std::map<unsigned int, std::string>	GetUnicodeTable() ;
static	std::map<unsigned int, std::string>	GetUTF_8Table() ;
};
#endif 
