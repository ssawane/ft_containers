/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:55:16 by ssawane           #+#    #+#             */
/*   Updated: 2022/12/07 11:57:58 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


namespace ft {
	
	template <typename T, T v>
	struct integral_constant
	{
		static const T value = v;

		typedef T							value_type;
		typedef integral_constant<T, v>		type;
		
		
		operator value_type() {
			return v;
		}

		T	operator ()() {
			return v;
		}
		
	};

	typedef	integral_constant<bool, true>	true_type;
	typedef	integral_constant<bool, false>	false_type;
	
	template <typename T>
	struct is_integral : false_type {};

	template <> struct is_integral<bool> : true_type {};

	template <> struct is_integral<char> : true_type {};

	template <> struct is_integral<char16_t> : true_type {};

	template <> struct is_integral<char32_t> : true_type {};

	template <> struct is_integral<wchar_t> : true_type {};
	
	template <> struct is_integral<signed char> : true_type {};

	template <> struct is_integral<short int> : true_type {};

	template <> struct is_integral<int> : true_type {};

	template <> struct is_integral<long int> : true_type {};

	template <> struct is_integral<long long int> : true_type {};

	template <> struct is_integral<unsigned char> : true_type {};

	template <> struct is_integral<unsigned short int> : true_type {};

	template <> struct is_integral<unsigned int> : true_type {};

	template <> struct is_integral<unsigned long int> : true_type {};

	template <> struct is_integral<unsigned long long int> : true_type {};

}