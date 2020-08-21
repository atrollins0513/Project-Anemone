#include "..\..\Anemone\utilities\Animation.h"

namespace ae
{
	void Animation::update(double dt)
	{
		time += dt;

		double current_frame_limit = frames[frame_index].limit;

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

	const Frame& Animation::getCurrentFrame() const
	{
		return frames[frame_index];
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