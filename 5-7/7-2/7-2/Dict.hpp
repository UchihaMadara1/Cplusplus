#pragma once

#include<string>
#include<unordered_map>


class Dict
{
public:
	Dict()
	{
		dict.insert({
			{ "apple", "ƻ��" },
			{ "apricot", "����" },
			{ "banana", "�㽶" },
			{ "flowering crab", "���Ĺ�" },
			{ "orange", "����" },
			{ "blackberry", "��ݮ" },
			{ "carambola", "����" },
			{ "cherry", "ӣ��" },
			{ "chestnut", "����" },
			{ "coconut", "Ҭ��" },
			{ "date", "��" },
			{ "fig", "�޻���" },
			{ "filbert", "���" },
			{ "peach", "����" },
			{ "gingko", "����" },
			{ "kumquat", "���" },
			{ "lemon", "����" },
			{ "litchi", "��֦" },
			{ "longan", "��Բ" },
			{ "mango", "â��" },
			{ "morello", "��ӣ��" },
			{ "muskmelon", "���" },
			{ "nut", "���" },
			{ "olive", "���" },
			{ "papaya", "ľ��" },
			{ "pear", "��" },
			{ "pineapple", "����" },
			{ "plum", "����" },
			{ "pomegranate", "ʯ��" },
			{ "pomelo", "����" },
		});
	}
	std::string Search(const std::string &k)
	{
		std::unordered_map<std::string, std::string>::const_iterator it = dict.find(k);
		if (it == dict.end())
			return "�Ҳ���";
		return it->second;
	}
	~Dict()
	{}
private:
	std::unordered_map<std::string, std::string> dict;
};
