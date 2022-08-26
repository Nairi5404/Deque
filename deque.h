#pragma once
#include <vector>

template <typename T>
class Deque
{
public:
	Deque() = default;
	explicit Deque(size_t);
	Deque(const Deque&);
	Deque(Deque&&);
	Deque(std::initializer_list<T>);
	~Deque();

public:
	Deque& operator=(const Deque&);
	Deque& operator=(Deque&&);
	Deque& operator=(std::initializer_list<T>);

public:
	class Iterator
	{
	friend class Deque;
	public:
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

	public:
		Iterator(std::vector<T>& vec1, std::vector<T>& vec2, T* it) :m_vec1(vec1), m_vec2(vec2), m_it(it) {}

	public:
		bool operator==(const Iterator&) const;
		bool operator!=(const Iterator&) const;
		const T& operator*() const;
		T& operator[](size_t);
		Iterator& operator++();
		const Iterator operator++(int);
		Iterator& operator--();
		const Iterator operator--(int);
		Iterator& operator+=(size_t);
		Iterator& operator-=(size_t);

	private:
		T* m_it{};
		std::vector<T>& m_vec1{};
		std::vector<T>& m_vec2{};
		bool found = false;
	};

public:
	Iterator begin() noexcept;
	const Iterator cbegin() const noexcept;
	Iterator end() noexcept;
	const Iterator cend() const noexcept;
	
public:
	void assign(size_t, const T&);
	T& at(size_t);
	const T& at(size_t) const;
	T& operator[](size_t);
	const T& operator[](size_t) const;
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
	bool empty() const noexcept;
	size_t size() const noexcept;
	void shrink_to_fit();

public:
	Iterator insert(Iterator, const T&);
	Iterator erase(Iterator);
	void push_back(const T&);
	void push_back(T&&);
	void push_front(const T&);
	void push_front(T&&);
	void pop_back();
	void pop_front();
	void resize(size_t);
	void resize(size_t, const T&);
	void clear();
	void print();

private:
	std::vector<T> vec_begin;
	std::vector<T> vec_end;
};

#include "deque.hpp"