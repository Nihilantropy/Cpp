# C++ STL Module - Exercises 00, 01, and 02

This repository contains the implementations for three exercises of the C++ STL module. The goal is to solve each exercise using an appropriate Standard Template Library (STL) container. Each exercise has specific container requirements, and understanding the best choice for each problem is key to the correct and efficient implementation.

## Exercise 00: Bitcoin Exchange

### Problem Overview:
In this exercise, we are tasked with creating a program that calculates the value of a certain amount of Bitcoin on a specified date. The program will read a CSV database containing Bitcoin prices over time, then read another file to get the dates and amounts to convert. If the exact date is not found, the program must return the closest earlier date and multiply the amount of Bitcoin by the exchange rate.

### Container Choice: `std::map`

#### Why `std::map`?
- **Key-Value Pairs**: We need to associate each date (key) with a corresponding exchange rate (value). A `std::map` is perfect for this because it allows us to store key-value pairs where the key is the date and the value is the exchange rate.
  
- **Automatic Ordering**: `std::map` stores elements in a sorted order based on the key. Since the date is the key, this feature allows us to efficiently find the closest earlier date when the exact date is not present.
  
- **Efficient Search**: `std::map` provides logarithmic time complexity (`O(log n)`) for searching and inserting elements, which is efficient for handling large datasets, such as the one in this exercise.

Using `std::map` guarantees that we can quickly look up a date and its corresponding exchange rate and find the nearest valid date when necessary.

---

## Exercise 01: Reverse Polish Notation

### Problem Overview:
The goal of this exercise is to evaluate expressions written in Reverse Polish Notation (RPN), where numbers and operators are presented in a postfix format. We need to perform arithmetic operations using these tokens and output the correct result.

### Container Choice: `std::stack`

#### Why `std::stack`?
- **LIFO Structure**: Reverse Polish Notation naturally follows a Last In, First Out (LIFO) principle, making `std::stack` the ideal container. When processing RPN:
  - We push operands (numbers) onto the stack.
  - We pop operands off the stack when encountering an operator, apply the operation, and push the result back onto the stack.
  - At the end of the expression, the stack will contain the final result.
  
- **Simple Interface**: `std::stack` is designed for this exact use case, where the primary operations are `push` and `pop`. It provides an intuitive and straightforward interface for handling RPN calculations.

Using `std::stack` ensures that the operations are efficiently managed and the logic is clear and simple to implement.

---

## Exercise 02: PmergeMe

### Problem Overview:
In this exercise, we need to sort a sequence of positive integers using the merge-insert sort algorithm (Ford-Johnson algorithm). The program must perform the sort on two different containers and compare the performance between them.

### Container Choices: `std::vector` and `std::deque`

#### Why `std::vector`?
- **Efficient Random Access**: `std::vector` provides constant-time access to elements, which is essential for efficient sorting algorithms. Merge sort, in particular, benefits from fast random access to the elements, making `std::vector` a natural choice.
  
- **Dynamic Sizing**: `std::vector` grows dynamically as needed, which makes it well-suited for handling large sequences of integers, such as the ones in this exercise (up to 3000 elements).
  
- **Cache-Friendly**: `std::vector` stores elements contiguously in memory, making it cache-friendly and generally more efficient in terms of both space and access speed compared to other containers like `std::list`.

#### Why `std::deque`?
- **Efficient Insertions at Both Ends**: `std::deque` is a double-ended queue that allows efficient insertions and deletions at both ends of the container. While it doesn't provide constant-time random access like `std::vector`, it can still be useful in certain sorting algorithms that involve modifying both ends of the data.

- **Comparison**: Using `std::deque` alongside `std::vector` allows us to compare the performance of two different container types with similar functionality. This comparison will highlight the differences in performance for the sorting algorithm on both containers.

By using `std::vector` and `std::deque`, we can implement the merge-insert sort algorithm on two different containers and compare the performance in a meaningful way.

---

## Conclusion

The choice of containers is crucial in implementing the solutions to these exercises. The containers selected for each exercise (`std::map`, `std::stack`, `std::vector`, and `std::deque`) are well-suited to their respective problems, ensuring efficient solutions while adhering to the requirements of each exercise.

- **Exercise 00**: `std::map` for storing key-value pairs of dates and exchange rates, ensuring efficient lookups and closest date search.
- **Exercise 01**: `std::stack` for evaluating Reverse Polish Notation expressions using the LIFO principle.
- **Exercise 02**: `std::vector` and `std::deque` for sorting a sequence of integers using the merge-insert sort algorithm, with a focus on performance comparison.

These choices ensure that the exercises are implemented correctly and efficiently while adhering to the constraints of using one container per exercise.
