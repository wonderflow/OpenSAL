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
#include "algebra.h"
#include "number.h"
#include "fastFourierTransform.h"
namespace lmtc{

	//计算方幂和公式
	Array<double> Algebra::powerSumFormula(const unsigned int K){
		//计算组合数数组C
		Array<double> C(2,K+1,K+1);
		for(unsigned int i=0;i<C.getDimLen(0);i++)
			C(i,0)=1;
		for(unsigned int i=1;i<C.getDimLen(0);i++)
			for(unsigned int j=1;j<=i;j++)
				C(i,j)=C(i-1,j-1)+C(i-1,j);
		Array<double> S(2,K+1,K+2);
		//初始化k=1时的公式
		S(0,0)=1;
		S(0,1)=1;
		//动态规划计算任意k的公式
		for(unsigned int k=1;k<=K;k++){
			S(k,k+1)=1.0/(k+1);
			for(unsigned int j=0;j<k;j++){
				double temp=C(k,j)*(k-j)/(k-j+1);
				S(k,j)-=temp;
				for(unsigned int t=0;t<(j+2);t++)
					S(k,t)+=temp*S(j,t);
			}
		}
		return S;
	}

	//计算方幂和
	double Algebra::powerSum(const unsigned int n,const unsigned int k){
		Array<double> S=powerSumFormula(k);
		std::vector<double> coef(k+2);
		for(unsigned int i=0;i<coef.size();i++)
			coef[i]=S(k,i);
		return computePolynomialByHonerRule(n,coef);
	}

	//LUP分解。
	bool Algebra::lupDecompose(const Array<double> &A,Array<double> &L,Array<double> &U,std::vector<unsigned int> &P){
		if(A.getDimNum()!=2||A.getDimLen(0)!=A.getDimLen(1))
			throw MatrixException("lupDecompose的参数A不为二维方阵！");
		Array<double> a=A;//待分解方阵副本
		unsigned int n=A.getDimLen(0);//方阵尺寸
		//重置L、U、P的大小
		if(L.getDimNum()!=2||L.getDimLen(0)!=L.getDimLen(1)||L.getDimLen(0)!=n)
			L=Array<double>(2,n,n);
		if(U.getDimNum()!=2||U.getDimLen(0)!=U.getDimLen(1)||U.getDimLen(0)!=n)
			U=Array<double>(2,n,n);
		if(P.size()!=n)
			P.resize(n);
		//初始化P
		for(unsigned int i=0;i<n;i++)
			P[i]=i;
		for(unsigned int k=0;k<n;k++){//第k次子分解
			//找到子矩阵首列绝对值最大元（数值稳定性）
			unsigned int k1=k;
			double p=0;
			for(unsigned int i=k;i<n;i++)
				if(std::abs(a(i,k))>p){
					p=std::abs(a(i,k));
					k1=i;
				}
			if(p<0.0000000001)
				return false;//首元太小，为奇异方阵,返回false。
			std::swap(P[k],P[k1]);
			for(unsigned i=0;i<k;i++)
				std::swap(L(k,i),L(k1,i));
			for(unsigned i=k;i<n;i++)
				std::swap(a(k,i),a(k1,i));
			L(k,k)=1;
			U(k,k)=a(k,k);
			for(unsigned int i=k+1;i<n;i++){
				L(i,k)=a(i,k)/a(k,k);
				U(k,i)=a(k,i);
				for(unsigned int j=k+1;j<n;j++)
					a(i,j)-=a(i,k)*a(k,j)/a(k,k);
			}
		}
		return true;
	}

	//解线性方程组LUx=Pb。L、U、P为某非奇异方阵的LUP分解，解存至x。
	//O(n^2),参见《算法导论p457》
	void Algebra::solveLinearEquationsGivenLUP(const Array<double> &L,const Array<double> &U,const std::vector<unsigned int> &P,const std::vector<double> &b,std::vector<double> &x){
		unsigned int n=b.size();
		if(x.size()!=n)
			x.resize(n);
		//解Ly=Pb
		std::vector<double> y(n);
		for(unsigned int i=0;i<n;i++){
			y[i]=b[P[i]];
			for(unsigned int j=0;j<i;j++)
				y[i]-=L(i,j)*y[j];
		}
		//解Ux=y
		for(unsigned int i=n;i>0;i--){
			x[i-1]=y[i-1];
			for(unsigned int j=i+1;j<=n;j++)
				x[i-1]-=U(i-1,j-1)*x[j-1];
			x[i-1]/=U(i-1,i-1);
		}
	}


