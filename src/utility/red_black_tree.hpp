/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:23:16 by ssawane           #+#    #+#             */
/*   Updated: 2022/12/23 15:23:53 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <ctime>

namespace ft {

	enum node_colors { RED, BLACK };

	template <typename T>
	struct Node
	{
		T*				data;
		Node<T>*		parent;
		Node<T>*		left;
		Node<T>*		right;
		node_colors		color;

		Node() : data(new T()), parent(NULL), left(NULL), right(NULL), color(RED) {}
		
		Node(const T& val) : data(new T(val)), parent(NULL),
			left(NULL), right(NULL), color(RED) {}

		Node(const Node<T>& other) : data(new T(other.data)), parent(other.parent),
			left(other.left), right(other.right), color(other.color) {}

		Node&	operator=(const Node<T>& other) {
			if (this != &other) {
				if (data) {
					delete data;
				}
				data = new T(other.data);
				parent = other.parent;
				left = other.left;
				right = other.right;
				color = other.color;
			}
			return *this;
		}

		~Node() {
			delete data;
		}
	};
	
	template <typename T>
	class Rbtree
	{	
	private:

		Node<T>*	grandparent(const Node<T>* n) const {
			if (n != NULL && n != fakeroot && n->parent != fakeroot) {
				return n->parent->parent;
			}
			else {
				return NULL;
			}
		}

		Node<T>*	uncle(const Node<T>* n) const {
			Node<T>*	g = grandparent(n);
			if (g == NULL) {
				return NULL;
			}
			if (n->parent == g->left) {
				return g->right;
			}
			else {
				return g->left;
			}
		}
		
		void	rotateLeft(Node<T>* n) {
			Node<T>*	pivot = n->right;

			pivot->parent = n->parent;
			if (n->parent != fakeroot) {
				if (n->parent->left == n) {
					n->parent->left = pivot;
				}
				else {
					n->parent->right = pivot;
				}
			}
			else {
				setRoot(pivot);
			}
			
			n->right = pivot->left;
			if (pivot->left) {
				pivot->left->parent = n;
			}
			n->parent = pivot;
			pivot->left = n;
		}

		void	rotateRight(Node<T>* n) {
			Node<T>*	pivot = n->left;

			pivot->parent = n->parent;
			if (n->parent != fakeroot) {
				if (n->parent->left == n) {
					n->parent->left = pivot;
				}
				else {
					n->parent->right = pivot;
				}
			}
			else {
				setRoot(pivot);
			}
			
			n->left = pivot->right;
			if (pivot->right != NULL) {
				pivot->right->parent = n;
			}
			n->parent = pivot;
			pivot->right = n;
		}

		void	insertCase5(Node<T>* n)
		{
			Node<T>* g = grandparent(n);

			n->parent->color = ft::BLACK;
			g->color = ft::RED;
			if ((n == n->parent->left) && (n->parent == g->left)) {
				rotateRight(g);
			}
			else {
				rotateLeft(g);
			}
		}

		void	insertCase4(Node<T>* n) {
			Node<T>* g = grandparent(n);
			
			if ((n == n->parent->right) && (n->parent == g->left)) {
				rotateLeft(n->parent);
				n = n->left;
			}
			else if ((n == n->parent->left) && (n->parent == g->right)) {
				rotateRight(n->parent);
				n = n->right;
			}
			insertCase5(n);
		}

		void	insertCase3(Node<T>* n) {
			Node<T>* u = uncle(n);

			if ((u != NULL) && (u->color == ft::RED)) {
				n->parent->color = ft::BLACK;
				u->color = ft::BLACK;
				Node<T>* g = grandparent(n);
				g->color = ft::RED;
				insertCase1(g);
			}
			else {
				insertCase4(n);
			}
		}
		
		void	insertCase2(Node<T>* n) {
			if (n->parent->color == ft::BLACK) {
				return;
			}
			else {
				insertCase3(n);
			}
		}

		void	insertCase1(Node<T>* n) {
			if (n->parent == fakeroot) {
				n->color = ft::BLACK;
			}
			else {
				insertCase2(n);
			}
		}

		Node<T>*	sibling(Node<T>* n)
		{
			if (n == n->parent->left)
				return n->parent->right;
			else
				return n->parent->left;
		}

		void	replaceNode(Node<T>* n, Node<T>* child) {
			child->parent = n->parent;
			if (n == n->parent->left) {
				n->parent->left = child;
			} else {
				n->parent->right = child;
			}
		}

		void delCase6(Node<T>* n) {
			Node<T>*	s = sibling(n);
			
			s->color = n->parent->color;
			n->parent->color = ft::BLACK;

			if (n == n->parent->left) {
				if (s->right) {
					s->right->color = ft::BLACK;
				}
				rotateLeft(n->parent);
			}
			else {
				if (s->left) {
					s->left->color = ft::BLACK;
				}
				rotateRight(n->parent);
			}
		}
		
		void delCase5(Node<T>* n) {
			Node<T>*	s = sibling(n);
			
			if  (s->color == ft::BLACK) {
				if ((n == n->parent->left) &&
					(!s->right || s->right->color == ft::BLACK) &&
					(!s->left || s->left->color == ft::RED)) {
						s->color = ft::RED;
						if (s->left) {
							s->left->color = ft::BLACK;
						}
						rotateRight(s);
				}
				else if ((n == n->parent->right) &&
						(!s->left || s->left->color == ft::BLACK) &&
						(!s->right || s->right->color == ft::RED)) {
							s->color = ft::RED;
							if (s->right) {
								s->right->color = ft::BLACK;
							}
							rotateLeft(s);
				}
			}
			delCase6(n);
		}

		void delCase4(Node<T>* n) {
			Node<T>*	s = sibling(n);
			
			if ((n->parent->color == ft::RED) &&
				(s->color == ft::BLACK) &&
				(!s->left || s->left->color == ft::BLACK) &&
				(!s->right || s->right->color == ft::BLACK)) {
					s->color = ft::RED;
					n->parent->color = ft::BLACK;
			}
			else {
				delCase5(n);
			}
		}
		
		void delCase3(Node<T>* n) {
			Node<T>*	s = sibling(n);
			
			if ((n->parent->color == ft::BLACK) &&
				(s->color == ft::BLACK) &&
				(!s->left || s->left->color == ft::BLACK) &&
				(!s->right || s->right->color == ft::BLACK)) {
					s->color = ft::RED;
					delCase1(n->parent);
			}
			else {
				delCase4(n);
			}
		}
		
		void delCase2(Node<T>* n) {
			Node<T>*	s = sibling(n);

			if (s->color == ft::RED) {
				n->parent->color = ft::RED;
				s->color = ft::BLACK;
				if (n == n->parent->left)
					rotateLeft(n->parent);
				else
					rotateRight(n->parent);
			} 
			delCase3(n);
		}
		
		void	delCase1(Node<T>* n) {
			if (n->parent != fakeroot)
				delCase2(n);
		}

		void	delOneChildCase(Node<T>* n) {
			Node<T>*	child;
			if (!n->left && n->right) {
				child = n->right;
			}
			else {
				child = n->left;
			}
			
			replaceNode(n, child);
			if (n->color == ft::BLACK) {
				if (child->color == ft::RED)
					child->color = ft::BLACK;
				else
					delCase1(child);
			}
		}

		void	swapNodes(Node<T>*n , Node<T>* sw) {
			n->left->parent = sw;
			n->right->parent = sw;
			if (n == n->parent->left) {
				n->parent->left = sw;
			}
			else if (n == n->parent->right) {
				n->parent->right = sw;
			}
			if (sw->left) {
				sw->left->parent = n;
			}
			if (sw->right) {
				sw->right->parent = n;
			}
			if (sw == sw->parent->left) {
				sw->parent->left = n;
			}
			else if (sw == sw->parent->right) {
				sw->parent->right = n;
			}
			Node<T>*	tmpp = sw->parent;
			Node<T>*	tmpl = sw->left;
			Node<T>*	tmpr = sw->right;
			node_colors	tmpc = sw->color;
			sw->parent = n->parent;
			if (sw != n->left) {
				sw->left = n->left;
			}
			if (sw != n->right) {
				sw->right = n->right;
			}
			sw->color = n->color;
			n->parent = tmpp;
			n->left = tmpl;
			n->right = tmpr;
			n->color = tmpc;
		}

		void	delBothChildsCase(Node<T>* n) {
			Node<T>*	sw = n->right;

			while (sw->left) {
				sw = sw->left;
			}

			swapNodes(n, sw);
			deleteNode(n);
		}

		void	refreshLimits(Node<T>* n) {
			Node<T>*	tmp = fakeroot->left;

			if (n == fakeroot->right) {
				while (tmp && tmp->right) {
					tmp = tmp->right;
				}
				setRightmost(tmp);
			}
			if (n == leftmost) {
				while (tmp && tmp->left) {
					tmp = tmp->left;
				}
				setLeftmost(tmp);
			}
		}
		
		
		Node<T>*	fakeroot;
		Node<T>*	leftmost;
		size_t		sz;

	public:

		Rbtree() : fakeroot(new Node<T>()), leftmost(NULL), sz(0) {}

		Rbtree(const Rbtree<T>& other) : fakeroot(new Node<T>()),
							leftmost(other.leftmost), sz(other.sz) {}
		
		Rbtree&	operator=(const Rbtree& other) {
			if (this != &other) {
				if (fakeroot) {
					delete fakeroot;
				}
				fakeroot = new Node<T>();
				leftmost = other.leftmost;
				sz = other.sz;
			}
			return *this;
		}

		~Rbtree() {
			delete fakeroot;
		};

		size_t	getSize() const {
			return sz;
		}

		Node<T>*	getRoot() const {
			return fakeroot->left;
		}

		Node<T>*	getFakeroot() const {
			return fakeroot;
		}

		Node<T>*	getRightmost() const {
			return fakeroot->right;
		}

		Node<T>*	getLeftmost() const {
			return leftmost;
		}

		void	setLeftmost(Node<T>* n) {
			leftmost = n;
		}

		void	setRightmost(Node<T>* n) {
			fakeroot->right = n;
		}

		void	setRoot(Node<T>* n) {
			fakeroot->left = n;
			if (!n) {
				fakeroot->right = NULL;
				leftmost = NULL;
				return;
			}
			n->parent = fakeroot;
			if (!sz) {
				n->color = ft::BLACK;
				fakeroot->right = n;
				leftmost = n;
				++sz;
			}
		}

		void	insertBalance(Node<T>* n) {
			++sz;
			insertCase1(n);
		}

		void	deleteNode(Node<T>* n) {
			if (!n || n == fakeroot) {
				return;
			}
			if (!n->left && !n->right) {
				--sz;
				if (n == n->parent->left) {
					if (!n->parent->right) {
						n->parent->color = ft::BLACK;
					}
					n->parent->left = NULL;
				}
				else if (n == n->parent->right) {
					if (!n->parent->left) {
						n->parent->color = ft::BLACK;
					}
					n->parent->right = NULL;
				}
			}
			else if ((!n->left && n->right) || (!n->right && n->left)) {
				delOneChildCase(n);
				--sz;
			}
			else {
				delBothChildsCase(n);
			}
			refreshLimits(n);
		}

















	/*----------------------------------------------------------------------------*/
	/*--------------------------------- TEMPORARY --------------------------------*/
	/*----------------------------------------------------------------------------*/


		void print_ranges() {
			Node<T>*	cur = getRoot();

			while (cur->left) {
				std::cout << cur->data->first << std::endl;
				cur = cur->left;
			}

			std::cout << std::endl;

			cur = getRoot();

			while (cur->right) {
				std::cout << cur->data->first << std::endl;
				cur = cur->right;
			}
		}
		
		void prindebug(Node<T>* par, int a) {
			// if (par->color == 0 && a == -1) {
			// 	return;
			// }	
			std::cout << "BLACK DEPTH INCORRECT " << a << " dest: " << par->data->first 
				<< " color: " << par->color;
		}	

		void depth_check() {
			std::srand(std::time(nullptr));

			int a, black, red, flag, black2, count;

			black2 = 0;
			count = 0;
			for (size_t i = 0; i < 500; ++i) {
				Node<T>*	cur = getRoot(), *par;
				black = 0;
				red = 0;
				flag = 0;
				while (cur != NULL) {
					if (cur->color == ft::BLACK) {
						black++;
						flag = 0;
					}
					if (cur->color == ft::RED) {
						if (flag) {
							std::cout << "RED TWICE\n";
							break;
						}
						flag = 1;
						red++;
					}
					a = rand() % 2;
					par = cur;
					if (a) {
						if (cur->left) {
							cur = cur->left;
						}
						else if (cur->right) {
							cur = cur->right;
						}
						else {
							cur = NULL;
						}
					}
					else {
						if (cur->right) {
							cur = cur->right;
						}
						else if (cur->left) {
							cur = cur->left;
						}
						else {
							cur = NULL;
						}
					}
					// cur = (a > 0) ? cur->left : cur->right;
				}
				if (black2 != black && count) {
					prindebug(par, black-black2);
				}
				if (!count) {
					black2 = black;
				}
				++count;
				// std::cout << "dest: " << par->data->first;
				// std::cout << " black: " << black;
				// std::cout << " red: " << red << "\n";
			}
			std::cout << "good\n"; 
			std::cout << "leftmost: " << leftmost->data->first
				<< " rightmost: " << fakeroot->right->data->first << "\n";
		}
	};

}