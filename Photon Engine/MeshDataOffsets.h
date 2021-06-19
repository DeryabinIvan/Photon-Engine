#pragma once

#include "Config.h"

namespace ph_engine {
	class PHOTONENGINE_API MeshDataHelper {
		bool has_vert, has_norm, has_color, has_texture, has_ind;
		std::pair<uint, uint> vertex, normal, color, texture, index;

		public:
			MeshDataHelper();

			void setVertex(uint offset, uint step);
			void setNormal(uint offset, uint step);
			void setColor(uint offset, uint step);
			void setTexture(uint offset, uint step);
			void setIndex(uint offset, uint step);

			bool hasVertex();
			bool hasNormal();
			bool hasColor();
			bool hasTexture();
			bool hasIndex();

			std::pair<uint, uint> getVertex();
			std::pair<uint, uint> getNormal();
			std::pair<uint, uint> getColor();
			std::pair<uint, uint> getTexture();
			std::pair<uint, uint> getIndex();
	};
}
