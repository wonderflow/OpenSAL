#ifndef numberConst
#define numberConst
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

#include "myException.h"
#include <string>
#include <cmath>
//处理复杂数字方面的类
namespace lmtc{
	//复数类，可与内置数字类型兼容运算。
	class ComplexNumber{
	public:
		ComplexNumber():rel(0),vir(0){}
		ComplexNumber(long double realPart):rel(realPart),vir(0){}
		ComplexNumber(long double realPart,long double virtualPart):rel(realPart),vir(virtualPart){}
		ComplexNumber operator+(const ComplexNumber &cxNb)const{return ComplexNumber(rel+cxNb.rel,vir+cxNb.vir);}
		ComplexNumber operator-(const ComplexNumber &cxNb)const{return ComplexNumber(rel-cxNb.rel,vir-cxNb.vir);}
		ComplexNumber operator*(const ComplexNumber &cxNb)const{return ComplexNumber(rel*cxNb.rel-vir*cxNb.vir,rel*cxNb.vir+vir*cxNb.rel);}
		ComplexNumber operator/(const ComplexNumber &cxNb)const{long double temp=cxNb.rel*cxNb.rel+cxNb.vir*cxNb.vir; if(temp<0.0000000001) throw ComplexNumberException("除零异常");return ComplexNumber((rel*cxNb.rel+vir*cxNb.vir)/temp,(cxNb.rel*vir-rel*cxNb.vir)/temp);}
		ComplexNumber& operator+=(const ComplexNumber &cxNb){rel+=cxNb.rel,vir+=cxNb.vir;return *this;}
		ComplexNumber& operator-=(const ComplexNumber &cxNb){rel-=cxNb.rel,vir-=cxNb.vir;return *this;}
		ComplexNumber& operator*=(const ComplexNumber &cxNb){long double rel1=rel*cxNb.rel-vir*cxNb.vir;long double vir1=rel*cxNb.vir+vir*cxNb.rel;rel=rel1;vir=vir1;return *this;}
		ComplexNumber& operator/=(const ComplexNumber &cxNb){long double temp=cxNb.rel*cxNb.rel+cxNb.vir*cxNb.vir;long double rel1=(rel*cxNb.rel+vir*cxNb.vir)/temp;long double vir1=(cxNb.rel*vir-rel*cxNb.vir)/temp;rel=rel1;vir=vir1;return *this;}
		
		//相等比较，实部和虚部的相等精度为accuracy
		bool equal(const ComplexNumber &cxNb,long double accuracy=0.0000001)const{if(std::abs(rel-cxNb.rel)<accuracy&&std::abs(vir-cxNb.vir)<accuracy) return true;else return false;}
		//字符串转换操作符
		operator std::string()const{char str[50];sprintf_s(str,"%.12lf + %.12lfi",rel,vir);return std::string(str);}
	
		//获取实部或虚部
		long double getRel()const{return rel;}
		long double getVir()const{return vir;}
	private:
		long double rel;//实部
		long double vir;//虚部
	};
}

#endif