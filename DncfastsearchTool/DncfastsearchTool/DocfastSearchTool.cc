#define _CRT_SECURE_NO_WARNINGS

#include "Common.h"
#include "SySutil.h"

#include "DataManager.h"
#include "ScanManager.h"
#include "Sysframe.h"

#include <vld.h>

char *title = "极限搜索";

int main(int argc,char *argv[])
{
	const string &path = "C:\\Users\\Administrator\\Desktop\\Test";
	//创建扫描实例
	//ScanManager::CreateInstance(path).ScanDirectory(path);
	ScanManager::CreateInstance(path);
	//创建搜索实例
	DataManager &dm = DataManager::Getinstance();
	string key;
	vector<pair<string, string>> doc_path;
	while (true)
	{
		DrawFrame(title);
		DrawMenu();
		cin >> key;
		if (key == "exit")
			break;
		dm.Search(key,doc_path);

		int init_row = 5;
		int count = 0;
		string prefix, highlight, suffix;
		for (const auto &e : doc_path)
		{
			string doc_name = e.first;
			string doc_path = e.second;

			DataManager::SplitHighlight(doc_name, key, prefix, highlight, suffix);

			SetCurPos(2, init_row + count++);
			//printf("%-31s", prefix.c_str());
			cout << prefix;
			ColourPrintf(highlight.c_str());
			cout << suffix;

			SetCurPos(33, init_row + count - 1);
			printf("%-50s", doc_path.c_str());
			//printf("%-31s%-50s\n",e.first.c_str(), e.second.c_str());
		}
		SystemEnd();
		system("pause");
	}
	SystemEnd();
	return 0;
}


//静态库


int sqlite3_get_table(
	sqlite3 *db,          /* An open database */
	const char *zSql,     /* SQL to be evaluated */
	char ***pazResult,    /* Results of the query */
	int *pnRow,           /* Number of result rows written here */
	int *pnColumn,        /* Number of result columns written here */
	char **pzErrmsg       /* Error msg written here */
	);
