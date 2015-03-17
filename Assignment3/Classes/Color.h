#ifndef COLOR_H
#define COLOR_H

class Color
{
	public:
		Color();
		Color(int,int,int);

		float GetR();
		float GetG();
		float GetB();

		void SetR(int);
		void SetG(int);
		void SetB(int);

		void SetRGB(int,int,int);
				
	private:
		float R;
		float G;
		float B;
};

#endif