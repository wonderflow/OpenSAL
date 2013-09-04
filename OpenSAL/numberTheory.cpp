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
#include "numberTheory.h"
#include <vector>
unsigned long lmtc::generatePrimeNumberBySimpleTest(const unsigned long minNumber,const unsigned long smallPrimeNumber){
	std::vector<unsigned long> smallPrimeVec;
	smallPrimeVec.push_back(2);
	unsigned long curNumber=3;
	while(smallPrimeVec.size()<smallPrimeNumber){
		for(std::vector<unsigned long>::iterator iter=smallPrimeVec.begin();iter!=smallPrimeVec.end();iter++){
			if((curNumber%(*iter))==0){
				curNumber+=2;
				break;
			}
			if((iter+1)==smallPrimeVec.end()){
				smallPrimeVec.push_back(curNumber);
				curNumber+=2;
				break;
			}
		}
	}
	unsigned long prime=minNumber;
	if(prime<=smallPrimeVec[smallPrimeVec.size()-1])
			return smallPrimeVec[smallPrimeVec.size()-1];
	while(true){
		for(std::vector<unsigned long>::iterator iter=smallPrimeVec.begin();iter!=smallPrimeVec.end();iter++){
			if((prime%(*iter))==0){
				prime++;
				break;
			}
			if((iter+1)==smallPrimeVec.end()){
				return prime;
			}
		}
		
	}
}