#ifndef ALIEN_INVASTION_SIMULATOR_PRIORITYQUEUE_H
#define ALIEN_INVASTION_SIMULATOR_PRIORITYQUEUE_H
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <type_traits>

template <typename T, typename Compare = std::greater_equal<T>>

/**
 * Priority Queue class implemented using a Max Heap
 * it has constructor using initializer list
 * u can use the copy and move constructor and assignment operators
 * default capacity is 15 and it will be resized when by double capacity when it is full
 * @param T
 *
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
class PriorityQueue {
    public:
        PriorityQueue();
        PriorityQueue(const std::initializer_list<T>& list);
        ~PriorityQueue();
        PriorityQueue(const PriorityQueue<T, Compare>& other);
        PriorityQueue<T, Compare>& operator=(const PriorityQueue<T, Compare>& other);
        PriorityQueue(PriorityQueue<T, Compare>&& other) noexcept;
        PriorityQueue<T, Compare>& operator=(PriorityQueue<T, Compare>&& other) noexcept;
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
     * comparator: the comparator function that is used to compare the elements of the priority queue
     */
        T *data;
        size_t capacity_;
        size_t length;
        Compare comparator;
    /**
     * utility functions
     * to resize the array when it is full
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
        static size_t nearest_power_of_2(size_t n);

};

template<typename T, typename Compare>
PriorityQueue<T, Compare> &PriorityQueue<T, Compare>::operator=(PriorityQueue<T, Compare> &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    delete[] data;
    data = other.data;
    length = other.length;
    capacity_ = other.capacity_;
    comparator = other.comparator;
    other.data = nullptr;
    other.length = {};
    other.capacity_ = {};
    return *this;
}

template<typename T, typename Compare>
PriorityQueue<T, Compare>::PriorityQueue(PriorityQueue<T, Compare> &&other) noexcept {
    data = other.data;
    length = other.length;
    capacity_ = other.capacity_;
    comparator = other.comparator;
    other.data = nullptr;
    other.length = {};
    other.capacity_ = {};
}

template<typename T, typename Compare>
PriorityQueue<T, Compare> &PriorityQueue<T, Compare>::operator=(const PriorityQueue<T, Compare> &other) {
    if (this == &other) {
        return *this;
    }
    delete[] data;
    data = new T[other.capacity_];
    std::copy(other.data, other.data + other.length, data);
    length = other.length;
    capacity_ = other.capacity_;
    comparator = other.comparator;
    return *this;
}

template<typename T, typename Compare>
PriorityQueue<T, Compare>::PriorityQueue(const PriorityQueue<T, Compare> &other) :
        length(other.length), capacity_(other.capacity_) , comparator(other.comparator) {
    data = new T[capacity_];
    std::copy(other.data, other.data + length, data);
}

template<typename T, typename Compare>
size_t PriorityQueue<T, Compare>::nearest_power_of_2(size_t n) {
    size_t nearest_power_of_2 = 1;

    //default capacity is 15
    if (n < 15) {
        return 15;
    }
    //if is n is a power of 2, increment it by 1 to get the next power of 2 to be the capacity
    //bcs the tree is a complete binary tree so wee need to have the next power of 2
    if ((n & (n - 1)) == 0) {
        ++n;
    }
    while (nearest_power_of_2 < n) {
        nearest_power_of_2 <<= 1;
    }
    return nearest_power_of_2;

}


template<typename T, typename Compare>
/**
 * @brief Priority Queue constructor using initializer list
 * @tparam T
 * @param list
 * Description: Build the Heap O(n) starting from the first non-leaf node
 */
PriorityQueue<T, Compare>::PriorityQueue(const std::initializer_list<T> &list) {
    length = list.size();
    capacity_ = nearest_power_of_2(length);
    data = new T[capacity_]{};
    comparator = Compare();
    std::copy(list.begin(), list.end(), data);

    //Build heap O(n) starting from the first non-leaf node
    for (int i = length / 2 - 1; i >= 0; --i) {
        heapify_down(i);
    }
}

template<typename T, typename Compare>
PriorityQueue<T, Compare>::~PriorityQueue() {
    delete[] data;
    data = {};
    length = {};
    capacity_ = {};
}

template<typename T, typename Compare>
void PriorityQueue<T, Compare>::clear() {
    length = {};
}

