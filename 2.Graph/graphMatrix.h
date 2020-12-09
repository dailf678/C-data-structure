#include<iostream>
#include<queue>
#include<stack>
#define N 5
#define MAX 1000
using namespace std;
/*
该类除了输出以外数组都是从0开始
! 代表DFS BFS必需的数据
@ 代表单源最短路径必需的数据
# 代表拓扑排序必需的数据
*/
struct ArcNode
{
	int adjvex;
	ArcNode* next;
};
struct VertexNode
{
	int vertex;
	int indegree;
	ArcNode* firstedge;
};
class graphMatrix
{
public:
	void graphMatrixCreat(int matrix[N][N]);
	void graphAdjacentListCreat(int matrix[N][N]);
	int miniDistance(int, int);//寻找图中两点最短距离
	void DFS(int start);
	void BFS(int start);
	void ShortestPath_Dijikstra(int v0);//单源最短路径
	void TopLogicalSort();
private:
	//采用临接矩阵的方法
	int Matrix[N][N];//邻接矩阵 ！@ #
	VertexNode Adjacentlist[N];//临接表 #
	bool visited[N];//记录是否访问过 ！
	bool S[N];//记录源点v0到终点vi是否被确定为最短路径 @
	int D[N];//记录源点v0到终点vi当前最短路径 @
	int Path[N];//记录源点v0到终点vi当前最短路径上vi的直接前驱顶点序号 @
	int INlookForMinimunOfDistance(int, int);
	void INvisitedReset();
};
void graphMatrix::INvisitedReset()
{
	for (int i = 0; i < N; i++)
	{
		visited[i] = false;
	}
}

int miniBet(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}
void graphMatrix::graphMatrixCreat(int matrix[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Matrix[i][j] = matrix[i][j];
		}
	}
	for (int i = 0; i < N; i++)
	{
		visited[i] = false;
	}
}

void graphMatrix::graphAdjacentListCreat(int matrix[N][N])
{
	for (int i = 0; i < N; i++)
	{
		Adjacentlist[i].vertex = i ;
		Adjacentlist[i].firstedge = NULL;
		Adjacentlist[i].indegree = 0;
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (matrix[i][j] != 0 && matrix[i][j] < MAX)//等于1代表他们连通的 且是从i指向j的
			{
				ArcNode* s = new ArcNode;
				s->adjvex = j;
				s->next = Adjacentlist[i].firstedge;
				Adjacentlist[i].firstedge = s;
				Adjacentlist[j].indegree++;
			}
		}
	}
	
}

void graphMatrix::DFS(int v)
{
	visited[v] = true;
	for (int i = 0; i < N; i++)
	{
		if (Matrix[v][i] != 0 && visited[i] == false)
		{
			DFS(i);
		}
	}
	cout << v;
}

void graphMatrix::BFS(int start)
{
	queue<int> Q;
	Q.push(start);
	visited[start] = true;
	while (!Q.empty())
	{
		int front = Q.front();
		cout << front << " ";
		Q.pop();
		for (int i = 0; i < N; i++)
		{
			if (!visited[i] && Matrix[front][i] != 0)
			{
				visited[i] = true;
				Q.push(i);
			}
		}
	}
}

int graphMatrix::miniDistance(int start, int end)
{
	INvisitedReset();
	return INlookForMinimunOfDistance(start - 1, end - 1);
}
int graphMatrix::INlookForMinimunOfDistance(int start, int end)
{
	if (start == end)
	{
		return 0;
	}
	int distance = 0;
	bool isFirst = true;
	visited[start] = true;
	for (int i = 0; i < N; i++)
	{
		if (Matrix[start][i] != 0 && !visited[i])
		{
			if (isFirst == true)
			{
				distance = INlookForMinimunOfDistance(i, end) + Matrix[start][i];
				isFirst = false;
			}
			else
			{
				distance = miniBet(distance, INlookForMinimunOfDistance(i, end) + Matrix[start][i]);
			}
		}
	}
	return distance;
}

void graphMatrix::ShortestPath_Dijikstra(int v0)
{
	for (int v = 0; v < N; v++)//先通过循环确定最初v0到vi的距离
	{
		S[v] = false;
		D[v] = Matrix[v0][v];
		if (D[v] < MAX)
		{
			Path[v] = v0;
		}
		else
		{
			Path[v] = -1;
		}
	}
	//将源点v0本身划入已确定集合S当中
	S[v0] = true;
	D[v0] = 0;

	int v;
	int min;
	for (int i = 1; i < N; i++)//遍历所有结点，既v0到每一个结点。
	{
		min = MAX;
		//通过这个循环来找到当前离v0最近的一个点
		for (int w = 0; w < N; w++)
		{
			if (S[w] == false && D[w] < min)
			{
				v = w;
				min = D[w];
			}
		}
		S[v] = true;
		//通过找出来的目前最近的一个点来找 以这个点为桥梁v0到达vi的最短距离
		for (int w = 0; w < N; w++)
		{
			if (S[w] == false && (D[v] + Matrix[v][w] < D[w]))
			{
				D[w] = D[v] + Matrix[v][w];
				Path[w] = v;
			}
		}
	}
	//到此就计算完成了 在之后的循环中 他们的初始路径都比你的初始路径长所以就可以直接判断现在是最短的了
	//接下来为结果输出了
	for (int i = 0; i < N; i++)
	{
		cout << "从" << v0 + 1 << "到" << i + 1 << "的路径" << ":" << i + 1 << " ";
		int tempI = i;
		while (tempI != v0 && tempI != -1)
		{
			cout << Path[tempI] + 1 << ' ';
			tempI = Path[tempI];
		}
		cout << D[i] << endl;
	}
}

void graphMatrix::TopLogicalSort()
{
	stack<int> indegreeIsZero;
	queue<int> sortNumber;
	//先找出初始入度为0的
	for (int i = 0; i < N; i++)
	{
		if (Adjacentlist[i].indegree == 0)
		{
			indegreeIsZero.push(i);
			Adjacentlist[i].indegree = -1;
		}
	}
	int tempNum;
	while (!indegreeIsZero.empty())
	{
		tempNum = indegreeIsZero.top();
		indegreeIsZero.pop();
		sortNumber.push(tempNum);
		while (Adjacentlist[tempNum].firstedge)
		{
			Adjacentlist[Adjacentlist[tempNum].firstedge->adjvex].indegree--;
			Adjacentlist[tempNum].firstedge = Adjacentlist[tempNum].firstedge->next;
		}
		for (int i = 0; i < N; i++)
		{
			if (Adjacentlist[i].indegree == 0)
			{
				indegreeIsZero.push(i);
				Adjacentlist[i].indegree = -1;
			}
		}
	}
	while (!sortNumber.empty())
	{
		cout << sortNumber.front() << ' ';
		sortNumber.pop();
	}
}



