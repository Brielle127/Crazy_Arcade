#ifndef _ITEM_CONFIG_H_
#define _ITEM_CONFIG_H_

#include "cocos2d.h"
USING_NS_CC;

#include "BaseDef.h"
#include "tinyxml.h"
#include <vector>
#include <string>
using namespace std;

struct ItemInfo
{
	ItemType type;
	int templateId;
	string group;
	string ani;
	int popoNum;
	int popoStr;
	int roleSpeed;
	bool canKick;
	string rideGroup;
};


typedef map<int, ItemInfo> TItemInfoMap;  // ID->ItemInfo
class ItemInfoMgr// 管理器
{
public:
	// 加载函数
	static ItemInfo* getItemInfo(int templaterId)
	{
		auto& rMap = getInfoMap();
		if (rMap.size() == 0) {
			load(rMap);
		}
		auto it = rMap.find(templaterId);
		if (it != rMap.end())
			return &it->second;
		return nullptr;
	}
private:
	static void load(TItemInfoMap& t)
	{
		TiXmlDocument doc;
		if (doc.LoadFile("Config/ItemTable.xml")) {
			auto& rMap = getInfoMap();
			auto root = doc.RootElement();
			auto info = root->FirstChildElement();
			while (info)
			{//读取info数据
				auto name = info->Attribute("type");
				static char* TypeTable[] = { "normal","ride" };
				static int len = sizeof(TypeTable) / sizeof(TypeTable[0]);
				int i = 0;

				for (; i < len; ++i) {
					if (strcmp(TypeTable[i], name) == 0)
						break;
				}
				if (i < len) {

					int tid = atoi(info->Attribute("templateId"));

					rMap.insert(make_pair(tid, ItemInfo()));
					auto& rInfo = rMap[tid];

					rInfo.templateId = tid;
					rInfo.type = ItemType(i);
					rInfo.group = info->Attribute("group");
					rInfo.ani = info->Attribute("ani");
					rInfo.popoNum = atoi(info->Attribute("popo_num"));
					rInfo.popoStr = atoi(info->Attribute("popo_str"));
					rInfo.roleSpeed = atoi(info->Attribute("role_speed"));
					rInfo.canKick = atoi(info->Attribute("kick_popo")) != 0;
					rInfo.rideGroup = info->Attribute("ride_group");
					//rInfo.isFlying = atoi(info->Attribute("fly")) != 0;
				}
				info = info->NextSiblingElement();
			}
		}
	}
	static TItemInfoMap& getInfoMap()
	{
		static TItemInfoMap tMap;
		return tMap;
	}
};
#endif 