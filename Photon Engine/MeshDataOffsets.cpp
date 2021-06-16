#include "MeshDataOffsets.h"

namespace ph_engine {
	MeshDataHelper::MeshDataHelper():
		is_vert(false),
		is_norm(false),
		is_col(false),
		is_tex(false),
		is_ind(false) {};

	void MeshDataHelper::setVertex(uint offset, uint step) {
		is_vert = true;

		vertex.first = offset;
		vertex.second = step;
	}
	void MeshDataHelper::setNormal(uint offset, uint step) {
		is_norm = true;

		normal.first = offset;
		normal.second = step;
	}
	void MeshDataHelper::setColor(uint offset, uint step) {
		is_col = true;

		color.first = offset;
		color.second = step;
	}
	void MeshDataHelper::setTexture(uint offset, uint step) {
		is_tex = true;

		texture.first = offset;
		texture.second = step;
	}
	void MeshDataHelper::setIndex(uint offset, uint step) {
		is_ind = true;

		index.first = offset;
		index.second = step;
	}

	bool MeshDataHelper::hasVertex() { return is_vert; }
	bool MeshDataHelper::hasNormal() { return is_norm; }
	bool MeshDataHelper::hasColor() { return is_col; }
	bool MeshDataHelper::hasTexture() { return is_tex; }
	bool MeshDataHelper::hasIndex() { return is_ind; }

	std::pair<uint, uint> MeshDataHelper::getVertex() {
		if (is_vert)
			return vertex;
		else
			return std::pair<uint, uint>(0, 0);
	}
	std::pair<uint, uint> MeshDataHelper::getNormal() {
		if (is_norm)
			return normal;
		else
			return std::pair<uint, uint>(0, 0);
	}
	std::pair<uint, uint> MeshDataHelper::getColor() {
		if (is_col)
			return color;
		else
			return std::pair<uint, uint>(0, 0);
	}
	std::pair<uint, uint> MeshDataHelper::getTexture() {
		if (is_tex)
			return texture;
		else
			return std::pair<uint, uint>(0, 0);
	}
	std::pair<uint, uint> MeshDataHelper::getIndex() {
		if (is_ind)
			return index;
		else
			return std::pair<uint, uint>(0, 0);
	}
}