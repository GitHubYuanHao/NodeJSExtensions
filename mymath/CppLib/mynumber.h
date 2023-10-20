#include <stdint.h>

class MyNumber
{
public:
	MyNumber() = default;
	~MyNumber() = default;
public:
	static double add(double a, double b);
	static double sub(double a, double b);
	static double mul(double a, double b);
	static double div(double a, double b);
};
