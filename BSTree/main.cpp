#include<iostream>
#include"BSTree.h"
using namespace std;
void main()
{
	//the tree is like this
	/*
					9
           5                13
       3        7      11         15
	1        6                14 


	9 5 13 11 3 7 1 6 15 14
	*/

	BSTree LengthOfTreeIs10;
	int a[10];
	int tempNum;
	for (int i = 0; i < 10; i++)
	{
		cin >> tempNum;
		a[i] = tempNum;
	}
	for (int i = 0; i < 10; i++)
	{
		LengthOfTreeIs10.insertNumberIntoBSTree(a[i]);
	}
	LengthOfTreeIs10.printBSTree();
	LengthOfTreeIs10.findIndexOfNumb(5);
	LengthOfTreeIs10.deleteNode(5);
	LengthOfTreeIs10.printBSTree();
	LengthOfTreeIs10.destory();
	LengthOfTreeIs10.printBSTree();
}