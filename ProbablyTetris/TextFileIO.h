#pragma once
#include <fstream>
#include <iostream>
#include <string>

class TextFileIO
{
public:
	static void WriteToTextFile(const std::string& fileName, const std::string& content)
	{
		std::ofstream outFile(fileName);
		if (outFile.is_open())
		{
			outFile << content;
			outFile.close();
		}
		return;
	}

	static std::string ReadFromTextFile(const std::string& fileName)
	{
		std::ifstream inFile(fileName);
		std::string fileContent = "0";
		if (inFile.is_open())
		{
			std::getline(inFile, fileContent);
			inFile.close();
		}
		return fileContent;
	}

	static bool FileExists(const std::string& fileName)
	{
		std::ifstream inFile(fileName);
		return inFile.good();
	}
};

