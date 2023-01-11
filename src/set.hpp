/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:06:28 by ssawane           #+#    #+#             */
/*   Updated: 2023/01/11 18:25:59 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "utility/pair.hpp"
#include "utility/red_black_tree.hpp"
#include "iterators/map_iterator.hpp"
#include "iterators/reverse_iterator.hpp"
#include "utility/is_integral.hpp"
#include "utility/enable_if.hpp"
#include "utility/equal_lexcompare.hpp"

namespace ft {

	template <typename Key, typename Compare = std::less<Key>,
		typename Allocator = std::allocator<Key> >
	class set
	{	

	public:

		typedef Key																key_type;
		typedef Key																value_type;
		typedef std::size_t														size_type;
		typedef std::ptrdiff_t													difference_type;
		typedef Compare															key_compare;
		typedef Compare															value_compare;
		typedef Allocator														allocator_type;
		typedef typename Allocator::reference									reference;
		typedef typename Allocator::const_reference								const_reference;
		typedef typename Allocator::pointer										pointer;
		typedef typename Allocator::const_pointer								const_pointer;
		typedef ft::map_iterator<value_type>									iterator;
		typedef const iterator													const_iterator;
		typedef ft::reverse_iterator<iterator>									reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;
		typedef typename Allocator::template rebind<Node<value_type> >::other	alloc_node_rebind;

	private:

		allocator_type					alloc;
		alloc_node_rebind				alloc_node;
		Compare							comp;
		Rbtree<value_type>				tree;

	public:
	
		/*----------------------------------------------------------------------------*/
		/*---------------------------- MEMBER FUNCTIONS ------------------------------*/
		/*----------------------------------------------------------------------------*/

		explicit set(const Compare& comp = Compare(), const Allocator& alloc = Allocator()) :
							alloc(alloc), comp(comp), tree(Rbtree<value_type>()) {}

		template <typename InputIt>
		set(InputIt first, InputIt last, const Compare& comp = Compare(),
     			const Allocator& alloc = Allocator()) : alloc(alloc), comp(comp), tree(Rbtree<value_type>()) {
			for (; first != last; ++first) {
				placeHereNode(tree.getRoot(), *first);
			}
		}

		set(const set& other) : alloc(other.alloc), comp(other.comp), tree(Rbtree<value_type>()) {
			if (other.size()) {
				for (iterator it = other.begin(); it != other.end(); ++it) {
					placeHereNode(tree.getRoot(), *it);
				}
			}
		}

		~set() {
			clear();
		}

		set&	operator=(const set& other) {
			if (this != &other) {
				if (size()) {
					iterator it2;
					for (iterator it1 = begin(); it1 != end();) {
						it2 = it1;
						++it1;
						erase(it2);
					}
				}
				alloc = other.alloc;
				comp = other.comp;
				tree = Rbtree<value_type>();
				if (other.size()) {
					for (iterator it = other.begin(); it != other.end(); ++it) {
						placeHereNode(tree.getRoot(), *it);
					}
				}
			}
			return *this;
		}

		allocator_type	get_allocator() const {
			return alloc;
		}

		/*----------------------------------------------------------------------------*/
		/*--------------------------------- ITERATORS --------------------------------*/
		/*----------------------------------------------------------------------------*/

		iterator	begin() {
			return iterator(tree.getLeftmost());
		}

		const_iterator	begin() const {
			return iterator(tree.getLeftmost());
		}

		iterator	end() {
			return iterator(tree.getFakeroot());
		}

		const_iterator end() const {
			return iterator(tree.getFakeroot());
		}

		reverse_iterator rbegin() {
			return reverse_iterator(tree.getFakeroot());
		}

		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(tree.getFakeroot());
		}

		reverse_iterator rend() {
			return reverse_iterator(tree.getLeftmost());
		}

		const_reverse_iterator rend() const {
			return const_reverse_iterator(tree.getLeftmost());
		}

		/*----------------------------------------------------------------------------*/
		/*--------------------------------- CAPACITY ---------------------------------*/
		/*----------------------------------------------------------------------------*/

		bool	empty() const {
			if (tree.getSize()) {
				return false;
			}
			return true;
		}

		size_type	size() const {
			return tree.getSize();
		}

		size_type	max_size() const {
			return std::numeric_limits<difference_type>::max() / sizeof(Node<value_type>);
		}

		/*----------------------------------------------------------------------------*/
		/*--------------------------------- MODIFIERS --------------------------------*/
		/*----------------------------------------------------------------------------*/

		void clear() {
			if (size()) {
				iterator it2;
				for (iterator it1 = begin(); it1 != end();) {
					it2 = it1;
					++it1;
					erase(it2);
				}
			}
		}

		ft::pair<iterator, bool> insert(const value_type& value) {
			return placeHereNode(tree.getRoot(), value);
		}

		iterator	insert(iterator position, const value_type& val) {
			if (position == end()) {
				return (placeHereNode(tree.getRoot(), val)).first;
			}
			if (comp(val, *position)) {
				iterator prev(position);
				--prev;
				while (prev != end() && !comp(*prev, val)) {
					--position;
					--prev;
				}
			}
			else if (comp(*position, val)) {
				iterator next(position);
				++next;
				while (next != end() && !comp(val, *next)) {
					++position;
					++next;
				}
			}
			if (position != end() && !comp(*position, val) && !comp(val, *position)) {
				return position;
			}
			return placeHereNode(position.base(), val).first;
		}

		template<typename InputIt>
		void insert(InputIt first, InputIt last,
			typename ft::enable_if<! ft::is_integral<InputIt>::value>::type* = 0) {
			for (; first != last; ++first) {
				placeHereNode(tree.getRoot(), *first);
			}
		}

		void	erase(iterator position) {
			tree.deleteNode(position.base());
			destroyNode(position.base());
		}

		size_type	erase(const key_type& k) {
			if (eraseNode(k)) {
				return 1;
			}
			return 0;
		}

		void	erase(iterator first, iterator last) {
			iterator	tmp;

			for (; first != last;) {
				tmp = first;
				++first;
				erase(tmp);
			}
		}

		void	swap(set& other) {
			set	tmp = *this;
			*this = other;
			other = tmp;
		}

		/*----------------------------------------------------------------------------*/
		/*----------------------------------- LOOKUP ---------------------------------*/
		/*----------------------------------------------------------------------------*/


		size_type	count(const key_type& k) const {
			if (find(k) != end()) {
				return 1;
			}
			return 0;
		}

		iterator	find(const key_type& k) {
			Node<value_type>*	cur = tree.getRoot();

			while (cur) {
				if (!comp(k, *(cur->data))
					&& !comp(*(cur->data), k)) {
					return iterator(cur);
				}
				cur = comp(k, *(cur->data)) ? cur->left : cur->right;
			}
			return end();
		}

		const_iterator	find(const key_type& k) const {
			Node<value_type>*	cur = tree.getRoot();

			while (cur) {
				if (!comp(k, *(cur->data))
					&& !comp(*(cur->data), k)) {
					return const_iterator(cur);
				}
				cur = comp(k, *(cur->data)) ? cur->left : cur->right;
			}
			return end();
		}

		ft::pair<iterator, iterator>	equal_range(const key_type& k) {
			return ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k));
		}

		ft::pair<const_iterator, const_iterator>	equal_range(const key_type& k) const {
			return ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
		}

		iterator	lower_bound(const key_type& k) {
			Node<value_type>*	n = tree.getRoot(), *par;

			if (!tree.getSize() || comp(*(tree.getRightmost()->data), k)) {
				return end();
			}
			while (n) {
				if (!comp(k, *(n->data))
					&& !comp(*(n->data), k)) {
					return iterator(n);
				}
				par = n;
				n = comp(k, *(n->data)) ? n->left : n->right;
			}
			iterator	it(par);
			if (comp(*it, k)) {
				++it;
			}
			return it;
		}

		const_iterator	lower_bound(const key_type& k) const {
			Node<value_type>*	n = tree.getRoot(), *par;

			if (!tree.getSize() || comp(*(tree.getRightmost()->data), k)) {
				return end();
			}
			while (n) {
				if (!comp(k, *(n->data))
					&& !comp(*(n->data), k)) {
					return const_iterator(n);
				}
				par = n;
				n = comp(k, *(n->data)) ? n->left : n->right;
			}
			const_iterator	it(par);
			if (comp(*it, k)) {
				++it;
			}
			return it;
		}

		iterator	upper_bound(const key_type& k) {
			Node<value_type>*	n = tree.getRoot(), *par;

			if (!tree.getSize() || comp(*(tree.getRightmost()->data), k)) {
				return end();
			}
			while (n) {
				if (!comp(k, *(n->data))
					&& !comp(*(n->data), k)) {
					par = n;
					break;
				}
				par = n;
				n = comp(k, *(n->data)) ? n->left : n->right;
			}
			iterator	it(par);
			if (!comp(k, *it)) {
				++it;
			}
			return it;
		}

		const_iterator	upper_bound(const key_type& k) const {
			Node<value_type>*	n = tree.getRoot(), *par;

			if (!tree.getSize() || comp(*(tree.getRightmost()->data), k)) {
				return end();
			}
			while (n) {
				if (!comp(k, *(n->data))
					&& !comp(*(n->data), k)) {
					par = n;
					break;
				}
				par = n;
				n = comp(k, *(n->data)) ? n->left : n->right;
			}
			const_iterator	it(par);
			if (!comp(k, *it)) {
				++it;
			}
			return it;
		}

		key_compare	key_comp() const {
			return comp;
		}

		value_compare	value_comp() const {
			return comp;
		}

	private:

		Node<value_type>*	createNode(const value_type& val) {
			Node<value_type>* n = alloc_node.allocate(1);
			alloc_node.construct(n, val);

			return n;
		}

		void	destroyNode(Node<value_type>* n) {
			alloc_node.destroy(n);
			alloc_node.deallocate(n, 1);
		}

		Node<value_type>*	createPush(Node<value_type>* n, const value_type& val) {
			Node<value_type>*	res = createNode(val);

			res->parent = n;
			if (comp(val, *(n->data))) {
				n->left = res;
			}
			else {
				n->right = res;
			}
			tree.insertBalance(res);
			
			if (comp(val, *(tree.getLeftmost()->data))) {
				tree.setLeftmost(res);
			}
			else if (comp(*(tree.getRightmost()->data), val)) {
				tree.setRightmost(res);
			}
			return res;
		}

		ft::pair<iterator, bool>	placeHereNode(Node<value_type>* n, const value_type& val) {
			Node<value_type> *par;
			
			if (!tree.getSize()) {
				Node<value_type>*	res = createNode(val);
				tree.setRoot(res);
				return ft::make_pair(iterator(res), true);
			}
			
			while (n) {
				if (!comp(val, *(n->data))
					&& !comp(*(n->data), val)) {
					return ft::make_pair(iterator(n), false);
				}
				par = n;
				n = comp(val, *(n->data)) ? n->left : n->right;
			}
			return ft::make_pair(iterator(createPush(par, val)), true);
		}

		bool	eraseNode(const key_type& k) {
			Node<value_type>	*cur;

			if (!tree.getSize()) {
				return false;
			}

			cur = tree.getRoot();
			while (cur) {
				if (!comp(k, *(cur->data))
					&& !comp(*(cur->data), k)) {
					tree.deleteNode(cur);
					destroyNode(cur);
					return true;
				}
				cur = comp(k, *(cur->data)) ? cur->left : cur->right;
			}
			return false;
		}
	};
}

template <class Key, class Compare, class Alloc>
bool	operator==(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs) {
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()) && lhs.size() == rhs.size());
}

template <class Key, class Compare, class Alloc>
bool	operator!=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs) {
	return !(lhs == rhs);
}

template <class Key, class Compare, class Alloc>
bool	operator<(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class Compare, class Alloc>
bool	operator<=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs) {
	return !(rhs < lhs);
}

template <class Key, class Compare, class Alloc>
bool	operator>(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs) {
	return rhs < lhs;
}

template <class Key, class Compare, class Alloc>
bool	operator>=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs) {
	return !(lhs < rhs);
}

template< class Key, class Compare, class Alloc>
void swap(ft::set<Key,Compare,Alloc>& lhs, ft::set<Key,Compare,Alloc>& rhs) {
	lhs.swap(rhs);
}