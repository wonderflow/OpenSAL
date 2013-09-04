#ifndef binomialHeapConst
#define binomialHeapConst
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
#include <iostream>
//二项堆模板
namespace lmtc{

	template<typename T> class BinomialHeap; //二项堆模板申明

	template<typename T>  //堆节点模板申明
	class BinomialHeapTreeItem{
	private://构造函数皆为私有，只有友元BinomialHeap<T>能访问
		BinomialHeapTreeItem():left(NULL),right(NULL),parent(NULL),degree(0){}
		BinomialHeapTreeItem(const T &t):data(t),left(NULL),right(NULL),parent(NULL),degree(0){}
		BinomialHeapTreeItem(const T &t,SmartPtr<BinomialHeapTreeItem<T>> *lt, SmartPtr<BinomialHeapTreeItem<T>> *rt, SmartPtr<BinomialHeapTreeItem<T>> * pt):data(t),left(NULL),right(NULL),parent(NULL),degree(0){if(lt!=NULL) left=*lt;if(rt!=NULL) right=*rt;if(pt!=NULL) parent=*pt;}	
	private://确认是否存在左右孩子与父节点，只有友元BinomialHeap<T>能访问
		bool hasLeft()const{return !left.isEmpty();}
		bool hasRight()const{return !right.isEmpty();}
		bool hasParent()const{return !parent.isEmpty();}
	public://析构函数必须为public，用于智能指针中的删除。
		~BinomialHeapTreeItem(){/*std::cout<<"deconstruct"<<data<<std::endl;*/}
	private:
		T data;//存储数据
		unsigned int degree;
		SmartPtr<BinomialHeapTreeItem<T>> left;//左孩子智能指针		
		SmartPtr<BinomialHeapTreeItem<T>> right;//右孩子智能指针		
		SmartPtr<BinomialHeapTreeItem<T>> parent;//父节点智能指针

	friend class BinomialHeap<T>; //把存储相同类型数据的二叉树设为友元
	};

	//二项堆模板
	template<typename T>
	class BinomialHeap{
	public:
	    typedef SmartPtr<BinomialHeapTreeItem<T>> ItemType; //节点智能指针类型别名

	public:
		BinomialHeap():root(NULL),nullItm(NULL),heap_size(0){root=nullItm;pri_compare=greater_default;} //构造函数，初始化root为空节点
		BinomialHeap(bool isMaxHeap):root(NULL),nullItm(NULL),heap_size(0){root=nullItm;if(isMaxHeap==true) pri_compare=greater_default; else pri_compare=less_default;} //构造函数，初始化root为空节点
		BinomialHeap(bool (*pri_comp)(const T &a,const T &b)):root(NULL),nullItm(NULL),heap_size(0){root=nullItm;pri_compare=pri_comp;} //构造函数，初始化root为空节点
	public:
		~BinomialHeap(){erase_parent_from(root);}

	public:
		/*二项堆接口*/
		//向堆中插入元素，O(lgn)
		ItemType insert(const T &key);
		//增加堆中原素的优先级，如果key比原始值优先级低则返回false，O(lgn)
		bool increaseKey(ItemType &itmPtr,const T &key);
		//返回最大优先级元素，O(lgn)
		ItemType get_prio()const;
		//抽取最大优先级元素，O(lgn)
		ItemType extract_prio();
		//将hp合并进来，并置hp为空堆，O(lgn)
		void heapUnion(BinomialHeap &hp); 
		//结合increaseKey和extract_prio可以删除元素，O(lgn)

		//判断是否为空二项堆
		bool isEmpty()const{return root.isEmpty();} 
		//置为空二项堆
		void setEmpty(){erase_parent_from(root); root=nullItm;heap_size=0;} 
		//获取堆大小
		unsigned int size()const{return heap_size;}
		//获取节点值
		T getItemValue(const ItemType &itmPtr)const{ if(itmPtr.isEmpty()) throw EmptySmartPtrAccessException();else return itmPtr->data;}	
	
	public:
		//测试函数
		void asertBinomialHeap()const;

	public://把二项堆当成二叉树进行前序、中序、后序遍历，对各个节点的数据运行f操作
		template<typename X>
		void traver_preOrder(void (*f)(X x))const;
		template<typename X>
		void traver_inOrder(void (*f)(X x))const;
		template<typename X>
		void traver_postOrder(void (*f)(X x))const;

