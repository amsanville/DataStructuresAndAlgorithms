#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#include<math.h>
#include<iostream>

/*
MyMath

This header file represents a collection of algorithms that play around with
the idea of using functions of functions in order to solve interesting
problems. Most of the problems solved here are your standard numerical
algorithms like root finders and ODE solvers and what not. However, I hope that
the work done here can be generalized in order to provide a framework for unit
tests.
*/


/*
Simple Real Function

Parent class meant to provide a way to pass functions around through the use of
functors and virtual function implementations. The idea is taht the operator()
acts as a stand in for f(x), which takes a double and returns a double. Then,
through inheritance, we can pass SimpleRealFunctions to other functions, like
binary search, and perform a general binary search.
*/
class SimpleRealFunction {
public:
	virtual double operator()(double x) const = 0;
};

/*
Test Function 0

Simple test case to check that the behavior of SimpleRealFunction is as expected.
*/
class TestFunction0 : public SimpleRealFunction {
public:
	double operator()(double x) const {
		return cos(x);
	}
};

/*
Binary Search

Uses the binary search to find a root between a and b for the function
implemented in the passed in SimpleRealFunction. The order of a and b does not
matter, just that a and b are different.

The binary search uses the idea that if a continuous function has a root, it
must change signs. Thus, by using a difference of signs, we can hone in on a
specific root. This method can only detect roots that actually cross the axis.

Parameters:
f - the function
a - one end point of the interval to search
b - the other end point of the interval to search
maxIter - the maximum number of iterations the algorithm should do before it
gives up
tol - the absolute difference from zero that we will tolerate on f, default
is 10^-6
Return - the location of the root, x, where |f(x)| < tol
*/
double binarySearch_func(SimpleRealFunction& f, double a, double b, int maxIter = 1000, double tol = pow(10., -6.)) {
	// Check that a != b
	if (a != b) {
		// Swap so there is only one algorithm
		if (b < a) {
			double temp = b;
			b = a;
			a = b;
		}

		// Perform binary search
		double fA = f(a);
		double fB = f(b);
		if (fA * fB <= 0.) {
			// Start the search
			bool done = false;	// Indicator for root found
			int currIter = 0;	// Current iteration
			double temp = 0.;	// Root test location
			double fTemp = 0.;	// Value of f at test location
			while (!done && currIter < maxIter) {
				temp = (a + b) / 2.;
				fTemp = f(temp);
				// If we've converged to within tolerance
				if (abs(temp) < tol) {
					done = true;
				}
				else {
					if (fA * fTemp <= 0.) {
						// b and the middle share the same sign
						b = temp;
						fB = fTemp;
					}
					else {
						// a and the middle share the same sign
						a = temp;
						fA = fTemp;
					}
				}
				currIter++;
			}
			return temp;
		}
		else {
			std::cout << "Error: cannot find root f(a) and f(b) need different signs." << std::endl;
		}
	}
	else {
		std::cout << "Error: a and b need to be different real numbers." << std::endl;
	}
}

/*
Newton's Method

Implements Newton's Method for root finding
*/
#endif