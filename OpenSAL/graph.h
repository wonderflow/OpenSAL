#ifndef graphConst
#define graphConst
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

#include <vector>
#include <list>
#include <queue>
#include "mySort.h"
#include "nonIntersectSet.h"
#include "fibonacciHeap.h"
#include "hash.h"
#include "numberTheory.h"
#include "myException.h"
#include "array.h"


/*图论中通用数据结构和图处理的通用算法*/
namespace lmtc{

	//边的类模板，一般指有向边。
	template<typename T>
	class Edge{
	public:
		unsigned int vSt;
		unsigned int vEd;
		T data;
	public:
		Edge(unsigned int v_st,unsigned int v_ed,const T &t):vSt(v_st),vEd(v_ed),data(t){}
		Edge(unsigned int v_st,unsigned int v_ed):vSt(v_st),vEd(v_ed),data(){}
		bool operator==(const Edge<T> &e)const{return vSt==e.vSt&&vEd==e.vEd;}
	};
	
	/*图论类，包含图论中常用算法，都以静态接口形式呈现
	  邻接矩阵（有向图或无向图，无向图的边出现两次）用lmtc::Array<T>(2,vN,vN)表示,T表示权类型，vN表示顶点数。值为零表示不连接，否则元素值表示权重
	  邻接表类型（有向图或无向图，无向图的边出现两次）std::vector<std::list<Edge<T>>>*/
	class Graph{
	public:
		//由邻接矩阵ajacencyMatrix转换成邻接表，结果存至ajacencyList。如果ajacencyMatrix不符合邻接矩阵要求，将置空ajacencyList。
		//O(V*V)
		template<typename T>
		static void ajacencyMatrixToList(const Array<T> &ajacencyMatrix,std::vector<std::list<Edge<T>>> &ajacencyList);

		//转置邻接表ajacencyList，结果存至transposedAjacencyList。必须保证ajacencyList为正确的邻接表。
		//O(V+E)
		template<typename T>
		static void transposeAjacencyList(const std::vector<std::list<Edge<T>>> &ajacencyList,std::vector<std::list<Edge<T>>> &transposedAjacencyList);

		/*广度和深度优先遍历及基于此的基本图算法*/
		//通用广度优先遍历（整个广度优先森林），需保证邻接表正确，该接口没有任何实际功能，仅作为待重用代码。
		template<typename T>
		static void bfs(const std::vector<std::list<Edge<T>>> &ajacencyList,const unsigned int s=0);

		//通用深度优先遍历（整个深度优先森林），需保证邻接表正确，该接口没有任何实际功能，仅作为待重用代码。
		template<typename T>
		static void dfs(const std::vector<std::list<Edge<T>>> &ajacencyList,const unsigned int s=0);

		//利用深度优先遍历确定有向图或者无向图是否存在回路，需保证邻接表正确。需要利用参数isDirectedGraph区分有向图或者无向图。
		//O(E)
		template<typename T>
		static bool hasLoop(const std::vector<std::list<Edge<T>>> &ajacencyList,bool isDirectedGraph=true);

		//通用深度优先遍历进行有向图拓扑排序，需保证邻接表正确。返回拓扑有序序列向量，如果是有环图，则返回空向量。
		//O(E+V)
		template<typename T>
		static std::vector<unsigned int> topologicalSort(const std::vector<std::list<Edge<T>>> &ajacencyList);

		//利用深度优先遍历找出有向图（无向图亦可）所有强连通分支，需保证邻接表ajacencyList正确。结果存在strongConnectComponents
		//O(E+VlgV)，VlgV时间主要花在第二次深度优先遍历时按时间戳排序。
		template<typename T>
		static void computeStrngConctComps(const std::vector<std::list<Edge<T>>> &ajacencyList,std::vector<std::vector<unsigned int>> &strongConnectComponents);

		//利用变形的深度优先遍历计算有向图或无向图的欧拉环，需保证邻接表ajacencyList正确。存在欧拉环返回true（结果存于EulerCircuit），否则返回false（EulerCircuit置空）。
		//O(V+E)，需要利用参数isDirectedGraph区分有向图或者无向图，当为无向图时利用散列进行边的逻辑删除，因此时间复杂度与有向图的是相同的。
		template<typename T>
		static bool computeEulerCircuit(const std::vector<std::list<Edge<T>>> &ajacencyList,std::list<Edge<T>> &EulerCircuit,bool isDirectedGraph=true);
	
		/*最小生成树问题*/
		//Kruskal计算无向图最小生成树，不连通则计算最小生成森林，允许图中有自环。采用不相交集合实现。
		//O(ElgE)
		template<typename T>
		static T mstKruskal(const std::vector<std::list<Edge<T>>> &ajacencyList,std::vector<std::list<Edge<T>>> &mstAjacencyList);

		//Prim计算无向图最小生成树，不连通则计算最小生成森林，允许图中有自环。采用斐波那契堆实现。
		//O(E+VlgV)
		template<typename T>
		static T mstPrim(const std::vector<std::list<Edge<T>>> &ajacencyList,std::vector<std::list<Edge<T>>> &mstAjacencyList);

		/*最短路径问题*/
		//Bellman-Ford算法，s表示原顶点序号，可判断是否有负回路（有向图或者无向图），允许图中有负权边。
		//最短路径树结果存于父节点向量p和距离向量d，如果有负回路则p和d向量表示找到的树并非最短路径树且返回false，否则返回true。
		//O(V*E)
		template<typename T>
		static bool shortestPathBellmanFord(const std::vector<std::list<Edge<T>>> &ajacencyList,const unsigned int s,std::vector<unsigned int> &p,std::vector<T> &d);
		
		//有向无回路图的单源最短路径，s表示原顶点序号，如果有回路则返回false且置空p、d向量，否则返回true。
		//最短路径树结果存于父节点向量p和距离向量d，如果有回路则返回false，否则返回true。
		//O(V+E)
		template<typename T>
		static bool shortestPathOfDag(const std::vector<std::list<Edge<T>>> &ajacencyList,const unsigned int s,std::vector<unsigned int> &p,std::vector<T> &d);

		//dijkstra算法（要求无负边），s表示原顶点序号，如果有负边则返回false且置空p、d向量，否则返回true。
		//最短路径树结果存于父节点向量p和距离向量d。如果非源顶点的父节点为自身，则不存在其到源顶点的路径。
		//O(E+VlgV)
		template<typename T>
		static bool shortestPathDijkstra(const std::vector<std::list<Edge<T>>> &ajacencyList,const unsigned int s,std::vector<unsigned int> &p,std::vector<T> &d);

		//利用快速矩阵乘法实现每对顶点间的最短路径，O(V^e*lgV),e<3。参见《算法导论p385》，略。

