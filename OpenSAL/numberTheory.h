#ifndef numberTheoryConst 
#define numberTheoryConst
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

//数论常用算法
namespace lmtc{
	//产生大于minNumber的最小质数，利用smallPrimeNumber个较小质数进行测试。
	unsigned long generatePrimeNumberBySimpleTest(const unsigned long minNumber,const unsigned long smallPrimeNumber);
	//unsigned long所能表示的最大质数
	const unsigned long MAX_PRIME=4294966297; 
	//圆周率
	const long double PI=3.1415926535897932384626433832795028841971; 
}
#endif