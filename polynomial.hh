#ifndef __class_polynomial_hh__
#define __class_polynomial_hh__

#include <string>
#include <iostream>
#include <gsl/gsl_poly.h>

using namespace std;

/**
 * polynomial
 *
 * Author: Kevin Peter Hickerson
 * Date:   Feb 23, 2009
 */
//template<typename T>
class polynomial
{
private:
	unsigned _degree; // TODO support Larant polynomial?
	//T c*;
	double* _c;
  
public:
	polynomial() : _degree(0)
  	{
		// TODO this is dangerous (or is it?)
		_c = new double[1];
		_c[0] = 0;
	}		
  
	polynomial(unsigned degree) : _degree(degree) 
  	{
		_c = new double[_degree + 1];
		
		for (unsigned i = 0; i <= _degree; i++) 
			_c[i] = 0; 
	};
	
	polynomial(const polynomial& p)
		: _degree(p._degree)
	{
		_c = new double[_degree + 1];	
		for (int n = _degree; n >=0; n--)
			_c[n] = p._c[n];
	}
	
	polynomial(unsigned degree, double* coefficents) 
		: _degree(degree) 
  	{
		_c = new double[_degree + 1];
		//cout << "degree " << degree << "->" << _degree << endl;
		for (unsigned i = 0; i <= _degree; i++) 
			_c[i] = coefficents[i];
	};
	
	~polynomial() 
	{ 
		delete [] _c; // calls destructor of T
	};
	
	void set(int i, double value)
	{
		// TODO resize polynomial to be higher order if out of bounds
		//      which will fail if polynomial is const
		_c[i % (_degree+1)] = value;
	}
	
	double get(int n) const
	{
		return _c[n % (_degree+1)];
	}
	
	double evaluate(double t) const
	{
		double value = _c[_degree];
		for (int n = _degree-1; n >= 0; n--)
		{
			value = _c[n] + t * value;
        	//value *= t;
			//value += _c[n];
			cout << "n=" << n <<endl;
		}
		return value;
	}
	
	double derivative(double t) const
	{
		double value = _c[_degree];
		for (int n = _degree-1; n > 0; n--)
		{
        	value = _c[n] + n * t * value;
		}
		return value;
	}
	
	unsigned get_degree() const
	{
		return _degree;
	}
	// TODO define math operators
	
	// expecting an array of size degree
	int solve_real_roots(double* root)
	{
		cout << *this << endl;
		//cout << _degree <<endl;
		if (_degree == 0)
			return 0;
		else if (_degree == 1)
		{
			double a = _c[1];
			double b = _c[0];
			if (a)
			{
				root[0] = -b/a;
				return 1;
			}
			else
				return 0;
		}
		else if (_degree == 2)
			return gsl_poly_solve_quadratic(_c[2], _c[1], _c[0], root, root+1);
	}
	
	const polynomial& operator=(const polynomial& p)
	{
		_degree = p._degree;
		delete [] _c;
		_c = new double[_degree + 1];
	
		for (int n = _degree; n >=0; n--)
			_c[n] = p._c[n];
		
		return p;
	}
	
	polynomial& operator=(double d)
	{
		_degree = 0;
		delete [] _c;
		_c = new double[1];
		_c[0] = d;
		return *this;
	}
	
	polynomial& operator*=(double d)
	{
		for (int n = _degree; n >=0; n--)
			_c[n] *= d;
		return *this;
	}
	
	polynomial& operator+=(double d)
	{
		_c[0] += d;
		return *this;
	}
	
	polynomial& operator+=(const polynomial& p)
	{
		if (p._degree > _degree)
		{
			// must resize
			double* c = new double[p._degree + 1];
			for (int n = p._degree; n > _degree; n--)
				c[n] = p._c[n];
			for (int n = _degree; n >=0; n--)
				c[n] = _c[n] + p._c[n];
			_degree = p._degree;
			delete [] _c;
			_c = c;
		}
		else
		{
			for (int n = p._degree; n >=0; n--)
				_c[n] += p._c[n];
		}
		return *this;
	}
	
	friend ostream& operator<< (ostream& out, const polynomial& p)
	{
		for (int n = p._degree; n > 0; n--)
			out << p._c[n] << "*t^" << n << " + ";
		out << p._c[0];
	}
};


#endif
