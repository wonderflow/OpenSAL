#ifndef redBlackTreeConst
#define redBlackTreeConst
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

#include "smartPtr.h"
#include "myException.h"
#include "defaultCompare.h"
#include <iostream>

//使用智能指针实现安全的树结构
namespace lmtc{

	template<typename T> class RedBlackTree; //红黑树模板申明

	template<typename T>  //红黑树节点模板申明
	class RedBlackTreeItem{
	private:
		//构造函数皆为私有，只有友元RedBlackTree<T>能访问
		RedBlackTreeItem():size(1),left(NULL),right(NULL),parent(NULL),isBlack(true){}
		RedBlackTreeItem(const T &t):size(1),data(t),left(NULL),right(NULL),parent(NULL),isBlack(true){}
		RedBlackTreeItem(const T &t,SmartPtr<RedBlackTreeItem<T>> *lt, SmartPtr<RedBlackTreeItem<T>> *rt, SmartPtr<RedBlackTreeItem<T>> * pt):data(t),size(1),left(NULL),right(NULL),parent(pt),isBlack(true){if(lt!=NULL) left=*lt;if(rt!=NULL) right=*rt;}	
		RedBlackTreeItem(bool is_black):size(1),left(NULL),right(NULL),parent(NULL),isBlack(is_black){}
		RedBlackTreeItem(const T &t,bool is_black):data(t),size(1),left(NULL),right(NULL),parent(NULL),isBlack(is_black){}
		RedBlackTreeItem(const T &t,SmartPtr<RedBlackTreeItem<T>> *lt, SmartPtr<RedBlackTreeItem<T>> *rt, SmartPtr<RedBlackTreeItem<T>> * pt,bool is_black):data(t),size(1),left(NULL),right(NULL),parent(pt),isBlack(is_black){if(lt!=NULL) left=*lt;if(rt!=NULL) right=*rt;}	
	private:
		//确认是否存在左右孩子与父节点，是否是黑节点，只有友元RedBlackTree<T>能访问
		bool hasLeft()const{return !left.isEmpty();}
		bool hasRight()const{return !right.isEmpty();}
		bool hasParent()const{return parent!=NULL&&!parent->isEmpty();}
		bool isBlackItem()const{return isBlack;}
	public://析构函数必须为public，用于智能指针中的删除。
		~RedBlackTreeItem(){/*std::cout<<"deconstruct"<<data<<std::endl;*/}
	private:
		T data;//存储数据
		unsigned long size;//以该节点为根的子树的节点数
		SmartPtr<RedBlackTreeItem<T>> left;//左孩子智能指针		
		SmartPtr<RedBlackTreeItem<T>> right;//右孩子智能指针		
		SmartPtr<RedBlackTreeItem<T>> *parent;//父节点智能指针的指针，此处这样设计是防止父子节点中的智能指针相互引用从而导致的内存泄露问题（智能指针不能相互引用，否则不会自动释放内存资源）
		bool isBlack;  //节点红黑性质
	friend class RedBlackTree<T>; //把存储相同类型数据的二叉树设为友元
	};

	//红黑树模板。（已扩展动态顺序统计功能）
	template<typename T>
	class RedBlackTree{
	public:
		typedef SmartPtr<RedBlackTreeItem<T>> ItemType; //节点智能指针类型别名
	public:
		RedBlackTree(bool (*less_compare)(const T &t1,const T &t2)=NULL):root(NULL),nullItm(NULL),lessCompare(less_compare){root=nullItm;if(lessCompare==NULL) lessCompare=less_default;} //构造函数，初始化root为空节点
		RedBlackTree(const T &e,bool (*less_compare)(const T &t1,const T &t2)=NULL):root(NULL),nullItm(NULL),lessCompare(less_compare){root= ItemType(new RedBlackTreeItem<T>(e,&nullItm,&nullItm,&nullItm));if(lessCompare==NULL) lessCompare=less_default;} //构造函数，初始化root为新建节点
	
