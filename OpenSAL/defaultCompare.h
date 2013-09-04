#ifndef defaultCompareConst
#define defaultCompareConst
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

namespace lmtc{

template<typename T1,typename T2> 
bool equal_default(const T1 &t1, const T2 &t2){
		return t1==t2;
	}
template<typename T1,typename T2> 
bool not_equal_default(const T1 &t1, const T2 &t2){
		return t1!=t2;
	}

template<typename T1,typename T2> 
bool less_default(const T1 &t1, const T2 &t2){
		return t1<t2;
	}
template<typename T1,typename T2> 
bool less_equal_default(const T1 &t1, const T2 &t2){
		return t1<=t2;
	}

template<typename T1,typename T2> 
bool greater_default(const T1 &t1, const T2 &t2){
		return t1>t2;
	}
template<typename T1,typename T2> 
bool greater_equal_default(const T1 &t1, const T2 &t2){
		return t1>=t2;
	}


}
#endif