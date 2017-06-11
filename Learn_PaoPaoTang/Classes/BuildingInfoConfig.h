#ifndef _BUILDING_INFO_CONFIG_H_
#define _BUILDING_INFO_CONFIG_H_

#include "cocos2d.h"
USING_NS_CC;

#include <string>
#include <vector>
#include <map>
using namespace std;

#include "tinyxml.h"

// 部件信息
struct PartInfo
{
	string name;
	string aniName;
	string group;
	Point offset;
};
struct BuildingInfo
{
	string name;
	vector<PartInfo> partInfo;
	int barrierX;// 横向阻挡
	int barrierY;// 纵向阻挡
	bool isDestroyEnable; // 是否可摧毁
};

typedef map<string, BuildingInfo> TBuildingInfoMap; 
// 管理器
class BuildingInfoMgr
{
public:
	static BuildingInfo* getBuildingInfo(const char* name)
	{
		auto& rMap = getInfoMap();
		if (rMap.size()==0) {
			load(rMap);
		}
		auto it = rMap.find(name);
		if (it != rMap.end())
			return &it->second;
		return nullptr;
	}
private:
	// 加载函数
	static void load(TBuildingInfoMap& t)
	{
		TiXmlDocument doc;
		if (doc.LoadFile("Config/BuildingInfoTable.xml")) {
			auto root = doc.RootElement();
			auto info = root->FirstChildElement();
			while(info)
			{//读取info数据
				auto name = info->Attribute("name");
				t[name] = BuildingInfo();
				auto& rInfo = t[name];
				rInfo.name = name;
				rInfo.barrierX = atoi(info->Attribute("barrierX"));
				rInfo.barrierY = atoi(info->Attribute("barrierY"));
				rInfo.isDestroyEnable = atoi(info->Attribute("destroy")) != 0;
				auto part = info->FirstChildElement();

				while (part)
				{// 读取part数据
					rInfo.partInfo.push_back(PartInfo());
					auto& rPart = rInfo.partInfo[rInfo.partInfo.size() - 1];
					rPart.aniName = part->Attribute("ani");
					rPart.group = part->Attribute("group");
					rPart.name = part->Attribute("name");
					rPart.offset.x = atoi(part->Attribute("offsetX"));
					rPart.offset.y = atoi(part->Attribute("offsetY"));
					
					part = part->NextSiblingElement();
				}
				info = info->NextSiblingElement();
			}
		}
	}
	static TBuildingInfoMap& getInfoMap()
	{
		static TBuildingInfoMap tMap;
		return tMap;
	}
};

#endif // !_BUILDING_INFO_CONFIG_H_
