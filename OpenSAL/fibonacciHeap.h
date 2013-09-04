#ifndef fibonacciHeapConst
#define fibonacciHeapConst
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

#include "smartPtr.h"
#include "myException.h"
#include "defaultCompare.h"
#include <vector>
#include <iostream>
//斐波那契堆模板
namespace lmtc{

	template<typename T> class FibonacciHeap; //斐波那契堆模板申明

	template<typename T>  //堆节点模板申明
	class FibonacciHeapTreeItem{
	private://构造函数皆为私有，只有友元FibonacciHeap<T>能访问
		FibonacciHeapTreeItem():left(NULL),right(NULL),parent(NULL),child(NULL),mark(false),degree(0){}
		FibonacciHeapTreeItem(const T &t):data(t),left(NULL),right(NULL),parent(NULL),child(NULL),mark(false),degree(0){}
		FibonacciHeapTreeItem(const T &t, SmartPtr<FibonacciHeapTreeItem<T>> * pt, SmartPtr<FibonacciHeapTreeItem<T>> * chd, SmartPtr<FibonacciHeapTreeItem<T>> *lt, SmartPtr<FibonacciHeapTreeItem<T>> *rt):data(t),left(NULL),right(NULL),parent(NULL),child(NULL),mark(false),degree(0){if(lt!=NULL) left=*lt;if(rt!=NULL) right=*rt;if(pt!=NULL) parent=*pt;if(chd!=NULL) child=*chd;}	
	private://确认是否存在左右兄弟与父子节点，只有友元FibonacciHeap<T>能访问
		bool hasParent()const{return !parent.isEmpty();}
		bool hasChild()const{return !child.isEmpty();}
		bool hasLeft()const{return !left.isEmpty();}
		bool hasRight()const{return !right.isEmpty();}
		
	public://析构函数必须为public，用于智能指针中的删除。
		~FibonacciHeapTreeItem(){/*std::cout<<"deconstruct"<<data<<std::endl;*/}
	private:
		T data;//存储数据
		unsigned int degree;//拥有孩子数目
		bool mark;//自上一次成为另一个节点的孩子以来，是否失去过孩子（只可能失去一个）

		SmartPtr<FibonacciHeapTreeItem<T>> parent;//父节点智能指针的指针。
		SmartPtr<FibonacciHeapTreeItem<T>> child;//孩子智能指针
		SmartPtr<FibonacciHeapTreeItem<T>> left;//左兄弟智能指针		
		SmartPtr<FibonacciHeapTreeItem<T>> right;//右兄弟智能指针		
		
	friend class FibonacciHeap<T>; //把存储相同类型数据的二叉树设为友元
	};

	//斐波那契堆模板
	template<typename T>
	class FibonacciHeap{
	public:
	    typedef SmartPtr<FibonacciHeapTreeItem<T>> ItemType; //节点智能指针类型别名

	public:
		FibonacciHeap():prioItm(NULL),nullItm(NULL),heap_size(0){prioItm=nullItm;pri_compare=greater_default;} //构造函数，初始化prioItm为空节点
		FibonacciHeap(bool isMaxHeap):prioItm(NULL),nullItm(NULL),heap_size(0){prioItm=nullItm;if(isMaxHeap==true) pri_compare=greater_default; else pri_compare=less_default;} //构造函数，初始化prioItm为空节点
		FibonacciHeap(bool (*pri_comp)(const T &a,const T &b)):prioItm(NULL),nullItm(NULL),heap_size(0){prioItm=nullItm;pri_compare=pri_comp;} //构造函数，初始化prioItm为空节点
	public:
		~FibonacciHeap(){erase_parentAndLeft_from(prioItm);}

	public:
		/*优先级队列接口*/
		//向堆中插入元素，平摊代价O(1)
		ItemType insert(const T &key);
		//增加堆中原素的优先级，如果key比原始值优先级低则返回false，平摊代价O(1)
		bool increaseKey(ItemType &itmPtr,const T &key);
		//返回最大优先级元素，平摊代价O(1)
		ItemType get_prio()const;
		//抽取最大优先级元素，平摊代价O(lgn)
		ItemType extract_prio();
		//将hp合并进来，并置hp为空堆，平摊代价O(1)
		void heapUnion(FibonacciHeap &hp); 
		//结合increaseKey和extract_prio可以删除元素 平摊代价O(lgn)

		//判断是否为空堆
		bool isEmpty()const{return prioItm.isEmpty();} 
		//置为空堆，并释放资源
		void setEmpty(){erase_parentAndLeft_from(prioItm); prioItm=nullItm;heap_size=0;} 
		//获取堆大小
		unsigned int size()const{return heap_size;}
		//获取节点值
		T getItemValue(const ItemType &itmPtr)const{ if(itmPtr.isEmpty()) throw EmptySmartPtrAccessException();else return itmPtr->data;}	
	
