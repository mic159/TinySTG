#ifndef TINY_MATHEMATICS_HPP
#define TINY_MATHEMATICS_HPP

class Mathmatics
{
public:
	static int Sin8(unsigned char theta);
	static int Cos8(unsigned char theta);
private:
	static const short sin_table[256];
	Mathmatics(void);
	Mathmatics(Mathmatics&);
	Mathmatics& operator = (Mathmatics&);
};

#endif