template<typename T, typename Compare>
bool PriorityQueue<T, Compare>::peek(T &value) const {
    if (empty()) {
        return false;
    }
    value = data[0];
    return true;
}



template<typename T, typename Compare>
bool PriorityQueue<T, Compare>::is_empty() const {
    return length == 0;
}

template<typename T, typename Compare>
bool PriorityQueue<T, Compare>::pop(T &value) {
    if (empty()) {
        return (false);
    }
    value = data[0];
    data[0] = data[--length];
    heapify_down(0);
    return (true);
}


template<typename T, typename Compare>
void PriorityQueue<T, Compare>::push(const T &value) {
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

template<typename T, typename Compare>
void PriorityQueue<T, Compare>::print() const {
    if (empty()) {
        return;
    }

    if (std::is_pointer<T>::value) {
        for (size_t i = 0; i < length; i++) {
            if (data[i] != nullptr) {
                data[i]->print();
            }
        }
        return;
    }

    for_each(data, data + length, [](const T &value) {
        std::cout << value << " ";
    });
    std::cout << std::endl;
}
template<typename T, typename Compare>
bool PriorityQueue<T, Compare>::empty() const {
    return length == 0;
}

template<typename T, typename Compare>
size_t PriorityQueue<T, Compare>::size() const {
    return length;
}

template<typename T, typename Compare>
size_t PriorityQueue<T, Compare>::capacity() const {
    return capacity_;
}

template<typename T, typename Compare>
void PriorityQueue<T, Compare>::heapify_down(int index) {
    //if u have no left child, then you are a leaf no need to heapify down
    while (has_left_child(index)) {
        //we need to find the largest child to swap with the parent so check the left and the right if exists
        int largest_idx = get_left_child_idx(index);
        if (has_right_child(index) && comparator(data[get_right_child_idx(index)], data[get_left_child_idx(index)])) {
            largest_idx = get_right_child_idx(index);
        }
        if (comparator(data[index], data[largest_idx])) {
            break;
        } else {
            std::swap(data[index], data[largest_idx]);
        }
        index = largest_idx;
    }
}

template<typename T, typename Compare>
void PriorityQueue<T, Compare>::heapify_up(int index) {
    while (has_parent(index) && comparator(data[index], data[get_parent_idx(index)])) {
        std::swap(data[index], data[get_parent_idx(index)]);
        index = get_parent_idx(index);
    }
}

template<typename T, typename Compare>
int PriorityQueue<T, Compare>::get_parent_idx(int index) const {
    /*Root has no parent*/
    if (index == 0) {
        return -1;
    }
    return (index - 1) >> 1;
}

template<typename T, typename Compare>
bool PriorityQueue<T, Compare>::has_parent(int index) const {
    return get_parent_idx(index) >= 0;
}

template<typename T, typename Compare>
int PriorityQueue<T, Compare>::get_right_child_idx(int index) const {
   return ((index << 1) + 2);
}

template<typename T, typename Compare>
int PriorityQueue<T, Compare>::get_left_child_idx(int index) const {
    return ((index << 1) + 1);
}

template<typename T, typename Compare>
bool PriorityQueue<T, Compare>::has_right_child(int index) const {
    return (get_right_child_idx(index) < static_cast<int>(length));
}

template<typename T, typename Compare>
bool PriorityQueue<T, Compare>::has_left_child(int index) const {
    return (get_left_child_idx(index) < static_cast<int>(length));
}

template<typename T, typename Compare>
void PriorityQueue<T, Compare>::ensure_extra_capacity() {
    if (is_full()) {
        capacity_ = (capacity_ << 1) + 1;
        T *temp = new T[capacity_];
        std::copy(data, data + length, temp);
        delete[] data;
        data = temp;
    }
}

//what to add here it doesno wrok with the template i think it waits for the compat
template<typename T, typename Compare>
bool PriorityQueue<T, Compare>::is_full() const {
    return length == capacity_;
}

template<typename T, typename Compare>
/**
 * @brief Priority Queue default constructor
 * @tparam T
 * Description: default capacity is 15 2^4 - 1 complete binary tree
 */
PriorityQueue<T, Compare>::PriorityQueue() : data(new T[15]{}), capacity_(15), length(0), comparator(Compare()) {}

#endif //ALIEN_INVASTION_SIMULATOR_PRIORITYQUEUE_H