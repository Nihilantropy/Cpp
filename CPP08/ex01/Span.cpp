#include "Span.hpp"

/*** parameterized constructor ***/
Span::Span(unsigned int N) : _maxSize(N)
{
    /* reserve N numbers in the container */
    _numbers.reserve(N);
}

/*** copy constructor ***/
Span::Span(const Span& other) : _numbers(other._numbers), _maxSize(other._maxSize) {}

/*** assignment operator ***/
Span& Span::operator=(const Span& other)
{
    if (this != &other)
    {
        _numbers = other._numbers;
        _maxSize = other._maxSize;
    }
    return *this;
}

/*** destructor ***/
Span::~Span() {}

/*** public methods ***/

/* add a single number to the Span (vector container) */
void Span::addNumber(int num)
{
    if (_numbers.size() >= _maxSize) {
        std::stringstream ss;
        ss << "Span is full: maximum capacity of " << _maxSize << " reached";
        throw std::overflow_error(ss.str());
    }
    _numbers.push_back(num);
}

/* Method to calculate the shortest span */
int Span::shortestSpan() const
{
    if (_numbers.size() < 2) {
        throw std::logic_error("Not enough numbers to calculate a span (need at least 2)");
    }
    
    std::vector<int> sorted = _numbers;
    std::sort(sorted.begin(), sorted.end());

    int minSpan = sorted[1] - sorted[0];
    for (size_t i = 1; i < sorted.size(); i++) {
        int currentSpan = sorted[i] - sorted[i - 1];
        if (currentSpan < minSpan) {
            minSpan = currentSpan;
        }
    }
    return minSpan;
}

/* Method to calculate the longest span */
int Span::longestSpan() const
{
    if (_numbers.size() < 2) {
        throw std::logic_error("Not enough numbers to calculate a span (need at least 2)");
    }
    
    int minElement = *std::min_element(_numbers.begin(), _numbers.end());
    int maxElement = *std::max_element(_numbers.begin(), _numbers.end());

    return maxElement - minElement;
}

/* Utility methods */
unsigned int Span::size() const {
    return _numbers.size();
}

unsigned int Span::capacity() const {
    return _maxSize;
}

bool Span::empty() const {
    return _numbers.empty();
}

bool Span::full() const {
    return _numbers.size() >= _maxSize;
}

void Span::clear() {
    _numbers.clear();
}

/* Access method with bounds checking */
int Span::at(unsigned int index) const {
    if (index >= _numbers.size()) {
        std::stringstream ss;
        ss << "Index " << index << " is out of bounds (size: " << _numbers.size() << ")";
        throw std::out_of_range(ss.str());
    }
    return _numbers[index];
}

/* Fill span with random numbers */
void Span::fillRandomly(int min, int max) {
    if (min >= max) {
        throw std::invalid_argument("Min value must be less than max value");
    }
    
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    while (_numbers.size() < _maxSize) {
        _numbers.push_back(min + std::rand() % (max - min + 1));
    }
}

/* Print all numbers (for debugging) */
void Span::print() const {
    std::cout << "Span [" << _numbers.size() << "/" << _maxSize << "]: ";
    for (size_t i = 0; i < _numbers.size(); ++i) {
        std::cout << _numbers[i];
        if (i < _numbers.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}