	public:
		//测试函数，验证斐波那契堆结构是否正确
		void asertFibonacciHeap()const;

	private:
		mutable ItemType prioItm; //最大优先级节点
		mutable ItemType nullItm;  //空节点
		unsigned int heap_size;    //堆大小
		bool (*pri_compare)(const T &a,const T &b);	//堆优先级比较函数。

	private:
		void erase_parentAndLeft_from(ItemType &itmPtr)const;//置堆的每个元素的父指针和左指针为空，并消去环路，这样才能保证自动释放资源
		void asertFibonacciTree(ItemType &itmPtr)const;//验证堆中某树是否符合斐波那契堆性质
		void concatenateList(ItemType &ls1,ItemType &ls2)const;//链接双链表
		void cut(ItemType &x,ItemType &y)const;//用于increaseKey中切断操作
		void cascading_cut(ItemType &y)const;//用于increaseKey中级联切断

	private:
		//获取节点左兄弟引用
		ItemType &getItemLeft(ItemType &itmPtr)const{ if(itmPtr.isEmpty()) throw EmptySmartPtrAccessException();else return itmPtr->left;}
		//获取节点右兄弟引用
		ItemType &getItemRight(ItemType &itmPtr)const{ if(itmPtr.isEmpty()) throw EmptySmartPtrAccessException();else return itmPtr->right;}
		//获取节点父节点引用
		ItemType &getItemParent(ItemType &itmPtr)const{ if(itmPtr.isEmpty()) throw EmptySmartPtrAccessException();else return itmPtr->parent;}
		//获取节点某个孩子的引用
		ItemType &getItemChild(ItemType &itmPtr)const{ if(itmPtr.isEmpty()) throw EmptySmartPtrAccessException();else return itmPtr->child;}
		
	};

	template<typename T>
	void FibonacciHeap<T>::erase_parentAndLeft_from(ItemType &itmPtr)const{
		if(itmPtr.isEmpty())
			return;
		ItemType x=itmPtr;
		ItemType left_x=x->left;
		if(x->hasLeft())
			x->left->right=nullItm;
		if(x->hasRight())
			x->right->left=nullItm;
		while(!x.isEmpty())
		{
			left_x=x->left;
			if(x->hasChild())
				erase_parentAndLeft_from(x->child);
			x->parent=nullItm;
			x->left=nullItm;
			x=left_x;
		}
	}


	template<typename T>
	void FibonacciHeap<T>::asertFibonacciTree(ItemType &itmPtr)const{
		if(!(itmPtr->left->right==itmPtr)||!(itmPtr->right->left==itmPtr))
			std::cout<<"error1"<<std::endl;
		if(itmPtr->hasChild()&&!(itmPtr->child->parent==itmPtr))
			std::cout<<"error2"<<std::endl;
		if(itmPtr->hasParent()&&pri_compare(itmPtr->data,itmPtr->parent->data))
			std::cout<<"error3"<<std::endl;

		int dgr=itmPtr->degree;
		if(itmPtr->hasChild()){
			ItemType px=itmPtr->child;
			dgr--;
			asertFibonacciTree(px);
			px=px->right;
			while(!(px==itmPtr->child)){
				dgr--;
				asertFibonacciTree(px);
				px=px->right;
			}
		}
		if(dgr!=0)
			std::cout<<"degree error:degree != sunNumber"<<std::endl;
	}

	template<typename T>
	void FibonacciHeap<T>::asertFibonacciHeap()const{
		if(isEmpty()){
			std::cout<<"asert end: empty tree"<<std::endl;
			return;
		}
		ItemType px=prioItm;
		asertFibonacciTree(px);
		px=px->right;
		while(!(px==prioItm)){
			asertFibonacciTree(px);
			px=px->right;
		}
	}

	template<typename T>
	typename FibonacciHeap<T>::ItemType FibonacciHeap<T>::get_prio()const{
		return prioItm;
	}
	template<typename T>
	bool FibonacciHeap<T>::increaseKey(ItemType &itmPtr,const T &key){
		if(itmPtr.isEmpty()) 
			throw EmptySmartPtrAccessException();
		if(!pri_compare(key,itmPtr->data))
			return false;
		itmPtr->data=key;
		ItemType x=itmPtr;
		ItemType y=x->parent;
		if(!y.isEmpty()&&!pri_compare(y->data,x->data)){
			cut(x,y);
			cascading_cut(y);
		}
		if(pri_compare(key,prioItm->data))
			prioItm=x;
		return true;
	}

