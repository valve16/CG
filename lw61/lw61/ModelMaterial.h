#pragma once

#include "Material.h"
#include "TextureMap.h"

class CModelMaterial : private boost::noncopyable
{
public:
	CModelMaterial();

	// Добавить текстурную карту №1 к материалу
	CTextureMap & AddTextureMap1(GLuint texture);

	// Связана ли с материалом текстурная карта №1?
	bool HasTextureMap1()const;

	// Получить текстурную карту №1
	CTextureMap const& GetTextureMap1()const;
	CTextureMap & GetTextureMap1();

	CTextureMap& AddTextureMap2(GLuint texture);
	bool HasTextureMap2() const;
	CTextureMap const& GetTextureMap2() const;
	CTextureMap& GetTextureMap2();

	// Получить материал OpenGL
	CMaterial & GetMaterial();
	CMaterial const& GetMaterial()const;

	// Материал видим с лицевой и нелицевой грани?
	bool IsTwoSided()const;
	void SetTwoSided(bool value);
private:
	CTextureMap	m_textureMap1;
	CTextureMap m_textureMap2;
	CMaterial m_material;
	bool m_twoSided;
};
