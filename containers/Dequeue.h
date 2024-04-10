#ifndef ALIEN_INVASTION_SIMULATOR_DEQUEUE_H
#define ALIEN_INVASTION_SIMULATOR_DEQUEUE_H
#include <initializer_list>
#include <iostream>

/**
 * Dequeue class
 * A double-ended queue implemented using a doubly linked list of a fake head, tail nodes to simplify the implementation
 * @tparam T the type of the data to store in the dequeue
 * @see Node
 *
 * Rule of five:
 * @see Dequeue::Node
 * @see Dequeue::Dequeue()
 * @see Dequeue::Dequeue(const std::initializer_list<T>&)
 * @see Dequeue::Dequeue(const Dequeue<T>&)
 * @see Dequeue::operator=(const Dequeue<T>&)
 * @see Dequeue::Dequeue(Dequeue<T>&&)
 * @see Dequeue::operator=(Dequeue<T>&&)
 * @see Dequeue::~Dequeue()
 *
 * Member functions:
 * @see Dequeue::push_front(T&)
 * @see Dequeue::push_back(T&)
 * @see Dequeue::pop_front(T&)
 * @see Dequeue::pop_back(T&)
 * @see Dequeue::peek_front(T&)
 * @see Dequeue::peek_back(T&)
 * @see Dequeue::is_empty()
 * @see Dequeue::clear()
 * @see Dequeue::print()
 * @see Dequeue::size()
 */
template<typename T>
class Dequeue {
    public:
        Dequeue();
        Dequeue(const std::initializer_list<T>& list);
        Dequeue(const Dequeue<T>& other);
        Dequeue<T>& operator=(const Dequeue<T>& other);
        Dequeue(Dequeue<T>&& other) noexcept;
        Dequeue<T>& operator=(Dequeue<T>&& other) noexcept;
        ~Dequeue();
        void push_front(const T &data);
        void push_back(const T &data);
        bool pop_front(T& data);
        bool pop_back(T& data);
        bool peek_front(T& data);
        bool peek_back(T& data);
        bool is_empty() const;
        void clear();
        void print() const;
        size_t size() const;
    private:
        struct Node {
            T data;
            Node* next;
            Node* prev;
            explicit Node(T data) : data(data), next(nullptr), prev(nullptr) {}
            Node(T data, Node* next, Node* prev) : data(data), next(next), prev(prev) {}
        };

        /**
         * data members
         * Fake head and tail nodes to simplify the implementation
         * size_t length to keep track of the number of elements in the dequeue
         */
        Node* head;
        Node* tail;
        size_t length;
        /**
         * Utility functions
         */
         bool is_moved() const;
};

template<typename T>
bool Dequeue<T>::is_moved() const {
    return head == nullptr && tail == nullptr;
}

template<typename T>
Dequeue<T> &Dequeue<T>::operator=(const Dequeue<T> &other) {
    if (this != &other) {
        Dequeue<T> temp(other);

        this->~Dequeue();
        *this = std::move(temp);
    }
    return *this;
}

template<typename T>
Dequeue<T>::Dequeue(const Dequeue<T> &other) {
    Node *iterator = other.head->next;
    Dequeue<T> temp;

    while (iterator != other.tail) {
        temp.push_back(iterator->data);
        iterator = iterator->next;
    }

    head = nullptr;
    tail = nullptr;
    length = 0;
    *this = std::move(temp);
}

template<typename T>
Dequeue<T> &Dequeue<T>::operator=(Dequeue<T> &&other) noexcept {
    if (this != &other) {
        this->~Dequeue();

        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(length, other.length);
    }
    return (*this);
}

template<typename T>
Dequeue<T>::Dequeue(Dequeue<T> &&other) noexcept {
    head = other.head;
    tail = other.tail;
    length = other.length;

    other.head = nullptr;
    other.tail = nullptr;
    other.length = 0;
}

template<typename T>
Dequeue<T>::Dequeue(const std::initializer_list<T> &list) {
    Dequeue<T> temp;

    for (const T &data : list) {
        temp.push_back(data);
    }

    head = nullptr;
    tail = nullptr;
    length = 0;
    *this = std::move(temp);
}

template<typename T>
Dequeue<T>::~Dequeue() {
    if (!is_moved()) {
        return;
    }
    clear();
    delete head;
    delete tail;

    head = nullptr;
    tail = nullptr;
    length = 0;
}

template<typename T>
size_t Dequeue<T>::size() const {
    return length;
}

template<typename T>
void Dequeue<T>::print() const {
    if (is_moved()) {
        return;
    }
    Node *current = head->next;
    if (is_empty()) {
        std::cout << "Dequeue is empty" << std::endl;
        return;
    }
    while (current != tail) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template<typename T>
void Dequeue<T>::clear() {
    if (is_moved()) {
        return;
    }
    while (!is_empty()) {
        T data;
        pop_front(data);
    }
}

template<typename T>
bool Dequeue<T>::peek_back(T &data) {
   if (is_moved() || is_empty()) {
       return false;
   }
    data = tail->prev->data;
     return true;
}

template<typename T>
bool Dequeue<T>::peek_front(T &data) {
   if (is_moved() || is_empty()) {
       return false;
   }
   data = head->next->data;
    return true;
}

template<typename T>
bool Dequeue<T>::pop_back(T &data) {
    if (is_moved() || is_empty()) {
        return false;
    }
    Node *to_del = tail->prev;

    data = to_del->data;
    tail->prev = to_del->prev;
    tail->prev->next = tail;

    delete to_del;
    to_del = nullptr;

    --length;
    return (true);
}

template<typename T>
bool Dequeue<T>::pop_front(T &data) {
    if (is_moved()) {
        return false;
    }
    Node *to_del = head->next;

    if (is_empty()) {
        return false;
    }

    data = to_del->data;
    head->next = to_del->next;
    head->next->prev = head;

    delete to_del;
    to_del = nullptr;

    --length;
    return (true);
}

template<typename T>
void Dequeue<T>::push_back(const T &data) {
    if (is_moved()) {
        return;
    }
    Node *new_node = new Node(data, tail, tail->prev);

    tail->prev->next = new_node;
    tail->prev = new_node;

    length++;
}

template<typename T>
void Dequeue<T>::push_front(const T &data) {
    if (is_moved()) {
        return;
    }
    Node *new_node = new Node(data, head->next, head);
    head->next->prev = new_node;
    head->next = new_node;

    ++length;
}

template<typename T>
bool Dequeue<T>::is_empty() const {
    if (is_moved()) {
        return true;
    }
    return head->next == tail && tail->prev == head;
}



template<typename T>
Dequeue<T>::Dequeue() : head(new Node(T())), tail(new Node(T())), length(0) {
    head->next = tail;
    tail->prev = head;
}
#endif //ALIEN_INVASTION_SIMULATOR_DEQUEUE_H
