#ifndef heapConst
#define heapConst
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
#include <cstddef>
#include <iostream>
#include "myException.h"
#include "defaultCompare.h"

namespace lmtc{
	template<typename T>
	class Heap{
	public:
		//构造函数，依pri_compare优先级建立堆。isMaxHeap确定大顶堆还是小顶堆，pri_comp为优先级函数指针，b和e为堆初始数据迭代器，O(n)
		Heap():heap_size(0){pri_compare=greater_default;}
		Heap(bool isMaxHeap):heap_size(0){if(isMaxHeap==true) pri_compare=greater_default; else pri_compare=less_default;}
		Heap(bool (*pri_comp)(const T &a,const T &b)):heap_size(0){ pri_compare=pri_comp;}
		template<typename Iterator> Heap( Iterator b, Iterator e);
		template<typename Iterator> Heap( Iterator b, Iterator e,bool isMaxHeap);
		template<typename Iterator> Heap( Iterator b, Iterator e,bool (*pri_comp)(const T &a,const T &b));

	public:	
		//优先级队列接口
		bool increaseKey(size_t i,const T &key);//增加堆中原素的优先级，如果i超出范围或者key比i位置原始值优先级低则返回false，O(lgn)
		T get_prio()const;//返回最大优先级元素，O(1)
		T extract_prio();//抽取最大优先级元素，O(lgn)
		void insert(const T &key);//向堆中插入元素，O(lgn)
		//结合increaseKey和extract_prio可以删除元素

		//堆排序接口，对所有数据排序（不仅限于堆中数据），并且保证恢复堆现场，O(nlgn)
		std::vector<T> sort();
		//打印堆，O(n)
		void printHeap(){ for(size_t i=0;i<heap_size;i++) std::cout<< hp[i]<<"  ";std::cout<<std::endl;}

	private:
		size_t parent(const size_t i)const{return (i+1)/2-1;}
		size_t left(const size_t i)const{ return 2*(i+1)-1;}
		size_t right(const size_t i)const{ return 2*(i+1);}
		void pri_heapify(size_t i);//下梳，合并以i为根的两个堆，O(lgn)
		void build_heap();//建堆，O(n)

	private:
		std::vector<T> hp;   //堆数据存储区
		size_t heap_size;    //堆大小
		bool (*pri_compare)(const T &a,const T &b);	//堆优先级比较函数。
		
	};

	template<typename T> template<typename Iterator> 
	Heap<T>::Heap( Iterator b, Iterator e):hp(b,e){
		heap_size=hp.size();
		pri_compare=greater_default;
		build_heap();
	}
	template<typename T> template<typename Iterator> 
	Heap<T>::Heap( Iterator b, Iterator e,bool isMaxHeap):hp(b,e){
		heap_size=hp.size();
		if(isMaxHeap==true)
			pri_compare=greater_default;
		else
			pri_compare=less_default;
		build_heap();

	}
	template<typename T> template<typename Iterator> 
	Heap<T>::Heap( Iterator b, Iterator e,bool (*pri_comp)(const T &a,const T &b)):hp(b,e){
		heap_size=hp.size();
		pri_compare=pri_comp;
		build_heap();
	}
	
	template<typename T>
	void Heap<T>::pri_heapify(size_t i){
		if(i>=heap_size)
			return;
		size_t l=left(i);
		size_t r=right(i);
		size_t largest=i;
		if(l<heap_size&&pri_compare(hp[l],hp[i]))
			largest=l;
		if(r<heap_size&&pri_compare(hp[r],hp[largest]))
			largest=r;
		if(largest!=i)
		{
			std::swap(hp[i],hp[largest]);
			pri_heapify(largest);
		}
	}

	template<typename T>
	void Heap<T>::build_heap(){
		heap_size=hp.size();
		if(heap_size<2)
			return;
		for(int i=parent(heap_size-1);i>=0;i--)
			pri_heapify(i);
	}
	
	template<typename T>
	std::vector<T> Heap<T>::sort(){  
		if(heap_size<2)
			return hp;
		//保存堆现场
		std::vector<T> hpOld=hp;
		size_t heap_size_old=heap_size;
		//如果堆不完整，则重新建堆
		if(heap_size!=hp.size())
			build_heap();
		for(int i=heap_size-1;i>0;i--)
		{
			std::swap(hp[0],hp[i]);
			heap_size--;
			pri_heapify(0);
		}
		hp.swap(hpOld);
		heap_size=heap_size_old;
		return hpOld;
	}
	template<typename T>
	bool Heap<T>::increaseKey(size_t i,const T &key){
		if(!(i<heap_size&&!pri_compare(hp[i],key)))
			return false;
		hp[i]=key;
		while(i>0&& pri_compare(hp[i],hp[parent(i)]))
		{
			std::swap(hp[i],hp[parent(i)]);
			i=parent(i);
		}
		return true;
	}
	template<typename T>
	T Heap<T>::get_prio()const{
		if(heap_size==0)
		{
			std::cout<<"不能返回空堆的首元"<<std::endl;
			throw HeapAccessException("不能返回空堆的首元");
		}
		return hp[0];
	}

	template<typename T>
	T Heap<T>::extract_prio(){
		if(heap_size==0)
		{
			std::cout<<"不能抽取空堆的首元"<<std::endl;
			throw HeapAccessException("不能抽取空堆的首元");
		}
		std::swap(hp[0],hp[heap_size-1]);
		heap_size--;
		pri_heapify(0);
		return hp[heap_size];
	}
	template<typename T>
	void Heap<T>::insert(const T &key){
		if(heap_size!=hp.size())
			hp[heap_size]=key;
		else
			hp.push_back(key);
		heap_size++;
		increaseKey(heap_size-1,key);
	}
}


#endif