	private:
	    mutable ItemType root; //根节点   
		mutable ItemType nullItm;  //空节点
		unsigned int heap_size;    //堆大小
		bool (*pri_compare)(const T &a,const T &b);	//堆优先级比较函数。

	private://以二项堆某节点为根的子二项树进行前序、中序、后序遍历，对各个节点的数据运行f操作
		template<typename X>
		void traver_preOrder_From(const ItemType &itmPtr,void (*f)(X x))const;
		template<typename X>
		void traver_inOrder_From(const ItemType &itmPtr,void (*f)(X x))const;
		template<typename X>
		void traver_postOrder_From(const ItemType &itmPtr,void (*f)(X x))const;

		void erase_parent_from(ItemType &itmPtr)const;//删除子二项树中任意节点的父指针，以便自动释放资源
		ItemType unionHeapList(ItemType &h1,ItemType &h2)const;//链接两根表
		void asertBinomialTree(ItemType &itmPtr)const;//验证某子二项树是否符合二项堆性质

	private:
		//获取节点左孩子引用
		ItemType &getItemLeft(ItemType &itmPtr)const{ if(itmPtr.isEmpty()) throw EmptySmartPtrAccessException();else return itmPtr->left;}
		//获取节点右孩子引用
		ItemType &getItemRight(ItemType &itmPtr)const{ if(itmPtr.isEmpty()) throw EmptySmartPtrAccessException();else return itmPtr->right;}
		//获取节点父节点引用
		ItemType &getItemParent(ItemType &itmPtr)const{ if(itmPtr.isEmpty()) throw EmptySmartPtrAccessException();else return itmPtr->parent;}
		
	};

	template<typename T>
	void BinomialHeap<T>::erase_parent_from(ItemType &itmPtr)const{
		if(itmPtr.isEmpty())
			return;
		itmPtr->parent=nullItm;
		erase_parent_from(itmPtr->left);
		erase_parent_from(itmPtr->right);
	}

	template<typename T> template<typename X>
	void BinomialHeap<T>::traver_preOrder_From(const ItemType &itmPtr,void (*f)(X x))const{
		if(itmPtr.isEmpty())
			return;
		f(itmPtr->data);
		traver_preOrder_From(itmPtr->left,f);
		traver_preOrder_From(itmPtr->right,f);
	}

	template<typename T> template<typename X>
	void BinomialHeap<T>::traver_inOrder_From(const ItemType &itmPtr,void (*f)(X x))const{
		if(itmPtr.isEmpty())
			return;
		traver_inOrder_From(itmPtr->left,f);
		f(itmPtr->data);
		traver_inOrder_From(itmPtr->right,f);
	}

	template<typename T> template<typename X>
	void BinomialHeap<T>::traver_postOrder_From(const ItemType &itmPtr,void (*f)(X x))const{
		if(itmPtr.isEmpty())
			return;
		traver_postOrder_From(itmPtr->left,f);
		traver_postOrder_From(itmPtr->right,f);
		f(itmPtr->data);
	}

	template<typename T> template<typename X>
	void BinomialHeap<T>::traver_preOrder(void (*f)(X x))const{
		traver_preOrder_From(root,f);
	}

	template<typename T> template<typename X>
	void BinomialHeap<T>::traver_inOrder(void (*f)(X x))const{
		traver_inOrder_From(root,f);
	}

	template<typename T> template<typename X>
	void BinomialHeap<T>::traver_postOrder(void (*f)(X x))const{
		traver_postOrder_From(root,f);
	}

	template<typename T>
	void BinomialHeap<T>::asertBinomialTree(ItemType &itmPtr)const{
		int dgr=itmPtr->degree;
		ItemType px=itmPtr->left;
		while(!px.isEmpty()){
			dgr--;
			if(px->degree!=dgr)
				std::cout<<"degree error:二项树子树度数错误"<<std::endl;
			if(pri_compare(px->data,itmPtr->data))
				std::cout<<"error:不符合堆的性质"<<std::endl;
			asertBinomialTree(px);
			px=px->right;
		}
		if(dgr!=0)
			std::cout<<"degree error:degree != sunNumber"<<std::endl;
	}

	template<typename T>
	void BinomialHeap<T>::asertBinomialHeap()const{
		ItemType px=root;
		while(!px.isEmpty()){
			if(px->hasRight()&&px->right->degree<=px->degree)
				std::cout<<"degree error:main chain"<<std::endl;
			asertBinomialTree(px);
			px=px->right;
		}
	}

