#ifndef mySortConst
#define mySortConst
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

#include "array.h"
#include "defaultCompare.h"
#include <vector>
/* 自己的排序算法接口，使用命名空间（lmtc）*/

namespace lmtc{

//合并排序，元素号保存在 orderedSeq[]中，而对应值保存在val[]中，返回按val升序的orderedSeq
//必须保证orderedSeq中的序号不大于val.size()-1;
template<typename T> void mergeSort(std::vector<unsigned int> &orderedSeq ,const std::vector<T> &val ,int st,int ed,bool (*lessEqualCompare)(const T &,const T &)=less_equal_default) 
{
	if(st==ed)
        return ;

	int mid=(st+ed)/2;
	mergeSort(orderedSeq,val,st,mid);
	mergeSort(orderedSeq,val,mid+1,ed);

	std::vector<unsigned int> orderMerge(ed-st+1);
	
	int i=st,j=mid+1,count=0;
	while(true)
	{
		if(i<=mid&&j<=ed)
		{
			if(lessEqualCompare(val[ orderedSeq[i] ],val[ orderedSeq[j] ]))
				orderMerge[count++] = orderedSeq[i++];
			else
				orderMerge[count++] = orderedSeq[j++];
		}
		else if(i<=mid&&j>ed)
			orderMerge[count++] = orderedSeq[i++];
		else if(i>mid&&j<=ed)
			orderMerge[count++] = orderedSeq[j++];
		else if(i>mid&&j>ed)
			break;
	}
	if(count!=(ed-st+1))
		printf("error of mergeSort\n");

	for( int k=st;k<=ed;k++)
		orderedSeq[k]=orderMerge[k-st];
}

//合并排序，元素保存在 seq[]中，而对应值保存在val[]中，返回按val升序的seq
template<typename T1, typename T2> bool sort(std::vector<T1> &seq ,const std::vector<T2> &val,bool (*lessEqualCompare)(const T2 &,const T2 &)=less_equal_default) 
{
	if(seq.size()!=val.size())
		return false;
	std::vector<unsigned int> order(val.size());
	for(unsigned int i=0;i<val.size();i++)
		order[i]=i;
	lmtc::mergeSort(order,val,0,val.size()-1,lessEqualCompare);
	std::vector<T1> seq2;
	for(unsigned int i=0;i<order.size();i++)
		seq2.push_back(seq[order[i]]);
	seq.swap(seq2);
	return true;
}



}

#endif 