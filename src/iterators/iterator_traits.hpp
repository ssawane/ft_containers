/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:26:08 by ssawane           #+#    #+#             */
/*   Updated: 2022/12/28 20:16:41 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iterator>

namespace ft {
	template <typename Iter>
	class iterator_traits
	{
	public:

		typedef typename Iter::difference_type		difference_type;
		typedef	typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;

	};

	template <typename T>
	class iterator_traits<T*>
	{
	public:

		typedef ptrdiff_t							difference_type;
		typedef	T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef std::random_access_iterator_tag		iterator_category;
	};

	template <typename T>
	class iterator_traits<const T*>
	{
	public:

		typedef ptrdiff_t							difference_type;
		typedef	T									value_type;
		typedef const T*							pointer;
		typedef const T&							reference;
		typedef std::random_access_iterator_tag		iterator_category;
	};
}