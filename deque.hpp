#pragma once

template <typename T>
Deque<T>::Deque(size_t count) : vec_begin(count / 2), vec_end(count - (count / 2)) {}

template <typename T>
Deque<T>::Deque(const Deque& ob)
{
	if(!ob.empty())
	{
		for (int i = 0;i < ob.vec_begin.size();++i)
		{
			vec_begin[i] = ob.vec_begin[i];
		}

		for (int i = 0;i < ob.vec_end.size();++i)
		{
			vec_end[i] = ob.vec_end[i];
		}
	}
}

template <typename T>
Deque<T>::Deque(Deque&& ob)
{
	if (!ob.empty())
	{
		vec_begin = std::move(ob.vec_begin);
		vec_end = std::move(ob.vec_end);
	}
}

template <typename T>
Deque<T>::Deque(std::initializer_list<T> ob)
{
	for (auto it = ob.begin();it != ob.end(); ++it) {
		push_back(*it);
	}
}

template <typename T>
Deque<T>& Deque<T>::operator=(const Deque& rhs)
{
	if (this == &rhs) {
		return *this;
	}

	if (!rhs.empty())
	{
		vec_begin.clear();
		vec_end.clear();

		for (int i = 0;i < rhs.vec_begin.size();++i)
		{
			vec_begin[i] = rhs.vec_begin[i];
		}

		for (int i = 0;i < rhs.vec_end.size();++i)
		{
			vec_end[i] = rhs.vec_end[i];
		}
	}
	return *this;
}

template <typename T>
Deque<T>& Deque<T>::operator=(Deque&& rhs)
{
	if (!rhs.empty())
	{
		vec_begin.clear();
		vec_end.clear();
		vec_begin = std::move(rhs.vec_begin);
		vec_end = std::move(rhs.vec_end);
	}
	return *this;
}

template <typename T>
Deque<T>& Deque<T>::operator=(std::initializer_list<T> ob)
{
	for (auto it = ob.begin();it != ob.end(); ++it) {
		push_back(*it);
	}
}

template <typename T>
Deque<T>::~Deque() {
	clear();
}

template <typename T>
typename Deque<T>::Iterator Deque<T>::insert(Iterator pos, const T& val)
{
	int count1{};
	int count2{};

	if (pos == begin()) 
	{
		push_front(val);
		return begin();
	}

	Deque::Iterator it(vec_begin, vec_end, &(*(vec_begin.begin())));
	if (pos == it)
	{
		vec_begin.insert(++vec_begin.begin(), val);
		return it;
	}
	
	for (Deque::Iterator it = begin(); it != end(); ++it)
	{
		if (pos == it && count1 <= vec_begin.size() - 1)
		{
			vec_begin.resize(vec_begin.size() + 1);
			for (int i = vec_begin.size() - 2; i >= count1; --i)
			{
				vec_begin[i + 1] = vec_begin[i];
			}
			vec_begin[vec_begin.size() - 1 - count1] = val;
			return it;
		}

		if (pos == it)
		{
			if (count2 == 0)
			{
				vec_end.insert(vec_end.begin(), val);
				return it;
			}

			vec_end.resize(vec_end.size() + 1);
			for (int i = vec_end.size() - 2; i >= count2 - 1; --i)
			{
				vec_end[i + 1] = vec_end[i];
			}
			vec_end[count2] = val;
			return it;
		}
		++count1;

		if (count1 > vec_begin.size()) {
			++count2;
		}
	}
}

template <typename T>
typename Deque<T>::Iterator Deque<T>::erase(Iterator pos)
{
	int count1{};
	int count2{};
	for (Deque::Iterator it = begin(); it != end(); ++it)
	{
		if (pos == it && count1 <= vec_begin.size() - 1)
		{
			if(count1 == 0)
			{
				pop_front();
				return it;
			}
			else if(count1 == vec_begin.size() - 1)
			{
				vec_begin.erase(vec_begin.begin());
				return it;
			}
			else
			{
				for (int i = count1; i < vec_begin.size() - 1; ++i)
				{
					vec_begin[vec_begin.size() - 1 - count1] = vec_begin[vec_begin.size() - 1 - count1 - 1];
					++count1;
				}
				vec_begin.erase(vec_begin.begin());
				return it;
			}
		}

		if (pos == it)
		{
			if (count2 == 0)
			{
				vec_end.erase(vec_end.begin());
				return it;
			}
			else if (count2 == vec_end.size() - 1)
			{
				vec_end.erase(--vec_end.end());
			}
			else
			{
				for (int i = count2; i < vec_end.size() - 1; ++i)
				{
					vec_end[i] = vec_end[i + 1];
				}
				vec_end.erase(--vec_end.end());
				return it;
			}
		}
		++count1;

		if (count1 > vec_begin.size()) {
			++count2;
		}
	}
}

