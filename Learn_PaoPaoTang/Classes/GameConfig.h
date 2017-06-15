#ifndef _GAME_CONFIG_H_
#define _GAME_CONFIG_H_

#include <map>
#include <string>
using namespace std;
#include "tinyxml.h"
class GameConfig
{
	static void load()
	{
		TiXmlDocument doc;
		if (doc.LoadFile("Config/GameConfig.xml")) {
			auto& tMap = getMap();
			auto root = doc.RootElement();
			auto conf = root->FirstChildElement();
			while (conf) {
				auto pKey = conf->Value();
				auto pValue = conf->GetText();
				tMap[pKey] = pValue;
				conf = conf->NextSiblingElement();
			}
		}
	}
	static 	map<string, string>& getMap()
	{
		static map<string, string> map_;
		return map_;
	}
public:
	static const char* getInfo(const char* pKey)
	{
		map<string, string>& tMap = getMap();
		if (tMap.size() == 0) {
			load();
		}
		auto it = tMap.find(pKey);
		if (it != tMap.end()) {
			return it->second.c_str();
		}
		return nullptr;
	}
};

#endif // !_GAME_CONFIG_H_
