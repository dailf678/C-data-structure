#include<iostream>
#include<queue>
#include<stack>
#define N 5
#define MAX 1000
using namespace std;
/*
�����������������鶼�Ǵ�0��ʼ
! ����DFS BFS���������
@ ����Դ���·�����������
# ��������������������
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
	int miniDistance(int, int);//Ѱ��ͼ��������̾���
	void DFS(int start);
	void BFS(int start);
	void ShortestPath_Dijikstra(int v0);//��Դ���·��
	void TopLogicalSort();
private:
	//�����ٽӾ���ķ���
	int Matrix[N][N];//�ڽӾ��� ��@ #
	VertexNode Adjacentlist[N];//�ٽӱ� #
	bool visited[N];//��¼�Ƿ���ʹ� ��
	bool S[N];//��¼Դ��v0���յ�vi�Ƿ�ȷ��Ϊ���·�� @
	int D[N];//��¼Դ��v0���յ�vi��ǰ���·�� @
	int Path[N];//��¼Դ��v0���յ�vi��ǰ���·����vi��ֱ��ǰ��������� @
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
			if (matrix[i][j] != 0 && matrix[i][j] < MAX)//����1����������ͨ�� ���Ǵ�iָ��j��
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
	for (int v = 0; v < N; v++)//��ͨ��ѭ��ȷ�����v0��vi�ľ���
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
	//��Դ��v0��������ȷ������S����
	S[v0] = true;
	D[v0] = 0;

	int v;
	int min;
	for (int i = 1; i < N; i++)//�������н�㣬��v0��ÿһ����㡣
	{
		min = MAX;
		//ͨ�����ѭ�����ҵ���ǰ��v0�����һ����
		for (int w = 0; w < N; w++)
		{
			if (S[w] == false && D[w] < min)
			{
				v = w;
				min = D[w];
			}
		}
		S[v] = true;
		//ͨ���ҳ�����Ŀǰ�����һ�������� �������Ϊ����v0����vi����̾���
		for (int w = 0; w < N; w++)
		{
			if (S[w] == false && (D[v] + Matrix[v][w] < D[w]))
			{
				D[w] = D[v] + Matrix[v][w];
				Path[w] = v;
			}
		}
	}
	//���˾ͼ�������� ��֮���ѭ���� ���ǵĳ�ʼ·��������ĳ�ʼ·�������ԾͿ���ֱ���ж���������̵���
	//������Ϊ��������
	for (int i = 0; i < N; i++)
	{
		cout << "��" << v0 + 1 << "��" << i + 1 << "��·��" << ":" << i + 1 << " ";
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
	//���ҳ���ʼ���Ϊ0��
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



