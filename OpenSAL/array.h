#ifndef arrayConst
#define arrayConst
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

/* 安全的值型数组模板，使用命名空间（lmtc）*/
#include <vector>
#include <cstddef>
#include <cstdarg>
#include <iostream>
#include <exception>
#include "myException.h"

namespace lmtc{

	template<typename T>
	class Array{
	public:	//常用接口
		//默认构造函数
		Array():dimNum(0),memory(0){}
		//采用可变参数列表，dimNum表示维数，后面不少于d个正整数实参，多余的参数自动省略。程序有义务保证参数数目正确，如果参数少于要求数目，程序很有可能以某种异常而终止，但是不能百分百保证。
		explicit Array(const size_t dimNum,...);
		//接受维界限向量的构造函数
		Array(const size_t d,const std::vector<unsigned int> &dimV);
		Array(const size_t d,const std::vector<int> &dimV);
		Array(const size_t d,const std::vector<unsigned long> &dimV);
		Array(const size_t d,const std::vector<long> &dimV);
		Array(const size_t d,const std::vector<unsigned short> &dimV);
		Array(const size_t d,const std::vector<short> &dimV);
		//接受迭代器的构造函数，初始化为1维数组
		template<typename Iterator>
		Array(Iterator  b, Iterator  e);
		//若干特化版本用以区别于采用可变参数列表的构造函数 完全匹配时调用特化版本，否则调用可变参数列表
		template<> Array(int  d, int  b){construct_initialize(d,b);}
		template<> Array(unsigned int  d, unsigned int  b){construct_initialize(d,b);}
		template<> Array(long  d, long  b){construct_initialize(d,b);}
		template<> Array(unsigned long  d, unsigned long  b){construct_initialize(d,b);}
		template<> Array(short  d, short  b){construct_initialize(d,b);}
		template<> Array(unsigned short  d, unsigned short  b){construct_initialize(d,b);}

		//采用函数调用形式访问数组，不少于dimNum个正整数实参，多余的参数自动省略。程序有义务保证参数数目正确，如果参数少于要求数目，程序很有可能以某种异常而终止，但是不能百分百保证。
		T& operator()(...);
		const T& operator()(...)const;
		//接受坐标向量的调用形式访问数组，要求类似可变参数形式。
		T& operator()(const std::vector<int> &psVec){return getElement(psVec);}
		T& operator()(const std::vector<unsigned int> &psVec){return getElement(psVec);}
		T& operator()(const std::vector<long> &psVec){return getElement(psVec);}
		T& operator()(const std::vector<unsigned long> &psVec){return getElement(psVec);}
		T& operator()(const std::vector<short> &psVec){return getElement(psVec);}
		T& operator()(const std::vector<unsigned short> &psVec){return getElement(psVec);}
		const T& operator()(const std::vector<int> &psVec)const{return getElement(psVec);}
		const T& operator()(const std::vector<unsigned int> &psVec)const{return getElement(psVec);}
		const T& operator()(const std::vector<long> &psVec)const{return getElement(psVec);}
		const T& operator()(const std::vector<unsigned long> &psVec)const{return getElement(psVec);}
		const T& operator()(const std::vector<short> &psVec)const{return getElement(psVec);}
		const T& operator()(const std::vector<unsigned short> &psVec)const{return getElement(psVec);}
		
		//初始化数组
		template<typename X>
		void initialize(const X &t);

		//清空数组
		void clear(){ dimNum=0;memory=0;dimVec.clear();arr.clear();}

		//转成一维数组
		void transformToOneDimension();

		//为了使得不同类型的数组元素之间也能互相访问，在定义兼容复制构造函数和赋值操作符时需要。
		template<typename Y> friend class Array;

		//不同类型数组兼容复制构造函数,X!=T时才使用，相同时使用合成的复制构造函数
		template<typename X>
		Array(const Array<X> & comArr);

		//不同类型数组兼容赋值操作符,X!=T时才使用，相同时使用合成的赋值操作符
		template<typename X>
		Array<T> &operator=(const Array<X> & comArr);

		//析构函数，不需额外处理
		~Array(){}

	public://获取数组信息
		//获取维数
		size_t getDimNum()const{ return dimNum;}
		//获取某维长度
		size_t getDimLen(const size_t d)const{ if(d>=dimNum) throw arrayOutBound("异常：不能获取超出数组维数的维长度");else return dimVec[d];}
		//获取存储内存大小
		size_t size()const{ return memory;}
		//验证是否为空
		bool empty()const{ return memory==0;}

