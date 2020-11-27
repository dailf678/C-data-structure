#include<iostream>
struct BSNode
{
	BSNode(int t)
		:data(t), lchild(nullptr), rchild(nullptr), father(nullptr) {}
	BSNode(int t,BSNode* f)
		:data(t), lchild(nullptr), rchild(nullptr), father(f) {}
	BSNode() = default;

	int data;
	BSNode* lchild;
	BSNode* rchild;
	BSNode* father;
};

class BSTree
{
public:
	BSTree();
	~BSTree();
	void insertNumberIntoBSTree(int data);//外部使用的添加数字
	BSNode* findIndexOfNumb(int data);//外部寻找某个数字
	bool deleteNode(int data);//外部使用删除某个数字
	void printBSTree();//外部使用打印这颗树
	//void destoryBSTree();
	void destory();
private:
	void INinserBet(BSNode*& root, BSNode*& father, int data);
	void INinsertTreeIntoBSTree(BSNode*& root, BSNode*& father, BSNode* newTree);
	void INprintBSTree(BSNode* node);
	bool INdeleteNode(BSNode* root, int data);
	void INdestory(BSNode*& p);
	BSNode* findIt(BSNode* root, int data);
	BSNode* Root;
};

BSTree::BSTree()
{
	Root = nullptr;
}
BSTree::~BSTree()
{
	destory();
}

void BSTree::INinserBet(BSNode*& root,BSNode*& father,int data)
{
	//如果是初始造树，就不需要考虑father
	if (root == nullptr && root == Root)
	{
		root = new BSNode(data);
	}
	else if (root == nullptr && root != Root)
	{
		root = new BSNode(data, father);
	}
	else if (data < root->data)
	{
		INinserBet(root->lchild, root, data);
	}
	else
	{
		INinserBet(root->rchild, root, data);
	}
}
void BSTree::insertNumberIntoBSTree(int data)
{
	INinserBet(Root, Root->father, data);
}

void BSTree::INinsertTreeIntoBSTree(BSNode*& root, BSNode*& father, BSNode* newTree)
{
	if (root == nullptr)
	{
		root = newTree;
		root->father = father;
	}
	else if (newTree->data < root->data)
	{
		INinsertTreeIntoBSTree(root->lchild, root, newTree);
	}
	else
	{
		INinsertTreeIntoBSTree(root->rchild, root,newTree);
	}
}

BSNode* BSTree::findIt(BSNode* root, int data)
{
	BSNode* Finded;
	if (root != nullptr)
	{
		if (root->data == data)
		{
			return root;
		}
		else if (data < root->data)
		{
			return findIt(root->lchild, data);
		}
		else
		{
			return findIt(root->rchild, data);
		}
	}
	else
	{
		return nullptr;
	}
}
BSNode* BSTree::findIndexOfNumb(int data)
{
	return findIt(Root, data);
	
}

bool BSTree::INdeleteNode(BSNode* root, int data)
{
	BSNode* Finded = findIt(root, data);
	if (Finded == Root)
	{
		Root = Finded->rchild;
		Finded->rchild->father = nullptr;
		INinsertTreeIntoBSTree(Finded->rchild->lchild, Finded->rchild, Finded->lchild);
		delete Finded;
		Finded = nullptr;
	}
	if (Finded->rchild != nullptr && Finded->lchild == nullptr)
	{
		if (Finded->data < Finded->father->data)
		{
			Finded->father->lchild = Finded->rchild;
			Finded->rchild->father = Finded->father;
			delete Finded;
			Finded = nullptr;
		}
		else
		{
			Finded->father->rchild = Finded->rchild;
			Finded->rchild->father = Finded->father;
			delete Finded;
			Finded = nullptr;
		}
	}

	if (Finded->rchild == nullptr && Finded->lchild != nullptr)
	{
		if (Finded->data < Finded->father->data)
		{
			Finded->father->lchild = Finded->lchild;
			Finded->lchild->father = Finded->father;
			delete Finded;
			Finded = nullptr;
		}
		else
		{
			Finded->father->rchild = Finded->lchild;
			Finded->lchild->father = Finded->father;
			delete Finded;
			Finded = nullptr;
		}
	}

	if (Finded->rchild != nullptr && Finded->lchild != nullptr)
	{
		if (Finded->data < Finded->father->data)
		{
			Finded->father->lchild = Finded->rchild;
			Finded->rchild->father = Finded->father;
			INinsertTreeIntoBSTree(Finded->rchild->lchild, Finded->rchild, Finded->lchild);
			delete Finded;
			Finded = nullptr;
		}
		else 
		{
			Finded->father->rchild = Finded->rchild;
			Finded->rchild->father = Finded->father;
			INinsertTreeIntoBSTree(Finded->rchild->lchild, Finded->rchild, Finded->lchild);
			delete Finded;
			Finded = nullptr;
		}
	}

	return true;
}
bool BSTree::deleteNode(int data)
{
	if (Root != nullptr)
	{
		INdeleteNode(Root, data);
		return true;
	}
}

void BSTree::INprintBSTree(BSNode* node)
{
	if (node != nullptr)
	{
		INprintBSTree(node->lchild);
		std::cout << node->data << " ";
		INprintBSTree(node->rchild);
	}
}
void BSTree::printBSTree()
{
	if (Root != nullptr)
	{
		INprintBSTree(Root);
	}
	else
	{
		std::cout << "there is nothing!!!";
	}
	std::cout << std::endl;
}

void BSTree::INdestory(BSNode*& p)
{
	if (p != nullptr)
	{
		if (p->lchild != nullptr)
			INdestory(p->lchild);
		if (p->rchild != nullptr)
			INdestory(p->rchild);
		delete p;
		p = nullptr;
	}
}
void BSTree::destory()
{
	INdestory(Root);
}