	public:
		//红黑树操作，所有接口中的ItemType &参数都不必是红黑树中节点的引用，只需要是指向树中节点就行了。
		ItemType insert(const T &t);
		ItemType search(const T &t)const;
		ItemType minimum()const;
		ItemType maximum()const;
		ItemType minimumFrom(const ItemType &t)const;
		ItemType maximumFrom(const ItemType &t)const;
		ItemType successor(const ItemType &t)const;
		ItemType predecessor(const ItemType &t)const;
		ItemType deleteItem(const ItemType &t);

		//顺序统计学，顺序从0开始
		ItemType searchItmOfOrder(unsigned long i)const;//查找第i顺序的节点
		unsigned long getOrderOfItm(const ItemType &t)const;//确定节点的顺序

		//判断是否为空树
		bool isEmpty()const{return root.isEmpty();} 
		//置为空树
		void setEmpty(){ root=nullItm;} 
		//获取节点总数目
		unsigned long size()const{return getItemSize(root);}
		//重置为单节点树
		void resetRoot(const T &e){root=ItemType(new RedBlackTreeItem<T>(e,&nullItm,&nullItm,&nullItm));}
		//获取根节点引用
		const ItemType &getRoot()const{return root;}
		//获取节点值
		T getItemValue(const ItemType &itmPtr)const{if(itmPtr.isEmpty()) throw EmptySmartPtrAccessException();else return itmPtr->data;}
		//获取节点的size值
		unsigned long getItemSize(const ItemType &itmPtr)const{if(itmPtr.isEmpty()) return 0;else return itmPtr->size;}
		

		//二叉树的前序、中序、后序遍历，对各个节点的数据运行f操作
		template<typename X>
		void traver_preOrder(void (*f)(X x))const;
		template<typename X>
		void traver_inOrder(void (*f)(X x))const;
		template<typename X>
		void traver_postOrder(void (*f)(X x))const;
		//以二叉树某节点为根的子树的前序、中序、后序遍历，对各个节点的数据运行f操作
		template<typename X>
		void traver_preOrder_From(const ItemType &itmPtr,void (*f)(X x))const;
		template<typename X>
		void traver_inOrder_From(const ItemType &itmPtr,void (*f)(X x))const;
		template<typename X>
		void traver_postOrder_From(const ItemType &itmPtr,void (*f)(X x))const;

	public:
		//测试函数
		unsigned long asertTree(const ItemType &itmPtr);

	private:
		//红黑树插入删除接口的附属函数
		void leftRotate(ItemType &itmPtr);
		void rightRotate(ItemType &itmPtr);
		void insertFixUp(ItemType *z);
		void deleteItemFixUp(ItemType *x,ItemType *p);

