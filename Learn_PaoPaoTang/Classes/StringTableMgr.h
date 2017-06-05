#ifndef _STRING_TABLE_MGR_
#define _STRING_TABLE_MGR_
#include"tinyxml.h"
#include<assert.h>
#include<map>
#include<string>
using namespace std;

class StringTableMgr
{
private:
	StringTableMgr(){}
	static void init(map<string,string>& StringTable)
	{
		
		TiXmlDocument doc;
		bool loaded = doc.LoadFile("Config/StringTable.xml");
		assert(loaded == true);
		auto element = doc.RootElement()->FirstChildElement();
		while (element != NULL)
		{
			auto pKey = element->Attribute("key");
			auto pText = element->Attribute("text");
			StringTable.insert(make_pair(pKey, pText));
			element = element->NextSiblingElement();
		}
	}
public:
	static string getString(string key)
	{
		static map<string, string> StringTable;
		if (StringTable.size() == 0)
			init(StringTable);
		map<string, string>::iterator it = StringTable.find(key);
		if (it != StringTable.end())
			return StringTable[key];
		else
			return "";
	}
};

#endif // !_STRING_TABLE_MGR_
