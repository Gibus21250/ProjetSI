#pragma once
class Drawable
{
public:
	virtual void draw() = 0;

	struct m_material_infos
	{
		float
			ambient[4],
			diffuse[4],
			specular[4],
			shininess,
			emission[4];
	};
};

