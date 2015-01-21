#ifndef MESSAGE_H
#define MESSAGE_H

#include "Ball.h"

class Message
{
	public:
		Message();
		Message(Ball);
		Message(Ball, int,int);

		int GetType();
		Ball GetBall();
		int GetId();

		void SetType(int);
		void SetBall(Ball);

	private:
		int type;
		Ball message_ball;
		int id;
};

#endif
