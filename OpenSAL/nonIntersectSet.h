#ifndef nonIntersectSetConst
#define nonIntersectSetConst
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
#include <iostream>
//使用智能指针实现安全的不相交集合
namespace lmtc{
	template<typename T> class NonIntersectSet;//不相交集合模板申明

	template<typename T>  //不相交集合节点模板申明
	class NonIntersectSetItem{
	public:
		void setValue(const T &t){data=t;}
		T getValue()const{return data;}
	private:
		//构造函数皆为私有，只有友元NonIntersectSet<T>能访问
		NonIntersectSetItem(const T &t):rank(0),data(t),parent(NULL){}
		NonIntersectSetItem():rank(0),parent(NULL){}
	private:
		//确认是否存在父节点
		bool hasParent()const{return !parent.isEmpty();}

	public://析构函数必须为public，用于智能指针中的删除。
		~NonIntersectSetItem(){/*std::cout<<"deconstruct"<<data<<std::endl;*/}

	private:
		T data;//存储数据
		unsigned long rank;//以该节点为根的子树的节点数
		SmartPtr<NonIntersectSetItem<T>> parent;//父节点智能指针

	friend class NonIntersectSet<T>;
	};

	template<typename T> //不相交集合模板
	class NonIntersectSet{
	public:
		typedef SmartPtr<NonIntersectSetItem<T>> ItemType;
	public:
		//构造函数，带卫星数据
		NonIntersectSet(const T &t):setItem(new NonIntersectSetItem<T>(t)){}
		//默认构造函数，卫星数据未定义
		NonIntersectSet():setItem(new NonIntersectSetItem<T>()){}
	
	public:
		//合并另一集合，如果属于同一集合则只会压缩路径但不会链接处理
		void unionSet(NonIntersectSet &st);
		//找到另一集合
		ItemType find(){return setFindFrom(setItem);}

		void setValue(const T &t){setItem->data=t;}
		T getValue()const{return setItem->data;}

	private:
		void link(ItemType &x,ItemType &y)const;
		ItemType setFindFrom(ItemType &st)const;

	private:
		 ItemType setItem;
	};

	template<typename T>
	void NonIntersectSet<T>::link(ItemType &x,ItemType &y)const{
		if(x==y)//已是同一集合的根不需再连接
			return;

		if(x->rank>y->rank)
			y->parent=x;
		else{
			x->parent=y;
			if(x->rank==y->rank)
				y->rank++;
		}
	}

	template<typename T>
	typename NonIntersectSet<T>::ItemType NonIntersectSet<T>::setFindFrom(ItemType &st)const{
		if(st->hasParent()){
			st->parent=setFindFrom(st->parent);
			return st->parent;
		}else
			return st;
	}

	template<typename T>
	void NonIntersectSet<T>::unionSet(NonIntersectSet &st){
		link(find(),st.find());
	}
}

#endif