	private://如下的为一些树操作接口，但是应该隐藏起来（因为用户直接使用可能破坏红黑树结构）
		//获取节点左孩子引用
		ItemType &getItemLeft(ItemType &itmPtr)const{ if(itmPtr.isEmpty()) throw EmptySmartPtrAccessException();else return itmPtr->left;}
		//获取节点右孩子引用
		ItemType &getItemRight(ItemType &itmPtr)const{ if(itmPtr.isEmpty()) throw EmptySmartPtrAccessException();else return itmPtr->right;}
		//获取节点父节点引用
		ItemType &getItemParent(const ItemType &itmPtr)const{ if(itmPtr.isEmpty()) throw EmptySmartPtrAccessException();else{if(itmPtr->parent!=NULL) return *itmPtr->parent; else return nullItm;} }
		//设置节点的数据
		void setItemValue(ItemType &itmPtr,const T &val)const{ if(itmPtr.isEmpty()) throw EmptySmartPtrAccessException();else  itmPtr->data=val;}
		//如下五个修改树结构的内部函数的形参itmPtr必须为树内部的引用
		//设置节点的左孩子，原左子树将被删除，返回新的左孩子引用
		ItemType &setItemLeft(ItemType &itmPtr,const T &e)const{ if(itmPtr.isEmpty()) throw EmptySmartPtrAccessException();else  itmPtr->left=ItemType(new RedBlackTreeItem<T>(e,&nullItm,&nullItm,&itmPtr));return itmPtr->left;}
		//插入节点的左孩子，原左子树将作为新左孩子的左子树，返回新的左孩子引用
		ItemType &insertItemLeft(ItemType &itmPtr,const T &e)const{ if(itmPtr.isEmpty()) throw EmptySmartPtrAccessException();else{ ItemType itmTemp(new RedBlackTreeItem<T>(e,&itmPtr->left,&nullItm,&itmPtr));if(!itmPtr->left.isEmpty()) itmPtr->left->parent=&itmPtr->left;  itmPtr->left=itmTemp ; } return itmPtr->left; }
		//设置节点的右孩子，原右子树将被删除，返回新的右孩子引用
		ItemType &setItemRight(ItemType &itmPtr,const T &e)const{ if(itmPtr.isEmpty()) throw EmptySmartPtrAccessException();else  itmPtr->right=ItemType(new RedBlackTreeItem<T>(e,&nullItm,&nullItm,&itmPtr));return itmPtr->right;}
		//插入节点的右孩子，原右子树将作为新右孩子的右子树，返回新的右孩子引用
		ItemType &insertItemRight(ItemType &itmPtr,const T &e)const{ if(itmPtr.isEmpty()) throw EmptySmartPtrAccessException();else{ ItemType itmTemp(new RedBlackTreeItem<T>(e,&nullItm,&itmPtr->right,&itmPtr));if(!itmPtr->right.isEmpty()) itmPtr->right->parent=&itmPtr->right; itmPtr->right=itmTemp;} return itmPtr->right; }
		//删除以某节点为根的子树
		void deleteSunTree(ItemType &itmPtr){if(itmPtr.isEmpty()) return; itmPtr=nullItm;}
		//获取节点的在树中的真实引用
		ItemType &getRealReference(ItemType &itmPtr){ if(itmPtr.isEmpty()) return nullItm;if(!itmPtr->hasParent()) return root;ItemType &parent=getItemParent(itmPtr);if(parent->left==itmPtr) return parent->left;else return parent->right;}