	template<typename T>
	void FibonacciHeap<T>::cut(ItemType &x,ItemType &y)const{
		if(x->right==x)
			y->child=nullItm;
		else{
			x->left->right=x->right;
			x->right->left=x->left;
			y->child=x->right;
		}
		x->parent=nullItm;
		x->left=x;
		x->right=x;
		x->mark=false;
		concatenateList(prioItm,x);
	}
	template<typename T>
	void FibonacciHeap<T>::cascading_cut(ItemType &y)const{
		ItemType z=y->parent;
		if(!z.isEmpty()){
			if(y->mark==false)
				y->mark=true;
			else{
				cut(y,z);
				cascading_cut(z);
			}
		}
	}

	template<typename T>
	void FibonacciHeap<T>::heapUnion(FibonacciHeap &hp){
		concatenateList(prioItm,hp.prioItm);
		if(!hp.isEmpty()&&(prioItm.isEmpty()||pri_compare(hp.prioItm->data,prioItm->data)))
			prioItm=hp.prioItm;
		heap_size+=hp.heap_size;
		hp.prioItm=hp.nullItm;
		hp.setEmpty();
	}

	template<typename T>
	void FibonacciHeap<T>::concatenateList(ItemType &ls1,ItemType &ls2)const{
		if(ls1.isEmpty()||ls2.isEmpty())
			return;
		ItemType right_ls1=ls1->right;
		ItemType right_ls2=ls2->right;
		ls1->right=right_ls2;
		right_ls2->left=ls1;
		ls2->right=right_ls1;
		right_ls1->left=ls2;
	}

	template<typename T>
	typename FibonacciHeap<T>::ItemType FibonacciHeap<T>::insert(const T &key){
		ItemType newItem(new FibonacciHeapTreeItem<T>(key,&nullItm,&nullItm,NULL,NULL));
		newItem->left=newItem;
		newItem->right=newItem;
		concatenateList(prioItm,newItem);
		if(prioItm.isEmpty()||pri_compare(key,prioItm->data))
			prioItm=newItem;
		heap_size++;
		return newItem;
	}

	template<typename T>
	typename FibonacciHeap<T>::ItemType FibonacciHeap<T>::extract_prio(){
		//空堆返回空节点
		if(isEmpty())
			return nullItm;
		//从根链表中删除prioItm暂存于prioItmTemp，prioItm指向根链表中另一节点。
		ItemType prioItmTemp=prioItm;
		if(prioItm->left==prioItm)
			prioItm=nullItm;
		else{
			prioItm->left->right=prioItm->right;
			prioItm->right->left=prioItm->left;
			prioItm=prioItm->left;
		}
		//置空prioItmTemp的左右孩子指针
		prioItmTemp->left=nullItm;
		prioItmTemp->right=nullItm;

		if(prioItmTemp->hasChild())
		{
			ItemType y=prioItmTemp->child;
			//置空prioItmTemp孩子的父指针
			do{
				y->parent=nullItm;
				y=y->right;
			}while(!(y==prioItmTemp->child));
			//将prioItmTemp的孩子链表链接至根链表
			concatenateList(prioItm,prioItmTemp->child);
			prioItm=prioItmTemp->child;
		}

		//如果删除后非空，则压缩根链表
		if(!prioItm.isEmpty()){
			//树的最大度数，将合并的新树存于vec
			unsigned int Dn=(int)(log(heap_size*1.0)/log(1.618));
			std::vector<ItemType> vec(Dn+1,nullItm);
			ItemType x=nullItm,y=nullItm;
			//遍历根表，将根表中的所有树合并并存于vec
			while(!prioItm.isEmpty()){
				//将根链表中当前节点删除，并暂存于x
				x=prioItm;
				if(x->right==x)
					prioItm=nullItm;
				else{
					prioItm->left->right=prioItm->right;
					prioItm->right->left=prioItm->left;
					prioItm=prioItm->right;
				}
				//置x为单链表
				x->right=x;
				x->left=x;
				unsigned int d=x->degree;
				//将x与vec中的树按度数递增顺序进行合并
				while(!vec[d].isEmpty()){
					y=vec[d];
					//如果x优先级较小，则交换x，y指针
					if(!pri_compare(x->data,y->data))
						std::swap(x,y);
					//将y与x的孩子链表合并
					if(x->hasChild())
						concatenateList(x->child,y);
					else
						x->child=y;
					//重置y的父指针，mark域，及x的degree。
					y->parent=x;
					y->mark=false;
					x->degree++;
					vec[d]=nullItm;
					d++;
				}
				//将合并得到的树存于vec
				vec[d]=x;
			}
			//将vec中的各棵树链入根表，并设置prioItm
			for(unsigned int i=0;i<=Dn;i++){
				if(!vec[i].isEmpty()){
					concatenateList(prioItm,vec[i]);
					if(prioItm.isEmpty()||pri_compare(vec[i]->data,prioItm->data))
						prioItm=vec[i];
				}
			}
		}
		heap_size--;
		return prioItmTemp;
	}
}

#endif