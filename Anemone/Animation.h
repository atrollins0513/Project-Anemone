#pragma once

#include <vector>

namespace Anemone
{
	struct Frame
	{
		float u, v;

		float u_width, v_height;

		float frame_limit;

		Frame()
		{
			u = v = u_width = v_height = frame_limit = 0.0f;
		}

		Frame(float _u, float _v, float _u_width, float _v_height, float _frame_limit)
		{
			u = _u;
			v = _v;
			u_width = _u_width;
			v_height = _v_height;
			frame_limit = _frame_limit;
		}
	};

	class Animation
	{
	public:

		Animation();

		void update(double dt);

		void addFrame(Frame frame);

		const Frame& getCurrentFrame() const
		{
			return frames[frame_index];
		}

		void setCurrentFrame(unsigned int _frame_index);

		void reset();

	protected:
	private:

		double time;

		unsigned int frame_index;

		std::vector<Frame> frames;

	};
}
