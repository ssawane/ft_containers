/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 21:17:05 by ssawane           #+#    #+#             */
/*   Updated: 2022/12/28 20:14:30 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"

namespace ft {
	template <typename Iterator>
	class reverse_iterator
	{
	public:

		typedef Iterator													iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
		typedef typename ft::iterator_traits<Iterator>::reference			reference;

		/*----------------------------------------------------------------------------*/
		/*---------------------- CONSTRUCTORS AND DESTRUCTOR -------------------------*/
		/*----------------------------------------------------------------------------*/

		reverse_iterator() : current(Iterator()) {}
		explicit reverse_iterator(iterator_type x) : current(x) {}
		
		template <typename U>
		reverse_iterator(const reverse_iterator<U>& other) : current(other.base()) {}

		template <typename U>
		reverse_iterator&	operator=(const reverse_iterator<U>& other) {
			if (this != &other) {
				current = other.base();
			}
			return *this;
		}
		~reverse_iterator() {}

		/*----------------------------------------------------------------------------*/
		/*----------------------------- MEMBER FUNCTIONS -----------------------------*/
		/*----------------------------------------------------------------------------*/

		iterator_type	base() const {
			return current;
		}

		/*----------------------------------------------------------------------------*/
		/*--------------------------------- OVERLOADS --------------------------------*/
		/*----------------------------------------------------------------------------*/

		reference	operator*() const {
			Iterator	tmp(current);

			return *--tmp;
		}

		pointer		operator->() const {
			Iterator	tmp(current);

			return &(*--tmp);
		}

		reference	operator[](difference_type n) const {
			return current[-n - 1];
		}

		reverse_iterator&	operator++() {
			--current;
			return *this;
		}

		reverse_iterator	operator++(int) {
			reverse_iterator	tmp = *this;

			--current;
			return tmp;
		}

		reverse_iterator&	operator--() {
			++current;
			return *this;
		}

		reverse_iterator	operator--(int) {
			reverse_iterator	tmp = *this;

			++current;
			return tmp;
		}

		reverse_iterator operator+(difference_type n) {
			reverse_iterator	tmp = *this;

			tmp -= n;
			return tmp;
		}

		reverse_iterator operator-(difference_type n) {
			reverse_iterator	tmp = *this;

			tmp += n;
			return tmp;
		}

		reverse_iterator&	operator+=(difference_type n) {
			current -= n;
			return *this;
		}

		reverse_iterator&	operator-=(difference_type n) {
			current += n;
			return *this;
		}

	protected:
		Iterator	current;

	};
}

template <class It1, class It2>
bool	operator==(const ft::reverse_iterator<It1>& lhs, const ft::reverse_iterator<It2>& rhs) {
	return lhs.base() == rhs.base();
}

template <class It1, class It2>
bool	operator!=(const ft::reverse_iterator<It1>& lhs, const ft::reverse_iterator<It2>& rhs) {
	return lhs.base() != rhs.base();
}

template <class It1, class It2>
bool	operator>(const ft::reverse_iterator<It1>& lhs, const ft::reverse_iterator<It2>& rhs) {
	return lhs.base() > rhs.base();
}

template <class It1, class It2>
bool	operator>=(const ft::reverse_iterator<It1>& lhs, const ft::reverse_iterator<It2>& rhs) {
	return lhs.base() >= rhs.base();
}

template <class It1, class It2>
bool	operator<(const ft::reverse_iterator<It1>& lhs, const ft::reverse_iterator<It2>& rhs) {
	return lhs.base() < rhs.base();
}

template <class It1, class It2>
bool	operator<=(const ft::reverse_iterator<It1>& lhs, const ft::reverse_iterator<It2>& rhs) {
	return lhs.base() <= rhs.base();
}
