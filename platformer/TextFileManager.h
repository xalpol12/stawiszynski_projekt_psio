#pragma once
class TextFileManager
{
private:


public:
	TextFileManager();
	~TextFileManager();

	void saveToFile(int points_, std::string filePath_);
	void readFromFile();
};

