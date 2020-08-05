#pragma once

#include "Common.h"
#include "DataManager.h"

class ScanManager
{
public:
	void ScanDirectory(const string &path);
	void StartScan(const string &path);
	void StartWatch(const string &path);
public:
	static ScanManager& CreateInstance(const string &path);
private:
	ScanManager();
private:
	//DataManager m_db;
	mutex m_mutex;
	condition_variable m_cond;
};