		//Floyd-Warshall算法，假设输入图不存在负回路。
		//最短路径森林结果存于父节点矩阵p和距离矩阵d。如果非源顶点的父节点为自身，则不存在其到源顶点的路径。
		//O(V^3)。参见《算法导论p387》
		template<typename T>
		static void shortestPathAllFloydWarshall(const std::vector<std::list<Edge<T>>> &ajacencyList,Array<unsigned int> &p,Array<T> &d);
		
		//Johnson算法，能够判断是否存在负回路。
		//最短路径森林结果存于父节点矩阵p和距离矩阵d。如果非源顶点的父节点为自身，则不存在其到源顶点的路径。
		//如果存在负回路，则置空p，d并返回false，否则返回true
		//O(V^2*lgV+VE)。参见《算法导论p391》
		template<typename T>
		static bool shortestPathAllJohnson(const std::vector<std::list<Edge<T>>> &ajacencyList,Array<unsigned int> &p,Array<T> &d);

		/*最大流问题*/
		//FordFulkerson_EdmondsKarp算法。思路为不断利用广度优先搜索寻找残余网络中的增广路径来增加流。
		//要求ajacencyList无负边(负边可事先转成反向正边，但本算法不负责此转换），起点s和汇点t，算法将自动忽略自环和s的入边以及t的出边，最大流网络存于flow之中，返回最大流的值。
		//O(V*E^2)。参见《算法导论p397-408》
		template<typename T>
		static T maximumFlowFordFulkerson_EdmondsKarp(const std::vector<std::list<Edge<T>>> &ajacencyList,const unsigned int s,const unsigned int t,std::vector<std::list<Edge<T>>> &flow);

		//Relabel_To_Front算法。思路为不断对容许网络拓扑排序中第一个溢出节点进行压入和重标记操作以使之不再溢出。
		//要求ajacencyList无负边(负边可事先转成反向正边，但本算法不负责此转换），起点s和汇点t，算法将自动忽略自环和s的入边以及t的出边，最大流网络存于flow之中，返回最大流的值。
		//O(V^3)。参见《算法导论p411-425》
		template<typename T>
		static T maximumFlowPushRelabelToFront(const std::vector<std::list<Edge<T>>> &ajacencyList,const unsigned int s,const unsigned int t,std::vector<std::list<Edge<T>>> &flow);
	
		//多源点多汇点网络流问题《算法导论p399》，最大二分匹配问题《算法导论p409》都可转化为单源点单汇点的网络流问题。
	private:
		//定义表示遍历过程中顶点颜色的枚举类型
		typedef enum{WHITE,GRAY,BLACK} Color; 

		//通用深度优先遍历（某棵深度优先树），需保证邻接表正确
		template<typename T>
		static void dfs_visit(const std::vector<std::list<Edge<T>>> &ajacencyList,const unsigned int u,std::vector<unsigned int> &d,std::vector<unsigned int> &f,std::vector<int> &p,std::vector<Color> &color,unsigned int &time);

		//利用深度优先遍历确定从某节点开始的深度优先树是否存在一回路，需保证邻接表正确
		template<typename T>
		static bool has_loop_visit(const std::vector<std::list<Edge<T>>> &ajacencyList,const unsigned int u,std::vector<unsigned int> &d,std::vector<unsigned int> &f,std::vector<int> &p,std::vector<Color> &color,unsigned int &time,bool isDirectedGraph);

		//通用深度优先遍历进行拓扑排序（仅对某棵深度优先树），需保证邻接表正确
		template<typename T>
		static void topologicalSort_visit(std::vector<unsigned int> &order,const std::vector<std::list<Edge<T>>> &ajacencyList,const unsigned int u,std::vector<unsigned int> &d,std::vector<unsigned int> &f,std::vector<int> &p,std::vector<Color> &color,unsigned int &time);

		//利用变形的深度优先遍历计算有向图的欧拉环（仅对某棵深度优先树），需保证邻接表ajacencyList正确。存在欧拉环返回true（结果存于EulerCircuit），否则返回false（EulerCircuit置空）。
		template<typename T>
		static bool computeEulerCircuit_visit(std::vector<std::list<Edge<T>>> &ajacencyList,std::list<Edge<T>> &EulerCircuit,const unsigned int s,bool isDirectedGraph,CompleteHash<unsigned long> &hash);

		//用于斐波那契堆的边 比较函数
		template<typename T>
		static bool pri_comp_edge(const Edge<T> &a,const Edge<T> &b){return a.data<b.data;}

		//用于散列的边相等比较函数
		template<typename T>
		static bool edge_equal(const Edge<T> &a,const Edge<T> &b){return a.vSt==b.vSt&&a.vEd==b.vEd;}

		//用于散列的默认键值转换函数
		template<typename T>
		static unsigned long key_to_number(const T &t){return t;}

		//用于散列的边转值函数,要求顶点数不超过100000。
		template<typename T>
		static unsigned long edge_to_number(const Edge<T> &e){return e.vSt*100000+e.vEd;}
	};
	
	//由邻接矩阵转换成邻接表，存至ajacencyList。如果ajacencyMatrix不符合邻接矩阵要求，将置空ajacencyList。
	template<typename T>
	void Graph::ajacencyMatrixToList(const Array<T> &ajacencyMatrix,std::vector<std::list<Edge<T>>> &ajacencyList){
		ajacencyList.clear();
		if(ajacencyMatrix.getDimNum()!=2||ajacencyMatrix.getDimLen(0)!=ajacencyMatrix.getDimLen(1))
			return;
		ajacencyList.resize(ajacencyMatrix.getDimLen(0));
		for(unsigned int i=0;i<ajacencyList.size();i++){
			for(unsigned int j=0;j<ajacencyMatrix.getDimLen(1);j++){
				if(ajacencyMatrix(i,j)==0)
					continue;
				ajacencyList[i].push_back(Edge<T>(i,j,ajacencyMatrix(i,j)));
			}
		}
	}

	//转置邻接表，存至transposedAjacencyList。必须保证ajacencyList为正确的邻接表。
	template<typename T>
	void Graph::transposeAjacencyList(const std::vector<std::list<Edge<T>>> &ajacencyList,std::vector<std::list<Edge<T>>> &transposedAjacencyList){
		transposedAjacencyList.clear();
		transposedAjacencyList.resize(ajacencyList.size());
		for(unsigned int i=0;i<ajacencyList.size();i++)
			for(std::list<Edge<T>>::const_iterator iter=ajacencyList[i].begin();iter!=ajacencyList[i].end();iter++)
				transposedAjacencyList[iter->vEd].push_back(Edge<T>(iter->vEd,iter->vSt,iter->data));
	}