	//解线性方程组，利用LUP分解。。
	//O(n^3),参见《算法导论p457》
	bool Algebra::solveLinearEquationsByLUP(const Array<double> &A,const std::vector<double> &b,std::vector<double> &x){
		if(A.getDimNum()!=2||A.getDimLen(0)!=A.getDimLen(1))
			throw MatrixException("solveLinearEquationsByLUP的参数A不为二维方阵！");
		if(b.size()!=A.getDimLen(0))
			throw MatrixException("solveLinearEquationsByLUP中系数矩阵A与b的尺寸不满足条件！");
		lmtc::Array<double> L,U;
		std::vector<unsigned int> P;
		if(!lupDecompose(A,L,U,P))
			return false;//LUP分解失败，则说明为奇异矩阵，不存在解。
		solveLinearEquationsGivenLUP(L,U,P,b,x);
		return true;
	}

	//解线性方程组Ax=b，利用快速矩阵求逆。解存至x，有解则返回true，无解返回false。
		//O(n^2.81)，《参见算法导论p456,465》
	bool Algebra::solveLinearEquationsFast(const Array<double> &A,const std::vector<double> &b,std::vector<double> &x){
		if(A.getDimNum()!=2||A.getDimLen(0)!=A.getDimLen(1))
			throw MatrixException("solveLinearEquationsFast的参数A不为二维方阵！");
		if(b.size()!=A.getDimLen(0))
			throw MatrixException("solveLinearEquationsFast中系数矩阵A与b的尺寸不满足条件！");
		Array<double> _A;
		if(!inverseMatrixFast(A,_A))
			return false;
		if(x.size()!=b.size())
			x.resize(b.size());
		for(unsigned i=0;i<b.size();i++){
			x[i]=0;
			for(unsigned j=0;j<b.size();j++)
				x[i]+=_A(i,j)*b[j];
		}
		return true;
	}

	//利用LUP分解求逆矩阵。求A的逆矩阵，结果存至_A，A可逆返回true，不可逆返回false。
	//O(n^3),参见《算法导论p464》。
	bool Algebra::inverseMatrixByLUP(const Array<double> &A,Array<double> &_A){
		lmtc::Array<double> L,U;
		std::vector<unsigned int> P;
		if(!lupDecompose(A,L,U,P))//进行LUP分解
			return false;
		unsigned int n=A.getDimLen(0);
		if(_A.getDimNum()!=2||_A.getDimLen(0)!=_A.getDimLen(1)||_A.getDimLen(0)!=n)
			_A=Array<double>(2,n,n);
		std::vector<double> ei(n);
		std::vector<double> x;
		for(unsigned int i=0;i<n;i++){//利用解方程组求逆矩阵的第i列
			ei[i]=1;
			if(i!=0)
				ei[i-1]=0;
			solveLinearEquationsGivenLUP(L,U,P,ei,x);
			for(unsigned int j=0;j<n;j++)
				_A(j,i)=x[j];
		}
		return true;
	}

