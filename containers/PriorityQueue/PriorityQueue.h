#ifndef ALIEN_INVASTION_SIMULATOR_PRIORITYQUEUE_H
#define ALIEN_INVASTION_SIMULATOR_PRIORITYQUEUE_H
#include <iostream>
#include <initializer_list>
#include <algorithm>

/**
 * Priority Queue class implemented using a Max Heap
 * it has constructor using initializer list
 * u can use the copy and move constructor and assignment operators
 * default capacity is 15 and it will be resized when by double capacity when it is full
 * @tparam T
 * available operations:
 * @see empty()
 * @see size()
 * @see push(const T&)
 * @see pop(T&)
 * @see peek(T&)
 * @see clear()
 * @see print()
 * @see capacity()
 */
template <typename T>
class PriorityQueue {
    public:
        PriorityQueue();
        PriorityQueue(const std::initializer_list<T>& list);
        ~PriorityQueue();
        PriorityQueue(const PriorityQueue<T>& other);
        PriorityQueue<T>& operator=(const PriorityQueue<T>& other);
        PriorityQueue(PriorityQueue<T>&& other) noexcept;
        PriorityQueue<T>& operator=(PriorityQueue<T>&& other) noexcept;
        void push(const T &value);
        bool pop(T &value);
        bool peek(T &value) const;
        bool empty() const;
        size_t size() const;
        void print() const;
        void clear();
        size_t capacity() const;
        bool is_empty() const;
    private:
    /**
     * data: pointer to the array that stores the elements of the priority queue
     * capacity_: the maximum number of elements that the priority queue can store
     * length: the number of elements currently in the priority queue
     */
        T *data;
        size_t capacity_;
        size_t length;
    /**
     * utility functions
     * to resizie the array when it is full
     * checking if the priority queue is full
     * to get the index of the parent, left child and right child of a node
     * to check if a node has a parent, left child and right child
     * to heapify up and down
     */
        void heapify_up(int index);
        void heapify_down(int index);
        int get_parent_idx(int index) const;
        int get_left_child_idx(int index) const;
        int get_right_child_idx(int index) const;
        bool has_parent(int index) const;
        bool has_left_child(int index) const;
        bool has_right_child(int index) const;
        void ensure_extra_capacity();
        bool is_full() const;
        size_t nearest_power_of_2(size_t n) const;
};

template<typename T>
PriorityQueue<T> &PriorityQueue<T>::operator=(PriorityQueue<T> &&other) noexcept {
    if (this != &other) {
        this->~PriorityQueue();
        std::swap(data, other.data);
        std::swap(capacity_, other.capacity_);
        std::swap(length, other.length);
    }
    return *this;
}

template<typename T>
PriorityQueue<T>::PriorityQueue(PriorityQueue<T> &&other) noexcept {
    data = other.data;
    capacity_ = other.capacity_;
    length = other.length;
    other.data = nullptr;
    other.capacity_ = 0;
    other.length = 0;
}

template<typename T>
PriorityQueue<T> &PriorityQueue<T>::operator=(const PriorityQueue<T> &other) {
    if (this != &other) {
        PriorityQueue<T> temp(other);
        //temp is a copy of other
        //this data is null and capacity_ is 0 and length is 0
        this->~PriorityQueue();
        std::swap(data, temp.data);
        std::swap(capacity_, temp.capacity_);
        std::swap(length, temp.length);
    }
    return *this;
}

template<typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T> &other) :data(new T[other.capacity_]),
    capacity_(other.capacity_), length(other.length) {
    std::copy(other.data, other.data + length, data);
}

template<typename T>
size_t PriorityQueue<T>::nearest_power_of_2(size_t n) const {
    size_t nearest_power_of_2 = 1;

    //default capacity is 15
    if (n < 15) {
        return 15;
    }
    //if is n is a power of 2, increament it by 1 to get the next power of 2 to be the capacity
    //bcs the tree is a complete binary tree so wee need to have the next power of 2
    if ((n & (n - 1)) == 0) {
        ++n;
    }
    while (nearest_power_of_2 < n) {
        nearest_power_of_2 <<= 1;
    }
    return nearest_power_of_2;
}

template<typename T>
/**
 * @brief Priority Queue constructor using initializer list
 * @tparam T
 * @param list
 * Description: Build the Heap O(n) starting from the first non-leaf nodeap
 */