	private:
	   ItemType root; //根节点  
       mutable ItemType nullItm;  //空节点
	   bool (*lessCompare)(const T &t1,const T &t2);//小于比较函数
	};
	template<typename T>
	void RedBlackTree<T>::leftRotate(ItemType &itm){
		if(itm.isEmpty()||!itm->hasRight())
			return;
		ItemType itmPtrX=itm,itmPtrY=itm->right,&itmPtrP=*(itm->parent);
		itmPtrX->right=itmPtrY->left;
		itmPtrY->left=itmPtrX;
		itmPtrY->parent=itmPtrX->parent;

		//左旋过程中额外结构信息维护
		itmPtrY->size=itmPtrX->size;
		itmPtrX->size=getItemSize(itmPtrX->left)+getItemSize(itmPtrX->right)+1;
		//维护结束
		
		if(itmPtrX->hasRight()){
			if(itmPtrX->right->hasLeft())
				itmPtrX->right->left->parent=&itmPtrX->right;
			if(itmPtrX->right->hasRight())
				itmPtrX->right->right->parent=&itmPtrX->right;
		}

		if(itmPtrP.isEmpty()){
			root=itmPtrY;
			if(root->hasRight())
				root->right->parent=&root;
			if(root->hasLeft()){
				root->left->parent=&root;
				if(root->left->hasLeft())
					root->left->left->parent=&root->left;
				if(root->left->hasRight())
					root->left->right->parent=&root->left;
			}
		}else{
			if(itmPtrX==itmPtrP->left){
				itmPtrP->left=itmPtrY;
				if(itmPtrY->hasRight())
					itmPtrY->right->parent=&itmPtrP->left;
				if(itmPtrY->hasLeft()){
					itmPtrY->left->parent=&itmPtrP->left;
					if(itmPtrY->left->hasLeft())
						itmPtrY->left->left->parent=&itmPtrP->left->left;
					if(itmPtrY->left->hasRight())
						itmPtrY->left->right->parent=&itmPtrP->left->left;
				}
			}
			else{
				itmPtrP->right=itmPtrY;
				if(itmPtrY->hasRight())
					itmPtrY->right->parent=&itmPtrP->right;
				if(itmPtrY->hasLeft()){
					itmPtrY->left->parent=&itmPtrP->right;
					if(itmPtrY->left->hasLeft())
						itmPtrY->left->left->parent=&itmPtrP->right->left;
					if(itmPtrY->left->hasRight())
						itmPtrY->left->right->parent=&itmPtrP->right->left;
				}
			}
		}
	}
	template<typename T>
	void RedBlackTree<T>::rightRotate(ItemType &itm){
		if(itm.isEmpty()||!itm->hasLeft())
			return;
		ItemType itmPtrX=itm,itmPtrY=itm->left,&itmPtrP=*(itm->parent);
		itmPtrX->left=itmPtrY->right;
		itmPtrY->right=itmPtrX;
		itmPtrY->parent=itmPtrX->parent;

		//右旋过程中额外结构信息维护
		itmPtrY->size=itmPtrX->size;
		itmPtrX->size=getItemSize(itmPtrX->left)+getItemSize(itmPtrX->right)+1;
		//维护结束

		if(itmPtrX->hasLeft()){
			if(itmPtrX->left->hasLeft())
				itmPtrX->left->left->parent=&itmPtrX->left;
			if(itmPtrX->left->hasRight())
				itmPtrX->left->right->parent=&itmPtrX->left;
		}
		
		if(itmPtrP.isEmpty()){
			root=itmPtrY;
			if(root->hasLeft())
				root->left->parent=&root;
			if(root->hasRight()){
				root->right->parent=&root;
				if(root->right->hasRight())
					root->right->right->parent=&root->right;
				if(root->right->hasLeft())
					root->right->left->parent=&root->right;
			}
		}else if(itmPtrX==itmPtrP->right){
			itmPtrP->right=itmPtrY;
			if(itmPtrY->hasLeft())
				itmPtrY->left->parent=&itmPtrP->right;
			if(itmPtrY->hasRight()){
				itmPtrY->right->parent=&itmPtrP->right;
				if(itmPtrY->right->hasRight())
					itmPtrY->right->right->parent=&itmPtrP->right->right;
				if(itmPtrY->right->hasLeft())
					itmPtrY->right->left->parent=&itmPtrP->right->right;
			}
		}else{
			itmPtrP->left=itmPtrY;
			if(itmPtrY->hasLeft())
				itmPtrY->left->parent=&itmPtrP->left;
			if(itmPtrY->hasRight()){
				itmPtrY->right->parent=&itmPtrP->left;
				if(itmPtrY->right->hasRight())
					itmPtrY->right->right->parent=&itmPtrP->left->right;
				if(itmPtrY->right->hasLeft())
					itmPtrY->right->left->parent=&itmPtrP->left->right;
			}
		}
	}

	template<typename T> template<typename X>
	void RedBlackTree<T>::traver_preOrder_From(const ItemType &itmPtr,void (*f)(X x))const{
		if(itmPtr.isEmpty())
			return;
		f(itmPtr->data);
		traver_preOrder_From(itmPtr->left,f);
		traver_preOrder_From(itmPtr->right,f);
	}

	template<typename T> template<typename X>
	void RedBlackTree<T>::traver_inOrder_From(const ItemType &itmPtr,void (*f)(X x))const{
		if(itmPtr.isEmpty())
			return;
		traver_inOrder_From(itmPtr->left,f);
		f(itmPtr->data);
		traver_inOrder_From(itmPtr->right,f);
	}

	template<typename T> template<typename X>
	void RedBlackTree<T>::traver_postOrder_From(const ItemType &itmPtr,void (*f)(X x))const{
		if(itmPtr.isEmpty())
			return;
		traver_postOrder_From(itmPtr->left,f);
		traver_postOrder_From(itmPtr->right,f);
		f(itmPtr->data);
	}
	

	template<typename T> template<typename X>
	void RedBlackTree<T>::traver_preOrder(void (*f)(X x))const{
		traver_preOrder_From(root,f);
	}

	template<typename T> template<typename X>
	void RedBlackTree<T>::traver_inOrder(void (*f)(X x))const{
		traver_inOrder_From(root,f);
	}

