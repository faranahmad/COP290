#ifndef COLOR_H
#define COLOR_H

class Color
{
	public:
		Color();

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

#endif