template <typename T>
void Deque<T>::push_back(const T& val) {
	vec_end.push_back(val);
}

template <typename T>
void Deque<T>::push_back(T&& val) {
	vec_end.push_back(std::move(val));
}

template <typename T>
void Deque<T>::push_front(const T& val) {
	vec_begin.push_back(val);
}

template <typename T>
void Deque<T>::push_front(T&& val) {
	vec_begin.push_back(std::move(val));
}

template <typename T>
void Deque<T>::pop_back() {
	vec_end.pop_back();
}

template <typename T>
void Deque<T>::pop_front() {
	vec_begin.pop_back();
}

template <typename T>
void Deque<T>::assign(size_t count, const T& val)
{
	if (!(vec_begin.empty()) && count > vec_begin.size())
	{
		for (int i = vec_begin.size() - 1; i >= 0; --i)
		{
			vec_begin[i] = val;
		}

		for (int i = 0;i < (count - vec_begin.size());++i)
		{
			vec_end[i] = val;
		}
	}

	if (!(vec_begin.empty()) && vec_end.empty() && count < vec_begin.size())
	{
		for (int i = vec_begin.size() - 1; i >= (vec_begin.size() - count); --i)
		{
			vec_begin[i] = val;
		}
	}

	if (vec_begin.empty() && !(vec_end.empty()) && count < vec_end.size())
	{
		for (int i = 0;i <= vec_end.size() - count;++i)
		{
			vec_end[i] = val;
		}
	}
}

template <typename T>
void Deque<T>::shrink_to_fit()
{
	if (!(vec_begin.empty) && !(vec_end.empty()))
	{
		vec_begin.shrink_to_fit();
		vec_end.shrink_to_fit();
	}
	else if (vec_begin.empty()) {
		vec_begin.shrink_to_fit();
	}
	else {
		vec_end.shrink_to_fit();
	}
}

template <typename T>
T& Deque<T>::at(size_t index)
{
	if (index > vec_begin.size() + vec_end.size()) {
		throw std::out_of_range("");
	}

	if (index < vec_begin.size()) {
		return vec_begin[(vec_begin.size() - 1) - index];
	}
	else {
		return vec_end[index - vec_begin.size()];
	}
}
template <typename T>
const T& Deque<T>::at(size_t index) const 
{
	if (index > vec_begin.size() + vec_end.size()) {
		throw std::out_of_range("");
	}

	if (index < vec_begin.size()) {
		return vec_begin[(vec_begin.size() - 1) - index];
	}
	else {
		return vec_end[index - vec_begin.size()];
	}
}

template <typename T>
T& Deque<T>::operator[](size_t index) 
{
	if (index < vec_begin.size()) {
		return vec_begin[(vec_begin.size() - 1) - index];
	}
	
	if(index < vec_begin.size() + vec_end.size()) {
		return vec_end[index - vec_begin.size()];
	}
}

template <typename T>
const T& Deque<T>::operator[](size_t index) const
{
	if (index < vec_begin.size()) {
		return vec_begin[(vec_begin.size() - 1) - index];
	}

	if (index < vec_begin.size() + vec_end.size()) {
		return vec_end[index - vec_begin.size()];
	}
}

template<typename T>
T& Deque<T>::front() 
{
	if (vec_begin.size() != 0) {
		return vec_begin.back();
	}
	else {
		return vec_end.front();
	}
}

template<typename T>
const T& Deque<T>::front() const
{
	if (vec_begin.size() != 0) {
		return vec_begin.back();
	}
	else {
		return vec_end.front();
	}
}

