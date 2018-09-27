#pragma once

#include "Anemone.h"

#include <vector>

#include "Frame.h"

namespace Anemone
{
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
