#ifndef COLOR_H
#define COLOR_H

// #include <vector>

class Color
{
	public:
		Color();
		Color(int,int,int);

		double GetR();
		double GetG();
		double GetB();

		void SetR(int);
		void SetG(int);
		void SetB(int);

		void SetRGB(int,int,int);
				
	private:
		double R;
		double G;
		double B;
};

// std::vector<Color> GoodColors;

#endif