template<typename T>
T& Deque<T>::back() 
{
	if (vec_end.size() != 0) {
		return vec_end.back();
	}
	else {
		return vec_begin.front();
	}	
}

template<typename T>
const T& Deque<T>::back() const 
{
	if (vec_end.size() != 0) {
		return vec_end.back();
	}
	else {
		return vec_begin.front();
	}
}
	
template <typename T>
void Deque<T>::print()
{
	for (int i = vec_begin.size() - 1; i >= 0 ; --i) {
		std::cout << vec_begin[i] << "  ";
	}

	for (int j = 0;j < vec_end.size(); ++j) {
		std::cout << vec_end[j] << "  ";
	}
}

template <typename T>
void Deque<T>::resize(size_t new_cap) {
	vec_end.resize(new_cap);
}

template <typename T>
void Deque<T>::resize(size_t new_cap, const T& val) {
	vec_end.resize(new_cap, val);
}

template <typename T>
bool Deque<T>::empty() const noexcept
{
	if (vec_begin.empty() && vec_end.empty()) {
		return true;
	}
	return false;
}

template <typename T>
size_t Deque<T>::size() const noexcept {
	return vec_begin.size() + vec_end.size();
}

template <typename T>
void Deque<T>::clear()
{
	if (!empty())
	{
		vec_begin.clear();
		vec_end.clear();
	}
	else if (vec_begin.empty()) {
		vec_end.clear();
	}
	else {
		vec_begin.clear();
	}
}

template <typename T>
typename Deque<T>::Iterator Deque<T>::begin() noexcept
{
	if (!vec_begin.empty())
	{
		Iterator it(vec_begin, vec_end, &(*(--vec_begin.end())));
		return it;
	}
	else if (!vec_end.empty())
	{
		Iterator it(vec_begin, vec_end, &(*(vec_end.begin())));
		return it;
	}
	else
	{
		Iterator it(vec_begin, vec_end, nullptr);
		return it;
	}
} 

template <typename T>
typename const Deque<T>::Iterator Deque<T>::cbegin() const noexcept
{
	if (!vec_begin.empty())
	{
		Iterator it(vec_begin, vec_end, &(*(--vec_begin.end())));
		return it;
	}
	else if (!vec_end.empty())
	{
		Iterator it(vec_begin, vec_end, &(*(vec_end.begin())));
		return it;
	}
	else
	{
		Iterator it(vec_begin, vec_end, nullptr);
		return it;
	}
}

template <typename T>
typename Deque<T>::Iterator Deque<T>::end() noexcept
{
	if (!vec_end.empty())
	{
		Iterator it(vec_begin, vec_end, (vec_end.data() + vec_end.size()));
		return it;
	}
	else if (!vec_begin.empty())
	{
		Iterator it(vec_begin, vec_end, ((vec_begin.data() + vec_begin.size() - 1) - vec_begin.size()));
		return it;
	}
	else
	{
		Iterator it(vec_begin, vec_end, nullptr);
		return it;
	}
}

template <typename T>
typename const Deque<T>::Iterator Deque<T>::cend() const noexcept
{
	if (!vec_end.empty())
	{
		Iterator it(vec_begin, vec_end, (vec_end.data() + vec_end.size()));
		return it;
	}
	else if (!vec_begin.empty())
	{
		Iterator it(vec_begin, vec_end, ((vec_begin.data() + vec_begin.size() - 1) - vec_begin.size()));
		return it;
	}
	else
	{
		Iterator it(vec_begin, vec_end, nullptr);
		return it;
	}
}

template <typename T>
bool Deque<T>::Iterator::operator==(const Iterator& ob) const {
	return m_it == ob.m_it;
}

template <typename T>
bool Deque<T>::Iterator::operator!=(const Iterator& ob) const {
	return !(*this == ob);
}

template <typename T>
typename const T& Deque<T>::Iterator::operator*() const {
	return *(m_it);
}

template <typename T>
typename T& Deque<T>::Iterator::operator[](size_t index) {
	return m_it[index];
}

