/*//Copyright Statements:
	This source code file is completed as part of the Open SAL(Open Standardized Algorithm 
Library) by Ming Li during the summer vocation of 2013 at College of Information Science 
and Engineering, Central South University. All rights reserved. No part of these files may
be reproduced or transmitted in any form or by any means without permission from the author.
While, you are permitted to download this Library and its instruction manual freely at 
http://www.oschina.net/code/snippet_1259068_24335# and use it by yourself. 
	If you find some bugs or problems of this Library,you are welcomed to email me(limingcsu
@foxmail.com). If you want to know any details or updates about this Library or would like
to discuss issues about algorithms with enthusiasts,you can apply to join the QQ group(222576709).
*///

//此文件（Algorithms_Lmtc.cpp）对本算法库中大部分算法进行测试。
//通过浏览此文件可以大致了解该算法库中的各个数据结构和算法的使用方式。

#include "stdafx.h"
//C++类库
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include <bitset>
#include <exception>
#include <memory>  //含有auto_ptr类，用于安全的管理动态申请的对象（不能管理动态数组，不能用于容器）
#include <algorithm> //标准库算法
#include <numeric> //算术型算法
#include <functional> //函数对象

//C函数库
#include <cctype>
#include <cstddef>
#include <cstring>
#include <ctime>

//自定义头文件
#include "smartPtr.h"
#include "myException.h"
#include "array.h"
#include "symmetryArray.h"
#include "coordinateMapping.h"
#include "algebra.h"
#include "heap.h"
#include "redBlackTree.h"
#include "hash.h"
#include "numberTheory.h"
#include "myMath.h"
#include "sequence.h"
#include "binomialHeap.h"
#include "fibonacciHeap.h"
#include "nonIntersectSet.h"
#include "graph.h"
#include "number.h"
#include "fastFourierTransform.h"

bool canExpandTo(const int &item,const std::vector<int> &st){return true;}
void expandTo(const int &item,std::vector<int> &st){st.push_back(item);}
using std::string;
bool g(const int &a,const int &b){return a<b;}
void f(double x){std::cout<<x<<std::endl;}
unsigned long keyToNumber(const unsigned long &t){return t;}
unsigned long stringToNumber(const std::string &str){
	unsigned long t=0;
	for(std::string::const_iterator c=str.begin();c!=str.end();c++)
	{	
		double tem=256.0*t+(unsigned long)(*c);
		unsigned long tem1=(unsigned long)(tem/lmtc::MAX_PRIME);
		tem-=(1.0*tem1*lmtc::MAX_PRIME);
		t=(unsigned long)tem;
	}
	return t;
}

