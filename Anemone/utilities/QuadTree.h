#pragma once

#include <vector>
#include <assert.h>
#include <type_traits>

#include "..\Math.h"

namespace ae
{

	struct QuadBase
	{
		virtual vec4 getQuad() = 0;
	};

	template<typename T>
	class QuadTree
	{
	public:

		// 0:NW, 1:NE, 2:SE, 3:SW

		QuadTree()
		{
			level = 0;
			max_level = 0;
			pos = 0.0f;
			size = 0.0f;
			for (int i = 0; i < 4; i++)
			{
				quads[i] = nullptr;
			}
		}

		QuadTree(vec2 _pos, vec2 _size, int _level, int _max_level)
		{
			pos = _pos;
			size = _size;
			level = _level;
			max_level = _max_level;
			if (level < max_level)
			{
				vec2 hsize = size / 2.0f;
				quads[0] = new QuadTree(pos + vec2(0.0f, hsize.y), hsize, level + 1, max_level);
				quads[1] = new QuadTree(pos + hsize, hsize, level + 1, max_level);
				quads[2] = new QuadTree(pos + vec2(hsize.x, 0.0f), hsize, level + 1, max_level);
				quads[3] = new QuadTree(pos, hsize, level + 1, max_level);
			}
		}

		void add(T* e)
		{
			static_assert(std::is_base_of<QuadBase, T>::value, "T must be derived from QuadBase.");

			if (level == max_level)
			{
				elements.push_back(e);
				return;
			}
			
			vec4 dim = e->getQuad();
			for (int i = 0; i < 4; i++)
			{
				if (quads[i]->contains(dim))
				{
					quads[i]->add(e);
				}
			}
		}

		bool contains(vec4 dim)
		{
			return (dim.x >= pos.x && dim.x + dim.z <= pos.x + size.x && dim.y >= pos.y && dim.y + dim.w <= pos.y + size.y);
		}

		bool getElementsAtLocation(ae::vec2 pos, std::vector<T*>& result)
		{
			if (level == max_level)
			{
				result = elements;
				return true;
			}

			for (int i = 0; i < 4; i++)
			{
				if (quads[i]->contains(vec4(pos, { 1.0f, 1.0f })))
				{
					if (quads[i]->getElementsAtLocation(pos, result))
					{
						return true;
					}
				}
			}
			return false;
		}

		void getMaxLevelQuads(std::vector<QuadTree*>& q)
		{
			if (level == max_level)
			{
				q.push_back(quads[0]);
				q.push_back(quads[1]);
				q.push_back(quads[2]);
				q.push_back(quads[3]);
				return;
			}

			for (int i = 0; i < 4; i++)
			{
				quads[i]->getMaxLevelQuads(q);
			}
		}

		const std::vector<T*>& getElements()
		{
			return elements;
		}

		void clear()
		{
			if (level == max_level)
			{
				elements.clear();
				return;
			}

			for (int i = 0; i < 4; i++)
			{
				quads[i]->clear();
			}
		}

	private:

		QuadTree* quads[4];

		std::vector<T*> elements;

		int level;

		int max_level;

		vec2 pos;

		vec2 size;

	};

};