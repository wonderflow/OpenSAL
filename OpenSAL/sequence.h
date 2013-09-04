#ifndef sequenceConst
#define sequenceConst
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
#include "array.h"
#include "defaultCompare.h"
/*序列相关的算法
*/
namespace lmtc{

//最长公共子序列——动态规划算法，时间为O(v1.size()*v2.size())
template<typename T>
std::vector<T> longestCommonSubsequence(const std::vector<T> &v1,const std::vector<T> &v2,bool (*equal)(const T &,const T &)=lmtc::equal_default){
	std::vector<T> vc;//公共序列存储向量
	if(v1.size()==0||v2.size()==0)
		return vc;
	lmtc::Array<int> arr(2,v1.size()+1,v2.size()+1);
	//动态规划计算
	for(unsigned int i=1;i<=v1.size();i++)
		for(unsigned int j=1;j<=v2.size();j++)
			if(equal(v1[i-1],v2[j-1]))
				arr(i,j)=arr(i-1,j-1)+1;
			else
				arr(i,j)=std::max(arr(i,j-1),arr(i-1,j));
	//反向求解
	unsigned int i=v1.size(),j=v2.size();
	while(i!=0&&j!=0){
		if(equal(v1[i-1],v2[j-1])){
			vc.push_back(v1[i-1]);
			i--;
			j--;
		}
		else if(arr(i,j)==arr(i,j-1))
			j--;
		else i--;
	}
	std::reverse(vc.begin(),vc.end());
	return vc;
}
//接受迭代器的参数的版本
template<typename T,typename Iterator1,typename Iterator2>
std::vector<T> longestCommonSubsequence(Iterator1 beg1,Iterator1 end1,Iterator2 beg2,Iterator2 end2,bool (*equal)(const T &,const T &)=lmtc::equal_default){
	std::vector<T> v1(beg1,end1);
	std::vector<T> v2(beg2,end2);
	return longestCommonSubsequence(v1,v2,equal);
}


}//end namespace
#endif