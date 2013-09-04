#ifndef myExceptionConst
#define myExceptionConst
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

/* 自己的异常类，使用命名空间（lmtc）*/
#include <exception>
#include <string>
namespace lmtc{

	class arrayOutBound:public std::exception{
	public:
		arrayOutBound():exception("异常：数组访问越界"){};	
		arrayOutBound(const char * str):exception(str){};
		arrayOutBound(const std::string &str):exception(str.c_str()){};	
	};

	class arrayAccessException:public std::exception{
	public:
		arrayAccessException():exception("异常：数组访问错误"){};	
		arrayAccessException(const char * str):exception(str){};
		arrayAccessException(const std::string &str):exception(str.c_str()){};	
	};

	class mappingException:public std::exception{
	public:
		mappingException():exception("异常：映射异常"){};	
		mappingException(const char * str):exception(str){};
		mappingException(const std::string &str):exception(str.c_str()){};	
	};

	class HeapAccessException:public std::exception{
	public:
		HeapAccessException():exception("异常：堆访问异常"){};	
		HeapAccessException(const char * str):exception(str){};
		HeapAccessException(const std::string &str):exception(str.c_str()){};	
	};

	class EmptySmartPtrAccessException:public std::exception{
	public:
		EmptySmartPtrAccessException():exception("异常：访问空的智能指针"){};	
		EmptySmartPtrAccessException(const char * str):exception(str){};
		EmptySmartPtrAccessException(const std::string &str):exception(str.c_str()){};	
	};

	class HashException:public std::exception{
	public:
		HashException():exception("异常：哈希表异常"){};	
		HashException(const char * str):exception(str){};
		HashException(const std::string &str):exception(str.c_str()){};	
	};

	class MatroidException:public std::exception{
	public:
		MatroidException():exception("异常：拟阵异常"){};	
		MatroidException(const char * str):exception(str){};
		MatroidException(const std::string &str):exception(str.c_str()){};	
	};

	class GraphException:public std::exception{
	public:
		GraphException():exception("异常：图异常"){};	
		GraphException(const char * str):exception(str){};
		GraphException(const std::string &str):exception(str.c_str()){};	
	};

	class MatrixException:public std::exception{
	public:
		MatrixException():exception("异常：矩阵异常"){};	
		MatrixException(const char * str):exception(str){};
		MatrixException(const std::string &str):exception(str.c_str()){};	
	};

	class ComplexNumberException:public std::exception{
	public:
		ComplexNumberException():exception("异常：复数异常"){};	
		ComplexNumberException(const char * str):exception(str){};
		ComplexNumberException(const std::string &str):exception(str.c_str()){};	
	};

	class FastFourierTransformException:public std::exception{
	public:
		FastFourierTransformException():exception("异常：快速傅里叶变换异常"){};	
		FastFourierTransformException(const char * str):exception(str){};
		FastFourierTransformException(const std::string &str):exception(str.c_str()){};	
	};
	

}



#endif 