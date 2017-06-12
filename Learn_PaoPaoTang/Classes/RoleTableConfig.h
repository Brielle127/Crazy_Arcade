#ifndef _ROLE_TABLE_CONFIG_H_
#define _ROLE_TABLE_CONFIG_H_

#include "cocos2d.h"
USING_NS_CC;

#include "BaseDef.h"
#include "tinyxml.h"
#include <vector>
#include <string>
using namespace std;

struct RoleInfo
{
	int templateId;
	string group;
	int min_speed;
	int max_speed;
	int original_speed;
	int min_str;
	int max_str;
	int original_str;
	int min_popo_num;
	int max_popo_num;
	int original_popo_num;
};

typedef map<int, RoleInfo> TRoleInfoMap;  // ID->RoleInfo
class RoleInfoMgr// 管理器
{
public:
	// 加载函数
	static RoleInfo* getRoleInfo(int templaterId)
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
	static void load(TRoleInfoMap& t)
	{
		TiXmlDocument doc;
		if (doc.LoadFile("Config/RoleTable.xml")) {
			auto& rMap = getInfoMap();
			auto root = doc.RootElement();
			auto info = root->FirstChildElement();
			while (info)
			{
				//读取info数据
				int tid = atoi(info->Attribute("template_id"));
				auto& rInfo = rMap[tid];
				
				// placement new.
				new (&rInfo)RoleInfo();  // 手动构造

				rInfo.templateId = tid;
				rInfo.group = info->Attribute("group");
				rInfo.min_speed = atoi(info->Attribute("min_speed"));
				rInfo.max_speed = atoi(info->Attribute("max_speed"));
				rInfo.original_speed = atoi(info->Attribute("original_speed"));
				rInfo.min_str = atoi(info->Attribute("min_str"));
				rInfo.max_str = atoi(info->Attribute("max_str"));
				rInfo.original_str = atoi(info->Attribute("original_str"));
				rInfo.min_popo_num = atoi(info->Attribute("min_popo_num"));			
				rInfo.max_popo_num = atoi( info->Attribute("max_popo_num"));
				rInfo.original_popo_num = atoi(info->Attribute("original_popo_num"));
				
				info = info->NextSiblingElement();
			}
		}
	}
	
	static TRoleInfoMap& getInfoMap()
	{
		static TRoleInfoMap tMap;
		return tMap;
	}
};
#endif // !_ITEM_CONFIG_H