	//通用广度优先遍历，需保证邻接表正确
	template<typename T>
	void Graph::bfs(const std::vector<std::list<Edge<T>>> &ajacencyList,const unsigned int s)
	{
		if(s>=ajacencyList.size())//源顶点超出邻接表范围
			return;
		/*定义一些遍历信息，其中d[u]表示u的深度，
		  p[u]表示u的父顶点（p[u]==-1表示u为根），
		  color[u]表示u的颜色， 
		  还可以定义其他的遍历信息......
		*/
		std::vector<unsigned int> d(ajacencyList.size());
		std::vector<int> p(ajacencyList.size());
		std::vector<Color> color(ajacencyList.size());
		for(unsigned int u=0;u<ajacencyList.size();u++){//初始化遍历信息
			d[u]=0;
			p[u]=-1;
			color[u]=WHITE;
		}

		/*f(?)加入遍历之前用户代码*/

		//利用先进先出队列进行遍历
		std::queue<unsigned int> Q;
		unsigned int x=s;
		do{
			if(color[x]==WHITE){

				/*f(?)加入分支根顶点被发现之时用户代码*/

				color[x]=GRAY;
				Q.push(x);
			}
			//对某联通分支进行遍历
			while(!Q.empty()){
				unsigned int u=Q.front();
				Q.pop();

				/*f(?)加入顶点被扩展之前用户代码*/

				for(std::list<Edge<T>>::const_iterator iter=ajacencyList[u].begin();iter!=ajacencyList[u].end();iter++){
					unsigned int v=iter->vEd;
					if(color[v]==WHITE){

						/*f(?)加入顶点被发现之时用户代码*/

						color[v]=GRAY;
						d[v]=d[u]+1;
						p[v]=u;
						Q.push(v);
					}
				}
				color[u]=BLACK;

				/*f(?)加入顶点u被扩展之后用户代码*/

			}
			x=(x+1)%ajacencyList.size();
		}while(x!=s);//遍历各联通分支

		/*f(?)遍历完毕后的用户代码*/

	}

	//通用深度优先遍历（某棵深度优先树），需保证邻接表正确
	template<typename T>
	void Graph::dfs_visit(const std::vector<std::list<Edge<T>>> &ajacencyList,const unsigned int u,std::vector<unsigned int> &d,std::vector<unsigned int> &f,std::vector<int> &p,std::vector<Color> &color,unsigned int &time){
		color[u]=GRAY;
		d[u]=++time;
		
		/*f(?)加入顶点u被发现之时用户代码*/

		for(std::list<Edge<T>>::const_iterator iter=ajacencyList[u].begin();iter!=ajacencyList[u].end();iter++){
			unsigned int v=iter->vEd;
			if(color[v]==WHITE){
				p[v]=u;
				dfs_visit(ajacencyList,v,d,f,p,color,time);
			}
		}
		color[u]=BLACK;
		f[u]=++time;

		/*f(?)加入顶点u访问结束用户代码*/
		//std::cout<<u<<std::endl;
	}

	//通用深度优先遍历（整个深度优先森林），需保证邻接表正确
	template<typename T>
	void Graph::dfs(const std::vector<std::list<Edge<T>>> &ajacencyList,const unsigned int s){
		if(s>=ajacencyList.size())//源顶点超出邻接表范围
			return;
		/*定义一些遍历信息，其中
		  d[u]表示u被发现的时间戳，f[u]表示u为根的子树被遍历完毕的时间戳
		  p[u]表示u的父顶点（p[u]==-1表示u为根），
		  color[u]表示u的颜色， 
		  time表示时间戳计数器
		  还可以定义其他的遍历信息......
		*/
		std::vector<unsigned int> d(ajacencyList.size());
		std::vector<unsigned int> f(ajacencyList.size());
		std::vector<int> p(ajacencyList.size());
		std::vector<Color> color(ajacencyList.size());
		unsigned int time=0;
		for(unsigned int u=0;u<ajacencyList.size();u++){//初始化遍历信息
			p[u]=-1;
			color[u]=WHITE;
		}

		/*f(?)加入遍历之前用户代码*/

		//遍历深度优先森林
		unsigned int u=s;
		do{
			if(color[u]==WHITE)
				dfs_visit(ajacencyList,u,d,f,p,color,time);//遍历某深度优先树
			u=(u+1)%ajacencyList.size();
		}while(u!=s);
		
		/*f(?)加入遍历完毕后的用户代码*/

	}

	//利用深度优先遍历确定从某节点开始的深度优先树是否存在一回路，需保证邻接表正确
	template<typename T>
	bool Graph::has_loop_visit(const std::vector<std::list<Edge<T>>> &ajacencyList,const unsigned int u,std::vector<unsigned int> &d,std::vector<unsigned int> &f,std::vector<int> &p,std::vector<Color> &color,unsigned int &time,bool isDirectedGraph){
		color[u]=GRAY;
		d[u]=++time;
		for(std::list<Edge<T>>::const_iterator iter=ajacencyList[u].begin();iter!=ajacencyList[u].end();iter++){
			unsigned int v=iter->vEd;
			if(color[v]==WHITE){
				p[v]=u;
				if(true==has_loop_visit(ajacencyList,v,d,f,p,color,time,isDirectedGraph))
					return true;
			}else if(color[v]==GRAY){
				if(isDirectedGraph==true)//如果新发现的节点为灰色，且为有向图则肯定存在回路
					return true;
				else if(p[u]!=v)//如果新发现的节点为灰色，且为无向图，则u的父亲不为v才有环。
					return true;
			}
		}
		color[u]=BLACK;
		f[u]=++time;
		return false;
	}

	//利用深度优先遍历确定是否存在回路，需保证邻接表正确
	template<typename T>
	bool Graph::hasLoop(const std::vector<std::list<Edge<T>>> &ajacencyList,bool isDirectedGraph){
		if(ajacencyList.empty())//源顶点超出邻接表范围
			return false;
		std::vector<unsigned int> d(ajacencyList.size());
		std::vector<unsigned int> f(ajacencyList.size());
		std::vector<int> p(ajacencyList.size());
		std::vector<Color> color(ajacencyList.size());
		unsigned int time=0;
		for(unsigned int u=0;u<ajacencyList.size();u++){//初始化遍历信息
			p[u]=-1;
			color[u]=WHITE;
		}
		unsigned int u=0;
		do{
			if(color[u]==WHITE)
				if(true==has_loop_visit(ajacencyList,u,d,f,p,color,time,isDirectedGraph))//遍历某深度优先树
					return true;
			u=(u+1)%ajacencyList.size();
		}while(u!=0);
		return false;
	}

