#pragma once

#include <vector>

namespace ae
{
	struct Frame
	{

		float u				{ 0.0f };
		float v				{ 0.0f };
		float uw			{ 0.0f };
		float vh			{ 0.0f };
		float limit			{ 0.0f };
		unsigned int index	{ 0 };

		Frame(float _u, float _v, float _uw, float _vh, float _limit) : limit(_limit), u(_u), v(_v), uw(_uw), vh(_vh), index(0) { }

		Frame(unsigned int _index, float _limit) : limit(_limit), u(0.0f), v(0.0f), uw(0.0f), vh(0.0f), index(_index) { }

	};

	class Animation
	{
	public:

		bool update(double dt);

		void addFrame(Frame frame);

		const Frame& getCurrentFrame() const;

		void setCurrentFrame(unsigned int _frame_index);

		void reset();

	private:

		double time					{ 0.0 };

		unsigned int frame_index	{ 0 };

		std::vector<Frame> frames;

	};
}
