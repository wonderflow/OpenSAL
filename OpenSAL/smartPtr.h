#ifndef smartPtrConst
#define smartPtrConst
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

/* 智能指针通用模板 支持赋值，复制，解引用，箭头操作（类类型）*/
#include <cstddef>
namespace lmtc{

template<typename T> class SmartPtr;

template<typename T>
class basePtr{
	//声明智能指针类为友元
	friend class SmartPtr<T> ;
	//基础数据指针
	T* sp;
	//引用计数
	size_t use;
	//私有构造函数，接受基础类型指针，引用计数初始化为1
	basePtr(T *p):sp(p),use(1) {}
	//析构函数
	~basePtr() { delete sp;}
};

template<typename T>
class SmartPtr{
public:
	//提供基础数据类型
	typedef T dataType;
	//构造函数，接受基础类型指针
	SmartPtr(T *p):ptr(new basePtr<T>(p)){}
	//复制构造函数，增加引用计数
	SmartPtr(const SmartPtr &orig):ptr(orig.ptr){ ++ptr->use;}
	//重载赋值操作符
	SmartPtr & operator=(const SmartPtr &);
	//析构函数
	~SmartPtr(){ if(--ptr->use==0) delete ptr;}
	//重载解引用操作符
	T &operator*(){return *ptr->sp;}
	const T &operator*()const{ return *ptr->sp;}
	//重载箭头操作符，只有当T为类类型时，该操作符才合法。
	T *operator->(){return ptr->sp;}
	const T *operator->()const{return ptr->sp;} 
	//判断指针是否为空
	bool isEmpty()const{return ptr->sp==NULL;}
	//判断两指针是否相等
	bool operator==(const SmartPtr &stPr)const{return ptr->sp==stPr.ptr->sp;}
	//判断两指针是否不相等
	bool operator!=(const SmartPtr &stPr)const{return !(ptr->sp==stPr.ptr->sp);}
private:
	basePtr<T> *ptr;
};

//智能指针的赋值操作符定义
template<typename T>
SmartPtr<T> &SmartPtr<T>::operator=(const SmartPtr &spt){
	++spt.ptr->use;
	if(--ptr->use==0)
		delete ptr;
	ptr=spt.ptr;
	return *this;
}

}


#endif