/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 17:01:36 by ssawane           #+#    #+#             */
/*   Updated: 2022/12/26 17:55:10 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"

namespace ft {
	template <typename T, typename Container = vector<T> >
	class stack {
	public:

		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;

		/*----------------------------------------------------------------------------*/
		/*---------------------------- MEMBER FUNCTIONS ------------------------------*/
		/*----------------------------------------------------------------------------*/

		explicit	stack(const container_type& ctnr = container_type())
													: c(ctnr) {}

		stack(const stack& other) : c(other.c) {}

		stack&	operator=(const stack& other) {
			if (this != &other) {
				c = other.c;
			}
			return *this;
		}

		~stack() {}

		reference	top() {
			return c.back();
		}

		const_reference	top() const {
			return c.back();
		}

		/*----------------------------------------------------------------------------*/
		/*--------------------------------- CAPACITY ---------------------------------*/
		/*----------------------------------------------------------------------------*/

		bool	empty() const {
			return c.empty();
		}

		size_type size() const {
			return c.size();
		}
		
		/*----------------------------------------------------------------------------*/
		/*-------------------------------- MODIFIERS ---------------------------------*/
		/*----------------------------------------------------------------------------*/

		void	push(const value_type& value) {
			c.push_back(value);
		}

		void	pop() {
			c.pop_back();
		}

		friend bool	operator==(const stack& lhs, const stack& rhs) {
			return lhs.c == rhs.c;
		}

		friend bool	operator!=(const stack& lhs, const stack& rhs) {
			return lhs.c != rhs.c;
		}

		friend bool	operator<(const stack& lhs, const stack& rhs) {
			return lhs.c < rhs.c;
		}

		friend bool	operator<=(const stack& lhs, const stack& rhs) {
			return !(rhs < lhs);
		}

		friend bool	operator>(const stack& lhs, const stack& rhs) {
			return lhs.c > rhs.c;
		}

		friend bool	operator>=(const stack& lhs, const stack& rhs) {
			return lhs.c >= rhs.c;
		}

	protected:

		Container	c;
	};
}
