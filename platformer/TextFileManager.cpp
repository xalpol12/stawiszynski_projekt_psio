#include "stdafx.h"
#include "TextFileManager.h"

TextFileManager::TextFileManager()
{

}

TextFileManager::~TextFileManager()
{
}

void TextFileManager::saveToFile(int points_, std::string filePath_)
{
	std::ofstream out_file;

	out_file.open(filePath_, std::ios_base::app | std::ios_base::out);
	if (out_file.is_open())
	{
		out_file << points_ << std::endl;
		out_file.close();
	}
}

void TextFileManager::readFromFile()
{
}
