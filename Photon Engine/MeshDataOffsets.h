#pragma once

#include "Config.h"

namespace ph_engine {
	class PHOTONENGINE_API MeshDataHelper {
		bool has_vert, has_norm, has_color, has_texture, has_ind;
		std::pair<int, int> vertex, normal, color, texture, index;
		int text_repeat = 0;

		public:
			MeshDataHelper();

			void setVertex(int offset, int step);
			void setNormal(int offset, int step);
			void setColor(int offset, int step);
			void setTexture(int offset, int step);
			void setIndex(int offset, int step);
			void setTextureRepeat(int times);

			bool hasVertex();
			bool hasNormal();
			bool hasColor();
			bool hasTexture();
			bool hasIndex();
			bool hasRepeatTex();

			std::pair<int, int> getVertex();
			std::pair<int, int> getNormal();
			std::pair<int, int> getColor();
			std::pair<int, int> getTexture();
			std::pair<int, int> getIndex();
			int getRepeatTimes();
	};
}