	public://类型信息
		typedef size_t size_type;
		typedef typename std::vector<T>::iterator iterator; 
		typedef typename std::vector<T>::const_iterator const_iterator; 
		typedef typename std::vector<T>::reverse_iterator reverse_iterator; 
		typedef typename std::vector<T>::const_reverse_iterator const_reverse_iterator; 
		typedef typename std::vector<T>::difference_type difference_type; 
		typedef typename std::vector<T>::value_type value_type; 
		typedef typename std::vector<T>::reference reference; 
		typedef typename std::vector<T>::const_reference const_reference; 

	public://迭代器
		iterator begin(){ return arr.begin();}
		const_iterator begin()const{ return arr.begin();}
		iterator end(){ return arr.end();}
		const_iterator end()const{ return arr.end();}
		reverse_iterator rbegin(){ return arr.rbegin();}
		const_reverse_iterator rbegin()const{ return arr.rbegin();}
		reverse_iterator rend(){ return arr.rend();}
		const_reverse_iterator rend()const{ return arr.rend();}

	private:
		void construct_initialize(size_t d,size_t b);//构造初始化器用于Array(d,b);
		template<typename D>
		const T &getElement(const std::vector<D> &psVec)const;//正向映射获取元素引用,用于调用操作符
		template<typename D>
		T &getElement(const std::vector<D> &psVec);//正向映射获取元素引用,用于调用操作符
		template<typename D>
		void initArray(const size_t d,const std::vector<D> &dimV);//构造初始化器用于Array( d,const vector<X> dimV);
	
	private://数组信息
		size_t dimNum;//维数
		std::vector<size_t> dimVec;	//维长度向量		
		size_t memory;//总内存大小
		std::vector<T> arr;	//数据存储向量
	};


	//可变参数列表通用数组模板构造函数定义
	template<typename T>
	Array<T>::Array(const size_t d,...)try: dimNum(d),memory(0){
		memory=1;
		va_list var_arg;
		va_start(var_arg,d);
		for(size_t count=0;count<d;count++){	
			dimVec.push_back(va_arg(var_arg,size_t));
			memory*=dimVec[dimVec.size()-1];
		}
		va_end(var_arg);
		if(0==d)
			memory=0;
		arr=std::vector<T>(memory);
	}
	catch(std::exception &e)
	{
		std::cout<<"Array initializing failed( 可变参数列表 ): "<<e.what()<<std::endl;
		throw;
	}

	//接受维界限向量的构造函数，在构造函数中调用另一构造函数并不会初始化本身，只是创建了一个与本身无关的对象。普通函数优先于可变参数列表。
	template<typename T>
	Array<T>::Array(const size_t d,const std::vector<unsigned int> &dimV){
		initArray(d,dimV);
	}
	template<typename T>
	Array<T>::Array(const size_t d,const std::vector<int> &dimV){
		initArray(d,dimV);
	}
	template<typename T>
	Array<T>::Array(const size_t d,const std::vector<unsigned long> &dimV){
		initArray(d,dimV);
	}
	template<typename T>
	Array<T>::Array(const size_t d,const std::vector<long> &dimV){
		initArray(d,dimV);
	}
	template<typename T>
	Array<T>::Array(const size_t d,const std::vector<unsigned short> &dimV){
		initArray(d,dimV);
	}
	template<typename T>
	Array<T>::Array(const size_t d,const std::vector<short> &dimV){
		initArray(d,dimV);
	}

	template<typename T>
	template<typename D>
	void Array<T>::initArray(const size_t d,const std::vector<D> &dimV)try{
		dimNum=d;
		if(d>dimV.size())
			throw arrayAccessException("构造时错误：维界限向量维数不能小于指定数组维数");
		memory=1;
		for(size_t count=0;count<dimNum;count++)
		{
			dimVec.push_back(dimV[count]);
			memory*=dimV[count];
		}
		if(0==dimNum)
			memory=0;
		arr=std::vector<T>(memory);
	}
	catch(arrayAccessException &e)
	{
		std::cout<<e.what()<<std::endl;
		throw;
	}

	//接受迭代器的构造函数，初始化为1维数组
	template<typename T>
	template<typename Iterator>
	Array<T>::Array(Iterator  b, Iterator  e):dimNum(1),memory(0){
		for(Iterator p=b;p!=e;p++){
			memory++;
			arr.push_back(*p);
		}
		dimVec.push_back(memory);
	}


