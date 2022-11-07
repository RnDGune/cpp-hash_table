// hash_tablle_array.cpp: определяет точку входа для приложения.
//


#include "hash_tablle_array.h"

int HashFunctionHorner (const std::string& str, int table_size, int key) {
	int hash_result = 0;
	for (int i = 0; str[i] != str.size();++i) {
		hash_result = (key * hash_result + str[i]) % table_size;
	}
	hash_result = (hash_result * 2 + 1) % table_size;
	return hash_result;
}


struct HashFunction1 {
	int operator()(const std::string& str, int table_size) {
		return HashFunctionHorner(str, table_size, table_size - 1);
	}
};
struct HashFunction2 {
	int operator()(const std::string& str, int table_size) {
		return HashFunctionHorner(str, table_size, table_size + 1);
	}
};



template <class T>
class HashTable {
public:
	HashTable() {
		buffer_size_ = DEFAULT_SIZE;
		size_ = 0;
		all_size_ = 0;
		arr_.resize(buffer_size_, nullptr);
	}

	void Resize() {
		all_size_ = 0;
		int past_buffer_size = buffer_size_;
		buffer_size_ *= 2;
		std::vector<Node*> tmp_arr(buffer_size_, nullptr);
		std::swap(arr_, tmp_arr);
		for (int i = 0; i < past_buffer_size; ++i) {
			if (tmp_arr[i] && tmp_arr[i]->state) {
				Add(tmp_arr[i]->value);
			}
		}
	}	
	/*
	* Перехеширования таблицы, нужно если скопилось много deleted элементов(state = false)
	*/
	void Rehash() {
		all_size_ = 0;
		std::vector<Node*> tmp_arr(buffer_size_, nullptr);
		std::swap(arr_, tmp_arr);
		for (int i = 0; i < past_buffer_size; ++i) {
			if (tmp_arr[i] && tmp_arr[i]->state) {
				Add(tmp_arr[i]->value);
			}
		}
	}
	
	bool Find(const T& value) {
		int h1 = HashFunction1(value, buffer_size_);
		int h2 = HashFunction2(value, buffer_size_);
		int i = 0;
		while (arr_[h1]!=nullptr && i<buffer_size_) {
			if (arr_[h1] == value && arr_[h1]->state) {
				return true;
			}
			h1 = (h1 + h2) % buffer_size_;
			++i;
		}
		return false;
	}

	void Remove(const T& value) {
		int h1 = HashFunction1(value, buffer_size_);
		int h2 = HashFunction2(value, buffer_size_);
		int i = 0;
		while (arr_[h1] != nullptr && i < buffer_size_) {
			if (arr_[h1] == value && arr_[h1]->state) {
				arr_[h1]->state = false;
				--size_;
			}
			h1 = (h1 + h2) % buffer_size_;
			++i;
		}

	}

	void Add(const T& value) {
		if (size_+1 > REHASH_COEFF*buffer_size_) {
			Resize();
		}
		else_if(all_size_ > 2*size_) {
			Rehash();
		}

		int h1 = HashFunction1(value, buffer_size_);
		int h2 = HashFunction2(value, buffer_size_);
		int i = 0;
		int first_deleted = -1; // скользкое место
		while (arr_[h1] != nullptr && i < buffer_size_) {
			if (arr_[h1]==value && arr_[h1]->state) {
				return;
			}
			if (!arr_[h1]->state && first_deleted == -1) {
				first_deleted = h1;
			}
			h1 = (h1 + h2) % buffer_size_;
			++i;
		}
		if (first_deleted == -1) {
			arr[h1] = new Node(value);
			++all_size_;
		}
		else {
			arr_[first_deleted]->value = value;
			arr_[first_deleted]->state = true;
		}
		++size;
	}
};












