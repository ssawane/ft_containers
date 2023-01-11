/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:11:29 by ssawane           #+#    #+#             */
/*   Updated: 2022/12/28 20:21:56 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft {
	template <bool B, typename T = void>
	struct enable_if {};

	template <typename T>
	struct enable_if<true, T>
	{
		typedef T	type;
	};
}