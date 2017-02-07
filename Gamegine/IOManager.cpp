#include "IOManager.h"

#include<fstream>

namespace Gamegine {
	bool IOManager::readFileToBuffer(const std::string& filePath, std::vector<unsigned char>& buffer)
	{
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail())
		{
			perror(filePath.c_str());
			return false;
		}
		//seek to the end
		file.seekg(0, std::ios::end);

		//get the file size
		int fileSize = file.tellg();
		file.seekg(0, std::ios::beg);//beg means that beginning of the file

		//reduce the file size by any header type that present
		fileSize -= file.tellg();

		//resize the size of file by the length of filesize
		buffer.resize(fileSize);
		file.read((char *)&(buffer[0]), fileSize);//buffer[0]---> the first element of memory array
		file.close();//at the end of operation,the file must be closed

		return true;
	}


}