	//快速矩阵求逆辅助函数（A为正合幂对称正定矩阵）。
	bool Algebra::inverseMatrixFast_visit(const Array<double> &A,Array<double> &_A){
		unsigned int n=A.getDimLen(0);
		if(_A.getDimNum()!=2||_A.getDimLen(0)!=_A.getDimLen(1)||_A.getDimLen(0)!=n)
			_A=Array<double>(2,n,n);
		if(n==1){//单元素矩阵
			if(std::abs(A(0,0))<0.0000000001)
				return false;
			_A(0,0)=1/A(0,0);
			return true;
		}
		//利用《算法导论p465》的矩阵代数进行矩阵求逆
		Array<double> B(2,n/2,n/2),C(2,n/2,n/2),CT(2,n/2,n/2),D(2,n/2,n/2),_B(2,n/2,n/2),S(2,n/2,n/2),_S(2,n/2,n/2);
		for(unsigned int i=0;i<B.getDimLen(0);i++)
			for(unsigned int j=0;j<B.getDimLen(1);j++){
				B(i,j)=A(i,j);
				C(i,j)=A(i+n/2,j);
				CT(i,j)=A(i,j+n/2);
				D(i,j)=A(i+n/2,j+n/2);
			}
		if(!inverseMatrixFast_visit(B,_B))
			return false;
		Array<double> temp1=matrixMultiplyStrassen(C,_B);
		Array<double> temp2=matrixMultiplyStrassen(temp1,CT);
		for(unsigned int i=0;i<S.getDimLen(0);i++)
			for(unsigned int j=0;j<S.getDimLen(1);j++)
				S(i,j)=D(i,j)-temp2(i,j);
		if(!inverseMatrixFast_visit(S,_S))
			return false;
		Array<double> temp3=matrixMultiplyStrassen(_S,temp1);
		Array<double> temp4=matrixMultiplyStrassen(transposeMatrix(temp1),temp3);
		for(unsigned int i=0;i<B.getDimLen(0);i++)
			for(unsigned int j=0;j<B.getDimLen(1);j++){
				_A(i,j)=_B(i,j)+temp4(i,j);
				_A(i+n/2,j)=-temp3(i,j);
				_A(i,j+n/2)=-temp3(j,i);
				_A(i+n/2,j+n/2)=_S(i,j);
			}
		return true;
	}

	//快速矩阵求逆。求A的逆矩阵，结果存至_A，A可逆返回true，不可逆返回false。
	//时间复杂度与矩阵乘法相同，O(n^2.81)
	bool Algebra::inverseMatrixFast(const Array<double> &A,Array<double> &_A){
		if(A.getDimNum()!=2||A.getDimLen(0)!=A.getDimLen(1)||A.getDimLen(0)==0)
			return false;
		unsigned int n=A.getDimLen(0);
		Array<double> AT=transposeMatrix(A);
		Array<double> ATA=matrixMultiplyStrassen(AT,A);
		Array<double> _ATA(2,n,n);
		unsigned int N=1;//求n的正合幂
		while(N<n)
			N*=2;
		if(n==N){//刚好为正合幂，求AT*A的逆
			if(!inverseMatrixFast_visit(ATA,_ATA))
				return false;
		}
		else{//扩展为正合幂进行计算，求AT*A的逆
			Array<double> ATAstd(2,N,N);
			for(unsigned int i=0;i<n;i++)
				for(unsigned int j=0;j<n;j++)
					ATAstd(i,j)=ATA(i,j);
			for(unsigned int i=n;i<N;i++)
				ATAstd(i,i)=1;
			Array<double> temp(2,N,N);
			if(!inverseMatrixFast_visit(ATAstd,temp))
				return false;
			for(unsigned int i=0;i<n;i++)
				for(unsigned int j=0;j<n;j++)
					_ATA(i,j)=temp(i,j);
		}
		_A=matrixMultiplyStrassen(_ATA,AT);//_A=_ATA*AT
		//利用A*_A==E进行验证。
		Array<double> E=matrixMultiplyStrassen(A,_A);
		for(unsigned int i=0;i<n;i++)
			for(unsigned int j=0;j<n;j++)
				if((i==j)&&std::abs(E(i,j)-1)>0.0000000001||(i!=j)&&std::abs(E(i,j))>0.0000000001)
					return false;
		return true;
	}

	//求A的前向伪逆矩阵A_（非方阵的逆矩阵，逆矩阵的自然推广）。有A_*A=E。
	bool Algebra::pseudoInverseMatrixForward(const Array<double> &A,Array<double> &A_){
		Array<double> AT=transposeMatrix(A);
		Array<double> _ATA;
		if(!inverseMatrixFast(matrixMultiplyStrassen(AT,A),_ATA))
			return false;
		A_=matrixMultiplyStrassen(_ATA,AT);
		return true;
	}

	//求A的后向伪逆矩阵_A（非方阵的逆矩阵，逆矩阵的自然推广）。有A*_A=E。
	bool Algebra::pseudoInverseMatrixBackward(const Array<double> &A,Array<double> &_A){
		Array<double> AT=transposeMatrix(A);
		Array<double> _AAT;
		if(!inverseMatrixFast(matrixMultiplyStrassen(A,AT),_AAT))
			return false;
		_A=matrixMultiplyStrassen(AT,_AAT);
		return true;
	}

