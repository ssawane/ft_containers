/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal_lexcompare.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:53:12 by ssawane           #+#    #+#             */
/*   Updated: 2022/12/26 18:14:49 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft {
	template <class InputIt1, class InputIt2>
	bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
		for (; first1 != last1; ++first1, ++first2) {
			if (*first1 != *first2) {
				return false;
			}
		}
		return true;
	}

	template <class InputIt1, class InputIt2, class BinaryPredicate>
	bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p) {
		for (; first1 != last1; ++first1, ++first2) {
			if (!p(*first1, *first2)) {
				return false;
			}
		}
		return true;
	}

	template <class InputIt1, class InputIt2>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2) {
			if (*first1 < *first2) {
				return true;
			}
			if (*first1 > *first2) {
				return false;
			}
		}
		return (first1 == last1) && (first2 != last2);
	}

	template <class InputIt1, class InputIt2, class Compare>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1,
				InputIt2 first2, InputIt2 last2, Compare comp) {
		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2) {
			if (comp(*first1, *first2)) {
				return true;
			}
			if (comp(*first2, *first1)) {
				return false;
			}
		}
		return (first1 == last1) && (first2 != last2);
	}
}