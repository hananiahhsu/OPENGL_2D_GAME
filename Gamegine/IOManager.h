#pragma once

//#include<string>
#include<vector>

namespace Gamegine {
	class IOManager
	{
	public:
		//static function anouncement or statement
		static bool readFileToBuffer(const std::string& filePath, std::vector<unsigned char>& buffer);



	};
}

