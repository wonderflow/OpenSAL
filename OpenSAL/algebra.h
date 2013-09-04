#ifndef algebraConst
#define algebraConst
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

//代数方面的算法
#include <vector>
#include "array.h"
#include "number.h"
#include <cmath>
#include "myException.h"
namespace lmtc{
	class Algebra{
	public:
		//计算方幂和公式,返回二维数组S,则有：对于任意k<=K, 0^k+1^k+2^k+...+n^k=S(k,0)+S(k,1)*n+S(k,2)*n^2+...+S(k,k+1)*n^(k+1) .
		//O(K^3)，本算法为作者发明。
		static Array<double> powerSumFormula(const unsigned int K);

		//计算方幂和：0^k+1^k+2^k+...+n^k .
		//O(k^3),与n无关，本算法为作者发明。
		static double powerSum(const unsigned int n,const unsigned int k);

		//利用霍纳规则计算朴素多项式coef[0]+coef[1]*x+......+coef[coef.size()-1]*x^(coef.size()-1)
		//O(n)，参见《算法导论p24，习题2-3》
		template<typename T>
		static double computePolynomialByHonerRule(const double x,const std::vector<T> coef);

		//普通的矩阵乘法，输入为matrix1，matrix2，二者需为二维数组，且满足矩阵相乘的要求。返回二维数组。
		//O(n^3)
		template<typename T>
		static Array<T> matrixMultiplySimple(const Array<T> &matrix1,const Array<T> &matrix2);

		//Strassen矩阵乘法，输入为matrix1，matrix2，二者需为二维数组，且满足矩阵相乘的要求。返回二维数组。
		//O(n^2.81),参见《算法导论p451-455》
		template<typename T>
		static Array<T> matrixMultiplyStrassen(const Array<T> &matrix1,const Array<T> &matrix2);

		//LUP分解。A为待分解矩阵，结果存在L、U、P，使得PA=LU，可分解返回true，不可分解（奇异方阵）返回false。
		//O(n^3),参见《算法导论p456-463》
		static bool lupDecompose(const Array<double> &A,Array<double> &L,Array<double> &U,std::vector<unsigned int> &P);

		//解线性方程组LUx=Pb。L、U、P为某非奇异方阵的LUP分解，解存至x。用户必须保证L、U、P正确，否则将会出现未知的异常或错误。
		//O(n^2),参见《算法导论p457》
		static void solveLinearEquationsGivenLUP(const Array<double> &L,const Array<double> &U,const std::vector<unsigned int> &P,const std::vector<double> &b,std::vector<double> &x);

		//解线性方程组Ax=b，利用LUP分解。解存至x，有解则返回true，无解返回false。
		//O(n^3),参见《算法导论p457》
		static bool solveLinearEquationsByLUP(const Array<double> &A,const std::vector<double> &b,std::vector<double> &x);

		//快速解线性方程组Ax=b，利用快速矩阵求逆。解存至x，有解则返回true，无解返回false。
		//O(n^2.81)，《参见算法导论p456,465》
		static bool solveLinearEquationsFast(const Array<double> &A,const std::vector<double> &b,std::vector<double> &x);

		//利用LUP分解求逆矩阵。求A的逆矩阵，结果存至_A，A可逆返回true，不可逆返回false。
		//O(n^3),参见《算法导论p464》。
		static bool inverseMatrixByLUP(const Array<double> &A,Array<double> &_A);

		//快速矩阵求逆。求A的逆矩阵，结果存至_A，A可逆返回true，不可逆返回false。
		//时间复杂度与矩阵乘法相同，采用Strassen乘法时为：O(n^2.81),参见《算法导论p465》
		static bool inverseMatrixFast(const Array<double> &A,Array<double> &_A);

		//矩阵转置。
		//O(n^2)
		template<typename T>
		static Array<T> transposeMatrix(const Array<T> &A);

		//求A的前向伪逆矩阵A_（非方阵的逆矩阵，逆矩阵的自然推广）。有A_*A=E。
		//当且仅当A列满秩时，A_存在，此时返回true，否则返回false。
		//O(n^2.81),利用Strassen快速乘法和快速求逆算法,参见《算法导论p469》。
		static bool pseudoInverseMatrixForward(const Array<double> &A,Array<double> &A_);

