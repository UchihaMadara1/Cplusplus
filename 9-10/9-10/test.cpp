#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<string>

using namespace std;

//三角矩阵最短路径
//class Solution {
//public:
//	int minimumTotal(vector<vector<int> > &triangle) {
//		if (triangle.empty())
//			return 0;
//		vector<vector<int>> sum_size(triangle);
//		for (int i = triangle.size() - 2; i >= 0; --i)
//		{
//			for (int j = 0; j <= i; ++j)
//			{
//				sum_size[i][j] = min(sum_size[i + 1][j], sum_size[i + 1][j + 1]);
//				sum_size[i][j] += triangle[i][j];
//			}
//		}
//		return sum_size[0][0];
//	}
//};
//class Solution {
//public:
//	int minimumTotal(vector<vector<int> > &triangle) {
//		if (triangle.empty())
//			return 0;
//		vector<vector<int>> sum_size(triangle);
//		int line = triangle.size();
//		for (int i = 1; i < line; ++i)
//		{
//			for (int j = 0; j <= i; ++j)
//			{
//				if (j == 0)
//				{
//					sum_size[i][j] = sum_size[i - 1][j];
//				}
//				else if (i == j)
//				{
//					sum_size[i][j] = sum_size[i - 1][j - 1];
//				}
//				else
//				{
//					sum_size[i][j] = min(sum_size[i - 1][j], sum_size[i - 1][j - 1]);
//				}
//				sum_size[i][j] += triangle[i][j];
//			}
//		}
//		int result = sum_size[line - 1][0];
//		for (int i = 0; i < line; ++i)
//		{
//			result = min(sum_size[line - 1][i], result);
//		}
//		return result;
//	}
//};


class Solution {
public:
	/**
	*
	* @param m int整型
	* @param n int整型
	* @return int整型
	*/
	int uniquePaths(int m, int n) {
		// write code here
		if (m < 1 || n < 1)
			return 0;
		vector<vector<int>> sum(m, vector<int>(n, 1));
		for (int i = 1; i < m; ++i)
		{
			for (int j = 1; j < n; ++j)
			{
				sum[i][j] = sum[i - 1][j] + sum[i][j - 1];
			}
		}
		return sum[m - 1][n - 1];
	}
};
int main()
{
	Solution s;
	int ret = s.uniquePaths(3,7);
	cout << ret << endl;
	return 0;
}