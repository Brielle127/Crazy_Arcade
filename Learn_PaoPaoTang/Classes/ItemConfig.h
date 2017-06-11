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
	string group;
	string ani;
	int speed;
	bool fly;    // 坐骑
	vector<ItemPropInfo> props;
};

struct ItemPropInfo
{
	ItemPropType type;
	string group;
	string ani;
	string name;
	int value;
};

typedef map<ItemType, ItemInfo> TItemInfoMap;
// 管理器
class ItemInfoMgr
{
public:
	// 加载函数
	static ItemInfo* getItemInfo(ItemType type)
	{
		auto& rMap = getInfoMap();
		if (rMap.size() == 0) {
			load(rMap);
		}
		auto it = rMap.find(type);
		if (it != rMap.end())
			return &it->second;
		return nullptr;
	}
private:
	static void load(TItemInfoMap& t)
	{
		TiXmlDocument doc;
		if (doc.LoadFile("Config/ItemInfoTable.xml")) {
			auto root = doc.RootElement();
			auto info = root->FirstChildElement();
			while (info)
			{//读取info数据
				auto name = info->Attribute("type");
				static char* TypeTable[] = { "popo","str_water","roller_skates","sport_shoe","red_evil","ride" };
				static int len = sizeof(TypeTable) / sizeof(TypeTable[0]);
				size_t i = 0;

				for (; i < len; ++i) {
					if (strcmp(TypeTable[i], name) == 0)
						break;
				}
				if (i <= len)
				{
					ItemType type = ItemType(i);
					t[type] = ItemInfo();
					auto& rInfo = t[type];
					rInfo.type = type;
					rInfo.group = info->Attribute("group");
					rInfo.ani = info->Attribute("ani");
					auto prop = info->FirstChildElement();
					
					while (prop){
						static char* typeTable[] = {"popo_num","popo_str","speed","move_popo"};
						static int len = sizeof(typeTable) / sizeof(typeTable[0]);
						size_t i = 0;

						for (; i < len; ++i) {
							if (strcmp(typeTable[i], name) == 0)
								break;
						}
						if (i < len) {
							ItemPropType propType = ItemPropType(i);
							rInfo.props.push_back(ItemPropInfo());
							auto& rProp = rInfo.props[rInfo.props.size() - 1];
							switch (propType)
							{
							case IPT_KICK_POPO:
							//case IPT_NUM:
							case IPT_POPO_NUM:
							case IPT_POPO_STR:
							case IPT_PLAYER_SPEED:
							{
								rProp.type = propType;
								rProp.value = atoi(prop->Attribute("value"));
							}
							break;
							}
						}
						prop = prop->NextSiblingElement();
					}
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
#endif // !_ITEM_CONFIG_H
