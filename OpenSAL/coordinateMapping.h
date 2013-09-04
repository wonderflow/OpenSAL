#ifndef coordinateMappingConst
#define coordinateMappingConst
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
namespace lmtc{
class CrossFace {
public:
    //计算Sp（m，limit）中w对角面对称元素数；array[X,Y,Z]为辅助数组，X>=m,Y>=limit,Z>=w;
	long crossFace(long m,long limit,long w,Array<long> &arr)const;

	//计算Sp（m，limit）中W对角面及之前元素数
	long sumNumofT(long m,long limit,long W)const;

	//初始化numInCroF数组
	long initNumInCroF(long m,long limit,long W,Array<long> &numInCroF)const;

	//初始化numBfCroF数组
	long initNumBfCroF(long m,long limit,long W,Array<long> &numInCroF,Array<long> &numBfCroF)const;

	//计算组合数C（m，n） arry为辅助数组可以为null。
	long combination(long m,long n,Array<long> &arry)const;

private:
	//计算组合数C（m，n） arry为辅助数组不可以为null，且数组不小于[m,n]。
	long combination1(long m,long n,Array<long> &arry1)const;	
};


class StandMapping {
	
public: //常用接口

	//构造dmNum维，界限为limit的标准对称空间
	StandMapping(long dmNum,long limit);

	//默认构造函数
	StandMapping():dm(0),limit(0),W(0){};
	
  //正向映射，必须保证pointDmNum<=dmNum,w>=pointDmNum;且数组满足limit及w；按对角面值升序排列，然后相同对角面才依从左到右优先级的各维坐标主序排列。
    long forwdMapping
	//(对称空间维数，界限，        待映射坐标，         坐标维数    ，对角面，数组中首坐标位置）
	(long dmNum,long limit,Array<long>&symPoint,long pointDmNum,long w,long st)const;
    
  //正向映射，必须保证pointDmNum<=dmNum,w>=pointDmNum;且数组满足limit及w；按对角面值升序排列，然后相同对角面才依从左到右优先级的各维坐标主序排列。
    long forwdMapping
	//(对称空间维数，界限，        待映射坐标，         坐标维数    ，对角面，数组中首坐标位置，坐标中最小正整数）
	(long dmNum,long limit,Array<long>&symPoint,long pointDmNum,long w,long st,long base)const;
   
    //逆向映射必须保证pointDmNum<=dmNum,w>=pointDmNum;且数组满足limit及w；
    long bkwdMapping
	//(对称空间维数，界限，        待映射坐标，  对角面 ， 坐标维数  ，带映射序号，  数组中末坐标位置，dmNum每维基值）
	(long dmNum,long limit,Array<long> &symPoint,long f, long dm,    long num,    long end,  long offset)const;

	//计算对角面特定维坐标序列中某对称点之后元素数 
   long forwdMappingIJ
   //（  待映射坐标，           坐标维数 ，  界限 ，   对角面 ，  数组中首坐标位置，坐标中最小正整数）
	(Array<long> &symPoint,long pointDmNum,long limit,long w,long st,long base)const;

public://非常用接口

    //折半查找寻找sp（dmNum，limit）中num对称点所在对角面
    long findFace(long dmNum,long limit,long num)const;

	//折半查找sp（dmNum，limit）中f对角面序号为num的对称点的维数：
     long findDm(long dmNum,long f,long limit,long num)const;
     
    //在sp（dm，limit）的f对角面dm维坐标折半查找大于等于minItem的首元，其之后元素数为back；
    long findFirstItem(long dm,long f,long limit,long minItem,long back)const;

    //计算组合数C（m，n）array[X,Y]为辅助数组其中X>=m+n,Y>=n
    long combination(long m,long n,Array<long> &arr)const;

    long numInCroF(long dm,long limit,long w)const;
    long numBfCroF(long dm,long limit,long w)const;

private:

	//设置对称空间（更加维数和界限改变数组numInCroFArr和numBfCroFArr
    void setArray(long dmNum,long limit);

private:
	Array<long> numInCroFArr;
	Array<long> numBfCroFArr;
	long dm;
	long limit;
	long W;
	CrossFace cross;
};


class UnsymMapping {

public:
	//初始维信息，dmAr[0]存储总维数；dmAr[i>0]表示i维界限。
	UnsymMapping(Array<long> &dmAr);

	//正向映射，由dm维坐标point返回序号
    long forwdMapping(Array<long> &point,long st)const;

    //逆向映射，由序号pn得到dm维坐标。
    void bkwdMapping(long pn,Array<long> &point,long st )const;

private:
	
	//设置维信息，dmAr[0]存储总维数；dmAr[i>0]表示i维界限。
	long setDm(Array<long> &dmAr);

private:
	long dm;//非规整对称空间维数
	Array<long> bd; //bd[0]存储总维数；bd[i>0]表示i维界限+1
    Array<long> bkDmMu;//bkDmMu[i]表示i维及以后维组成子空间大小即：bd[i]*bd[i+1]*......*bd[dm]
};


class UnTrimMapping {	//与标准的规整映射不兼容
public:

	//初始维信息，dmAr[0]存储总维数；dmAr[i>0]表示i维界限。
	UnTrimMapping(Array<long> &dmAr) ;

	//默认构造函数
	UnTrimMapping(){}
	
	//非规整正向映射，按非零维数升序排列，然后相同非零维数按对角面值升序排列，然后才依从左到右优先级的各维坐标主序排列。
	//st表示最低非零维（全零坐标值为dm，symPoint(0--dm-1)表示第i维坐标值，要求非降序排列。
	//返回坐标次序
	long forwdMapping(long i,long j, Array<long> &symPoint,long st)const;
	
	//非规整逆向映射
	//在（i，j）左下方子空间降序号n逆映射，存于symPoint（从j位置向前）
	//返回非零最低维
	long bkwdMapping(long i,long j,Array<long> &symPoint,long n)const;

	//返回坐标总数目
	long countN()const;

	//返回水平分割线数
	long getbm()const;
	long getdm()const{return dm;}

private:
	//初始维信息，dmAr[0]存储总维数；dmAr[i>0]表示i维界限。
	long initArray(Array<long> &dmAr);

	//返回（i，j）左下方子问题对称元素数
	long countSunPro(long i,long j)const;

	long findU(long i,long j,long n)const;
	long findV(long i,long j,long u,long n)const;

private:
	Array<long> boundVal;
    Array<long> boundBegin;
    Array<long> sumNumOfSunSp;
    Array<long> sumNumOfSunPro;
    Array<long> sumNumBfSunPro;
    Array<long> cubeTr;
    long dm;//非规整对称空间维数
	Array<long> bd;//bd[0]存储总维数；bd[i>0]表示i维界限
	long bm;//水平分隔线数
	long maxBound;//最大相邻水平界限差
	Array<long> limitBetwBd;
	StandMapping stMap;
};


}

#endif
      