	template<typename T> template<typename X>
	void RedBlackTree<T>::traver_postOrder(void (*f)(X x))const{
		traver_postOrder_From(root,f);
	}

	template<typename T>
	typename RedBlackTree<T>::ItemType RedBlackTree<T>::insert(const T &t){
		ItemType *y=&nullItm;
		ItemType *x=&root;
		while(!x->isEmpty()){
			y=x;
			if(lessCompare(t,(*x)->data))
				x=&(*x)->left;
			else
				x=&(*x)->right;

			//插入过程的额外结构信息维护
			(*y)->size++;
			//维护结束
		}
		if(y->isEmpty()){
			resetRoot(t);

			//插入过程的额外结构信息维护
			//维护结束

			return root;
		}
		else if(lessCompare(t,(*y)->data)){
			insertItemLeft((*y),t);
			(*y)->left->isBlack=false;
			ItemType son=(*y)->left;
			insertFixUp(&(*y)->left);
			return son;
		}else{
			insertItemRight((*y),t);
			(*y)->right->isBlack=false;
			ItemType son=(*y)->right;
			insertFixUp(&(*y)->right);
			return son;
		}

	}

	template<typename T>
	void RedBlackTree<T>::insertFixUp(ItemType *z){
		while((*z)->hasParent()&&getItemParent(*z)->isBlack==false){//z的父亲存在，且父节点为红色
			ItemType &gp=getItemParent(getItemParent(*z));
			ItemType &p=getItemParent(*z);
			if(p==gp->left){//z的父亲是祖父的左孩子
				ItemType &y=gp->right;
				if(!y.isEmpty()&&y->isBlack==false){
					y->isBlack=true;
					p->isBlack=true;
					gp->isBlack=false;
					z=&gp;
				}else{
					if(*z==p->right)
						leftRotate(p);
					gp->isBlack=false;
					gp->left->isBlack=true;
					rightRotate(gp);
					break;
				}
			}else{//z的父亲是祖父的右孩子
				ItemType &y=gp->left;
				if(!y.isEmpty()&&y->isBlack==false){
					y->isBlack=true;
					p->isBlack=true;
					gp->isBlack=false;
					z=&gp;
				}else{
					if(*z==p->left)
						rightRotate(p);
					gp->isBlack=false;
					gp->right->isBlack=true;
					leftRotate(gp);
					break;
				}
			}
		}
		root->isBlack=true;
	}

	template<typename T>
	typename RedBlackTree<T>::ItemType RedBlackTree<T>::search(const T &k)const{
		ItemType x=root;
		while(!x.isEmpty()&&(lessCompare(x->data,k)||lessCompare(k,x->data))){
			if(lessCompare(k,x->data))
				x=x->left;
			else
				x=x->right;
		}
		return x;
	}
	template<typename T>
	typename RedBlackTree<T>::ItemType RedBlackTree<T>::minimum()const{
		return minimumFrom(root);
	}
	template<typename T>
	typename RedBlackTree<T>::ItemType RedBlackTree<T>::maximum()const{
		return maximumFrom(root);
	}

	template<typename T>
	typename RedBlackTree<T>::ItemType RedBlackTree<T>::minimumFrom(const ItemType &itmPtr)const{
		if(itmPtr.isEmpty()) 
			return itmPtr;
		ItemType x=itmPtr;
		while(x->hasLeft())
			x=x->left;
		return x;
	}
	template<typename T>
	typename RedBlackTree<T>::ItemType RedBlackTree<T>::maximumFrom(const ItemType &itmPtr)const{
		if(itmPtr.isEmpty()) 
			return itmPtr;	
		ItemType x=itmPtr;
		while(x->hasRight())
			x=x->right;
		return x;
	}

