#include "..\Anemone\Animation.h"

namespace ae
{
	Animation::Animation()
	{
		time = 0.0;
		frame_index = 0;
	}

	void Animation::update(double dt)
	{
		time += dt;

		double current_frame_limit = frames[frame_index].frame_limit;

		if (time >= current_frame_limit)
		{
			time -= current_frame_limit;

			if (frame_index + 1 < frames.size())
			{
				frame_index++;
			}
			else
			{
				frame_index = 0;
			}
		}
	}

	void Animation::addFrame(Frame frame)
	{
		frames.push_back(frame);
	}

	void Animation::setCurrentFrame(unsigned int _frame_index)
	{
		if (_frame_index < frames.size())
		{
			frame_index = _frame_index;
		}
	}

	void Animation::reset()
	{
		time = 0.0;
		setCurrentFrame(0);
	}
};