void sqlite3_free_table(char **result);
void Test_Sqlite()
{
	//创建数据库
	sqlite3 *db;
	int rc = sqlite3_open("test.db", &db);
	if (rc != SQLITE_OK)
	{
		cout << "open database is failed!" << endl;
	}
	else
	{
		cout << "open database is successfally" << endl;
	}
	//操作数据库
	string sql = "select * from doc_db";
	char **result;
	int row;
	int col;
	char *zErrMsg = 0;
	rc = sqlite3_get_table(db,sql.c_str(),&result,&row,&col,&zErrMsg);

	for (int i = 0; i <= row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			//cout << *(result + (i * col) + j) << " ";
			printf("%s ", *(result + (i * col) + j));
		}
		cout << endl;
	}
	sqlite3_free_table(result);
	//关闭数据库
	sqlite3_close(db);
}
void Test_SqliteManager()
{
	SqliteManager sm;
	sm.Open("test.db");

	/*string sql = "create table if not exists doc_db(id integer primary key autoincrement, name text, path text)";
	sm.ExcuteSql(sql);
	string sql1 = "insert into doc_db values(1,'bss.text','c:\\')";
	string sql2 = "insert into doc_db values(NULL,'nxz.text','d:\\')";
	sm.ExcuteSql(sql1);
	sm.ExcuteSql(sql2);*/
	string sql = "select * from doc_db";
	int row = 0, col = 0;
	char **ppRet = 0;
	sm.GetResultTable(sql,row,col,ppRet);
	for (int i = 0; i <= row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			printf("%-10s",*(ppRet + (i * col) + j));
		}
		cout << endl;
	}
	sqlite3_free_table(ppRet);
}
void Test_Log()
{
	FILE *fp = fopen("Test.txt","w");
	if (fp == NULL)
	{
		//__TraceDebug(const char* filename, int line, const char* function,
		//const char* format, ...)
		//__TraceDebug(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__);
		TRACE_LOG("open test.txt failed...");
		return;
	}
	else
	{
		//__ErrorDebug(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__);
		TRACE_LOG("open test.txt successfully...");
	}
	fclose(fp);
}
void Test_Set()
{
	vector<int> v = {2,3,5,1,9,7,4,10,6,8};
	set<int> s;
	s.insert(v.begin(),v.end());
	for (auto &e : s)
	{
		cout << e <<" ";
	}
	cout << endl;

	s.erase(5);

	for (auto &e : s)
	{
		cout << e << " ";
	}
	cout << endl;
}
void Test_Map()
{
	pair<int, string> p1 = { 1, "abc" };
	pair<int, string> p2 = { 6, "dfg" };
	pair<int, string> p3 = { 4, "rgb" };
	pair<int, string> p4 = { 3,  "wdf"};
	pair<int, string> p5 = { 2, "uhg" };
	pair<int, string> p6 = { 5, "nht" };

	map<int, string> mp;
	mp.insert(p1);
	mp.insert(p2);
	mp.insert(p3);
	mp.insert(p4);
	mp.insert(p5);
	mp.insert(p6);

	for (auto &e : mp)
	{
		cout << e.first << " : " << e.second;
		cout << endl;
	}
}
void Test_Scan()
{
	//const string &path = "D:\\git上传目录\\DncfastsearchTool\\DncfastsearchTool";
	const string &path = "C:\\Users\\Administrator\\Desktop\\Test";
	
	ScanManager &sm = ScanManager::CreateInstance(path);
	
	sm.ScanDirectory(path);
}
void Test_Search()
{
	const string &path = "C:\\Users\\Administrator\\Desktop\\Test";
	//创建扫描实例

	//ScanManager sm;
	//sm.ScanDirectory(path);
	ScanManager &sm = ScanManager::CreateInstance(path);
	sm.ScanDirectory(path);
	//创建搜索实例
	DataManager &dm = DataManager::Getinstance();

	string key;
	vector<pair<string, string>> doc_path;
	while (true)
	{
		cout << "请输入要搜索的关键字：>";
		cin >> key;
		dm.Search(key,doc_path);

		//显示结果
		printf("%-15s%-50s\n","名称","路径");
		for (auto &e : doc_path)
			printf("%-15s%-50s\n", e.first.c_str(), e.second.c_str());
	}
}
void Test_ChineseConvert()
{
	string str = "比特科技";
	string pinyin = ChineseConvertPinYinAllSpell(str);
	cout << "pinyin = " << pinyin << endl;

	string initials = ChineseConvertPinYinInitials(str);
	cout << "initials = " << initials << endl;
}
//void Test_Frame()
//{
//	//system("mode con cols=60 lines=10");
//	//SetCurPos(4,(60 - strlen("hello bit..."))/2);
//	//printf("hello bit...\n");
//	char *title = "文档搜索神器";
//	DrawFrame(title);
//}
//void main()
//{
//	//Test_Search();
//	//Test_ChineseConvert();
//	Test_Frame();
//}
//void Thread_fun(int n)
//{
//	for (int i = 0; i < n; ++i)
//	{
//		cout << "This is Child thread" << endl;
//	}
//}
//void Test_Thread()
//{
//	int n = 2;
//	thread th(Thread_fun,n);
//	th.detach();
//	for (int i = 0; i < 10; ++i)
//	{
//		cout << "This is Main thread" << endl;
//	}
//	//th.join();
//}
//int main(int argc, char *argv[])
//{
//	//Test_Log();
//	//Test_Sqlite();
//	//Test_SqliteManager();
//	//Test_Set;
//	//Test_Map();
//	//Test_Scan();
//	//Test_Search();
//	Test_Thread();
//
//	return 0;
//}
//void Test_DirectionList()
//{
//	const string &path = "D:\\我的文档\\Tencent Files\\1374638229\\QQ";
//	vector<string> subfile, subdir;
//	DirectionList(path,subfile,subdir);
//	for (auto &e : subfile)
//		cout << e << endl;
//	cout << "dir>" << endl;
//	for (auto &e : subdir)
//		cout << e << endl;
//}
//void Test_Sql()
//{
//	sqlite3 *db;
//	char *zErrMsg = 0;
//	int rc;
//
//	rc = sqlite3_open("test.db", &db);
//
//	if (rc){
//		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
//		exit(0);
//	}
//	else{
//		fprintf(stderr, "Opened database successfully\n");
//	}
//	sqlite3_close(db);
//}
//static int callback(void *data, int argc, char **argv, char **azColName)
//{
//	int i;
//	fprintf(stderr, "%s: \n", (const char*)data);
//	for (i = 0; i<argc; i++){
//		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//	}
//	printf("\n");
//	return 0;
//}
//void Test_Sqlite()
//{
//	//创建数据库
//	sqlite3 *db;
//	int rc = sqlite3_open("test.db",&db);
//	if (rc != SQLITE_OK)
//	{
//		cout << "open database is failed!" << endl;
//	}
//	else
//	{
//		cout << "open database is successfally" << endl;
//	}
//	//操作数据库
//	//string sql = "create table doc_db(id integer primary key autoincrease,name varchar(20),path varchar(100))";
//	//string sql = "insert into doc_db values(NULL,'xyz','d:\\')";
//	string sql = "select * from doc_db";
//	char *zErrmgz = 0;
//	const char* data = "Callback function called";
//	//sqlite3_exec(sqlite3*, const char *sql, sqlite_callback, void *data, char **errmsg)
//	//rc = sqlite3_exec(db,sql.c_str(),0,0,&zErrmgz);
//	rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrmgz);//callback-》回调函数
//
//	if (rc != SQLITE_OK)
//	{
//		fprintf(stderr,"SQL error: %s\n",zErrmgz);
//		sqlite3_free(zErrmgz);
//	}
//	else
//	{
//		//fprintf(stdout,"create table successfully\n");
//		fprintf(stdout, "progrmme run successfully\n");
//		
//	}
//	sqlite3_close(db);
//}
//int main(int argc,char *argv[])
//{
//	//Test_DirectionList();
//	//Test_Sql();
//	Test_Sqlite();
//	return 0;
//}
