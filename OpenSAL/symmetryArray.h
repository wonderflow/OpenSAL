#ifndef symmetryArrayConst
#define symmetryArrayConst
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
#include "coordinateMapping.h"
#include "array.h"

namespace lmtc{

	template<typename T>
	class SymmetryArray{
	public:	//常用接口
		//默认构造函数
		SymmetryArray();
		//采用可变参数列表，dimNum表示维数，后面不少于d个正整数实参，多余的参数自动省略。程序有义务保证参数数目正确，如果参数少于要求数目，程序很有可能以某种异常而终止，但是不能百分百保证。
		explicit SymmetryArray(const size_t dimNum,...);
		//接受维界限向量的构造函数
		SymmetryArray(const size_t d,const std::vector<unsigned int> &dimV);
		SymmetryArray(const size_t d,const std::vector<int> &dimV);
		SymmetryArray(const size_t d,const std::vector<unsigned long> &dimV);
		SymmetryArray(const size_t d,const std::vector<long> &dimV);
		SymmetryArray(const size_t d,const std::vector<unsigned short> &dimV);
		SymmetryArray(const size_t d,const std::vector<short> &dimV);
		//接受迭代器的构造函数，初始化为1维数组
		template<typename Iterator>
		SymmetryArray( Iterator b, Iterator e);
		//若干特化版本用以区别于采用可变参数列表的构造函数 完全匹配时调用特化版本，否则调用可变参数列表
		template<> SymmetryArray(int  d, int  b){construct_initialize(d,b);}
		template<> SymmetryArray(unsigned int  d, unsigned int  b){construct_initialize(d,b);}
		template<> SymmetryArray(long  d, long  b){construct_initialize(d,b);}
		template<> SymmetryArray(unsigned long  d, unsigned long  b){construct_initialize(d,b);}
		template<> SymmetryArray(short  d, short  b){construct_initialize(d,b);}
		template<> SymmetryArray(unsigned short  d, unsigned short  b){construct_initialize(d,b);}
		
		//采用函数调用形式访问数组，不少于dimNum个正整数实参，多余的参数自动省略。程序有义务保证参数数目正确，如果参数少于要求数目，程序很有可能以某种异常而终止，但是不能百分百保证。
		T& operator()(...);
		const T& operator()(...)const;
		//接受坐标向量的调用形式访问数组，要求类似可变参数形式。
		T& operator()(const std::vector<int> &psVec){ return getElement(psVec);}
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

		//非规整正向映射，按非零维数升序排列，然后相同非零维数按对角面值升序排列，然后才依从左到右优先级的各维坐标主序排列。
		//st表示最低非零维（全零坐标值为dm，symPoint(0--dm-1)表示第i维坐标值，要求非降序排列。
		//返回坐标次序
		long forwdMapping(const Array<long> &symPoint,const size_t st)const;
	
		//非规整逆向映射
		//返回非零最低维
		long bkwdMapping(Array<long> &symPoint,const size_t n)const;

		//初始化数组
		template<typename X>
		void initialize(const X &t);

		//清空数组
		void clear(){ dimNum=0;memory=0;dimVec.clear();arr.clear();unTriMp=UnTrimMapping();}

		//转成一维数组
		void transformToOneDimension();

		//为了使得不同类型的数组元素之间也能互相访问，在定义兼容复制构造函数和赋值操作符时需要。
		template<typename Y> friend class SymmetryArray;

		//不同类型数组兼容复制构造函数,X!=T时才使用，相同时使用合成的复制构造函数
		template<typename X>
		SymmetryArray(const SymmetryArray<X> & comArr);

		//不同类型数组兼容赋值操作符,X!=T时才使用，相同时使用合成的赋值操作符
		template<typename X>
		SymmetryArray<T> &operator=(const SymmetryArray<X> & comArr);

		//析构函数，不需额外处理
		~SymmetryArray(){}

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
		void construct_initialize(size_t d,size_t b);//构造初始化器用于SymmetryArray(d,b);
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
		UnTrimMapping unTriMp;//非规整映射对象
	};

	//默认构造函数
	template<typename T>
	SymmetryArray<T>::SymmetryArray():dimNum(0),memory(0){
	}

	//可变参数列表通用数组模板构造函数定义
	template<typename T>
	SymmetryArray<T>::SymmetryArray(const size_t d,...)try: dimNum(d),memory(0){
		if(d==0)
			return;
		std::vector<size_t> dimV;
		dimV.push_back(d);
		va_list var_arg;
		va_start(var_arg,d);
		for(size_t count=0;count<d;count++){	
			size_t temp=va_arg(var_arg,size_t);
			dimVec.push_back(temp);
			dimV.push_back(temp);
		}
		va_end(var_arg);
		std::sort(dimV.begin()+1,dimV.end());
		if(dimV[1]!=0)
		{
			for(size_t i=1;i<=d;i++)
				dimV[i]--;
			unTriMp=UnTrimMapping(Array<long>(dimV.begin(),dimV.end()));
		    memory=unTriMp.countN();
		    arr=std::vector<T>(memory);
		}
	}
	catch(std::exception &e)
	{
		std::cout<<"Array initializing failed( 可变参数列表 ): "<<e.what()<<std::endl;
		throw;
	}

