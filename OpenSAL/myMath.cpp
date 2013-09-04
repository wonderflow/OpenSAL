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

#include "stdafx.h"
#include <cstdlib>
#include <ctime>
#include "myMath.h"

double lmtc::averageRandom(double min,double max)//生成一个平均分布的随机数，精度为0.000001， 区间最好不大于10
{ 
	if(max-min<0.00001)
	{
		if(rand()%2==0)
			return min;
		else
			return max;
	}	  
    long minInteger=(long)(min*1000000); 
    long maxInteger=(long)(max*1000000); 
    long randInteger=(long)(rand()*10000+rand()%9999);
    long diffInteger=maxInteger-minInteger; 
    long resultInteger=randInteger%diffInteger+minInteger; 
    return (double)(resultInteger/1000000.0); 
} 

double lmtc::averageRandom()//生成一个平均分布的随机数,范围为[0-1)，精度为0.000001
{ 
    long randInteger=(long)(rand()*10000+rand()%9999);
    long resultInteger=randInteger%1000000; 
    return (double)(resultInteger/1000000.0); 
} 
