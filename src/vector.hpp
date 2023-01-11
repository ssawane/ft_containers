/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 22:42:58 by ssawane           #+#    #+#             */
/*   Updated: 2023/01/11 18:26:17 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include "iterators/vector_iterator.hpp"
#include "iterators/reverse_iterator.hpp"
#include "utility/is_integral.hpp"
#include "utility/enable_if.hpp"
#include "utility/equal_lexcompare.hpp"

namespace ft {
	template <typename T, typename Allocator = std::allocator<T> >
	class vector
	{
	private:

		T*			arr;
		size_t		sz;
		size_t		cap;
		Allocator	alloc;

	public:

		typedef T										value_type;
		typedef Allocator								allocator_type;
		typedef size_t									size_type;
		typedef ptrdiff_t								difference_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef value_type*								pointer;
		typedef const value_type*						const_pointer;
		typedef vec_iterator<T>							iterator;
		typedef const iterator							const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		
		/*----------------------------------------------------------------------------*/
		/*---------------------- CONSTRUCTORS AND DESTRUCTOR -------------------------*/
		/*----------------------------------------------------------------------------*/

		vector() : arr(NULL), sz(0), cap(0) {
			alloc = Allocator();
		}

		explicit vector(const Allocator& alloc) : arr(NULL), sz(0), cap(0), alloc(alloc) {}

		explicit vector(size_type count, const T& value = T(),
						const Allocator& alloc = Allocator()) : alloc(alloc) {
			if (count > 0) {
				arr = alloc.allocate(count);
				size_t i = 0;
				try {
					for (; i < count; ++i) {
						alloc.construct(arr + i, value);
					}
				}
				catch (...) {
					for (size_t j = 0; j < i; ++j) {
						alloc.destroy(arr + j);
					}
					alloc.deallocate(arr, count);
					return;
				}
			}
			else {
				arr = NULL;
			}
			cap = sz = count;
		}

		template <typename InputIt>
		vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(),
				typename ft::enable_if<! ft::is_integral<InputIt>::value, InputIt>::type* = 0) : alloc(alloc) {
			difference_type	dis = std::distance(first, last);
			if (dis > 0) {
				arr = alloc.allocate(dis);
				try {
					for (InputIt it = first; it != last; ++it) {
						alloc.construct(arr + sz, *it);
						++sz;
					}
				}
				catch (...) {
					for (size_t j = 0; j < sz; ++j) {
						alloc.destroy(arr + j);
					}
					alloc.deallocate(arr, dis);
					return;
				}
				cap = dis;
			}
			else {
				arr = NULL;
				sz = cap = 0;
			}
		}
		
		vector(const vector& other) : alloc(other.alloc) {
			if (other.sz) {
				arr = alloc.allocate(other.cap);
				size_t	i = 0;
				try {
					for (; i < other.sz; ++i) {
						alloc.construct(arr + i, other.arr[i]);
					}
				}
				catch (...) {
					for (size_t j = 0; j < i; ++j) {
						alloc.destroy(arr + j);
					}
					alloc.deallocate(arr, other.cap);
					return;
				}
			}
			else {
				arr = NULL;
			}
			sz = other.sz;
			cap = other.cap;
		}

		~vector() {
			if (sz) {
				for (size_t j = 0; j < sz; ++j) {
					alloc.destroy(arr + j);
				}
				alloc.deallocate(arr, cap);
			}
		}

		/*----------------------------------------------------------------------------*/
		/*----------------------------- MEMBER FUNCTIONS -----------------------------*/
		/*----------------------------------------------------------------------------*/

		vector&	operator=(const vector& other) {
			if (this != &other) {
				T* newarr = NULL;
				if (other.sz > 0) {
					newarr = alloc.allocate(other.cap);
					size_t	i = 0;
					try {
						for (; i < other.sz; ++i) {
							alloc.construct(newarr + i, other.arr[i]);
						}
					}
					catch (...) {
						for (size_t j = 0; j < i; ++j) {
							alloc.destroy(arr + j);
						}
						alloc.deallocate(newarr, other.cap);
						return *this;
					}
				}
				if (sz > 0) {
					clear();
					alloc.deallocate(arr, cap);
				}
				arr = newarr;
				sz = other.sz;
				cap = other.cap;
			}
			return *this;
		}

		void	assign(size_type count, const_reference value) {
			if (count) {
				T* newarr = alloc.allocate(count);
				size_t	i = 0;
				try {
					for (; i < count; ++i) {
							alloc.construct(newarr + i, value);
					}
				}
				catch (...) {
					for (size_t j = 0; j < i; ++j) {
						alloc.destroy(newarr + j);
					}
					alloc.deallocate(newarr, count);
					throw;
				}
				clear();
				alloc.deallocate(arr, cap);
				arr = newarr;
				sz = count;
				if (cap > count) {
					size_t	tmp = cap;
					cap = sz;
					reserve(tmp);
				}
				else {
					cap = count;
				}
			}
			else {
				clear();
			}
		}

		template <typename InputIt>
		void	assign(InputIt first, InputIt last, 
				typename ft::enable_if<! ft::is_integral<InputIt>::value, InputIt>::type* = 0) {
			difference_type	dis = std::distance(first, last);
			if (dis > 0) {
				T* newarr = alloc.allocate(dis);
				size_t tmp = 0;
				try {
					for (InputIt it = first; it != last; ++it) {
						alloc.construct(newarr + tmp, *it);
						++tmp;
					}
					sz = tmp;
				}
				catch (...) {
					for (size_t j = 0; j < tmp; ++j) {
						alloc.destroy(newarr + j);
					}
					alloc.deallocate(newarr, dis);
					throw;
				}
				clear();
				alloc.deallocate(arr, cap);
				arr = newarr;
				sz = tmp;
				if (cap > dis) {
					tmp = cap;
					cap = sz;
					reserve(tmp);
				}
				else {
					cap = dis;
				}
			}
			else {
				clear();
			}
		}
		
		Allocator	get_allocator() const {
			return alloc;
		}

		/*----------------------------------------------------------------------------*/
		/*------------------------------ ELEMENT ACCESS ------------------------------*/
		/*----------------------------------------------------------------------------*/

		reference		at(size_t pos) {
			if (pos >= sz) {
				throw std::out_of_range("vector");
			}
			return *(arr + pos);
		}

		const_reference	at(size_t pos) const {
			if (pos >= sz) {
				throw std::out_of_range("vector");
			}
			return *(arr + pos);
		}

		reference		operator[](size_type pos) {
			return *(arr + pos);
		}

		const_reference	operator[](size_type pos) const {
			return *(arr + pos);
		}

		reference		front() {
			return *arr;
		}

		const_reference	front() const {
			return *arr;
		}

		reference		back() {
			return *(arr + sz - 1);
		}

		const_reference	back() const {
			return *(arr + sz - 1);
		}

		pointer			data(){
			return arr;
		}

		const_pointer	data() const {
			return arr;
		}
		
		/*----------------------------------------------------------------------------*/
		/*-------------------------------- ITERATORS ---------------------------------*/
		/*----------------------------------------------------------------------------*/

		iterator				begin() {
			return iterator(arr);
		}

		const_iterator			begin() const {
			return const_iterator(arr);
		}

		iterator				end() {
			return iterator(arr + sz);
		}

		const_iterator			end() const {
			return const_iterator(arr + sz);
		}

		reverse_iterator		rbegin() {
			return	reverse_iterator(end());
		}

		const_reverse_iterator	rbegin() const {
			return	const_reverse_iterator(end());
		}

		reverse_iterator		rend() {
			return	reverse_iterator(begin());
		}

		const_reverse_iterator	rend() const {
			return	const_reverse_iterator(begin());
		}

		/*----------------------------------------------------------------------------*/
		/*--------------------------------- CAPACITY ---------------------------------*/
		/*----------------------------------------------------------------------------*/

		bool		empty() const {
			return sz == 0;
		}

		size_type	size() const {
			return sz;
		}

		size_type	max_size() const {
			return std::numeric_limits<difference_type>::max();
		}

		void		reserve(size_t new_cap) {
			if (new_cap <= cap) {
				return;
			}
			if (new_cap > max_size()) {
				throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
			}
			T*	newarr = alloc.allocate(new_cap);
			size_t	i = 0;
			try {
				for (; i < sz; ++i) {
					alloc.construct(newarr + i, arr[i]);
				}
			}
			catch (...) {
				for (size_t j = 0; j < i; ++j) {
					alloc.destroy(newarr + j);
				}
				alloc.deallocate(newarr, new_cap);
				throw;
			}
			if (arr) {
				for (size_t j = 0; j < sz; ++j) {
					alloc.destroy(arr + j);
				}
				alloc.deallocate(arr, cap);
			}
			arr = newarr;
			cap = new_cap;
		}

		size_type	capacity() const {
			return cap;
		}

		/*----------------------------------------------------------------------------*/
		/*--------------------------------- MODIFIERS --------------------------------*/
		/*----------------------------------------------------------------------------*/

		void		clear() {
			if (sz > 0) {
				for (size_t j = 0; j < sz; ++j) {
					alloc.destroy(arr + j);
				}
				sz = 0;
			}
		}

		iterator	insert(const_iterator pos, const T& value) {
			if (sz == cap) {
				if (!cap) {
					reserve(1);
				}
				else {
					reserve(cap * 2);
				}
			}
			difference_type	i = sz;
			for (iterator en = end(); en != pos; --en) {
				arr[i] = arr[i - 1];
				--i;
			}
			alloc.construct(arr + i, value);
			++sz;
			return iterator(arr + i);
		}
		
		iterator	insert(const_iterator pos, size_type count, const T& value) {
			difference_type p = std::distance(begin(), pos);
			if (sz + count > cap) {
				reserve(sz + count);
			}
			difference_type	i = sz;
			for (; i > p; --i) {
				arr[i + count - 1] = arr[i - 1];
			}
			size_t j = count;
			try {
				for (; j > 0; --j) {
					alloc.construct(arr + i, value);
					++i;
				}
			}
			catch(...) {
				for (; j < count; ++j) {
					alloc.destroy(arr + i);
					--i;
				}
				i = sz;
				for (; i > p; --i) {
					arr[i - 1] = arr[i + count - 1];
				}
				throw;
			}
			sz += count;
			return iterator(arr + p);
		}

		template <class InputIt>
		iterator	insert(const iterator pos, InputIt first, InputIt last,
							typename ft::enable_if<! ft::is_integral<InputIt>::value, InputIt>::type* = 0) {
			difference_type	range = std::distance(first, last);
			difference_type p = std::distance(begin(), pos);
			if (range > 0) {
				T* tmparr = alloc.allocate(range);
				difference_type i = 0;
				for (; i < range; ++i) {
					tmparr[i] = *first;
					++first;
				}
				first = InputIt(tmparr);
				last = InputIt(tmparr + i);
				if (sz + range > cap) {
					reserve(sz + range);
				}
				i = sz;
				for (; i > p; --i) {
					arr[i + range - 1] = arr[i - 1];
				}
				difference_type	j = range;
				try {
					for (; j > 0; --j) {
						alloc.construct(arr + i, *first);
						++i;
						++first;
					}
				}
				catch(...) {
					for (; j < range; ++j) {
						alloc.destroy(arr + i);
						--i;
					}
					i = sz;
					for (; i > p; --i) {
						arr[i - 1] = arr[i + range - 1];
					}
					alloc.deallocate(tmparr, range);
					throw;
				}
				alloc.deallocate(tmparr, range);
				sz += range;
			}
			return iterator(arr + p);
		}

		iterator	erase(iterator pos) {
			if (sz) {
				difference_type dis = std::distance(begin(), pos);
				if (dis >= 0 && dis < static_cast<ptrdiff_t>(sz)) {
					alloc.destroy(arr + dis);
					difference_type	i = dis;
					for (iterator bg = pos; bg != end(); ++bg) {
						arr[i] = arr[i + 1];
						++i;
					}
					--sz;
					return iterator(arr + dis);
				}
			}
			return end();
		}

		iterator	erase(iterator first, iterator last) {
			difference_type range = std::distance(first, last);
			if (range == 0) {
				return last;
			}
			if (sz) {
				difference_type beg = std::distance(begin(), first);
				if (beg >= 0 && beg < static_cast<ptrdiff_t>(sz)
					&& range > 0 && range <= static_cast<ptrdiff_t>(sz)) {
					difference_type i = beg;
					for (size_t tmp = 0; tmp < static_cast<size_t>(range); ++tmp) {
						alloc.destroy(arr + i);
						++i;
					}
					i = beg;
					for (size_t tmp = 0; tmp < static_cast<size_t>(range); ++tmp) {
						arr[i] = arr[i + range];
						++i;
					}
					sz -= range;
					return iterator(arr + beg);
				}
			}
			return end();
		}

		void		push_back(const T& value) {
			if (sz == cap) {
				T* tmparr = alloc.allocate(1);
				try {
					alloc.construct(tmparr, value);
				}
				catch (...) {
					alloc.deallocate(tmparr, 1);
					throw;
				}
				alloc.destroy(tmparr);
				alloc.deallocate(tmparr, 1);
				if (!cap) {
					reserve(1);
				}
				else {
					reserve(cap * 2);
				}
			}
			alloc.construct(arr + sz, value);
			++sz;
		}

		void		pop_back() {
			alloc.destroy(arr + sz);
			sz--;
		}

		void		resize(size_type count, T value = T()) {
			size_t	tmp = cap;
			if (count > sz) {
				while (count > tmp) {
					tmp *= 2;
				}
				T*	newarr = alloc.allocate(tmp);
				size_t i = 0;
				try {
					for (; i < sz; ++i) {
						alloc.construct(newarr + i, arr[i]);
					}
					for (; i < count; ++i) {
						alloc.construct(newarr + i, value);
					}
				}
				catch (...) {
					for (size_t j = 0; j < i; ++j) {
						alloc.destroy(newarr + j);
					}
					alloc.deallocate(newarr, tmp);
					throw;
				}
				clear();
				alloc.deallocate(arr, cap);
				arr = newarr;
				sz = count;
				cap = tmp;
			}
			else if (count < sz) {
				tmp = count;
				for (; tmp < sz; ++tmp) {
					alloc.destroy(arr + tmp);
				}
				sz = count;
			}
		}

		void		swap(vector& other) {
			std::swap(arr, other.arr);
			std::swap(sz, other.sz);
			std::swap(cap, other.cap);
			std::swap(alloc, other.alloc);
		}
	};
}
	
	/*----------------------------------------------------------------------------*/
	/*--------------------------- NON-MEMBER FUNCTIONS ---------------------------*/
	/*----------------------------------------------------------------------------*/