	//通用深度优先遍历进行拓扑排序，需保证邻接表正确
	template<typename T>
	void Graph::topologicalSort_visit(std::vector<unsigned int> &order,const std::vector<std::list<Edge<T>>> &ajacencyList,const unsigned int u,std::vector<unsigned int> &d,std::vector<unsigned int> &f,std::vector<int> &p,std::vector<Color> &color,unsigned int &time){
		color[u]=GRAY;
		d[u]=++time;
		for(std::list<Edge<T>>::const_iterator iter=ajacencyList[u].begin();iter!=ajacencyList[u].end();iter++){
			unsigned int v=iter->vEd;
			if(color[v]==WHITE){
				p[v]=u;
				topologicalSort_visit(order,ajacencyList,v,d,f,p,color,time);
			}
		}
		color[u]=BLACK;
		f[u]=++time;
		order.push_back(u);
	}


	//通用深度优先遍历进行拓扑排序，需保证邻接表正确
	template<typename T>
	std::vector<unsigned int> Graph::topologicalSort(const std::vector<std::list<Edge<T>>> &ajacencyList){
		if(ajacencyList.empty()||hasLoop(ajacencyList))//邻接表为空或者有回路，则返回空向量
			return std::vector<unsigned int>();
		std::vector<unsigned int> order;//拓扑有序序列存储向量
		//进行深度优先遍历，遍历过程即完成order序列的生成。
		std::vector<unsigned int> d(ajacencyList.size());
		std::vector<unsigned int> f(ajacencyList.size());
		std::vector<int> p(ajacencyList.size());
		std::vector<Color> color(ajacencyList.size());
		unsigned int time=0;
		for(unsigned int u=0;u<ajacencyList.size();u++){
			p[u]=-1;
			color[u]=WHITE;
		}
		unsigned int u=0;
		do{
			if(color[u]==WHITE)
				topologicalSort_visit(order,ajacencyList,u,d,f,p,color,time);
			u=(u+1)%ajacencyList.size();
		}while(u!=0);

		std::reverse(order.begin(),order.end());
		return order;
	}


	//利用深度优先遍历找出所有的强连通分支，需保证邻接表正确
	template<typename T>
	void Graph::computeStrngConctComps(const std::vector<std::list<Edge<T>>> &ajacencyList,std::vector<std::vector<unsigned int>> &strongConnectComponents){
		strongConnectComponents.clear();
		//深度优先遍历计算结束时间戳
		if(ajacencyList.empty())//邻接表为空
			return ;
		std::vector<unsigned int> d(ajacencyList.size());
		std::vector<unsigned int> f(ajacencyList.size());
		std::vector<int> p(ajacencyList.size());
		std::vector<Color> color(ajacencyList.size());
		unsigned int time=0;
		for(unsigned int u=0;u<ajacencyList.size();u++){//初始化遍历信息
			p[u]=-1;
			color[u]=WHITE;
		}
		unsigned int u=0;
		do{
			if(color[u]==WHITE)
				dfs_visit(ajacencyList,u,d,f,p,color,time);//遍历某深度优先树
			u=(u+1)%ajacencyList.size();
		}while(u!=0);

		//计算按结束时间戳降序序列
		std::vector<unsigned int> order(ajacencyList.size());
		for(unsigned int i=0;i<ajacencyList.size();i++)
			order[i]=i;
		mergeSort(order,f,0,ajacencyList.size()-1);
		std::reverse(order.begin(),order.end());
		//获得转置邻接表
		std::vector<std::list<Edge<T>>> transposedAjacencyList;
		transposeAjacencyList(ajacencyList,transposedAjacencyList);
		//重置颜色为白色
		for(unsigned int u=0;u<ajacencyList.size();u++)
			color[u]=WHITE;
		//按结束时间戳降序序列对转置邻接表进行深度遍历产生各连通分支
		for(unsigned int i=0;i<order.size();i++)
		{
			if(color[order[i]]==WHITE){
				strongConnectComponents.push_back(std::vector<unsigned int>());
				strongConnectComponents.back().push_back(order[i]);
				dfs_visit(transposedAjacencyList,order[i],d,f,p,color,time);
			}else
				strongConnectComponents.back().push_back(order[i]);
		}
	}

	//利用深度优先遍历计算欧拉环（仅对某棵深度优先树），需保证邻接表ajacencyList正确。存在欧拉环返回true（结果存于EulerCircuit），否则返回false。不可能返回false
	template<typename T>
	static bool Graph::computeEulerCircuit_visit(std::vector<std::list<Edge<T>>> &ajacencyList,std::list<Edge<T>> &EulerCircuit,const unsigned int s,bool isDirectedGraph,CompleteHash<unsigned long> &hash){
		while(!ajacencyList[s].empty()){
			Edge<T> e=ajacencyList[s].front();
			ajacencyList[s].pop_front();
			if(isDirectedGraph==false&&hash.search(std::max(e.vSt,e.vEd)*ajacencyList.size()+std::min(e.vSt,e.vEd))!=NULL)//如果为无向图且该边已扩展，则跳过。
				continue;
			//if(!EulerCircuit.empty()&&EulerCircuit.back().vEd!=s)//没必要进行检查。
				//return false;
			EulerCircuit.push_back(e);
			if(isDirectedGraph==false)
				hash.insert(std::max(e.vSt,e.vEd)*ajacencyList.size()+std::min(e.vSt,e.vEd));
			if(false==computeEulerCircuit_visit(ajacencyList,EulerCircuit,e.vEd,isDirectedGraph,hash))
				return false;
		}
		if(!EulerCircuit.empty()){
			if(EulerCircuit.back().vEd!=EulerCircuit.front().vSt)//如果当前节点扩展完毕，则EulerCircuit必须为欧拉环路
				return false;
			EulerCircuit.push_front(EulerCircuit.back());
			EulerCircuit.pop_back();
		}
		return true;
	}

	//利用深度优先遍历计算欧拉环（针对所有深度优先树，但只允许欧拉环包含在一棵深度优先树中），需保证邻接表ajacencyList正确。存在欧拉环返回true（结果存于EulerCircuit），否则返回false（EulerCircuit置空）。
	template<typename T>
	static bool Graph::computeEulerCircuit(const std::vector<std::list<Edge<T>>> &ajacencyList,std::list<Edge<T>> &EulerCircuit,bool isDirectedGraph){
		EulerCircuit.clear();
		if(ajacencyList.empty())//邻接表为空，则存在空的欧拉回路
			return true;
		std::vector<std::list<Edge<T>>> ajacencyListCopy=ajacencyList;
		//如果为无向图，则计算边数并设置哈希表槽数，采用全域散列
		CompleteHash<unsigned long> hash(1,lmtc::MAX_PRIME,key_to_number);
		if(isDirectedGraph==false){
			unsigned int count=1;
			for(unsigned int i=0;i<ajacencyList.size();i++)
				count+=ajacencyList[i].size();
			hash.resetSlotNumber(count);
		}
		unsigned int u=0;
		do{
			if(EulerCircuit.empty()&&!ajacencyListCopy[u].empty()){
				if(false==computeEulerCircuit_visit(ajacencyListCopy,EulerCircuit,u,isDirectedGraph,hash)){
					EulerCircuit.clear();
					return false;
				}
			}else if(!EulerCircuit.empty()&&!ajacencyListCopy[u].empty()){
				EulerCircuit.clear();
				return false;
			}
			u=(u+1)%ajacencyListCopy.size();
		}while(u!=0);
		return true;
	}

