#include<iostream>
#include"graphMatrix.h"
using namespace std;

int main()
{
	/*
	��������DFS BFS��
	0 3 7 0 0
	3 0 0 8 2
	7 0 0 0 2
	0 8 0 0 1
	0 2 2 1 0
	�������Ե�Դ���·����
	0 50 10 1000 45
	1000 0 15 50 10
	20 1000 0 15 1000
	1000 20 1000 0 35
	1000 1000 1000 30 0
	�����������������
	0 1 1 1 1000
	1000 1000 1000 1000 1000
	1000 1 0 1000 1
	1000 1000 1000 0 1
	1000 1000 1000 1000 1000
	*/
	graphMatrix graphA;
	int Matrix[N][N];
	int tempNum = 0;
	cout << "������" << N << "X" << N << "��С���ٽӾ������������ͼ������" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> tempNum;
			Matrix[i][j] = tempNum;
		}
	}
	//graphA.graphMatrixCreat(Matrix);
	graphA.graphAdjacentListCreat(Matrix);
	//graphA.DFS(0);
	//cout << endl;

	/* ����������̾���
	int distance;
	distance = graphA.miniDistance(1, 5);
	cout << distance;
	*/

	//graphA.BFS(0);
	graphA.TopLogicalSort();
	//graphA.ShortestPath_Dijikstra(1);
}