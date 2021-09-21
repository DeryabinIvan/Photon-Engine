#include "MeshDataOffsets.h"

namespace ph_engine {
	MeshDataHelper::MeshDataHelper():
		has_vert(false),
		has_norm(false),
		has_color(false),
		has_texture(false),
		has_ind(false) {};

	void MeshDataHelper::setVertex(int offset, int step) {
		has_vert = true;

		vertex.first = offset;
		vertex.second = step;
	}
	void MeshDataHelper::setNormal(int offset, int step) {
		has_norm = true;

		normal.first = offset;
		normal.second = step;
	}
	void MeshDataHelper::setColor(int offset, int step) {
		has_color = true;

		color.first = offset;
		color.second = step;
	}
	void MeshDataHelper::setTexture(int offset, int step) {
		has_texture = true;

		texture.first = offset;
		texture.second = step;
	}
	void MeshDataHelper::setIndex(int offset, int step) {
		has_ind = true;

		index.first = offset;
		index.second = step;
	}

	void MeshDataHelper::setTextureRepeat(int times) {
		text_repeat = times;
	}

	bool MeshDataHelper::hasVertex() { return has_vert; }
	bool MeshDataHelper::hasNormal() { return has_norm; }
	bool MeshDataHelper::hasColor() { return has_color; }
	bool MeshDataHelper::hasTexture() { return has_texture; }
	bool MeshDataHelper::hasIndex() { return has_ind; }

	bool MeshDataHelper::hasRepeatTex() {
		return text_repeat > 0;
	}

	std::pair<int, int> MeshDataHelper::getVertex() {
		if (has_vert)
			return vertex;
		else
			return std::pair<int, int>(0, 0);
	}
	std::pair<int, int> MeshDataHelper::getNormal() {
		if (has_norm)
			return normal;
		else
			return std::pair<int, int>(0, 0);
	}
	std::pair<int, int> MeshDataHelper::getColor() {
		if (has_color)
			return color;
		else
			return std::pair<int, int>(0, 0);
	}
	std::pair<int, int> MeshDataHelper::getTexture() {
		if (has_texture)
			return texture;
		else
			return std::pair<int, int>(0, 0);
	}
	std::pair<int, int> MeshDataHelper::getIndex() {
		if (has_ind)
			return index;
		else
			return std::pair<int, int>(0, 0);
	}
int MeshDataHelper::getRepeatTimes() {
		return text_repeat;
	}
}