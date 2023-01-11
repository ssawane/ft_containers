/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 11:55:40 by ssawane           #+#    #+#             */
/*   Updated: 2023/01/11 18:24:36 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iterator>
#include "../utility/red_black_tree.hpp"

namespace ft {

	template <typename T>
	class map_iterator
	{
	public:

		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef value_type*						pointer;
		typedef const value_type*				const_pointer;
		typedef value_type&						reference;
		typedef const value_type&				const_reference;

		/*----------------------------------------------------------------------------*/
		/*---------------------- CONSTRUCTORS AND DESTRUCTOR -------------------------*/
		/*----------------------------------------------------------------------------*/

		map_iterator() : n(NULL), fakeroot(NULL), leftmost(NULL) {}
		map_iterator(Node<value_type>* val) : n(val), fakeroot(val), leftmost(val) {
			if (val) {
				while (fakeroot->parent != NULL) {
					fakeroot = fakeroot->parent;
				}
				leftmost = fakeroot;
				while (leftmost->left != NULL) {
					leftmost = leftmost->left;
				}
			}
		}
		map_iterator(const map_iterator& other) :
			n(other.n), fakeroot(other.fakeroot), leftmost(other.leftmost) {}
		map_iterator& operator=(const map_iterator& other) {
			if (*this != other) {
				n = other.n;
				fakeroot = other.fakeroot;
				leftmost = other.leftmost;
			}
			return *this;
		}
		~map_iterator() {}

		/*----------------------------------------------------------------------------*/
		/*----------------------------- MEMBER FUNCTIONS -----------------------------*/
		/*----------------------------------------------------------------------------*/	


		Node<T>*	base() const {
			return n;
		}
		
		bool	operator==(const map_iterator& other) {
			return n == other.n;
		}

		bool	operator!=(const map_iterator& other) {
			return !(n == other.n);
		}

		reference	operator*() {
			return *(n->data);
		}

		const_reference	operator*() const {
			return *(n->data);
		}

		pointer	operator->() {
			return n->data;
		}

		const_pointer	operator->() const {
			return n->data;
		}

		map_iterator&	operator++() {
			Node<T>*	tmp = n;
			
			if (n == fakeroot) {
				n = leftmost;
				return *this;
			}
			if (n == fakeroot->right) {
				n = fakeroot;
				return *this;
			}
			if (n->right) {
				n = n->right;
				while (n->left) {
					n = n->left;
				}
			}
			else {
				while (tmp != n->left) {
					tmp = n;
					n = n->parent;
				}
			}
			return *this;
		}

		map_iterator	operator++(int) {
			map_iterator tmp = *this;

			++(*this);
			return tmp;
		}

		map_iterator&	operator--() {
			Node<T>*	tmp = n;

			if (n == fakeroot) {
				n = fakeroot->right;
				return *this;
			}
			if (n == leftmost) {
				n = fakeroot;
				return *this;
			}
			if (n->left) {
				n = n->left;
				while (n->right) {
					n = n->right;
				}
			}
			else {
				while (tmp != n->right) {
					tmp = n;
					n = n->parent;
				}
			}
			return *this;
		}

		map_iterator	operator--(int) {
			map_iterator tmp = *this;

			--(*this);
			return tmp;
		}

	private:

		Node<value_type>*	n;
		Node<value_type>*	fakeroot;
		Node<value_type>*	leftmost;

	};
}

template <typename T, typename U>
bool	operator==(ft::map_iterator<T>& first, ft::map_iterator<U>& second)  {
	return first.base() == second.base();
}

template <typename T, typename U>
bool	operator==(const ft::map_iterator<T>& first, const ft::map_iterator<U>& second)  {
	return first.base() == second.base();
}

template <typename T, typename U>
bool	operator!=(ft::map_iterator<T>& first, ft::map_iterator<U>& second)  {
	return !(first.base() == second.base());
}

template <typename T, typename U>
bool	operator!=(const ft::map_iterator<T>& first, const ft::map_iterator<U>& second)  {
	return !(first.base() == second.base());
}
