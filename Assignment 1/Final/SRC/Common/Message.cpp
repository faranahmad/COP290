#include "Message.h"

Message::Message()
{
	// Creates a message having a default ball
	type=0;
	message_ball=Ball();
	id=0;
}

Message::Message(Ball b1)
{
	// Sets the default type of the message to be 0
	type=0;
	message_ball=b1;
}

Message::Message(Ball b1, int type1, int ballid1)
{
	// Creates a message based on the ball, id and type
	type=type1;
	message_ball=b1;
	id=ballid1;
}

int Message::GetType()
{
	return type;
}

Ball Message::GetBall()
{
	return message_ball;
}

int Message::GetId()
{
	return id;
}

void Message::SetType(int type1)
{
	type=type1;
}

void Message::SetBall(Ball ball1)
{
	message_ball=ball1;
}