	//接受维界限向量的构造函数，在构造函数中调用另一构造函数并不会初始化本身，只是创建了一个与本身无关的对象。普通函数优先于可变参数列表。
	template<typename T>
	SymmetryArray<T>::SymmetryArray(const size_t d,const std::vector<unsigned int> &dimV){
		initArray(d,dimV);
	}
	template<typename T>
	SymmetryArray<T>::SymmetryArray(const size_t d,const std::vector<int> &dimV){
		initArray(d,dimV);
	}
	template<typename T>
	SymmetryArray<T>::SymmetryArray(const size_t d,const std::vector<unsigned long> &dimV){
		initArray(d,dimV);
	}
	template<typename T>
	SymmetryArray<T>::SymmetryArray(const size_t d,const std::vector<long> &dimV){
		initArray(d,dimV);
	}
	template<typename T>
	SymmetryArray<T>::SymmetryArray(const size_t d,const std::vector<unsigned short> &dimV){
		initArray(d,dimV);
	}
	template<typename T>
	SymmetryArray<T>::SymmetryArray(const size_t d,const std::vector<short> &dimV){
		initArray(d,dimV);
	}
	
	template<typename T>
	template<typename D>
	void SymmetryArray<T>::initArray(const size_t d,const std::vector<D> &dv)try{
		dimNum=d;
		memory=0;
		if(d>dv.size())
			throw arrayAccessException("构造时错误：维界限向量维数不能小于指定数组维数");
		if(d==0)
			return;
		std::vector<size_t> dimV;
		dimV.push_back(d);
		for(size_t count=0;count<dimNum;count++)
		{
			dimVec.push_back(dv[count]);
			dimV.push_back(dv[count]);
		}
		std::sort(dimV.begin()+1,dimV.end());
		if(dimV[1]!=0)
		{
			for(size_t i=1;i<=d;i++)
				dimV[i]--;
			unTriMp=UnTrimMapping(Array<long>(dimV.begin(),dimV.end()));
		    memory=unTriMp.countN();
		    arr=std::vector<T>(memory);
		}
		
	}
	catch(arrayAccessException &e)
	{
		std::cout<<e.what()<<std::endl;
		throw;
	}


	//接受迭代器的构造函数，初始化为1维数组
	template<typename T>
	template<typename Iterator>
	SymmetryArray<T>::SymmetryArray( Iterator b,  Iterator e):dimNum(1),memory(0){
		for(Iterator p=b;p!=e;p++){
			memory++;
			arr.push_back(*p);
		}
		dimVec.push_back(memory);
		if(memory!=0)
		{
		    Array<long> dimArr(1,2);
		    dimArr(0)=1;
		    dimArr(1)=memory-1;
		    unTriMp=UnTrimMapping(dimArr);	
		}
	}