	//Kruskal计算最小生成树
	template<typename T>
	static T Graph::mstKruskal(const std::vector<std::list<Edge<T>>> &ajacencyList,std::vector<std::list<Edge<T>>> &mstAjacencyList){
		mstAjacencyList.clear();
		mstAjacencyList.resize(ajacencyList.size());
		if(ajacencyList.empty())
			return 0;
		//每个顶点构成一集合
		std::vector<lmtc::NonIntersectSet<unsigned int>> setVec;
		for(unsigned int i=0;i<ajacencyList.size();i++)
			setVec.push_back(NonIntersectSet<unsigned int>(i));
		//从邻接表获得边集向量和对应的权值向量，并将边集向量按权值排序
		std::vector<Edge<T>> edgVec;
		std::vector<T> valueVec;
		for(unsigned int i=0;i<ajacencyList.size();i++){
			for(std::list<Edge<T>>::const_iterator iter=ajacencyList[i].begin();iter!=ajacencyList[i].end();iter++){
				if(iter->vSt<iter->vEd){
					edgVec.push_back(*iter);
					valueVec.push_back(iter->data);
				}
			}
		}
		sort(edgVec,valueVec);
		T treeWeight=0;
		//按权值从小到大考虑各边，如果两端点不属于同一集合则将边加入最小生成树的邻接表，并合并两集合
		for(std::vector<Edge<T>>::iterator iter=edgVec.begin();iter!=edgVec.end();iter++){
			if(!(setVec[iter->vSt].find()==setVec[iter->vEd].find())){
				setVec[iter->vSt].unionSet(setVec[iter->vEd]);
				mstAjacencyList[iter->vSt].push_back(*iter);
				mstAjacencyList[iter->vEd].push_back(Edge<T>(iter->vEd,iter->vSt,iter->data));
				treeWeight+=iter->data;
			}
		}
		return treeWeight;
	}

	//Prim计算最小生成树
	template<typename T>
	static T Graph::mstPrim(const std::vector<std::list<Edge<T>>> &ajacencyList,std::vector<std::list<Edge<T>>> &mstAjacencyList){	
		mstAjacencyList.clear();
		mstAjacencyList.resize(ajacencyList.size());
		if(ajacencyList.empty())
			return 0;
		//获得最大权重上限
		T max=0;
		for(unsigned int i=0;i<ajacencyList.size();i++)
			for(std::list<Edge<T>>::const_iterator iter=ajacencyList[i].begin();iter!=ajacencyList[i].end();iter++)
				if(max<iter->data)
					max=iter->data;
		max+=1;
		//存储每个顶点信息的斐波那契堆和堆节点向量，顶点信息存储于Edge<T>中，vSt表示顶点号，vEd表示vSt连接到当前生成树的最近顶点，data表示连接到当前生成树的最小权重
		FibonacciHeap<Edge<T>> Q(pri_comp_edge);
		std::vector<FibonacciHeap<Edge<T>>::ItemType> itemVec;
		//顶点是否输入优先队列向量
		std::vector<bool> blgVec(ajacencyList.size(),true);
		//从顶点0开始
		itemVec.push_back(Q.insert(Edge<T>(0,0,0)));
		//初始化各顶点信息，并存入斐波那契堆和堆节点向量
		for(unsigned int i=1;i<ajacencyList.size();i++)
			itemVec.push_back(Q.insert(Edge<T>(i,i,max)));
		while(!Q.isEmpty()){
			//抽取最小节点作为待扩展顶点，并更新与之相连顶点的信息
			Edge<T> u=Q.getItemValue(Q.extract_prio());
			blgVec[u.vSt]=false;
			for(std::list<Edge<T>>::const_iterator iter=ajacencyList[u.vSt].begin();iter!=ajacencyList[u.vSt].end();iter++){
				Edge<T> v=Q.getItemValue(itemVec[iter->vEd]);
				if(blgVec[v.vSt]&&iter->data<v.data)
					Q.increaseKey(itemVec[v.vSt],Edge<T>(v.vSt,u.vSt,iter->data));
			}
		}
		T treeWeight=0;
		//将最小生成树结果存入mstAjacencyList
		for(unsigned int i=1;i<ajacencyList.size();i++){
			Edge<T> u=Q.getItemValue(itemVec[i]);
			if(u.vSt==u.vEd){
				continue;
			}
			mstAjacencyList[u.vSt].push_back(u);
			mstAjacencyList[u.vEd].push_back(Edge<T>(u.vEd,u.vSt,u.data));
			treeWeight+=u.data;
		}
		return treeWeight;
	}

	template<typename T>
	static bool Graph::shortestPathBellmanFord(const std::vector<std::list<Edge<T>>> &ajacencyList,const unsigned int s,std::vector<unsigned int> &p,std::vector<T> &d){
		p.clear();
		d.clear();
		if(ajacencyList.empty())
			return true;
		if(s>=ajacencyList.size())
			throw GraphException("异常：shortestPathBellmanFord算法中原顶点序号超出范围！");
		//获得最大权重上限
		T max=0;
		for(unsigned int i=0;i<ajacencyList.size();i++)
			for(std::list<Edge<T>>::const_iterator iter=ajacencyList[i].begin();iter!=ajacencyList[i].end();iter++)
				if(max<iter->data)
					max=iter->data;
		max+=1;
		//初始化父节点向量和距离向量,原点距离清零
		p.resize(ajacencyList.size());
		d.resize(ajacencyList.size());
		for(unsigned int i=0;i<ajacencyList.size();i++){
			p[i]=i;
			d[i]=max*ajacencyList.size();
		}
		d[s]=0;
		//进行ajacencyList.size()-1遍对所有边的松弛，以此构筑最短路径树
		for(unsigned int c=1;c<ajacencyList.size();c++){
			for(unsigned int i=0;i<ajacencyList.size();i++)
				for(std::list<Edge<T>>::const_iterator iter=ajacencyList[i].begin();iter!=ajacencyList[i].end();iter++)
				{
					if(d[iter->vEd]>d[iter->vSt]+iter->data)
					{
						d[iter->vEd]=d[iter->vSt]+iter->data;
						p[iter->vEd]=iter->vSt;
					}
				}
		}
		//如果此时还有边可松弛，则必存在负回路
		for(unsigned int i=0;i<ajacencyList.size();i++)
			for(std::list<Edge<T>>::const_iterator iter=ajacencyList[i].begin();iter!=ajacencyList[i].end();iter++)
				if(d[iter->vEd]>d[iter->vSt]+iter->data)
					return false;
		return true;
	}

