#include <vector>
#include <iostream>
#include <assert.h>
#include <string>
#include <list>
#include <sstream>

template <typename T>
class Set {
	std::list<T> *table;
	int table_size;

public:
	Set(int set_size);
	~Set() { };

	void set_insert(T element);
	int hash_function(T element);
	T set_remove(T element);
	bool set_is_member(T element);
	void set_display();
	static Set set_union(Set set1, Set set2);
	static Set set_intersection(Set set1, Set set2);
	static Set set_difference(Set set1, Set set2);
};

template<typename T>
Set<T>::Set(int set_size) {
		table_size = set_size;
		table = new std::list<T>[table_size];
}


template<typename T>
int Set<T>::hash_function(T element) {

	std::ostringstream temp;
	temp << element;
	std::string str_el = temp.str();

	int sum = 0;
	for(int i = 0; str_el[i] != '\0'; i++) {
		sum += str_el[i];
	}

	return sum%table_size;
}

template<typename T>
Set<T> Set<T>::set_difference(Set set1, Set set2) {


	for(int index = 0; index < set1.table_size; index++) {
			
		for(auto it1 = set1.table[index].begin(); 
			it1 != set1.table[index].end(); it1++) {

			if(set2.set_is_member(*it1)) {
				T temp = *it1;
				it1--;
				set1.set_remove(temp);
			}

		}
	}
	
	return set1;
}


template<typename T>
Set<T> Set<T>::set_union(Set set1, Set set2) {

	for(int i = 0; i < set2.table_size; i++) {
			
		for(auto it2 : set2.table[i])
			if(!set1.set_is_member(it2))
				set1.set_insert(it2);
	}

	return set1;
}


template<typename T>
Set<T> Set<T>::set_intersection(Set set1, Set set2) {

	for(int index = 0; index < set1.table_size; index++) {
			
		for(auto it1 = set1.table[index].begin(); 
			it1 != set1.table[index].end(); it1++) {

			if(!set2.set_is_member(*it1)) {
				T temp = *it1;
				it1--;
				set1.set_remove(temp);
			}

		}
	}

	return set1;
}

template <typename T>
void Set<T>::set_insert(T element) {

	if(!set_is_member(element)) {
		int index = hash_function(element);
		table[index].push_back(element);
	}
}

template <typename T>
T Set<T>::set_remove(T element) {

	int index = hash_function(element);

	for(auto it = table[index].begin(); 
		it != table[index].end(); it++)
		if(*it == element) {
			table[index].erase(it);
			return element;
		}

	return element;
}

template <typename T>
bool Set<T>::set_is_member(T element) {

	int index = hash_function(element);
	for(T el : table[index])
		if(el == element)
			return true;

	return false;
}


template <typename T>
void Set<T>::set_display() {

	for(int i = 0; i < table_size; i++) {
		for(auto x : table[i])
			std::cout << x << ", ";
	}

	std::cout << "\n";
}

int main(int argc, char const *argv[])
{

	if(argc == 1) {	return 0; }

	std::string arg1(argv[1]);
	if(arg1 == "integer") {
		
		Set<int> set(argc-1);
		for(int i = 2; i < argc; i++) {

			set.set_insert(atoi(argv[i]));
		}

		set.set_display();

	} else if(arg1 == "string") {

		Set<std::string> set(argc-1);
		for(int i = 2; i < argc; i++) {

			std::string arg(argv[i]);
			set.set_insert(arg);
		}

		set.set_display();

	} else {

		Set<int> set(argc-1);
		for(int i = 1; i < argc; i++) {

			set.set_insert(atoi(argv[i]));
		}

		set.set_display();

	}

	return 0;
}