	template<typename T>
	T& SymmetryArray<T>::operator()(...)try{
		if(0==memory)
			throw(arrayOutBound("0长度数组，拒绝访问"));
		va_list var_arg;
		va_start(var_arg,const_cast<SymmetryArray<T> *>(this));
	    Array<long> symPoint(1,dimNum);
		for(size_t count=0;count<dimNum;count++){
			size_t len=va_arg(var_arg,size_t);
			if(len>=dimVec[count])
				throw(arrayOutBound());
			symPoint(count)=len;
		}
		va_end(var_arg);
		bool issorted=true;
		for(size_t i=0;i<dimNum-1;i++)
			if(symPoint(i)>symPoint(i+1))
				issorted=false;
		if(issorted==false)
		    std::sort(symPoint.begin(),symPoint.end());
		size_t st=0;
		for(size_t i=0;i<dimNum;i++)
		{
			if(symPoint(i)==0)
				st=i+1;
			else
				break;
		}
		return arr[forwdMapping(symPoint, st)];
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
	const T& SymmetryArray<T>::operator()(...)const try{
		if(0==memory)
			throw(arrayOutBound("0长度数组，拒绝访问"));
		va_list var_arg;
		va_start(var_arg,const_cast<const SymmetryArray<T> *>(this));
	    Array<long> symPoint(1,dimNum);
		for(size_t count=0;count<dimNum;count++){
			size_t len=va_arg(var_arg,size_t);
			if(len>=dimVec[count])
				throw(arrayOutBound());
			symPoint(count)=len;
		}
		va_end(var_arg);
		bool issorted=true;
		for(size_t i=0;i<dimNum-1;i++)
			if(symPoint(i)>symPoint(i+1))
				issorted=false;
		if(issorted==false)
		    std::sort(symPoint.begin(),symPoint.end());
		size_t st=0;
		for(size_t i=0;i<dimNum;i++)
		{
			if(symPoint(i)==0)
				st=i+1;
			else
				break;
		}
		return arr[forwdMapping(symPoint, st)];
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
	const T &SymmetryArray<T>::getElement(const std::vector<D> &psVec)const try{
		if(0==memory)
			throw(arrayOutBound("0长度数组，拒绝访问"));
		if(dimNum>psVec.size())
			throw arrayAccessException("数组访问错误：坐标向量维数不能小于数组维数");
	    lmtc::Array<long> symPoint(1,dimNum);
		for(size_t count=0;count<dimNum;count++){
			size_t len=psVec[count];
			if(len>=dimVec[count])
				throw(arrayOutBound());
			symPoint(count)=len;
		}
		bool issorted=true;
		for(size_t i=0;i<dimNum-1;i++)
			if(symPoint(i)>symPoint(i+1))
				issorted=false;
		if(issorted==false)
		    std::sort(symPoint.begin(),symPoint.end());
		size_t st=0;
		for(size_t i=0;i<dimNum;i++)
		{
			if(symPoint(i)==0)
				st=i+1;
			else
				break;
		}
		return arr[forwdMapping(symPoint, st)];
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
	T &SymmetryArray<T>::getElement(const std::vector<D> &psVec) try{
		if(0==memory)
			throw(arrayOutBound("0长度数组，拒绝访问"));
		if(dimNum>psVec.size())
			throw arrayAccessException("数组访问错误：坐标向量维数不能小于数组维数");
	    lmtc::Array<long> symPoint(1,dimNum);
		for(size_t count=0;count<dimNum;count++){
			size_t len=psVec[count];
			if(len>=dimVec[count])
				throw(arrayOutBound());
			symPoint(count)=len;
		}
		bool issorted=true;
		for(size_t i=0;i<dimNum-1;i++)
			if(symPoint(i)>symPoint(i+1))
				issorted=false;
		if(issorted==false)
		    std::sort(symPoint.begin(),symPoint.end());
		size_t st=0;
		for(size_t i=0;i<dimNum;i++)
		{
			if(symPoint(i)==0)
				st=i+1;
			else
				break;
		}
		return arr[forwdMapping(symPoint, st)];
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
	long SymmetryArray<T>::forwdMapping(const Array<long> &symPoint,const size_t st)const{
		return unTriMp.forwdMapping(unTriMp.getbm()-1, unTriMp.getdm()-1, const_cast<Array<long> &>(symPoint), st)-1;
	}
	
	template<typename T>
	long SymmetryArray<T>::bkwdMapping(Array<long> &symPoint,const size_t n)const{
		if(n>=memory)
		{
			std::cout<<"逆向映射序号超出范围"<<std::endl;
			throw mappingException("逆向映射序号超出范围");
		}
		return unTriMp.bkwdMapping(unTriMp.getbm()-1,unTriMp.getdm()-1,symPoint,n+1);
	}

	template<typename T>
	template<typename X>
	void SymmetryArray<T>::initialize(const X &t){
		for(size_t i=0;i<memory;i++)
			arr[i]=t;
	}

	//转成一维数组
	template<typename T>
	void SymmetryArray<T>::transformToOneDimension(){
		dimNum=1;
		dimVec.clear();
		dimVec.push_back(memory);
		if(memory!=0)
		{
			Array<long> dimArr(1,2);
			dimArr(0)=1;
			dimArr(1)=memory-1;
			unTriMp=UnTrimMapping(dimArr);	
		}
		else
			unTriMp=UnTrimMapping();	
	}


	//不同类型数组兼容复制构造函数
	template<typename T>
	template<typename X>
	SymmetryArray<T>::SymmetryArray(const SymmetryArray<X> & comArr):dimNum(comArr.dimNum),dimVec(comArr.dimVec),memory(comArr.memory),unTriMp(comArr.unTriMp){
		arr.assign(comArr.arr.begin(),comArr.arr.end());
	}

	//不同类型数组兼容赋值操作符
	template<typename T>
	template<typename X>
	SymmetryArray<T> & SymmetryArray<T>::operator=(const SymmetryArray<X> & comArr){
		dimNum=comArr.dimNum;
		dimVec=comArr.dimVec;
		memory=comArr.memory;
		arr.assign(comArr.arr.begin(),comArr.arr.end());
		unTriMp=comArr.unTriMp;
		return *this;
	}

	template<typename T>
	void SymmetryArray<T>::construct_initialize(size_t d,size_t b){
		dimNum=1;
		memory=b;
		if(d!=1)
		{
			std::cout<<"构造时错误：数组维数不等于1"<<std::endl;
			throw arrayAccessException("构造时错误：数组维数不等于1");
		}
		dimVec.push_back(b);
		arr=std::vector<T>(memory);	
		if(memory!=0)
		{
			Array<long> dimArr(1,2);
			dimArr(0)=1;
			dimArr(1)=memory-1;
			unTriMp=UnTrimMapping(dimArr);	
		}
	}
}


#endif 