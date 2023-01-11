/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 13:57:27 by ssawane           #+#    #+#             */
/*   Updated: 2023/01/11 18:24:51 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
  
#include <iterator>
#include "../vector.hpp"

namespace ft {
	template <typename T>
	class vec_iterator
	{

	public:

		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef value_type*						pointer;
		typedef value_type&						reference;
		typedef const value_type&				const_reference;

		/*----------------------------------------------------------------------------*/
		/*---------------------- CONSTRUCTORS AND DESTRUCTOR -------------------------*/
		/*----------------------------------------------------------------------------*/
		
		vec_iterator() : ptr(nullptr) {}
		vec_iterator(pointer ptr) : ptr(ptr) {}
		vec_iterator(const vec_iterator& other) : ptr(other.base()) {}
		vec_iterator&	operator=(const vec_iterator& other) {
			if (*this != other) {
				ptr = other.base();
			}
			return *this;
		}

		~vec_iterator() {}

		/*----------------------------------------------------------------------------*/
		/*----------------------------- MEMBER FUNCTIONS -----------------------------*/
		/*----------------------------------------------------------------------------*/	
		
		pointer			base(void) const {
			return ptr;
		}

		/*----------------------------------------------------------------------------*/
		/*--------------------------------- OVERLOADS --------------------------------*/
		/*----------------------------------------------------------------------------*/
		
		vec_iterator&	operator+=(difference_type n) {
			ptr += n;
			return *this;
		}
		
		vec_iterator	operator+(difference_type n) {
			return vec_iterator<T>(ptr + n);
		}

		vec_iterator&	operator-=(difference_type n) {
			ptr -= n;
			return *this;
		}

		vec_iterator	operator-(difference_type n) {
			return vec_iterator<T>(ptr - n);
		} 

		difference_type	operator-(const vec_iterator& other) {
			return ptr - other.base();
		}

		difference_type	operator+(const vec_iterator& other) {
			return ptr + other.base();
		}

		reference		operator[](difference_type n) {
			return *(ptr + n);
		}

		const_reference	operator[](difference_type n) const {
			return *(ptr + n);
		}

		vec_iterator&	operator++(void) {
			++ptr;
			return *this;
		}

		vec_iterator	operator++(int) {
			vec_iterator	tmp = *this;
			++ptr;
			return tmp;
		}

		vec_iterator&	operator--(void) {
			--ptr;
			return *this;
		}

		vec_iterator	operator--(int) {
			vec_iterator	tmp = *this;
			--ptr;
			return tmp;
		}

		reference		operator*() {
			return *ptr;
		}

		const_reference	operator*() const {
			return *ptr;
		}

		pointer			operator->() {
			return ptr;
		}

		const pointer	operator->() const {
			return ptr;
		}

		bool			operator<(const vec_iterator& other) {
			return this->ptr < other.base();
		}

		bool			operator>(const vec_iterator& other) {
			return this->ptr > other.base();
		}

		bool			operator<=(const vec_iterator& other) {
			return this->ptr <= other.base();
		}

		bool			operator>=(const vec_iterator& other) {
			return this->ptr >= other.base();
		}

		bool			operator==(const vec_iterator& other) {
			return this->ptr == other.base();
		}

		bool			operator!=(const vec_iterator& other) {
			return this->ptr != other.base();
		}

	private:

		pointer	ptr;

	};
}

template <typename T, typename U>
bool			operator<(ft::vec_iterator<T>& first, ft::vec_iterator<U>& second)  {
	return first.base() < second.base();
}

template <typename T, typename U>
bool			operator>(ft::vec_iterator<T>& first, ft::vec_iterator<U>& second)  {
	return first.base() > second.base();
}

template <typename T, typename U>
bool			operator<=(ft::vec_iterator<T>& first, ft::vec_iterator<U>& second)  {
	return first.base() <= second.base();
}

template <typename T, typename U>
bool			operator>=(ft::vec_iterator<T>& first, ft::vec_iterator<U>& second)  {
	return first.base() >= second.base();
}

template <typename T, typename U>
bool			operator==(ft::vec_iterator<T>& first, ft::vec_iterator<U>& second)  {
	return first.base() == second.base();
}

template <typename T, typename U>
bool			operator!=(ft::vec_iterator<T>& first, ft::vec_iterator<U>& second)  {
	return first.base() != second.base();
}