# Data Structures and Algorithms
This repository stores a collection of data structures and algorithms that I'm writing to learn:
A.) How they work
B.) Exactly how they are implemented in C++
I'm using this as an opportunity to both learn the algorithms and C++ language features. The repository contains the following:
* Data Structures
* Discrete Search Algorithms
* Sorting Algorithms
* Mathematical Algorithms
Most of these things can be found in other libraries or even just the standard template library, so I'm not breaking ground on anything new. It's more for my education than anything. I'm very much a learn by doing type of person, hence why I'm writing these structures myself. 

## Data Structures
Data structures are backend fundamentals, so I figure I should play around with the exact details of implementing some of the most commonly used data structures.
### Array List with a Shadow Array
This data structure is based on C++'s `vector` or Java's `ArrayLists`. The idea is that it is a list class (container that stores things linearly) using an array at the backend. One of the key features of this class over just default arrays is that it should be able to change size. A basic implementation of that type of class can be found in https://github.com/amsanville/MIT-CS-6.096-Intro-to-C-Assignment-3 (one of my other repositories) where I implement such a class specifically for the Point class also implemented there. The assignment though, makes a point of mentioning the fact taht resizing the array and copying everything all at once is bad for time complexity (worst

### Linked List

## Searches
These searches are for searching through structures with some sort of organization. For example, if you have a sorted list, can you find a specific item? The goal always to beat the linear search algorithm, i.e. just visit every item and see if it's the item you're looking for.
###

## Sorts



## Mathematical Algorithms
By higher education training, I'm an applied math major with a strong emphasis in numerics. Since my area of application was mechanical engineering, this meant doing a lot of MatLab. In this library, I use many of the built-in features of C++ to recreate some of the better features of MatLab, like the root finding algorithm `fzero` and the ordinary differential equation solver `ode45`. I make no claims that my algorithms are state of the art or competitive. However, I do plan to use this as an opportunity to learn exactly how C++ does stuff like function handles through functors and lambda functions.
###