	template<typename T>
	T& Array<T>::operator()(...)try{
		if(0==memory)
			throw(arrayOutBound("0长度数组，拒绝访问"));
		va_list var_arg;
		va_start(var_arg,const_cast<Array<T> *>(this));
		size_t preDimPdc=1;
		size_t storeSite=0;
		for(size_t count=0;count<dimNum;count++){
			size_t len=va_arg(var_arg,size_t);
			if(len>=dimVec[count])
				throw(arrayOutBound());
			storeSite+=len*preDimPdc;
			preDimPdc*=dimVec[count];
		}
		va_end(var_arg);
		return arr[storeSite];
	}
	catch(arrayOutBound &e)
	{
		std::cout<<e.what()<<std::endl;
		throw;
	}
	catch(std::exception &e)
	{
		std::cout<<"Array accessing failed( 可变参数列表 ): "<<e.what()<<std::endl;
		throw;
	}

	template<typename T>
	const T& Array<T>::operator()(...)const try{
		if(0==memory)
			throw(arrayOutBound("0长度数组，拒绝访问"));
		va_list var_arg;
		va_start(var_arg,const_cast<const Array<T> *>(this));
		size_t preDimPdc=1;
		size_t storeSite=0;
		for(size_t count=0;count<dimNum;count++){
			size_t len=va_arg(var_arg,size_t);
			if(len>=dimVec[count])
				throw(arrayOutBound());
			storeSite+=len*preDimPdc;
			preDimPdc*=dimVec[count];
		}
		va_end(var_arg);
		return arr[storeSite];
	}
	catch(arrayOutBound &e)
	{
		std::cout<<e.what()<<std::endl;
		throw;
	}
	catch(std::exception &e)
	{
		std::cout<<"Array accessing failed( 可变参数列表 ): "<<e.what()<<std::endl;
		throw;
	}

	template<typename T>
	template<typename D>
	const T &Array<T>::getElement(const std::vector<D> &psVec)const try{
		if(0==memory)
			throw(arrayOutBound("0长度数组，拒绝访问"));
		if(dimNum>psVec.size())
			throw arrayAccessException("数组访问错误：坐标向量维数不能小于数组维数");
		size_t preDimPdc=1;
		size_t storeSite=0;
		for(size_t count=0;count<dimNum;count++){
			size_t len=psVec[count];
			if(len>=dimVec[count])
				throw(arrayOutBound());
			storeSite+=len*preDimPdc;
			preDimPdc*=dimVec[count];
		}
		return arr[storeSite];
	}
	catch(arrayOutBound &e)
	{
		std::cout<<e.what()<<std::endl;
		throw;
	}
	catch(arrayAccessException &e)
	{
		std::cout<<e.what()<<std::endl;
		throw;
	}

	template<typename T>
	template<typename D>
	T &Array<T>::getElement(const std::vector<D> &psVec)try{
		if(0==memory)
			throw(arrayOutBound("0长度数组，拒绝访问"));
		if(dimNum>psVec.size())
			throw arrayAccessException("数组访问错误：坐标向量维数不能小于数组维数");
		size_t preDimPdc=1;
		size_t storeSite=0;
		for(size_t count=0;count<dimNum;count++){
			size_t len=psVec[count];
			if(len>=dimVec[count])
				throw(arrayOutBound());
			storeSite+=len*preDimPdc;
			preDimPdc*=dimVec[count];
		}
		return arr[storeSite];
	}
	catch(arrayOutBound &e)
	{
		std::cout<<e.what()<<std::endl;
		throw;
	}
	catch(arrayAccessException &e)
	{
		std::cout<<e.what()<<std::endl;
		throw;
	}

	template<typename T>
	template<typename X>
	void Array<T>::initialize(const X &t){
		for(size_t i=0;i<memory;i++)
			arr[i]=t;
	}

	//转成一维数组
	template<typename T>
	void Array<T>::transformToOneDimension(){
		dimNum=1;
		dimVec.clear();
		dimVec.push_back(memory);
	}


	//不同类型数组兼容复制构造函数
	template<typename T>
	template<typename X>
	Array<T>::Array(const Array<X> & comArr):dimNum(comArr.dimNum),dimVec(comArr.dimVec),memory(comArr.memory){
		arr.assign(comArr.arr.begin(),comArr.arr.end());
	}

	//不同类型数组兼容赋值操作符
	template<typename T>
	template<typename X>
	Array<T> & Array<T>::operator=(const Array<X> & comArr){
		dimNum=comArr.dimNum;
		dimVec=comArr.dimVec;
		memory=comArr.memory;
		arr.assign(comArr.arr.begin(),comArr.arr.end());
		return *this;
	}

	template<typename T>
	void Array<T>::construct_initialize(size_t d,size_t b){
			dimNum=1;
			memory=b;
			if(d!=1)
			{
				std::cout<<"构造时错误：数组维数不等于1"<<std::endl;
				throw arrayAccessException("构造时错误：数组维数不等于1");
			}
			dimVec.push_back(b);
			arr=std::vector<T>(memory);	
		}
}


#endif 