	template<typename T>
	typename RedBlackTree<T>::ItemType RedBlackTree<T>::successor(const ItemType &itmPtr)const{
		if(itmPtr.isEmpty()) 
			throw EmptySmartPtrAccessException();
		if(itmPtr->hasRight())
			return minimumFrom(itmPtr->right);
		ItemType x=itmPtr;
		ItemType y=getItemParent(itmPtr);
		while(!y.isEmpty()&&x==y->right){
			x=y;
			y=getItemParent(y);
		}
		return y;
	}
	template<typename T>
	typename RedBlackTree<T>::ItemType RedBlackTree<T>::predecessor(const ItemType &itmPtr)const{
		if(itmPtr.isEmpty()) 
			throw EmptySmartPtrAccessException();
		if(itmPtr->hasLeft())
			return maximumFrom(itmPtr->left);
		ItemType x=itmPtr;
		ItemType y=getItemParent(itmPtr);
		while(!y.isEmpty()&&x==y->left){
			x=y;
			y=getItemParent(y);
		}
		return y;

	}

	template<typename T>
	typename RedBlackTree<T>::ItemType RedBlackTree<T>::deleteItem(const ItemType &itmPtr){
		if(itmPtr.isEmpty()) 
			return itmPtr;
		ItemType z=itmPtr;
		ItemType y(NULL);
		if(!z->hasLeft()||!z->hasRight())
			y=z;
		else
			y=successor(z);
		ItemType x(NULL);
		if(y->hasLeft())
			x=y->left;
		else
			x=y->right;
		if(!x.isEmpty())
			x->parent=y->parent;
		if(!y->hasParent()){
			root=x;
			if(!x.isEmpty()&&x->hasLeft())
				x->left->parent=&root;
			if(!x.isEmpty()&&x->hasRight())
				x->right->parent=&root;
		}
		else {
			ItemType &p=getItemParent(y);
			if(y==p->left){
				p->left=x;
				if(!x.isEmpty()&&x->hasLeft())
					x->left->parent=&p->left;
				if(!x.isEmpty()&&x->hasRight())
					x->right->parent=&p->left;
			}else{
				p->right=x;
				if(!x.isEmpty()&&x->hasLeft())
					x->left->parent=&p->right;
				if(!x.isEmpty()&&x->hasRight())
					x->right->parent=&p->right;
			}	
		}

		if(!(y==z))
			std::swap(z->data,y->data);

		ItemType *xPtr=NULL,*xparentPtr=y->parent;
		if(xparentPtr->isEmpty())
			xPtr=&root;
		else{
			if(x==(*xparentPtr)->left)
				xPtr=&(*xparentPtr)->left;
			else 
				xPtr=&(*xparentPtr)->right;
		}

		//删除过程的额外结构信息维护，修改y原来的每个祖先
		ItemType *p=xparentPtr;
		while(!p->isEmpty()){
			(*p)->size--;
			p=(*p)->parent;
		}
		//维护结束
		
		if(y->isBlack==true)
			deleteItemFixUp(xPtr,xparentPtr);

		return y;
	}


	template<typename T>
	void RedBlackTree<T>::deleteItemFixUp(ItemType *x,ItemType *p){
		while(!((*x)==root)&&(x->isEmpty()||(*x)->isBlack==true)){
			if((*x)==(*p)->left){
				ItemType w=(*p)->right;
				if(w->isBlack==false){
					w->isBlack=true;
					(*p)->isBlack=false;
					leftRotate(*p);
					x=&w->left->left;
					p=&w->left;
					w=w->left->right;
				}
				if((!w->hasLeft()||w->left->isBlack==true)&&(!w->hasRight()||w->right->isBlack==true)){
					w->isBlack=false;
					x=p;
					p=(*p)->parent;
				}else{
					if(!w->hasRight()||w->right->isBlack==true){
						w->left->isBlack=true;
						w->isBlack=false;
						rightRotate((*p)->right);
						w=(*p)->right;
					}
					w->isBlack=(*p)->isBlack;
					(*p)->isBlack=true;
					w->right->isBlack=true;
					leftRotate(*p);
					x=&root;
				}
			}else
			{
				ItemType w=(*p)->left;
				if(w->isBlack==false){
					w->isBlack=true;
					(*p)->isBlack=false;
					rightRotate(*p);
					x=&w->right->right;
					p=&w->right;
					w=w->right->left;
				}
				if((!w->hasRight()||w->right->isBlack==true)&&(!w->hasLeft()||w->left->isBlack==true)){
					w->isBlack=false;
					x=p;
					p=(*p)->parent;
				}else{
					if(!w->hasLeft()||w->left->isBlack==true){
						w->right->isBlack=true;
						w->isBlack=false;
						leftRotate((*p)->left);
						w=(*p)->left;
					}
					w->isBlack=(*p)->isBlack;
					(*p)->isBlack=true;
					w->left->isBlack=true;
					rightRotate(*p);
					x=&root;
				}
			}
		}
		if(!x->isEmpty())
			    (*x)->isBlack=true;
	}