	template<typename T>
	static bool Graph::shortestPathOfDag(const std::vector<std::list<Edge<T>>> &ajacencyList,const unsigned int s,std::vector<unsigned int> &p,std::vector<T> &d){
		p.clear();
		d.clear();
		if(s>=ajacencyList.size())
			throw GraphException("异常：shortestPathOfDag算法中原顶点序号超出范围！");
		std::vector<unsigned int> order=topologicalSort(ajacencyList);
		if(order.empty())//表示有环或空图
			return false;
		//获得最大权重上限
		T max=0;
		for(unsigned int i=0;i<ajacencyList.size();i++)
			for(std::list<Edge<T>>::const_iterator iter=ajacencyList[i].begin();iter!=ajacencyList[i].end();iter++)
				if(max<iter->data)
					max=iter->data;
		max+=1;
		//初始化父节点向量和距离向量,原点距离清零
		p.resize(ajacencyList.size());
		d.resize(ajacencyList.size());
		for(unsigned int i=0;i<ajacencyList.size();i++){
			p[i]=i;
			d[i]=max*ajacencyList.size();
		}
		d[s]=0;
		//按拓扑排序顺序对各顶点的边进行松弛
		for(unsigned int i=0;i<order.size();i++)
			for(std::list<Edge<T>>::const_iterator iter=ajacencyList[order[i]].begin();iter!=ajacencyList[order[i]].end();iter++)
			{
				if(d[iter->vEd]>d[iter->vSt]+iter->data)
				{
					d[iter->vEd]=d[iter->vSt]+iter->data;
					p[iter->vEd]=iter->vSt;
				}
			}
		return true;
	}

	template<typename T>
	static bool  Graph::shortestPathDijkstra(const std::vector<std::list<Edge<T>>> &ajacencyList,const unsigned int s,std::vector<unsigned int> &p,std::vector<T> &d){
		p.clear();
		d.clear();
		if(ajacencyList.empty())
			return true;
		if(s>=ajacencyList.size())
			throw GraphException("异常：shortestPathBellmanFord算法中原顶点序号超出范围！");

		//获得最短路径权重上限,并确定不存在负边,如果存在负边，返回false。
		T max=0;
		for(unsigned int i=0;i<ajacencyList.size();i++)
			for(std::list<Edge<T>>::const_iterator iter=ajacencyList[i].begin();iter!=ajacencyList[i].end();iter++){
				if(iter->data<0)
					return false;
				if(max<iter->data)
					max=iter->data;
			}
		max*=ajacencyList.size();
		
		//存储每个顶点信息的斐波那契堆和堆节点向量，顶点信息存储于Edge<T>中，vSt表示顶点号，vEd表示vSt的当前最短路径父节点，data表示该顶点当前的最短路径长度上限
		FibonacciHeap<Edge<T>> Q(pri_comp_edge);
		std::vector<FibonacciHeap<Edge<T>>::ItemType> itemVec;
		//初始化各顶点信息，并存入斐波那契堆和堆节点向量
		for(unsigned int i=0;i<ajacencyList.size();i++)
			if(i==s)
				itemVec.push_back(Q.insert(Edge<T>(i,i,0)));
			else
				itemVec.push_back(Q.insert(Edge<T>(i,i,max)));
		while(!Q.isEmpty()){
			//抽取最小节点作为待扩展顶点，并松弛与之相连的各边
			Edge<T> u=Q.getItemValue(Q.extract_prio());
			for(std::list<Edge<T>>::const_iterator iter=ajacencyList[u.vSt].begin();iter!=ajacencyList[u.vSt].end();iter++){
				Edge<T> v=Q.getItemValue(itemVec[iter->vEd]);
				if(v.data>u.data+iter->data)
					Q.increaseKey(itemVec[v.vSt],Edge<T>(v.vSt,u.vSt,u.data+iter->data));
			}
		}
		//将最短路径树结果存至p,d,返回true。
		p.resize(ajacencyList.size());
		d.resize(ajacencyList.size());
		for(unsigned int i=0;i<ajacencyList.size();i++){
			Edge<T> u=Q.getItemValue(itemVec[i]);
			p[i]=u.vEd;
			d[i]=u.data;
		}
		return true;
	}

	template<typename T>
	static void Graph::shortestPathAllFloydWarshall(const std::vector<std::list<Edge<T>>> &ajacencyList,Array<unsigned int> &p,Array<T> &d){
		d.clear();
		p.clear();
		if(ajacencyList.empty())
			return ;
		//申明临时距离矩阵和父节点矩阵
		Array<T> d0(2,ajacencyList.size(),ajacencyList.size());
		Array<T> d1(2,ajacencyList.size(),ajacencyList.size());
		Array<unsigned int> p0(2,ajacencyList.size(),ajacencyList.size());
		Array<unsigned int> p1(2,ajacencyList.size(),ajacencyList.size());
		//获得最短路径权重上限。
		T max=0;
		for(unsigned int i=0;i<ajacencyList.size();i++)
			for(std::list<Edge<T>>::const_iterator iter=ajacencyList[i].begin();iter!=ajacencyList[i].end();iter++){
				if(max<iter->data)
					max=iter->data;
			}
		max*=ajacencyList.size();
		//初始化临时距离矩阵和父节点矩阵
		d0.initialize(max);
		d1.initialize(max);
		for(unsigned int i=0;i<ajacencyList.size();i++)
			for(unsigned int j=0;j<ajacencyList.size();j++){
				p0(i,j)=j;
				p1(i,j)=j;
			}
		for(unsigned int i=0;i<ajacencyList.size();i++)
			for(std::list<Edge<T>>::const_iterator iter=ajacencyList[i].begin();iter!=ajacencyList[i].end();iter++){
				d0(iter->vSt,iter->vEd)=iter->data;
				d1(iter->vSt,iter->vEd)=iter->data;
				p0(iter->vSt,iter->vEd)=iter->vSt;
				p1(iter->vSt,iter->vEd)=iter->vSt;
			}
		for(unsigned int i=0;i<ajacencyList.size();i++){
			d0(i,i)=0;
			d1(i,i)=0;
		}
		//动态规划计算迭代计算距离矩阵和父节点矩阵
		for(unsigned int k=0;k<ajacencyList.size();k++)
			for(unsigned int i=0;i<ajacencyList.size();i++)
				for(unsigned int j=0;j<ajacencyList.size();j++){
					if(k%2==0){
						d1(i,j)=std::min(d0(i,j),d0(i,k)+d0(k,j));
						if(d0(i,j)>d0(i,k)+d0(k,j))
							p1(i,j)=p0(k,j);
						else
							p1(i,j)=p0(i,j);
					}else{
						d0(i,j)=std::min(d1(i,j),d1(i,k)+d1(k,j));
						if(d1(i,j)>d1(i,k)+d1(k,j))
							p0(i,j)=p1(k,j);
						else
							p0(i,j)=p1(i,j);
					}
				}
		//保存最终结果至p，d
		if(ajacencyList.size()%2==0){
			p=p0;
			d=d0;
		}else{
			p=p1;
			d=d1;
		}
	}