		//求A的后向伪逆矩阵_A（非方阵的逆矩阵，逆矩阵的自然推广）。有A*_A=E。
		//当且仅当A行满秩时，_A存在，此时返回true，否则返回false。
		//O(n^2.81),利用Strassen快速乘法和快速求逆算法,参见《算法导论p469》。
		static bool pseudoInverseMatrixBackward(const Array<double> &A,Array<double> &_A);

		//利用LUP解正态方程组Ax=b。要求A的行数不小于列数，b的行数等于A的列数（否则异常）。
		//A为列满秩则可解返回true，否则返回false，解存至x。
		//O(n^3),参见《算法导论p469》。
		static bool solveNormalityEquationsByLUP(const Array<double> &A,const std::vector<double> &b,std::vector<double> &x);

		//快速解正态方程组Ax=b。要求A的行数不小于列数，b的行数等于A的列数（否则异常）。
		//A为列满秩则可解返回true，否则返回false，解存至x。
		//O(n^2.81),参见《算法导论p469》。
		static bool solveNormalityEquationsFast(const Array<double> &A,const std::vector<double> &b,std::vector<double> &x);

		//最小二乘估计（LUP），minimize{|F(X).C-Y|},其中F(x)=( f(0,x),f(1,x),...,f(n-1,x) )。
		//f和n给出待估计函数的形式，X、Y给出数据样本，估计结果存至C。
		//要求X与Y尺寸相同，并不小于n（否则异常），估计成功返回true，否则说明数据不够估计失败返回false。
		//O(n^3),参见《算法导论p469》。
		static bool leastSquaresEstimationByLUP(double (*f)(unsigned int i,double x),const unsigned int n,const std::vector<double> &X,const std::vector<double> &Y,std::vector<double> &C);

		//快速最小二乘估计，minimize{|F(X).C-Y|},其中F(x)=( f(0,x),f(1,x),...,f(n-1,x) )。
		//f和n给出待估计函数的形式，X、Y给出数据样本，估计结果存至C。
		//要求X与Y尺寸相同，并不小于n（否则异常），估计成功返回true，否则说明数据不够估计失败返回false。
		//O(n^2.81),参见《算法导论p469》。
		static bool leastSquaresEstimationFast(double (*f)(unsigned int i,double x),const unsigned int n,const std::vector<double> &X,const std::vector<double> &Y,std::vector<double> &C);

		//利用快速傅里叶变换求卷积a(*)b,返回卷积向量。卷积即为多项式乘积。
		//O(nlgn),其中n=a.size()+b.size()。参见《算法导论p506-515》
		static std::vector<ComplexNumber> convolution(const std::vector<ComplexNumber> &a,const std::vector<ComplexNumber> &b);

		//利用多维快速傅里叶变换求多维卷积a(*)b,返回卷积张量。多维卷积即为多维多项式乘积。
		//当a和b的维数为常数时，O(nlgn),其中n=c.size(),c为返回的卷积张量。参见《算法导论p506-515，520》
		static Array<ComplexNumber> convolution(const Array<ComplexNumber> &a,const Array<ComplexNumber> &b);

	private:
		//Strassen矩阵乘法辅助函数。
		template<typename T>
		static Array<T> matrixMultiplyStrassen_visit(const Array<T> &matrix1,const Array<T> &matrix2);

		//快速矩阵求逆辅助函数（A为正合幂对称正定矩阵）。
		static bool inverseMatrixFast_visit(const Array<double> &A,Array<double> &_A);
	};

	//利用霍纳规则计算朴素多项式coef[0]+coef[1]*x+......+coef[coef.size()-1]*x^(coef.size()-1)
	template<typename T>
	double Algebra::computePolynomialByHonerRule(const double x,const std::vector<T> coef){
		double rs=0;
		for(int i=coef.size()-1;i>=0;i--)
		    rs=rs*x+coef[i];
		return rs;
	}

	//普通的矩阵乘法
	//O(n^3)
	template<typename T>
	Array<T> Algebra::matrixMultiplySimple(const Array<T> &matrix1,const Array<T> &matrix2){
		if(matrix1.getDimNum()!=2||matrix2.getDimNum()!=2||matrix1.getDimLen(1)!=matrix2.getDimLen(0))
			throw MatrixException("矩阵乘法matrixMultiplySimple的参数不符合要求！");
		Array<T> matrixRs(2,matrix1.getDimLen(0),matrix2.getDimLen(1));
		for(unsigned int i=0;i<matrixRs.getDimLen(0);i++)
			for(unsigned int j=0;j<matrixRs.getDimLen(1);j++)
				for(unsigned int k=0;k<matrix1.getDimLen(1);k++)
					matrixRs(i,j)+=matrix1(i,k)*matrix2(k,j);
		return matrixRs;
	}
	
