#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <deque>
#include <iterator>

/* MutantStack: A stack with iterator support */
/* Header implementation allowed for function template */
template <typename T>
class MutantStack : public std::stack<T> {
public:
    /* Typedefs for iterator support */
    /**
     * Why deque container?
     * We use std::deque for iterator implementation in MutantStack because:
     * 
     * 1 - std::deque is the default underlying container for std::stack.
     * 2 - std::deque provides efficient operations and full iterator support (random access and bidirectional).
     * 3 - This allows MutantStack to extend std::stack by providing iterator-based functionality without reinventing the wheel.
     */
    typedef typename std::deque<T>::iterator iterator;
    typedef typename std::deque<T>::const_iterator const_iterator;
    typedef typename std::deque<T>::reverse_iterator reverse_iterator;
    typedef typename std::deque<T>::const_reverse_iterator const_reverse_iterator;

    /* Orthodox Canonical Form */
    MutantStack() : std::stack<T>() {}
    MutantStack(const MutantStack& other) : std::stack<T>(other) {}
    MutantStack& operator=(const MutantStack& other) {
        if (this != &other) {
            std::stack<T>::operator=(other);
        }
        return *this;
    }
    ~MutantStack() {}

    /* Iterator support */
    /**
     * Why c?
     * std::stack has a protected member named c, which represents the underlying container it uses to store its elements.
     * Since MutantStack inherits from std::stack, it can access c directly because c is protected.
     */
    iterator begin() { return this->c.begin(); }
    iterator end() { return this->c.end(); }
    const_iterator begin() const { return this->c.begin(); }
    const_iterator end() const { return this->c.end(); }
    reverse_iterator rbegin() { return this->c.rbegin(); }
    reverse_iterator rend() { return this->c.rend(); }
    const_reverse_iterator rbegin() const { return this->c.rbegin(); }
    const_reverse_iterator rend() const { return this->c.rend(); }
};

/* TPP implementation */
// #include "MutantStack.tpp"
#endif