	template<typename T>
	typename BinomialHeap<T>::ItemType BinomialHeap<T>::get_prio()const{
		if(isEmpty())
			return nullItm;
		ItemType y=root;
		ItemType x=root->right;
		while(!x.isEmpty()){
			if(pri_compare(x->data,y->data))
				y=x;
			x=x->right;
		}
		return y;
	}
	template<typename T>
	bool BinomialHeap<T>::increaseKey(ItemType &itmPtr,const T &key){
		if(!pri_compare(key,itmPtr->data))
			return false;
		itmPtr->data=key;
		ItemType y=itmPtr;
		ItemType z=getItemParent(y);
		while(!z.isEmpty()&&pri_compare(y->data,z->data)){
			std::swap(y->data,z->data);
			y=z;
			z=getItemParent(y);
		}
		return true;
	}

	template<typename T>
	void BinomialHeap<T>::heapUnion(BinomialHeap &hp){
		root=unionHeapList(root,hp.root);
		heap_size+=hp.heap_size;
		hp.setEmpty();
	}

	template<typename T>
	typename BinomialHeap<T>::ItemType BinomialHeap<T>::unionHeapList(ItemType &h1,ItemType &h2)const{
		if(h1.isEmpty())
			return h2;
		if(h2.isEmpty())
			return h1;

		ItemType px=nullItm;
		ItemType newRoot=nullItm;
		ItemType p1=h1;
		ItemType p2=h2;
		if(p1->degree<p2->degree){
			px=p1;
			newRoot=p1;
			p1=p1->right;
		}
		else{
			px=p2;
			newRoot=p2;
			p2=p2->right;	
		}
		while(!p1.isEmpty()||!p2.isEmpty()){
			if(p1.isEmpty()){
				px->right=p2;
				break;
			}
			if(p2.isEmpty()){
				px->right=p1;
				break;
			}
			if(p1->degree<p2->degree){
				px->right=p1;
				px=p1;
				p1=p1->right;
			}else{
				px->right=p2;
				px=p2;
				p2=p2->right;
			}
		}
		ItemType prev_x=nullItm;
		ItemType x=newRoot;
		ItemType next_x=x->right;
		while(!next_x.isEmpty()){
			if(x->degree!=next_x->degree||(next_x->hasRight()&&next_x->right->degree==x->degree)){
				prev_x=x;
				x=next_x;
				next_x=x->right;
			}else if(pri_compare(x->data,next_x->data)){
				x->right=next_x->right;
				next_x->parent=x;
				next_x->right=x->left;
				x->left=next_x;
				x->degree++;
				next_x=x->right;
			}else{
				if(prev_x.isEmpty())
					newRoot=next_x;
				else
					prev_x->right=next_x;
				x->parent=next_x;
				x->right=next_x->left;
				next_x->left=x;
				next_x->degree++;
				x=next_x;
				next_x=x->right;
			}
		}
		return newRoot;
	}

	template<typename T>
	typename BinomialHeap<T>::ItemType BinomialHeap<T>::insert(const T &key){
		ItemType newItem(new BinomialHeapTreeItem<T>(key,&nullItm,&nullItm,&nullItm));
		root=unionHeapList(root,newItem);
		heap_size++;
		return newItem;
	}

	template<typename T>
	typename BinomialHeap<T>::ItemType BinomialHeap<T>::extract_prio(){
		if(isEmpty())
			return nullItm;
		ItemType y=root;
		ItemType pre_y=nullItm;
		ItemType x=root->right;
		ItemType pre_x=root;
		while(!x.isEmpty()){
			if(pri_compare(x->data,y->data)){
				y=x;
				pre_y=pre_x;
			}
			pre_x=x;
			x=x->right;
		}

		if(pre_y.isEmpty())
			root=y->right;
		else
			pre_y->right=y->right;

		ItemType sunListHead=nullItm;
		x=y->left;
		while(!x.isEmpty()){
			ItemType next_x=x->right;
			x->parent=nullItm;
			x->right=sunListHead;
			sunListHead=x;
			x=next_x;
		}
		root=unionHeapList(root,sunListHead);
		y->left=nullItm;
		y->right=nullItm;
		heap_size--;
		return y;
	}
}

#endif