template <typename T>
typename Deque<T>::Iterator& Deque<T>::Iterator::operator++()
{
	if (!m_vec1.empty() && !m_vec2.empty())
	{
		if (m_it == &(*(m_vec1.begin())))
		{
			m_it = &(*(m_vec2.begin()));
			found = true;
			return *this;
		}
		else if (found)
		{
			++m_it;
			return *this;
		}
		else
		{
			--m_it;
			return *this;
		}
	}
	else if (m_vec1.empty())
	{
		++m_it;
		return *this;
	}
	else
	{
		--m_it;
		return *this;
	}
}

template <typename T>
typename const Deque<T>::Iterator Deque<T>::Iterator::operator++(int)
{
	if (!m_vec1.empty() && !m_vec2.empty())
	{
		if (m_it == &(*(m_vec1.begin())))
		{
			const Deque::Iterator oldvalue = *this;
			m_it = &(*(m_vec2.begin()));
			found = true;
			return oldvalue;
		}
		else if (found)
		{
			const Deque::Iterator oldvalue = *this;
			++(*this);
			return oldvalue;
		}
		else
		{
			const Deque::Iterator oldvalue = *this;
			--(*this);
			return oldvalue;
		}
	}
	else if (m_vec1.empty())
	{
		const Deque::Iterator oldvalue = *this;
		++(*this);
		return oldvalue;
	}
	else
	{
		const Deque::Iterator oldvalue = *this;
		--(*this);
		return oldvalue;
	}
}

template <typename T>
typename Deque<T>::Iterator& Deque<T>::Iterator::operator--()
{
	found = false;
	if (!m_vec1.empty() && !m_vec2.empty())
	{
		if (m_it == &(*(m_vec2.begin())))
		{
			m_it = &(*(m_vec1.begin()));
			found = true;
			return *this;
		}
		if (found)
		{
			++m_it;
			return *this;
		}
		else
		{
			--m_it;
			return *this;
		}
	}
	else if (m_vec1.empty())
	{
		--m_it;
		return *this;
	}
	else
	{
		++m_it;
		return *this;
	}
}

template <typename T>
typename const Deque<T>::Iterator Deque<T>::Iterator::operator--(int)
{
	found = false;
	if (!m_vec1.empty() && !m_vec2.empty())
	{
		if (m_it == &(*(m_vec2.begin())))
		{
			const Deque::Iterator oldvalue = *this;
			m_it = &(*(m_vec1.begin()));
			found = true;
			return oldvalue;
		}
		if (found)
		{
			const Deque::Iterator oldvalue = *this;
			++(*this);
			return oldvalue;
		}
		else
		{
			const Deque::Iterator oldvalue = *this;
			--(*this);
			return oldvalue;
		}
	}
	else if (m_vec1.empty())
	{
		const Deque::Iterator oldvalue = *this;
		--(*this);
		return oldvalue;
	}
	else
	{
		const Deque::Iterator oldvalue = *this;
		++(*this);
		return oldvalue;
	}
}

template <typename T>
typename Deque<T>::Iterator& Deque<T>::Iterator::operator+=(size_t diff)
{
	int count{};
	if (!m_vec1.empty() && !m_vec2.empty())
	{
		while (true)
		{
			if (m_it == &(*(m_vec1.begin()))) 
			{
				m_it = &(*(m_vec2.begin()));
				found = true;
				++count;
				if (count == diff) {
					return *this;
				}
			}
			++count;

			if (found) {
				++m_it;
			}
			else {
				--m_it;
			}

			if (count == diff) {
				return *this;
			}
		}
	}
	else if (m_vec1.empty())
	{
		m_it += diff;
		return *this;
	}
	else
	{
		m_it -= diff;
		return *this;
	}
}

template <typename T>
typename Deque<T>::Iterator& Deque<T>::Iterator::operator-=(size_t diff)
{
	int count{};
	if (!m_vec1.empty() && !m_vec2.empty())
	{
		while (true)
		{
			if (m_it == &(*(m_vec2.begin())))
			{
				m_it = &(*(m_vec1.begin()));
				found = true;
				++count;
				if (count == diff) {
					return *this;
				}
			}
			++count;

			if (found) {
				++m_it;
			}
			else {
				--m_it;
			}

			if (count == diff) {
				return *this;
			}
		}
	}
	else if (m_vec1.empty())
	{
		m_it += diff;
		return *this;
	}
	else
	{
		m_it -= diff;
		return *this;
	}
}