	template<typename T>
	static bool Graph::shortestPathAllJohnson(const std::vector<std::list<Edge<T>>> &ajacencyList,Array<unsigned int> &p,Array<T> &d){
		unsigned int V=ajacencyList.size();
		//构建辅助图，并计算hv（dV）
		std::vector<std::list<Edge<T>>> ajacencyList1=ajacencyList;
		ajacencyList1.push_back(std::list<Edge<T>>());
		for(unsigned int i=0;i<V;i++)
			ajacencyList1[V].push_back(Edge<T>(V,i,0));
		std::vector<unsigned int> pV;
		std::vector<T> dV;//即相当于hv
		bool notHasNegLoop=shortestPathBellmanFord(ajacencyList1,V,pV,dV);
		if(notHasNegLoop==false){
			p.clear();
			d.clear();
			return false;
		}
		//重赋权
		ajacencyList1.pop_back();
		for(unsigned int i=0;i<ajacencyList1.size();i++)
			for(std::list<Edge<T>>::iterator iter=ajacencyList1[i].begin();iter!=ajacencyList1[i].end();iter++)
				iter->data+=(dV[iter->vSt]-dV[iter->vEd]);
		
		//对每个顶点运行Dijkstra算法
		std::vector<unsigned int> pTemp;
		std::vector<T> dTemp;
		Array<unsigned int> pM(2,V,V);
		Array<T> dM(2,V,V);
		for(unsigned int s=0;s<V;s++){
			shortestPathDijkstra(ajacencyList1,s,pTemp,dTemp);
			for(unsigned int i=0;i<V;i++){
				pM(s,i)=pTemp[i];
				dM(s,i)=dTemp[i]+dV[i]-dV[s];
			}
		}
		//存储最终结果
		p=pM;
		d=dM;
		return true;
	}

	template<typename T>
	static T Graph::maximumFlowFordFulkerson_EdmondsKarp(const std::vector<std::list<Edge<T>>> &ajacencyList,const unsigned int s,const unsigned int t,std::vector<std::list<Edge<T>>> &flow){
		if(ajacencyList.empty())
		{	
			flow.clear();
			return 0;
		}
		if(s>=ajacencyList.size()||t>=ajacencyList.size()||s==t)
			throw GraphException("异常：maximumFlowFordFulkerson_EdmondsKarp算法中始末顶点序号超出范围或二者相同！");
		//利用邻接表管理残留网络图结构，利用散列管理对应的流
		unsigned int count=1;
		for(unsigned int i=0;i<ajacencyList.size();i++)
			count+=ajacencyList[i].size();
		std::vector<std::list<Edge<T>>> flowGraph;
		flowGraph.resize(ajacencyList.size());
		CompleteHash<Edge<T>> flowHash(count*2,lmtc::MAX_PRIME,edge_to_number,edge_equal);
		for(unsigned int i=0;i<ajacencyList.size();i++)
			for(std::list<Edge<T>>::const_iterator iter=ajacencyList[i].begin();iter!=ajacencyList[i].end();iter++){
				if(iter->vSt==iter->vEd||iter->vSt==t||iter->vEd==s)//流网络忽略自环和s的入边以及t的出边
					continue;
				if(iter->data<0)
					throw GraphException("异常：maximumFlowFordFulkerson_EdmondsKarp算法中存在负边！");
				flowGraph[iter->vSt].push_back(*iter);
				flowHash.insert(Edge<T>(iter->vSt,iter->vEd,0));
			}
		for(unsigned int i=0;i<ajacencyList.size();i++)
			for(std::list<Edge<T>>::const_iterator iter=ajacencyList[i].begin();iter!=ajacencyList[i].end();iter++){
				if(iter->vSt==iter->vEd||iter->vSt==t||iter->vEd==s)//流网络忽略自环和s的入边以及t的出边
					continue;
				if(flowHash.search(Edge<T>(iter->vEd,iter->vSt))==NULL){
					flowGraph[iter->vEd].push_back(Edge<T>(iter->vEd,iter->vSt,0));
					flowHash.insert(Edge<T>(iter->vEd,iter->vSt,0));
				}
			}
		flowHash.completeHashOptimize();//完全散列

		//不断利用广度优先搜索寻找s至t的增广路径
		while(true){
			//初始化遍历信息
			std::vector<unsigned int> d(ajacencyList.size());
			std::vector<int> p(ajacencyList.size());
			std::vector<Color> color(ajacencyList.size());
			std::vector<T> cfp(ajacencyList.size());//各广度优先最短路径能够增加的流的最大值

			for(unsigned int u=0;u<ajacencyList.size();u++){
				d[u]=0;
				p[u]=-1;
				color[u]=WHITE;
				cfp[u]=-1;
			}
			//利用先进先出队列进行遍历
			std::queue<unsigned int> Q;
			color[s]=GRAY;
			Q.push(s);
			//对以s为根的联通分支进行遍历
			while(!Q.empty()){
				unsigned int u=Q.front();
				Q.pop();
				for(std::list<Edge<T>>::const_iterator iter=flowGraph[u].begin();iter!=flowGraph[u].end();iter++){
					T temp=iter->data-flowHash.search(Edge<T>(iter->vSt,iter->vEd))->data;
					if(temp<=0.0000000001)//避免浮点数相等相减不为零
						continue;
					unsigned int v=iter->vEd;
					if(color[v]==WHITE){
						color[v]=GRAY;
						d[v]=d[u]+1;
						p[v]=u;
						Q.push(v);
						if(u==s||temp<cfp[u])
							cfp[v]=temp;
						else
							cfp[v]=cfp[u];
					}
				}
				color[u]=BLACK;
			}
			
			if(p[t]==-1)//找不到增广路径
				break;
			unsigned int cur=t;
			while(p[cur]!=-1){
				flowHash.search(Edge<T>(p[cur],cur))->data+=cfp[t];
				flowHash.search(Edge<T>(cur,p[cur]))->data-=cfp[t];
				cur=p[cur];
			}
		}
		//将最大流网络存至flow，并计算最大流。
		flow.clear();
		flow.resize(ajacencyList.size());
		for(unsigned int i=0;i<ajacencyList.size();i++)
			for(std::list<Edge<T>>::const_iterator iter=ajacencyList[i].begin();iter!=ajacencyList[i].end();iter++){
				if(iter->vSt==iter->vEd||iter->vSt==t||iter->vEd==s)//流网络忽略自环和s的入边以及t的出边
					continue;
				T temp=flowHash.search(*iter)->data;
				if(temp>0)
					flow[iter->vSt].push_back(Edge<T>(iter->vSt,iter->vEd,temp));
			}
		T maxF=0;
		for(std::list<Edge<T>>::const_iterator iter=flow[s].begin();iter!=flow[s].end();iter++)
			maxF+=iter->data;
		return maxF;
	}

