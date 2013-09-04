#ifndef fastFourierTransformConst
#define fastFourierTransformConst
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

//快速傅里叶变换及其逆变换
#include "number.h"
#include <vector>
#include "array.h"
namespace lmtc{
	class FastFourierTransform{
	public:
		//快速傅里叶变换，系数向量a的尺寸自动扩充为正合幂，用零进行填充，返回傅里叶点值向量。
		//O(nlgn),n=a.size(),参见《算法导论p506-515》
		static std::vector<ComplexNumber> fft(const std::vector<ComplexNumber> &a);

		//快速傅里叶逆变换，y尺寸必须为正合幂（否则异常），返回原系数向量。
		//O(nlgn),n=a.size(),参见《算法导论p506-515》
		static std::vector<ComplexNumber> _fft(const std::vector<ComplexNumber> &y);

		//多维快速傅里叶变换，系数张量a的各维尺寸自动扩充为正合幂，用零进行填充，返回傅里叶点值张量。
		//O(nlgn),n=a.size(),参见《算法导论p520，习题30-3》
		static lmtc::Array<ComplexNumber> fft(const lmtc::Array<ComplexNumber> &a);

		//多维快速傅里叶逆变换，张量y各维尺寸必须为正合幂（否则异常），返回原系数张量。
		//O(nlgn),n=a.size(),参见《算法导论p520，习题30-3》
		static lmtc::Array<ComplexNumber> _fft(const lmtc::Array<ComplexNumber> &y);

	private:
		//快速傅里叶变换辅助函数。
		static std::vector<ComplexNumber> fft_visit(const std::vector<ComplexNumber> &a);

		//快速傅里叶逆变换辅助函数。
		static std::vector<ComplexNumber> _fft_visit(const std::vector<ComplexNumber> &y);

		//多维快速傅里叶变换辅助函数。
		static lmtc::Array<ComplexNumber> fft_visit(const lmtc::Array<ComplexNumber> &a);

		//多维快速傅里叶逆变换辅助函数。
		static lmtc::Array<ComplexNumber> _fft_visit(const lmtc::Array<ComplexNumber> &y);
	};
}
#endif