	template<typename T>
	typename RedBlackTree<T>::ItemType RedBlackTree<T>::searchItmOfOrder(unsigned long i)const{//查找第i顺序的节点
		if(isEmpty())
			return nullItm;
		const ItemType *p=&root;
		while(!p->isEmpty()){
			unsigned long s=getItemSize((*p)->left);
			if(i==s)
				return *p;
			if(i<s)
				p=&(*p)->left;
			else{
				p=&(*p)->right;
				i-=s;
				i--;
			}	
		}
		return nullItm;

	}
	template<typename T>
	unsigned long RedBlackTree<T>::getOrderOfItm(const ItemType &t)const{//确定节点的顺序
		if(t.isEmpty())
			throw EmptySmartPtrAccessException();
		unsigned long s=getItemSize(t->left);
		const ItemType *p=&t;
		while(!((*p)==root)){
			if((*p)==getItemParent(*p)->right)
				s=s+getItemSize(getItemParent(*p)->left)+1;
			p=(*p)->parent;
		}
		return s;
	}

	template<typename T>
	unsigned long RedBlackTree<T>::asertTree(const ItemType &itmPtr){
		//验证节点不为空
		if(itmPtr.isEmpty()){
			std::cout<<"empty"<<std::endl;
			return 0;
		}

		//验证根结点为黑色
		if(itmPtr==root&&root->isBlack==false)
			std::cout<<"错误根节点为红色"<<std::endl;

		unsigned long L0=0,L1=0,L2=0;
		if(itmPtr->isBlack==true)
			L0=1;

		if(itmPtr->hasLeft())
		{
			//std::cout<<"father is "<<itmPtr->data<<" and left son is "<<itmPtr->left->data<<std::endl;
			//std::cout<<" father is "<<getItemParent(itmPtr->left)->data<<std::endl;

			//验证父子关系是否正确
			if(!(getItemParent(itmPtr->left)==itmPtr))
				std::cout<<"wrong when father is "<<itmPtr->data<<" and left son is "<<itmPtr->left->data<<"  wrong father is "<<getItemParent(itmPtr->left)->data<<std::endl;
			
			//验证红节点不能有红孩子
			if(itmPtr->isBlack==false&&itmPtr->left->isBlack==false)
				std::cout<<"color wrong:   red father is "<<itmPtr->data<<" and red left son is "<<itmPtr->left->data<<std::endl;

			L1=asertTree(itmPtr->left);
		}
		if(itmPtr->hasRight())
		{
			//std::cout<<"father is "<<itmPtr->data<<" and right son is "<<itmPtr->right->data<<std::endl;
			//std::cout<<" father is "<<getItemParent(itmPtr->right)->data<<std::endl;
			
			//验证父子关系是否正确
			if(!(getItemParent(itmPtr->right)==itmPtr))
				std::cout<<"wrong when father is "<<itmPtr->data<<" and right son is "<<itmPtr->right->data<<"  wrong father is "<<getItemParent(itmPtr->right)->data<<std::endl;
			
			//验证红节点不能有红孩子
			if(itmPtr->isBlack==false&&itmPtr->right->isBlack==false)
				std::cout<<"color wrong:   red father is "<<itmPtr->data<<" and red right son is "<<itmPtr->right->data<<std::endl;

			L2=asertTree(itmPtr->right);
		}

		//验证每个分支的黑高度相同
		if(L1!=L2)
			std::cout<<"black height wrong:   when father is "<<itmPtr->data<<std::endl;
		return L1+L0;
	}
}

#endif