	//压入重标记前移算法
	template<typename T>
	static T Graph::maximumFlowPushRelabelToFront(const std::vector<std::list<Edge<T>>> &ajacencyList,const unsigned int s,const unsigned int t,std::vector<std::list<Edge<T>>> &flow){
		if(ajacencyList.empty())
		{	
			flow.clear();
			return 0;
		}
		if(s>=ajacencyList.size()||t>=ajacencyList.size()||s==t)
			throw GraphException("异常：maximumFlowPushRelabelToFront算法中始末顶点序号超出范围或二者相同！");
		//利用邻接表管理残留网络图结构，利用散列管理对应的前置流
		unsigned int count=1;
		for(unsigned int i=0;i<ajacencyList.size();i++)
			count+=ajacencyList[i].size();
		std::vector<std::list<Edge<T>>> flowGraph;
		flowGraph.resize(ajacencyList.size());
		CompleteHash<Edge<T>> flowHash(count*2,lmtc::MAX_PRIME,edge_to_number,edge_equal);
		for(unsigned int i=0;i<ajacencyList.size();i++)
			for(std::list<Edge<T>>::const_iterator iter=ajacencyList[i].begin();iter!=ajacencyList[i].end();iter++){
				if(iter->vSt==iter->vEd||iter->vSt==t||iter->vEd==s)//流网络忽略自环和s的入边以及t的出边
					continue;
				if(iter->data<0)
					throw GraphException("异常：maximumFlowPushRelabelToFront算法中存在负边！");
				flowGraph[iter->vSt].push_back(*iter);
				flowHash.insert(Edge<T>(iter->vSt,iter->vEd,0));
			}
		for(unsigned int i=0;i<ajacencyList.size();i++)
			for(std::list<Edge<T>>::const_iterator iter=ajacencyList[i].begin();iter!=ajacencyList[i].end();iter++){
				if(iter->vSt==iter->vEd||iter->vSt==t||iter->vEd==s)//流网络忽略自环和s的入边以及t的出边
					continue;
				if(flowHash.search(Edge<T>(iter->vEd,iter->vSt))==NULL){
					flowGraph[iter->vEd].push_back(Edge<T>(iter->vEd,iter->vSt,0));
					flowHash.insert(Edge<T>(iter->vEd,iter->vSt,0));
				}
			}
		flowHash.completeHashOptimize();//完全散列

		//初始化前置流
		std::vector<unsigned int> h(flowGraph.size(),0);
		std::vector<T> e(flowGraph.size(),0);
		h[s]=flowGraph.size();
		for(std::list<Edge<T>>::const_iterator iter=flowGraph[s].begin();iter!=flowGraph[s].end();iter++){
			flowHash.search(*iter)->data=iter->data;
			flowHash.search(Edge<T>(iter->vEd,iter->vSt))->data=-iter->data;
			e[iter->vEd]=iter->data;
			e[s]-=iter->data;
		}

		//L维护容许网络中顶点的拓扑排序
		std::list<unsigned int> L;
		for(unsigned int i=0;i<flowGraph.size();i++)
			if(i!=s&&i!=t)
				L.push_back(i);
		//current维护邻接表flowGraph各顶点的当前指针。
		std::vector<std::list<Edge<T>>::const_iterator> current;
		for(unsigned int i=0;i<flowGraph.size();i++)
			current.push_back(flowGraph[i].begin());
		std::list<unsigned int>::const_iterator u=L.begin();
		while(u!=L.end()){
			unsigned int old_height=h[*u];
			//DISCHARGE(u)
			while(e[*u]>0.0000000001){//即e[*u]>0
				std::list<Edge<T>>::const_iterator v=current[*u];
				if(v==flowGraph[*u].end()){
					//RELABEL(u)
					unsigned int minH=flowGraph.size()*2;
					for(std::list<Edge<T>>::const_iterator iter=flowGraph[*u].begin();iter!=flowGraph[*u].end();iter++)
						if(iter->data-flowHash.search(*iter)->data>0.0000000001)
							minH=std::min(minH,h[iter->vEd]);
					h[*u]=minH+1;
					current[*u]=flowGraph[*u].begin();
				}
				else if((v->data-flowHash.search(*v)->data>0.0000000001)&&((h[v->vSt]-h[v->vEd])==1)){
					//PUSH(u,v)
					T df=std::min(e[*u],v->data-flowHash.search(*v)->data);
					flowHash.search(*v)->data+=df;
					flowHash.search(Edge<T>(v->vEd,v->vSt))->data-=df;
					e[*u]-=df;
					e[v->vEd]+=df;
				}
				else
					current[*u]++;
			}
			if(h[*u]>old_height){
				unsigned int tempU=*u;
				L.erase(u);
				L.push_front(tempU);
				u=++L.begin();
			}
			else
				u++;
		}
	
		//将最大流网络存至flow，并计算最大流。
		flow.clear();
		flow.resize(ajacencyList.size());
		for(unsigned int i=0;i<ajacencyList.size();i++)
			for(std::list<Edge<T>>::const_iterator iter=ajacencyList[i].begin();iter!=ajacencyList[i].end();iter++){
				if(iter->vSt==iter->vEd||iter->vSt==t||iter->vEd==s)//流网络忽略自环和s的入边以及t的出边
					continue;
				T temp=flowHash.search(*iter)->data;
				if(temp>0)
					flow[iter->vSt].push_back(Edge<T>(iter->vSt,iter->vEd,temp));
			}
		T maxF=0;
		for(std::list<Edge<T>>::const_iterator iter=flow[s].begin();iter!=flow[s].end();iter++)
			maxF+=iter->data;
		return maxF;
	}
	

}

#endif