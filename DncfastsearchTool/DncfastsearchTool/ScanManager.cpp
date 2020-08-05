#define _CRT_SECURE_NO_WARNINGS

#include "ScanManager.h"
#include "SySutil.h"

size_t g_FileCount = 0;
size_t g_ScanCount = 0;

ScanManager::ScanManager()
{}

void ScanManager::StartScan(const string &path)
{
	while (true)
	{
		//�ȴ�������ɨ��
		//this_thread::sleep_for(chrono::seconds(3));
		unique_lock<mutex> lock(m_mutex);
		m_cond.wait(lock);
		ScanDirectory(path);
	}
}

void ScanManager::StartWatch(const string &path)
{
	g_FileCount = GetFileCount(path);
	while (1)
	{
		this_thread::sleep_for(chrono::seconds(3));
		g_ScanCount = 0;
		bool ischange = DirectoryWatch(path);
		if (ischange)
		{
			m_cond.notify_one();
			g_FileCount = g_ScanCount;
		}
	}
}

ScanManager& ScanManager::CreateInstance(const string &path)
{
	static ScanManager inst;

	thread Scan_thread(&StartScan,&inst,path);
	Scan_thread.detach();

	thread Watch_thread(&StartWatch,&inst,path);
	Watch_thread.detach();

	return inst;
}
void ScanManager::ScanDirectory(const string &path)
{
	//ɨ�豾���ļ�ϵͳ

	vector <string> local_files;
	vector <string> local_dirs;
	DirectionList(path,local_files,local_dirs);
	set<string> local_set;
	local_set.insert(local_dirs.begin(),local_dirs.end());
	local_set.insert(local_files.begin(),local_files.end());
	//ɨ�����ݿ��ļ�ϵͳ
	DataManager &m_db = DataManager::Getinstance();
	multiset<string> db_set;
	m_db.GetDocs(path,db_set);     //?����
	//�����ݿ��õ���������

	//�Աȱ����ļ������ݿ��ļ�

	auto local_it = local_set.begin();
	auto db_it = db_set.begin();
	while (local_it != local_set.end() && db_it != db_set.end())
	{
		if (*local_it < *db_it)
		{
			//�����ļ����ڣ����ݿ��ļ������ڣ����ݿ������ļ�
			m_db.InsertDoc(path,*local_it);
			local_it++;
		}
		else if (*local_it > *db_it)
		{
			//�����ļ������ڣ����ݿ��ļ����ڣ����ݿ�ɾ���ļ�
			m_db.DeleteDoc(path,*db_it);
			db_it++;
		}
		else
		{
			//�����ļ����ڣ����ݿ��ļ����ڣ����ݿⲻ��
			local_it++;
			db_it++;
		}
	}
	while (local_it != local_set.end())
	{
		//�����ļ����ڣ����ݿ��ļ������ڣ����ݿ������ļ�
		m_db.InsertDoc(path,*local_it);
		local_it++;
	}
	while (db_it != db_set.end())
	{
		//�����ļ������ڣ����ݿ��ļ����ڣ����ݿ�ɾ���ļ�
		m_db.DeleteDoc(path,*db_it);
		db_it++;
	}
	//�ݹ������Ŀ¼
	for (auto &dir : local_dirs)
	{
		string dir_path = path;
		dir_path += "\\";
		dir_path += dir; //������һ��Ŀ¼�µ��ļ�
		ScanDirectory(dir_path);
	}
}