PriorityQueue<T>::PriorityQueue(const std::initializer_list<T> &list) {
    length = list.size();
    capacity_ = nearest_power_of_2(length);
    data = new T[capacity_];
    std::copy(list.begin(), list.end(), data);

    //Build heap O(n) starting from the first non-leaf node
    for (int i = length / 2 - 1; i >= 0; --i) {
        heapify_down(i);
    }
}

template<typename T>
PriorityQueue<T>::~PriorityQueue() {
    delete[] data;
    data = {};
    length = {};
    capacity_ = {};
}

template<typename T>
void PriorityQueue<T>::clear() {
    length = {};
}

template<typename T>
bool PriorityQueue<T>::peek(T &value) const {
    if (empty()) {
        return false;
    }
    value = data[0];
    return true;
}

template<typename T>
bool PriorityQueue<T>::is_empty() const {
   return length == 0;
}

template<typename T>
bool PriorityQueue<T>::pop(T &value) {
    if (empty()) {
        return false;
    }
    value = data[0];
    data[0] = data[--length];
    heapify_down(0);
    return true;
}

template<typename T>
void PriorityQueue<T>::push(const T &value) {
    if (data == nullptr) {
        //in case of move constructor the user used it after moving
        //it shouldn't be used after moving so this shouldn't be called but just in case it is called
        return;
    }
    ensure_extra_capacity();
    data[length] = value;
    heapify_up(length);
    ++length;
}

template<typename T>
void PriorityQueue<T>::print() const {
    std::for_each(data, data + length, [](const T& value) {
        std::cout << value << " ";
    });
    std::cout << std::endl;
}

template<typename T>
bool PriorityQueue<T>::empty() const {
   return length == 0;
}

template<typename T>
size_t PriorityQueue<T>::size() const {
    return length;
}


template<typename T>
size_t PriorityQueue<T>::capacity() const {
    return capacity_;
}

template<typename T>
void PriorityQueue<T>::heapify_down(int index) {
    //if u have no left child, then you are a leaf no need to heapify down
    while (has_left_child(index)) {
        //we need to find the largest child to swap with the parent so checke the left and the right if exists
        int largest_idx = get_left_child_idx(index);
        if (has_right_child(index) && data[get_right_child_idx(index)] > data[get_left_child_idx(index)]) {
            largest_idx = get_right_child_idx(index);
        }
        if (data[index] > data[largest_idx]) {
            break;
        } else {
            std::swap(data[index], data[largest_idx]);
        }
        index = largest_idx;
    }
}

template<typename T>
void PriorityQueue<T>::heapify_up(int index) {
    while (has_parent(index) && data[index] > data[get_parent_idx(index)]) {
        std::swap(data[index], data[get_parent_idx(index)]);
        index = get_parent_idx(index);
    }
}

template<typename T>
int PriorityQueue<T>::get_parent_idx(int index) const {
    /*Root has no parent*/
    if (index == 0) {
        return -1;
    }
    return (index - 1) >> 1;
}

template<typename T>
bool PriorityQueue<T>::has_parent(int index) const {
    return get_parent_idx(index) >= 0;
}

template<typename T>
int PriorityQueue<T>::get_right_child_idx(int index) const {
   return 2 * index + 2;
}

template<typename T>
int PriorityQueue<T>::get_left_child_idx(int index) const {
    return 2 * index + 1;
}

template<typename T>
bool PriorityQueue<T>::has_right_child(int index) const {
    return get_right_child_idx(index) < static_cast<int>(length);
}

template<typename T>
bool PriorityQueue<T>::has_left_child(int index) const {
    return get_left_child_idx(index) < static_cast<int>(length);
}

template<typename T>
void PriorityQueue<T>::ensure_extra_capacity() {
    if (is_full()) {
        capacity_ = (capacity_ << 1) + 1;
        T *temp = new T[capacity_];
        std::copy(data, data + length, temp);
        delete[] data;
        data = temp;
    }
}

template<typename T>
bool PriorityQueue<T>::is_full() const {
    return length == capacity_;
}

template<typename T>
/**
 * @brief Priority Queue default constructor
 * @tparam T
 * Description: default capacity is 15 2^4 - 1 complete binary tree
 */
PriorityQueue<T>::PriorityQueue() :data(new T[15]), capacity_(15), length(0) {}

#endif //ALIEN_INVASTION_SIMULATOR_PRIORITYQUEUE_H