double polynomial(unsigned int i,double x){
	return std::pow(x,(int)i);
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand((long)time(NULL));

	///*对称数组测试
	std::cout<<"对称数组测试："<<std::endl;
	std::vector<unsigned int>symArrDimV(4);
	symArrDimV[0]=7;symArrDimV[1]=8;symArrDimV[2]=6;symArrDimV[3]=9;
	lmtc::SymmetryArray<int> symArr(4,symArrDimV);
	symArrDimV[0]=1;symArrDimV[1]=2;symArrDimV[2]=3;symArrDimV[3]=4;
	symArr(symArrDimV)=12;
	symArrDimV[0]=4;symArrDimV[1]=2;symArrDimV[2]=3;symArrDimV[3]=1;
	const lmtc::SymmetryArray<int> symArrConst=symArr;
	std::cout<<symArrConst(1,2,4,3)<<"  "<<symArr(1,4,2,3)<<"  "<<symArrConst(1,3,2,4)<<"  "<<symArr(1,4,3,2)<<"  "<<symArrConst(symArrDimV)<<"  "<<symArr(symArrDimV)<<std::endl;
	std::cout<<"7*8*6*9="<<7*8*6*9<<std::endl;
	std::cout<<"actual memory needed ="<<symArr.size()<<std::endl;
	std::cout<<std::endl;//*/

	///*一般堆测试
	std::cout<<"一般堆测试："<<std::endl;
	int arrHeap[]={5,4,3,2,1,6,8,10,-1};
	lmtc::Heap<int> hp(arrHeap,arrHeap+9);
	hp.printHeap();
	hp.increaseKey(3,5);
	hp.insert(9);
	hp.printHeap();
    std::vector<int> st=hp.sort();
	for(size_t i=0;i<st.size();i++)
		std::cout<<st[i]<<"  ";
	std::cout<<std::endl; 
	hp.printHeap();
	std::cout<<std::endl;//*/

	///*全域完全散列测试
	std::cout<<"全域完全散列测试："<<std::endl;
	lmtc::CompleteHash<unsigned long> hash(50,lmtc::MAX_PRIME,keyToNumber);
	hash.insert(20);
	for(unsigned int i=0;i<1000;i++)
		hash.insert((unsigned long)(lmtc::averageRandom()*50000));
	hash.completeHashOptimize();
	unsigned long *hashItem=hash.search(20);
	hash.remove(*hashItem);
	std::cout<<std::endl;//*/
	

	///*红黑树测试
	std::cout<<"红黑树测试："<<std::endl;
	lmtc::RedBlackTree<int> rbtree;
	std::cout<<"随机插入"<<std::endl;
	for(int i=1;i<20;i++)
	{
		int temp=(int)(lmtc::averageRandom()*50000);//(int)(lmtc::averageRandom()*100000);
		if(temp!=rbtree.getItemValue(rbtree.insert(temp)))
			std::cout<<"error"<<std::endl;
		if(temp!=rbtree.getItemValue(rbtree.search(temp)))
			std::cout<<"error"<<std::endl;
		std::cout<<temp<<std::endl;
	}

	std::cout<<"size= "<<rbtree.size()<<std::endl;
	
	rbtree.insert(12);
	lmtc::RedBlackTree<int>::ItemType &po=rbtree.deleteItem(rbtree.search(12));

	for(unsigned int i=0;i<rbtree.size();i++){
		lmtc::RedBlackTree<int>::ItemType t=rbtree.searchItmOfOrder(i);
		if(rbtree.getOrderOfItm(t)!=i)
			std::cout<<"顺序统计错误"<<std::endl;
	}

	std::cout<<"size= "<<rbtree.size()<<std::endl;

	std::cout<<"随机删除"<<std::endl;
	for(int i=1;i<20;i++)
	{
		int temp=(int)(lmtc::averageRandom()*50000);//(int)(lmtc::averageRandom()*100000);
		lmtc::RedBlackTree<int>::ItemType del=rbtree.deleteItem(rbtree.search(temp));
		if(!del.isEmpty())
			std::cout<<rbtree.getItemValue(del)<<std::endl;
	}

	std::cout<<"size= "<<rbtree.size()<<std::endl;

	std::cout<<"逆序输出："<<std::endl;
	lmtc::RedBlackTree<int>::ItemType x=rbtree.maximum();
	while(true){
		if(x.isEmpty())
			break;
		std::cout<<rbtree.getItemValue(x)<<std::endl;
		x=rbtree.predecessor(x);
	}

	std::cout<<"中序遍历"<<std::endl;
	rbtree.traver_inOrder(f);
	std::cout<<"前序遍历"<<std::endl;
	rbtree.traver_preOrder(f);
	std::cout<<"遍历结束"<<std::endl;

	std::cout<<"开始验证"<<std::endl;
	rbtree.asertTree(rbtree.getRoot());

	for(unsigned int i=0;i<rbtree.size();i++){
		lmtc::RedBlackTree<int>::ItemType t=rbtree.searchItmOfOrder(i);
		if(rbtree.getOrderOfItm(t)!=i)
			std::cout<<"顺序统计错误"<<std::endl;
	}
    std::cout<<rbtree.size()<<std::endl;
	rbtree.setEmpty();
	std::cout<<"over"<<rbtree.size()<<std::endl;
	std::cout<<std::endl;//*/

///*利用标准库顺序统计测试
std::cout<<"标准库顺序统计测试："<<std::endl;
int ntha1[]={2,5,8,10,12,7,99,3,54,46};
int ntha2[]={3,5,6,13,9,19,8,7,54,28,99,46,3,5,2,5,8,10,12,7,99,3,54,46,2,5,8,10,12,7,99,3,54,46,2,5,8,10,12,7,99,3,54,46};
std::vector<int> nthv1(ntha1,ntha1+10);
std::vector<int> nthv2(ntha2,ntha2+44);
std::vector<int> nthvec=lmtc::longestCommonSubsequence<int>(nthv1.begin(),nthv1.end(),nthv2.begin(),nthv2.end());
for(unsigned int i=0;i<nthvec.size();i++)
	std::cout<<nthvec[i]<<std::endl;
std::random_shuffle(ntha2,ntha2+44);
std::nth_element(ntha2,ntha2+20,ntha2+44);
std::cout<<"顺序统计"<<std::endl;
for(int i=0;i<44;i++)
	std::cout<<ntha2[i]<<std::endl;
std::cout<<std::endl;//*/

///*二项堆测试
std::cout<<"二项堆测试："<<std::endl;
lmtc::BinomialHeap<int> bihp;
lmtc::BinomialHeap<int> bihp1;

for(int i=0;i<100;i++){
	int temp=(int)(lmtc::averageRandom()*5000000);
	int temp1=(int)(lmtc::averageRandom()*5000000);
	bihp.increaseKey(bihp.insert(temp),(int)(lmtc::averageRandom()*5000000));
	bihp1.increaseKey(bihp1.insert(temp1),(int)(lmtc::averageRandom()*5000000));
	if(bihp.get_prio().isEmpty()||bihp1.get_prio().isEmpty())
		std::cout<<"error"<<std::endl;
	if(lmtc::averageRandom()<0.5){
		int pio=bihp.getItemValue(bihp.get_prio());
		int pio1=bihp.getItemValue(bihp.extract_prio());
		if(pio!=pio1)
			std::cout<<"error1"<<std::endl;
	}
	if(lmtc::averageRandom()<0.5){
		int pio=bihp1.getItemValue(bihp1.get_prio());
		int pio1=bihp1.getItemValue(bihp1.extract_prio());
		if(pio!=pio1)
			std::cout<<"error1"<<std::endl;
	}

	if(lmtc::averageRandom()<0.1)
		bihp.asertBinomialHeap();

	if(lmtc::averageRandom()<0.1)
		bihp1.asertBinomialHeap();
}

bihp.heapUnion(bihp1);
std::cout<<"验证开始"<<std::endl;
bihp.asertBinomialHeap();
std::cout<<"验证结束"<<std::endl;

std::cout<<bihp.size()<<"end"<<bihp1.size()<<std::endl;

std::cout<<"释放资源1"<<std::endl;
bihp.setEmpty();
std::cout<<"释放资源2"<<std::endl;
bihp.traver_inOrder(f);
std::cout<<std::endl;//*/

///*斐波那契堆测试
std::cout<<"斐波那契堆测试："<<std::endl;
lmtc::FibonacciHeap<int> fbnqhp;
lmtc::FibonacciHeap<int> fbnqhp1;
for(int i=0;i<100;i++){
	int temp=(int)(lmtc::averageRandom()*5000000);
	int temp1=(int)(lmtc::averageRandom()*5000000);
	fbnqhp.increaseKey(fbnqhp.insert(temp),(int)(lmtc::averageRandom()*5000000));
	fbnqhp1.increaseKey(fbnqhp1.insert(temp1),(int)(lmtc::averageRandom()*5000000));
	if(fbnqhp.get_prio().isEmpty()||fbnqhp1.get_prio().isEmpty())
		std::cout<<"error"<<std::endl;
	if(lmtc::averageRandom()<0.5){
		int pio=fbnqhp.getItemValue(fbnqhp.get_prio());
		int pio1=fbnqhp.getItemValue(fbnqhp.extract_prio());
		if(pio!=pio1)
			std::cout<<"error1"<<std::endl;
	}
	if(lmtc::averageRandom()<0.5){
		int pio=fbnqhp1.getItemValue(fbnqhp1.get_prio());
		int pio1=fbnqhp1.getItemValue(fbnqhp1.extract_prio());
		if(pio!=pio1)
			std::cout<<"error1"<<std::endl;
	}

	if(lmtc::averageRandom()<0.1)
		fbnqhp.asertFibonacciHeap();

	if(lmtc::averageRandom()<0.1)
		fbnqhp1.asertFibonacciHeap();
}
fbnqhp.heapUnion(fbnqhp1);

std::cout<<"验证开始"<<std::endl;
fbnqhp.asertFibonacciHeap();
std::cout<<"验证结束"<<std::endl;

std::cout<<fbnqhp.size()<<"end"<<fbnqhp1.size()<<std::endl;

std::cout<<"释放资源1"<<std::endl;
fbnqhp.setEmpty();
std::cout<<"释放资源2"<<std::endl;
std::cout<<std::endl;//*/

///*不相交集合测试
std::cout<<"不相交集合测试："<<std::endl;
std::vector<lmtc::NonIntersectSet<int>> setVec;
for(int i=0;i<10;i++){
	setVec.push_back(lmtc::NonIntersectSet<int>());
	setVec[i].setValue(i);
	if(setVec[i].getValue()!=i)
		std::cout<<"error1"<<std::endl;
}
for(int i=0;i<10;i++){
	unsigned int a=(unsigned int)(lmtc::averageRandom()*10);
	unsigned int b=(unsigned int)(lmtc::averageRandom()*10);
	if(setVec[a].find()==setVec[b].find())
		std::cout<<a<<"===="<<b<<std::endl;
	setVec[a].unionSet(setVec[b]);
}
for(int i=0;i<10;i++){
	std::cout<<i<<"->"<<setVec[i].find()->getValue()<<std::endl;
	setVec[i].find()->setValue(setVec[i].find()->getValue());
}
std::cout<<std::endl;//*/

int arr[][5]={{0,1,0,0,0},{0,0,0,0,0},{1,1,0,1,1},{1,0,0,0,0},{1,0,0,1,0}};
lmtc::Array<int> ajacencyMatrix(2,5,5);
for(int i=0;i<5;i++)
	for(int j=0;j<5;j++)
		ajacencyMatrix(i,j)=arr[i][j];

//邻接矩阵转邻接表
std::vector<std::list<lmtc::Edge<int>>> ajacencyList;
lmtc::Graph::ajacencyMatrixToList(ajacencyMatrix,ajacencyList);

//邻接表的转置
std::vector<std::list<lmtc::Edge<int>>> transposedAjacencyList;
lmtc::Graph::transposeAjacencyList(ajacencyList,transposedAjacencyList);


///*拓扑排序测试
std::cout<<"拓扑排序测试："<<std::endl;
std::vector<unsigned int> order=lmtc::Graph::topologicalSort(transposedAjacencyList);
std::cout<<"拓扑序列为："<<std::endl;
for(std::vector<unsigned int>::iterator iter=order.begin();iter!=order.end();iter++)
	std::cout<<*iter<<"  ";
std::cout<<std::endl;//*/

///*强连通分支测试
std::cout<<"强连通分支测试："<<std::endl;
std::vector<std::vector<unsigned int>> strongConnectComponents;
lmtc::Graph::computeStrngConctComps(ajacencyList,strongConnectComponents);
for(unsigned int i=0;i<strongConnectComponents.size();i++){
	std::cout<<"连通分支"<<i<<std::endl;
	for(std::vector<unsigned int>::iterator iter=strongConnectComponents[i].begin();iter!=strongConnectComponents[i].end();iter++)
		std::cout<<*iter<<" ; ";
	std::cout<<std::endl;
}
std::cout<<std::endl;//*/

///*欧拉回路测试
std::cout<<"欧拉回路测试："<<std::endl;
int arr1[][5]={{1,1,1,0,0},{0,1,1,1,0},{0,0,0,1,1},{1,0,0,0,1},{1,1,0,0,0}};
//int arr1[][5]={{2,0,1,1,0},{0,2,0,1,1},{1,0,0,0,1},{1,1,0,0,0},{0,1,1,0,0}};
lmtc::Array<int> ajacencyMatrix1(2,5,5);
for(int i=0;i<5;i++)
	for(int j=0;j<5;j++)
		ajacencyMatrix1(i,j)=arr1[i][j];
std::vector<std::list<lmtc::Edge<int>>> ajacencyList1;
lmtc::Graph::ajacencyMatrixToList(ajacencyMatrix1,ajacencyList1);

std::list<lmtc::Edge<int>> EulerCircuit;
bool existEuler=lmtc::Graph::computeEulerCircuit(ajacencyList1,EulerCircuit,true);
if(existEuler==false&&EulerCircuit.empty())
	std::cout<<"Euler circuit or path not existed"<<std::endl;
else{
	std::cout<<"欧拉回路为："<<std::endl;
	for(std::list<lmtc::Edge<int>>::iterator iter=EulerCircuit.begin();iter!=EulerCircuit.end();iter++)
		std::cout<<iter->vSt<<"-"<<iter->vEd<<"   -->   ";
	std::cout<<std::endl;
}
std::cout<<std::endl;//*/

///*最小生成树测试
std::cout<<"最小生成树测试："<<std::endl;
int arr2[][8]={{1,1,2,7,3,0,0,0},{1,1,6,2,0,0,0,0},{2,6,1,4,0,0,0,0},{7,2,4,1,5,0,0,0},{3,0,0,5,1,0,0,0},{0,0,0,0,0,1,2,3},{0,0,0,0,0,2,1,1},{0,0,0,0,0,3,1,1}};
lmtc::Array<int> ajacencyMatrix2(2,8,8);
for(int i=0;i<8;i++)
	for(int j=0;j<8;j++)
		ajacencyMatrix2(i,j)=arr2[i][j];
std::vector<std::list<lmtc::Edge<int>>> ajacencyList2;
lmtc::Graph::ajacencyMatrixToList(ajacencyMatrix2,ajacencyList2);
std::vector<std::list<lmtc::Edge<int>>> mstAjacencyList;
int weightKruskal=lmtc::Graph::mstKruskal(ajacencyList2,mstAjacencyList);
std::cout<<"Kruskal最小生成树为：权重："<<weightKruskal<<std::endl;
for(unsigned int i=0;i<mstAjacencyList.size();i++){
	for(std::list<lmtc::Edge<int>>::const_iterator iter=mstAjacencyList[i].begin();iter!=mstAjacencyList[i].end();iter++){
		std::cout<<iter->vSt<<"-"<<iter->vEd<<":"<<iter->data<<"   ";
	}
	std::cout<<std::endl;
}
std::vector<std::list<lmtc::Edge<int>>> mstAjacencyListPrim;
int weightPrim=lmtc::Graph::mstPrim(ajacencyList2,mstAjacencyListPrim);
std::cout<<"Prim最小生成树为：权重："<<weightPrim<<std::endl;
for(unsigned int i=0;i<mstAjacencyListPrim.size();i++){
	for(std::list<lmtc::Edge<int>>::const_iterator iter=mstAjacencyListPrim[i].begin();iter!=mstAjacencyListPrim[i].end();iter++){
		std::cout<<iter->vSt<<"-"<<iter->vEd<<":"<<iter->data<<"   ";
	}
	std::cout<<std::endl;
}
std::cout<<std::endl;//*/

///*判断有向图或者无向图是否存在回路
std::cout<<"判断有向图或者无向图是否存在回路测试："<<std::endl;
int arr3[][4]={{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
lmtc::Array<int> ajacencyMatrix3(2,4,4);
for(int i=0;i<4;i++)
	for(int j=0;j<4;j++)
		ajacencyMatrix3(i,j)=arr3[i][j];
std::vector<std::list<lmtc::Edge<int>>> ajacencyList3;
lmtc::Graph::ajacencyMatrixToList(ajacencyMatrix3,ajacencyList3);
if(lmtc::Graph::hasLoop(ajacencyList3,true)==true)
	std::cout<<"存在回路"<<std::endl;
else
	std::cout<<"不存在回路"<<std::endl;
std::cout<<std::endl;//*/

///*计算最短路径
std::cout<<"最短路径测试："<<std::endl;
int arr4[][4]={{0,1,3,4},{0,3,1,2},{2,1,6,0},{6,3,0,1}};
lmtc::Array<int> ajacencyMatrix4(2,4,4);
for(int i=0;i<4;i++)
	for(int j=0;j<4;j++)
		ajacencyMatrix4(i,j)=arr4[i][j];
std::vector<std::list<lmtc::Edge<int>>> ajacencyList4;
lmtc::Graph::ajacencyMatrixToList(ajacencyMatrix4,ajacencyList4);
unsigned s=0;
std::vector<unsigned int> p;
std::vector<int>d;
//if(true==lmtc::Graph::shortestPathBellmanFord(ajacencyList4,s,p,d))shortestPathDijkstra
//if(true==lmtc::Graph::shortestPathOfDag(ajacencyList4,s,p,d))
if(true==lmtc::Graph::shortestPathDijkstra(ajacencyList4,s,p,d))
	for(unsigned int i=0;i<p.size();i++)
		std::cout<<"parent of "<<i<<" is "<<p[i]<<" , and d of the path is "<<d[i]<<std::endl;
else
	std::cout<<"存在负边"<<std::endl;
std::cout<<std::endl;//*/

///*计算每对顶点间的最短路径
std::cout<<"每对顶点间的最短路径测试："<<std::endl;
int arr5[][4]={{1,1,3,4},{0,1,1,2},{-2,-1,1,0},{6,3,0,1}};
lmtc::Array<int> ajacencyMatrix5(2,4,4);
for(int i=0;i<4;i++)
	for(int j=0;j<4;j++)
		ajacencyMatrix5(i,j)=arr5[i][j];
std::vector<std::list<lmtc::Edge<int>>> ajacencyList5;
lmtc::Graph::ajacencyMatrixToList(ajacencyMatrix5,ajacencyList5);
lmtc::Array<unsigned int> pMatrix;
lmtc::Array<int>dMatrix;
//lmtc::Graph::shortestPathAllFloydWarshall(ajacencyList5,pMatrix,dMatrix);
if(lmtc::Graph::shortestPathAllJohnson(ajacencyList5,pMatrix,dMatrix))
for(unsigned int k=0;k<pMatrix.getDimLen(0);k++){
	std::cout<<"以k="<<k<<"为源点的最短路径树"<<std::endl;
	for(unsigned int i=0;i<pMatrix.getDimLen(1);i++)
		std::cout<<"parent of "<<i<<" is "<<pMatrix(k,i)<<" , and d of the path is "<<dMatrix(k,i)<<std::endl;
}
std::cout<<std::endl;//*/

///*计算最大流
std::cout<<"最大流测试："<<std::endl;
int arr6[][6]={{-6,16,13,0,0,0},{0,0,10,12,0,0},{-6,4,0,0,14,0},{0,0,9,0,0,20},{0,0,0,7,0,4},{-4,0,0,-4,0,-4}};
lmtc::Array<int> ajacencyMatrix6(2,6,6);
for(int i=0;i<6;i++)
	for(int j=0;j<6;j++)
		ajacencyMatrix6(i,j)=arr6[i][j];
std::vector<std::list<lmtc::Edge<int>>> ajacencyList6;
lmtc::Graph::ajacencyMatrixToList(ajacencyMatrix6,ajacencyList6);
std::vector<std::list<lmtc::Edge<int>>> flow;
//int maxF=lmtc::Graph::maximumFlowFordFulkerson_EdmondsKarp(ajacencyList6,0,5,flow);
int maxF=lmtc::Graph::maximumFlowPushRelabelToFront(ajacencyList6,0,5,flow);
std::cout<<"最大流="<<maxF<<std::endl;
for(unsigned int i=0;i<flow.size();i++)
	for(std::list<lmtc::Edge<int>>::const_iterator iter=flow[i].begin();iter!=flow[i].end();iter++)
		std::cout<<iter->vSt<<"-"<<iter->vEd<<":"<<iter->data<<"   ";
std::cout<<std::endl;
std::cout<<std::endl;//*/


/*矩阵运算*/

///*矩阵乘法测试
std::cout<<"矩阵乘法测试："<<std::endl;
int arr7[][3]={{0,1,2},{3,1,5},{4,2,6},{1,8,3}};
lmtc::Array<int> Matrix1(2,4,3);
for(int i=0;i<4;i++)
	for(int j=0;j<3;j++)
		Matrix1(i,j)=arr7[i][j];

int arr8[][5]={{4,8,2,1,3},{3,2,6,4,7},{2,5,6,3,5}};
lmtc::Array<int> Matrix2(2,3,5);
for(int i=0;i<3;i++)
	for(int j=0;j<5;j++)
		Matrix2(i,j)=arr8[i][j];

//lmtc::Array<int> matrixRs=lmtc::Algebra::matrixMultiplySimple(Matrix1,Matrix2);
lmtc::Array<int> matrixRs=lmtc::Algebra::matrixMultiplyStrassen(Matrix1,Matrix2);
std::cout<<"矩阵乘法结果"<<std::endl;
for(unsigned int i=0;i<matrixRs.getDimLen(0);i++){
	for(unsigned int j=0;j<matrixRs.getDimLen(1);j++)
		std::cout<<matrixRs(i,j)<<"   ";
	std::cout<<std::endl;
}
std::cout<<std::endl;//*/

///*LUP 分解测试
std::cout<<"LUP 分解测试："<<std::endl;
double arr9[][4]={{2,0,2,0.6},{3,3,4,-2},{5,5,4,2},{-1,-2,3.4,-1}};
lmtc::Array<double> A(2,4,4);
for(int i=0;i<4;i++)
	for(int j=0;j<4;j++)
		A(i,j)=arr9[i][j];
lmtc::Array<double> L,U;
std::vector<unsigned int> P;
bool b=lmtc::Algebra::lupDecompose(A,L,U,P);
std::cout<<"LUP分解结果"<<std::endl;
if(b==true){
	std::cout<<"L:"<<std::endl;
	for(unsigned int i=0;i<L.getDimLen(0);i++){
		for(unsigned int j=0;j<L.getDimLen(1);j++)
			std::cout<<L(i,j)<<"   ";
		std::cout<<std::endl;
	}
	std::cout<<"U:"<<std::endl;
	for(unsigned int i=0;i<U.getDimLen(0);i++){
		for(unsigned int j=0;j<U.getDimLen(1);j++)
			std::cout<<U(i,j)<<"   ";
		std::cout<<std::endl;
	}
	std::cout<<"P:"<<std::endl;
	for(unsigned int i=0;i<P.size();i++)
		std::cout<<P[i]<<"   ";
	std::cout<<std::endl;
}
else
	std::cout<<"LUP分解失败，奇异方阵！"<<std::endl;
std::cout<<std::endl;//*/

///*解线性方程组
std::cout<<"解线性方程组测试："<<std::endl;
double arr10[][3]={{1,2,0},{3,4,4},{5,6,3}};
std::vector<double> b1;
b1.push_back(3);
b1.push_back(7);
b1.push_back(8);
lmtc::Array<double> A1(2,3,3);
for(int i=0;i<3;i++)
	for(int j=0;j<3;j++)
		A1(i,j)=arr10[i][j];
std::vector<double> X1;
if(lmtc::Algebra::solveLinearEquationsFast(A1,b1,X1))
//if(lmtc::Algebra::solveLinearEquationsByLUP(A1,b1,X1))
	for(unsigned int i=0;i<X1.size();i++)
		std::cout<<X1[i]<<"   ";
else
	std::cout<<"无解";
std::cout<<std::endl;//*/

///*求逆矩阵测试
std::cout<<"矩阵求逆测试："<<std::endl;
double arr11[][3]={{1,2,0},{2,4,5},{5,6,3}};
lmtc::Array<double> A2(2,3,3);
for(int i=0;i<3;i++)
	for(int j=0;j<3;j++)
		A2(i,j)=arr11[i][j];
lmtc::Array<double> _A;
std::cout<<"矩阵求逆"<<std::endl;
if(lmtc::Algebra::inverseMatrixFast(A2,_A)){
//if(lmtc::Algebra::inverseMatrixByLUP(A2,_A)){
	for(unsigned int i=0;i<_A.getDimLen(0);i++){
		for(unsigned int j=0;j<_A.getDimLen(1);j++)
			std::cout<<_A(i,j)<<"   ";
		std::cout<<std::endl;
	}
	lmtc::Array<double> matrixRs=lmtc::Algebra::matrixMultiplyStrassen(A2,_A);
	std::cout<<"与逆矩阵相乘的单位矩阵"<<std::endl;
	for(unsigned int i=0;i<matrixRs.getDimLen(0);i++){
		for(unsigned int j=0;j<matrixRs.getDimLen(1);j++)
			std::cout<<matrixRs(i,j)<<"   ";
		std::cout<<std::endl;
	}
}
else
	std::cout<<"不可逆"<<std::endl;
std::cout<<std::endl;//*/

///*伪逆矩阵测试
std::cout<<"伪逆矩阵测试："<<std::endl;
double arr12[][3]={{1,-1,1},{1,1,1},{1,2,4},{1,3,9},{1,5,25}};
lmtc::Array<double> A3(2,5,3);
for(int i=0;i<5;i++)
	for(int j=0;j<3;j++)
		A3(i,j)=arr12[i][j];
lmtc::Array<double> A3T=lmtc::Algebra::transposeMatrix(A3);
lmtc::Array<double> _Af;
lmtc::Array<double> _Ab;
std::cout<<"求前向伪逆矩阵"<<std::endl;
if(lmtc::Algebra::pseudoInverseMatrixForward(A3,_Af)){
	for(unsigned int i=0;i<_Af.getDimLen(0);i++){
		for(unsigned int j=0;j<_Af.getDimLen(1);j++)
			std::cout<<_Af(i,j)<<"   ";
		std::cout<<std::endl;
	}
	lmtc::Array<double> matrixRs=lmtc::Algebra::matrixMultiplyStrassen(_Af,A3);
	std::cout<<"与前向伪逆矩阵相乘的单位矩阵"<<std::endl;
	for(unsigned int i=0;i<matrixRs.getDimLen(0);i++){
		for(unsigned int j=0;j<matrixRs.getDimLen(1);j++)
			std::cout<<matrixRs(i,j)<<"   ";
		std::cout<<std::endl;
	}
}
else
	std::cout<<"不可前向伪逆"<<std::endl;

std::cout<<"求后向伪逆矩阵"<<std::endl;
if(lmtc::Algebra::pseudoInverseMatrixBackward(A3T,_Ab)){
	for(unsigned int i=0;i<_Ab.getDimLen(0);i++){
		for(unsigned int j=0;j<_Ab.getDimLen(1);j++)
			std::cout<<_Ab(i,j)<<"   ";
		std::cout<<std::endl;
	}
	lmtc::Array<double> matrixRs=lmtc::Algebra::matrixMultiplyStrassen(A3T,_Ab);
	std::cout<<"与后向伪逆矩阵相乘的单位矩阵"<<std::endl;
	for(unsigned int i=0;i<matrixRs.getDimLen(0);i++){
		for(unsigned int j=0;j<matrixRs.getDimLen(1);j++)
			std::cout<<matrixRs(i,j)<<"   ";
		std::cout<<std::endl;
	}
}
else
	std::cout<<"不可后向伪逆"<<std::endl;
std::cout<<std::endl;//*/

///*最小二乘估计与解正态方程组测试
std::cout<<"解正态方程组测试："<<std::endl;
double arr13[][3]={{1,-1,1},{1,1,1},{1,2,4},{1,3,9},{1,5,25}};
lmtc::Array<double> A4(2,5,3);
for(int i=0;i<5;i++)
	for(int j=0;j<3;j++)
		A4(i,j)=arr13[i][j];
double yArr[]={2,1,1,0,3};
double xArr[]={-1,1,2,3,5};
std::vector<double> X(xArr,xArr+5);
std::vector<double> Y(yArr,yArr+5);
std::vector<double> C;
std::vector<double> C1;
if(lmtc::Algebra::solveNormalityEquationsByLUP(A4,Y,C)){
//if(lmtc::Algebra::solveNormalityEquationsFast(A4,Y,C)){
	std::cout<<"正态方程组的解为：";
	for(unsigned int i=0;i<C.size();i++)
		std::cout<<C[i]<<"   ";
	std::cout<<std::endl;
}
else
	std::cout<<"正态方程组不可解"<<std::endl;
std::cout<<"最小二乘估计测试："<<std::endl;
//if(lmtc::Algebra::leastSquaresEstimationByLUP(polynomial,3,X,Y,C1)){
if(lmtc::Algebra::leastSquaresEstimationFast(polynomial,3,X,Y,C1)){
	std::cout<<"最小二乘估计的解为：";
	for(unsigned int i=0;i<C1.size();i++)
		std::cout<<C1[i]<<"   ";
	std::cout<<std::endl;
}
else
	std::cout<<"最小二乘不可解"<<std::endl;
std::cout<<std::endl;//*/

///*方幂和测试
std::cout<<"方幂和测试："<<std::endl;
const unsigned int K=6;
const unsigned int N=100;
lmtc::Array<double> S=lmtc::Algebra::powerSumFormula(K);
std::cout<<"方幂和公式如下"<<std::endl;
for(unsigned int i=0;i<=K;i++){
	std::cout<<"幂为"<<i<<"时的公式：";
	for(unsigned int j=0;j<i+2;j++)
		std::cout<<"c"<<j<<" = "<<S(i,j)<<", ";
	std::cout<<std::endl;
}
std::cout<<"when K="<<K<<" ,N="<<N<<"  时，0^K+1^K+2^K+...+N^K = "<<lmtc::Algebra::powerSum(N,K)<<std::endl;
std::cout<<std::endl;//*/

///*复数运算测试
std::cout<<"复数运算测试："<<std::endl;
lmtc::ComplexNumber c1(0.34,0.69);
lmtc::ComplexNumber c2(0.53,0.49);
c1+=c2;
std::cout<<(std::string)c1<<std::endl;
c1-=c2;
std::cout<<(std::string)c1<<std::endl;
c1*=c2;
std::cout<<(std::string)c1<<std::endl;
c1/=c2;
std::cout<<(std::string)c1<<std::endl;
std::cout<<std::endl;//*/

///*快速傅里叶变换,及逆变换，数值稳定性非常好，当cN=1000时为0.00000000001，当cN=10000时为0.0000000001，当cN=100000时为0.000000001，当cN=1000000时为0.00000001，
std::cout<<"快速傅里叶变换测试："<<std::endl;
std::vector<lmtc::ComplexNumber> a;
unsigned int cN=100;
for(unsigned i=0;i<cN;i++)
	a.push_back(lmtc::ComplexNumber(lmtc::averageRandom(0,10),lmtc::averageRandom(0,10)));
std::vector<lmtc::ComplexNumber> y=lmtc::FastFourierTransform::fft(a);
std::vector<lmtc::ComplexNumber> a1=lmtc::FastFourierTransform::_fft(y);
std::cout<<"系数向量a：";
for(unsigned i=0;i<a.size();i++)
	std::cout<<(std::string)a[i]<<"   ";
std::cout<<std::endl;
std::cout<<"点值向量y：";
for(unsigned i=0;i<y.size();i++)
	std::cout<<(std::string)y[i]<<"   ";
std::cout<<std::endl;
std::cout<<"系数向量a1：";
for(unsigned i=0;i<a1.size();i++)
	std::cout<<(std::string)a1[i]<<"   ";
std::cout<<std::endl;

for(unsigned int i=0;i<a1.size();i++){
	if(i<a.size()&&!a[i].equal(a1[i],0.00000001))
		std::cout<<"error:"<<(std::string)a[i]<<"==?"<<(std::string)a1[i]<<"   "<<std::endl;
	if(i>=a.size()&&!a1[i].equal(0,0.00000001))
		std::cout<<"error1"<<std::endl;
}
std::cout<<std::endl;//*/

///*求卷积
std::cout<<"卷积测试："<<std::endl;
double Aarr[]={1,2,3,23};
double Barr[]={5,4,34};
std::vector<lmtc::ComplexNumber> Avec(Aarr,Aarr+4);
std::vector<lmtc::ComplexNumber> Bvec(Barr,Barr+3);
std::vector<lmtc::ComplexNumber>Cvec=lmtc::Algebra::convolution(Avec,Bvec);
std::cout<<"卷积为："<<std::endl;
for(unsigned int i=0;i<Cvec.size();i++)
	std::cout<<(std::string)Cvec[i]<<"   ";
std::cout<<std::endl;//*/

///*多维傅里叶变换测试
std::cout<<"高维傅里叶变换测试："<<std::endl;
lmtc::Array<lmtc::ComplexNumber> aMultiFFT(2,3,4);
for(unsigned int i=0;i<aMultiFFT.getDimLen(0);i++)
	for(unsigned int j=0;j<aMultiFFT.getDimLen(1);j++)
		aMultiFFT(i,j)=lmtc::ComplexNumber(lmtc::averageRandom(0,10),lmtc::averageRandom(0,10));
lmtc::Array<lmtc::ComplexNumber> yMultiFFT=lmtc::FastFourierTransform::fft(aMultiFFT);
lmtc::Array<lmtc::ComplexNumber> a1MultiFFT=lmtc::FastFourierTransform::_fft(yMultiFFT);
std::cout<<"高维傅里叶变换"<<std::endl;
std::cout<<"aMultiFFT:"<<std::endl;
for(unsigned int i=0;i<aMultiFFT.getDimLen(0);i++){
	for(unsigned int j=0;j<aMultiFFT.getDimLen(1);j++)
		std::cout<<(std::string)aMultiFFT(i,j)<<", ";
	std::cout<<std::endl;
}
std::cout<<"yMultiFFT:"<<std::endl;
for(unsigned int i=0;i<yMultiFFT.getDimLen(0);i++){
	for(unsigned int j=0;j<yMultiFFT.getDimLen(1);j++)
		std::cout<<(std::string)yMultiFFT(i,j)<<", ";
	std::cout<<std::endl;
}
std::cout<<"a1MultiFFT:"<<std::endl;
for(unsigned int i=0;i<a1MultiFFT.getDimLen(0);i++){
	for(unsigned int j=0;j<a1MultiFFT.getDimLen(1);j++)
		std::cout<<(std::string)a1MultiFFT(i,j)<<", ";
	std::cout<<std::endl;
}
for(unsigned int i=0;i<a1MultiFFT.getDimLen(0);i++)
	for(unsigned int j=0;j<a1MultiFFT.getDimLen(1);j++){
		if(i<aMultiFFT.getDimLen(0)&&j<aMultiFFT.getDimLen(1)){
			if(!aMultiFFT(i,j).equal(a1MultiFFT(i,j),0.00001))
				std::cout<<"error:"<<(std::string)a1MultiFFT(i,j)<<"==?"<<(std::string)aMultiFFT(i,j)<<"   "<<std::endl;
		}else{
			if(!a1MultiFFT(i,j).equal(0,0.00001))
				std::cout<<"error1:"<<(std::string)a1MultiFFT(i,j)<<"==?"<<0<<"   "<<std::endl;
		}
	}
std::cout<<std::endl;//*/

///*多维卷积测试
std::cout<<"多维卷积测试："<<std::endl;
lmtc::Array<lmtc::ComplexNumber> mutiAvec(2,3,2);
lmtc::Array<lmtc::ComplexNumber> mutiBvec(3,2,3,3);
mutiAvec(1,1)=1;
mutiAvec(2,1)=2;
mutiAvec(0,1)=4;
mutiBvec(1,1,1)=3;
mutiBvec(1,2,0)=6;
mutiBvec(0,1,2)=5;
lmtc::Array<lmtc::ComplexNumber>mutiCvec=lmtc::Algebra::convolution(mutiAvec,mutiBvec);
std::cout<<"多维卷积为："<<std::endl;
std::vector<unsigned int> dimC(mutiCvec.getDimNum(),0);
while(dimC[mutiCvec.getDimNum()-1]<mutiCvec.getDimLen(mutiCvec.getDimNum()-1)){//将a中元素复制到正合幂数组a1
	if(!mutiCvec(dimC).equal(0,0.001)){
		std::cout<<"mutiCvec(";
		for(unsigned int i=0;i<dimC.size();i++)
			std::cout<<dimC[i]<<"  ";
		std::cout<<")   =   "<<(std::string)mutiCvec(dimC)<<std::endl;
	}
	for(unsigned int i=0;i<mutiCvec.getDimNum();i++){//计算多维数组遍历的下一个坐标
		if(dimC[i]!=(mutiCvec.getDimLen(i)-1)){
			dimC[i]++;
			break;
		}else if(i!=(mutiCvec.getDimNum()-1))
			dimC[i]=0;
		else
			dimC[i]++;
	}
}
std::cout<<std::endl;//*/


std::cout<<"all test over!!!"<<std::endl;
	return 0;//表示成功执行
}


