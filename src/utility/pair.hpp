/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:31:17 by ssawane           #+#    #+#             */
/*   Updated: 2022/12/12 23:42:15 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft {

	template <typename T1, typename T2>
	struct pair
	{

		typedef T1	first_type;
		typedef T2	second_type;

		T1	first;
		T2	second;

		pair() : first(T1()), second(T2()) {}
		pair(const T1& x, const T2& y) : first(x), second(y) {}

		template <typename U1, typename U2>
		pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}

		pair&	operator=(const pair& other) {
			if (this != &other) {
				first = other.first;
				second = other.second;
			}
			return *this;
		}
	};

	template <typename T1, typename T2>
	pair<T1, T2> make_pair(T1 t, T2 u) {
		return pair<T1, T2>(t, u);
	}

}

template <typename T1, typename T2>
bool operator==(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
	return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <typename T1, typename T2>
bool operator!=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
	return !(lhs == rhs);
}

template <typename T1, typename T2>
bool operator<(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
	if (lhs.first == rhs.first) {
		return lhs.second < rhs.second;
	}
	return lhs.first < rhs.first;
}

template <typename T1, typename T2>
bool operator<=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
	return !(rhs < lhs);
}

template <typename T1, typename T2>
bool operator>(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
	return rhs < lhs;
}

template <typename T1, typename T2>
bool operator>=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
	return !(lhs < rhs);
}
