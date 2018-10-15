#pragma once

#include "Anemone.h"

#include <vector>

namespace Anemone
{
	struct Frame
	{
		AE_FLOAT u, v;

		AE_FLOAT u_width, v_height;

		AE_FLOAT frame_limit;

		Frame()
		{
			u = v = u_width = v_height = frame_limit = 0.0f;
		}

		Frame(AE_FLOAT _u, AE_FLOAT _v, AE_FLOAT _u_width, AE_FLOAT _v_height, AE_FLOAT _frame_limit)
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

		void update(AE_DOUBLE dt);

		void addFrame(Frame frame);

		const Frame& getCurrentFrame() const
		{
			return frames[frame_index];
		}

		void setCurrentFrame(AE_UINT _frame_index);

		void reset();

	protected:
	private:

		AE_DOUBLE time;

		AE_UINT frame_index;

		std::vector<Frame> frames;

	};
}