template <typename U, typename Alloc>
bool operator==(const ft::vector<U, Alloc>& lhs, const ft::vector<U, Alloc>& rhs) {
	if (lhs.size() != rhs.size())
		return (false);
	for (size_t i = 0; i < lhs.size(); i++)
		if (lhs[i] != rhs[i])
			return (false);
	return (true);
}

template <typename U, typename Alloc>
bool operator!=(const ft::vector<U, Alloc>& lhs, const ft::vector<U, Alloc>& rhs) {
	return !(lhs == rhs);
}

template <typename U, typename Alloc>
bool operator<(const ft::vector<U, Alloc>& lhs, const ft::vector<U, Alloc>& rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename U, typename Alloc>
bool operator<=(const ft::vector<U, Alloc>& lhs, const ft::vector<U, Alloc>& rhs) {
	return !(rhs < lhs);
}

template <typename U, typename Alloc>
bool operator>(const ft::vector<U, Alloc>& lhs, const ft::vector<U, Alloc>& rhs) {
	return rhs < lhs;
}

template <typename U, typename Alloc>
bool operator>=(const ft::vector<U, Alloc>& lhs, const ft::vector<U, Alloc>& rhs) {
	return !(lhs < rhs);
}

template <typename U, typename Alloc>
void swap(ft::vector<U, Alloc>& lhs, ft::vector<U, Alloc>& rhs) {
	lhs.swap(rhs);
}