	//解正态方程组（LUP）。
	bool Algebra::solveNormalityEquationsByLUP(const Array<double> &A,const std::vector<double> &b,std::vector<double> &x){
		if(A.getDimNum()!=2||A.getDimLen(0)<A.getDimLen(1))
			throw MatrixException("solveNormalityEquationsByLUP的参数A不为列满秩方阵！");
		if(b.size()!=A.getDimLen(0))
			throw MatrixException("solveNormalityEquationsByLUP中系数矩阵A与b的尺寸不满足条件！");
		Array<double> AT=transposeMatrix(A);
		Array<double> ATA=matrixMultiplySimple(AT,A);
		std::vector<double> y(AT.getDimLen(0));
		for(unsigned int i=0;i<y.size();i++)
			for(unsigned int j=0;j<AT.getDimLen(1);j++)
				y[i]+=AT(i,j)*b[j];
		if(!solveLinearEquationsByLUP(ATA,y,x))
			return false;
		return true;
	}

	//快速解正态方程组。
	bool Algebra::solveNormalityEquationsFast(const Array<double> &A,const std::vector<double> &b,std::vector<double> &x){
		if(A.getDimNum()!=2||A.getDimLen(0)<A.getDimLen(1))
			throw MatrixException("solveNormalityEquationsFast的参数A不为列满秩方阵！");
		if(b.size()!=A.getDimLen(0))
			throw MatrixException("solveNormalityEquationsFast中系数矩阵A与b的尺寸不满足条件！");
		Array<double> AT=transposeMatrix(A);
		Array<double> ATA=matrixMultiplyStrassen(AT,A);
		std::vector<double> y(AT.getDimLen(0));
		for(unsigned int i=0;i<y.size();i++)
			for(unsigned int j=0;j<AT.getDimLen(1);j++)
				y[i]+=AT(i,j)*b[j];
		if(!solveLinearEquationsFast(ATA,y,x))
			return false;
		return true;
	}

	//最小二乘估计（LUP）。
	bool Algebra::leastSquaresEstimationByLUP(double (*f)(unsigned int i,double x),const unsigned int n,const std::vector<double> &X,const std::vector<double> &Y,std::vector<double> &C){
		if(X.size()!=Y.size()||X.size()<n)
			throw MatrixException("leastSquaresEstimationByLUP的参数X,Y尺寸不匹配或小于n！");
		Array<double> A(2,X.size(),n);
		for(unsigned int i=0;i<A.getDimLen(0);i++)
			for(unsigned int j=0;j<A.getDimLen(1);j++)
				A(i,j)=f(j,X[i]);
		if(!solveNormalityEquationsByLUP(A,Y,C))
			return false;
		return true;
	}

	//快速最小二乘估计。
	bool Algebra::leastSquaresEstimationFast(double (*f)(unsigned int i,double x),const unsigned int n,const std::vector<double> &X,const std::vector<double> &Y,std::vector<double> &C){
		if(X.size()!=Y.size()||X.size()<n)
			throw MatrixException("leastSquaresEstimationFast的参数X,Y尺寸不匹配或小于n！");
		Array<double> A(2,X.size(),n);
		for(unsigned int i=0;i<A.getDimLen(0);i++)
			for(unsigned int j=0;j<A.getDimLen(1);j++)
				A(i,j)=f(j,X[i]);
		if(!solveNormalityEquationsFast(A,Y,C))
			return false;
		return true;
	}

	//利用FFT求卷积
	std::vector<ComplexNumber> Algebra::convolution(const std::vector<ComplexNumber> &a,const std::vector<ComplexNumber> &b){
		if(a.empty()||b.empty())
			return std::vector<ComplexNumber>();
		unsigned int n=a.size()+b.size()-1;
		std::vector<ComplexNumber> a1(n),b1(n);
		for(unsigned int i=0;i<a.size();i++)
			a1[i]=a[i];
		for(unsigned int i=0;i<b.size();i++)
			b1[i]=b[i];
		std::vector<ComplexNumber> a2=FastFourierTransform::fft(a1);
		std::vector<ComplexNumber> b2=FastFourierTransform::fft(b1);
		std::vector<ComplexNumber> c2(a2.size());
		for(unsigned int i=0;i<a2.size();i++)
			c2[i]=a2[i]*b2[i];
		std::vector<ComplexNumber> _c2=FastFourierTransform::_fft(c2);
		std::vector<ComplexNumber> C(n);
		for(unsigned int i=0;i<n;i++)
			C[i]=_c2[i];
		return C;
	}