	//Strassen矩阵乘法
	template<typename T>
	Array<T> Algebra::matrixMultiplyStrassen(const Array<T> &matrix1,const Array<T> &matrix2){
		if(matrix1.getDimNum()!=2||matrix2.getDimNum()!=2||matrix1.getDimLen(1)!=matrix2.getDimLen(0))
			throw MatrixException("矩阵乘法matrixMultiplySimple的参数不符合要求！");
		unsigned int u=0,v=0,w=0;
		unsigned int cout=1;
		while(u==0||v==0||w==0)
		{	
			if(u==0&&matrix1.getDimLen(0)<=cout)
				u=cout;
			if(v==0&&matrix1.getDimLen(1)<=cout)
				v=cout;
			if(w==0&&matrix2.getDimLen(1)<=cout)
				w=cout;
			cout*=2;
		}
		Array<T> matrixStd1(2,u,v);
		Array<T> matrixStd2(2,v,w);
		for(unsigned int i=0;i<matrix1.getDimLen(0);i++)
			for(unsigned int j=0;j<matrix1.getDimLen(1);j++){
				matrixStd1(i,j)=matrix1(i,j);
			}
		for(unsigned int i=0;i<matrix2.getDimLen(0);i++)
			for(unsigned int j=0;j<matrix2.getDimLen(1);j++){
				matrixStd2(i,j)=matrix2(i,j);
			}
		Array<T> matrixStdRs = matrixMultiplyStrassen_visit(matrixStd1,matrixStd2);
		Array<T> matrixRs(2,matrix1.getDimLen(0),matrix2.getDimLen(1));
		for(unsigned int i=0;i<matrixRs.getDimLen(0);i++)
			for(unsigned int j=0;j<matrixRs.getDimLen(1);j++)
				matrixRs(i,j)=matrixStdRs(i,j);
		return matrixRs;
	}
	//Strassen矩阵乘法辅助函数。
	template<typename T>
	Array<T> Algebra::matrixMultiplyStrassen_visit(const Array<T> &matrix1,const Array<T> &matrix2){
		if(matrix1.getDimLen(0)==1||matrix1.getDimLen(1)==1||matrix2.getDimLen(1)==1)
			return matrixMultiplySimple(matrix1,matrix2);
		Array<T> temp1(2,matrix1.getDimLen(0)/2,matrix1.getDimLen(1)/2);
		Array<T> temp2(2,matrix2.getDimLen(0)/2,matrix2.getDimLen(1)/2);
		Array<T> matrixRs(2,matrix1.getDimLen(0),matrix2.getDimLen(1));

		for(unsigned int i=0;i<temp1.getDimLen(0);i++)
			for(unsigned int j=0;j<temp1.getDimLen(1);j++)
				temp1(i,j)=matrix1(i,j);
		for(unsigned int i=0;i<temp2.getDimLen(0);i++)
			for(unsigned int j=0;j<temp2.getDimLen(1);j++)
				temp2(i,j)=matrix2(i,j+temp2.getDimLen(1))-matrix2(i+temp2.getDimLen(0),j+temp2.getDimLen(1));
		Array<T> p1=matrixMultiplyStrassen_visit(temp1,temp2);

		for(unsigned int i=0;i<temp1.getDimLen(0);i++)
			for(unsigned int j=0;j<temp1.getDimLen(1);j++)
				temp1(i,j)=matrix1(i,j)+matrix1(i,j+temp1.getDimLen(1));
		for(unsigned int i=0;i<temp2.getDimLen(0);i++)
			for(unsigned int j=0;j<temp2.getDimLen(1);j++)
				temp2(i,j)=matrix2(i+temp2.getDimLen(0),j+temp2.getDimLen(1));
		Array<T> p2=matrixMultiplyStrassen_visit(temp1,temp2);

		for(unsigned int i=0;i<temp1.getDimLen(0);i++)
			for(unsigned int j=0;j<temp1.getDimLen(1);j++)
				temp1(i,j)=matrix1(i+temp1.getDimLen(0),j)+matrix1(i+temp1.getDimLen(0),j+temp1.getDimLen(1));
		for(unsigned int i=0;i<temp2.getDimLen(0);i++)
			for(unsigned int j=0;j<temp2.getDimLen(1);j++)
				temp2(i,j)=matrix2(i,j);
		Array<T> p3=matrixMultiplyStrassen_visit(temp1,temp2);

		for(unsigned int i=0;i<temp1.getDimLen(0);i++)
			for(unsigned int j=0;j<temp1.getDimLen(1);j++)
				temp1(i,j)=matrix1(i+temp1.getDimLen(0),j+temp1.getDimLen(1));
		for(unsigned int i=0;i<temp2.getDimLen(0);i++)
			for(unsigned int j=0;j<temp2.getDimLen(1);j++)
				temp2(i,j)=matrix2(i+temp2.getDimLen(0),j)-matrix2(i,j);
		Array<T> p4=matrixMultiplyStrassen_visit(temp1,temp2);

		for(unsigned int i=0;i<temp1.getDimLen(0);i++)
			for(unsigned int j=0;j<temp1.getDimLen(1);j++)
				temp1(i,j)=matrix1(i,j)+matrix1(i+temp1.getDimLen(0),j+temp1.getDimLen(1));
		for(unsigned int i=0;i<temp2.getDimLen(0);i++)
			for(unsigned int j=0;j<temp2.getDimLen(1);j++)
				temp2(i,j)=matrix2(i,j)+matrix2(i+temp2.getDimLen(0),j+temp2.getDimLen(1));
		Array<T> p5=matrixMultiplyStrassen_visit(temp1,temp2);

		for(unsigned int i=0;i<temp1.getDimLen(0);i++)
			for(unsigned int j=0;j<temp1.getDimLen(1);j++)
				temp1(i,j)=matrix1(i,j+temp1.getDimLen(1))-matrix1(i+temp1.getDimLen(0),j+temp1.getDimLen(1));
		for(unsigned int i=0;i<temp2.getDimLen(0);i++)
			for(unsigned int j=0;j<temp2.getDimLen(1);j++)
				temp2(i,j)=matrix2(i+temp2.getDimLen(0),j)+matrix2(i+temp2.getDimLen(0),j+temp2.getDimLen(1));
		Array<T> p6=matrixMultiplyStrassen_visit(temp1,temp2);

		for(unsigned int i=0;i<temp1.getDimLen(0);i++)
			for(unsigned int j=0;j<temp1.getDimLen(1);j++)
				temp1(i,j)=matrix1(i,j)-matrix1(i+temp1.getDimLen(0),j);
		for(unsigned int i=0;i<temp2.getDimLen(0);i++)
			for(unsigned int j=0;j<temp2.getDimLen(1);j++)
				temp2(i,j)=matrix2(i,j)+matrix2(i,j+temp2.getDimLen(1));
		Array<T> p7=matrixMultiplyStrassen_visit(temp1,temp2);

		for(unsigned int i=0;i<temp1.getDimLen(0);i++)
			for(unsigned int j=0;j<temp2.getDimLen(1);j++){
				matrixRs(i,j)=p5(i,j)+p4(i,j)-p2(i,j)+p6(i,j);
				matrixRs(i+temp1.getDimLen(0),j)=p3(i,j)+p4(i,j);
				matrixRs(i,j+temp2.getDimLen(1))=p1(i,j)+p2(i,j);
				matrixRs(i+temp1.getDimLen(0),j+temp2.getDimLen(1))=p5(i,j)+p1(i,j)-p3(i,j)-p7(i,j);
			}
		return matrixRs;
	}

	//矩阵转置。
	template<typename T>
	Array<T> Algebra::transposeMatrix(const Array<T> &A){
		if(A.getDimNum()!=2)
			throw MatrixException("transposeMatrix的参数A不为二维矩阵！");
		Array<T> AT(2,A.getDimLen(1),A.getDimLen(0));
		for(unsigned int i=0;i<AT.getDimLen(0);i++)
			for(unsigned int j=0;j<AT.getDimLen(1);j++)
				AT(i,j)=A(j,i);
		return AT;
	}

}

#endif