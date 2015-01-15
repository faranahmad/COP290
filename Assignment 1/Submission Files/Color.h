#ifndef COLOR_H
#define COLOR_H

// #include <vector>

class Color
{
	public:
		Color();
		Color(int,int,int);

		int GetR();
		int GetG();
		int GetB();

		void SetR(int);
		void SetG(int);
		void SetB(int);

		void SetRGB(int,int,int);
				
	private:
		int R;
		int G;
		int B;
};

// std::vector<Color> GoodColors;

#endif