	//利用多维快速傅里叶变换求多维卷积a(*)b
	Array<ComplexNumber> Algebra::convolution(const Array<ComplexNumber> &a,const Array<ComplexNumber> &b){
		if(a.empty()||b.empty())//空卷积
			return lmtc::Array<ComplexNumber>();
		unsigned int dimN=std::max(a.getDimNum(),b.getDimNum());
		std::vector<unsigned int> dim(dimN);//计算各维的相乘最高幂
		for(unsigned int i=0;i<dim.size();i++){
			if(i<a.getDimNum())
				dim[i]+=a.getDimLen(i);
			else
				dim[i]+=1;
			if(i<b.getDimNum())
				dim[i]+=b.getDimLen(i);
			else
				dim[i]+=1;
			dim[i]-=1;
		}
		Array<ComplexNumber> a1(dimN,dim),b1(dimN,dim);

		std::vector<unsigned int> dimC(dimN,0);
		while(dimC[a.getDimNum()-1]<a.getDimLen(a.getDimNum()-1)){//将a中元素复制到正合幂数组a1
			a1(dimC)=a(dimC);
			for(unsigned int i=0;i<a.getDimNum();i++){//计算多维数组遍历的下一个坐标
				if(dimC[i]!=(a.getDimLen(i)-1)){
					dimC[i]++;
					break;
				}else if(i!=(a.getDimNum()-1))
					dimC[i]=0;
				else
					dimC[i]++;
			}
		}
		dimC.assign(dimN,0);
		while(dimC[b.getDimNum()-1]<b.getDimLen(b.getDimNum()-1)){//将b中元素复制到正合幂数组b1
			b1(dimC)=b(dimC);
			for(unsigned int i=0;i<b.getDimNum();i++){//计算多维数组遍历的下一个坐标
				if(dimC[i]!=(b.getDimLen(i)-1)){
					dimC[i]++;
					break;
				}else if(i!=(b.getDimNum()-1))
					dimC[i]=0;
				else
					dimC[i]++;
			}
		}

		//傅里叶张量点乘c2=a2*b2;
		Array<ComplexNumber> a2=FastFourierTransform::fft(a1);
		Array<ComplexNumber> b2=FastFourierTransform::fft(b1);
		std::vector<unsigned int> dim2(dimN);//傅里叶变换后的各项幂
		for(unsigned int i=0;i<a2.getDimNum();i++)
			dim2[i]=a2.getDimLen(i);
		Array<ComplexNumber> c2(dimN,dim2);
		dimC.assign(dimN,0);
		while(dimC[c2.getDimNum()-1]<c2.getDimLen(c2.getDimNum()-1)){//将a中元素复制到正合幂数组a1
			c2(dimC)=a2(dimC)*b2(dimC);
			for(unsigned int i=0;i<c2.getDimNum();i++){//计算多维数组遍历的下一个坐标
				if(dimC[i]!=(c2.getDimLen(i)-1)){
					dimC[i]++;
					break;
				}else if(i!=(c2.getDimNum()-1))
					dimC[i]=0;
				else
					dimC[i]++;
			}
		}
		//傅里叶逆变换，并把有效元素拷贝至C
		Array<ComplexNumber> _c2=FastFourierTransform::_fft(c2);
		Array<ComplexNumber> C(dimN,dim);
		dimC.assign(dimN,0);
		while(dimC[C.getDimNum()-1]<C.getDimLen(C.getDimNum()-1)){//将a中元素复制到正合幂数组a1
			C(dimC)=_c2(dimC);
			for(unsigned int i=0;i<C.getDimNum();i++){//计算多维数组遍历的下一个坐标
				if(dimC[i]!=(C.getDimLen(i)-1)){
					dimC[i]++;
					break;
				}else if(i!=(C.getDimNum()-1))
					dimC[i]=0;
				else
					dimC[i]++;
			}
		}
		return C;
	}



}