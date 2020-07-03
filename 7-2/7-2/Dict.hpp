#pragma once

#include<string>
#include<unordered_map>


class Dict
{
public:
	Dict()
	{
		dict.insert({
			{ "apple", "苹果" },
			{ "apricot", "杏子" },
			{ "banana", "香蕉" },
			{ "flowering crab", "海棠果" },
			{ "orange", "橙子" },
			{ "blackberry", "黑莓" },
			{ "carambola", "杨桃" },
			{ "cherry", "樱桃" },
			{ "chestnut", "栗子" },
			{ "coconut", "椰子" },
			{ "date", "枣" },
			{ "fig", "无花果" },
			{ "filbert", "榛子" },
			{ "peach", "桃子" },
			{ "gingko", "银杏" },
			{ "kumquat", "金柑" },
			{ "lemon", "柠檬" },
			{ "litchi", "荔枝" },
			{ "longan", "桂圆" },
			{ "mango", "芒果" },
			{ "morello", "黑樱桃" },
			{ "muskmelon", "香瓜" },
			{ "nut", "坚果" },
			{ "olive", "橄榄" },
			{ "papaya", "木瓜" },
			{ "pear", "梨" },
			{ "pineapple", "菠萝" },
			{ "plum", "李子" },
			{ "pomegranate", "石榴" },
			{ "pomelo", "柚子" },
		});
	}
	std::string Search(const std::string &k)
	{
		std::unordered_map<std::string, std::string>::const_iterator it = dict.find(k);
		if (it == dict.end())
			return "找不到";
		return it->second;
	}
	~Dict()
	{}
private:
	std::unordered_map<std::string, std::string> dict;
};
