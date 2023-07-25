#include "Material.h"
#include <fstream>
#include <sstream>
#include "D3D12Common.h"
#include "Mesh.h"
#include "Model.h"
using namespace std;

void LoadColorRGBStream(istringstream& stream, ColorRGB& color)
{
	Vector3 colorTemp;
	stream >> colorTemp.x;
	stream >> colorTemp.y;
	stream >> colorTemp.z;
	color.r = colorTemp.x;
	color.g = colorTemp.y;
	color.b = colorTemp.z;
}

void Material::Load(Mesh* mesh)
{
	ifstream file;
	file.open(mesh->directoryPath + mesh->materialFileName);
	assert(!file.fail());

	string line;
	while (getline(file, line))
	{
		istringstream line_stream(line);
		string key;
		getline(line_stream, key, ' ');

		if (key[0] == '\t') { key.erase(key.begin()); }
		if (key == "newmtl") { line_stream >> materialName; }
		if (key == "Ka") { LoadColorRGBStream(line_stream, ambient); }
		if (key == "Kd") { LoadColorRGBStream(line_stream, diffuse); }
		if (key == "Ks") { LoadColorRGBStream(line_stream, specular); }
		if (key == "map_Kd")
		{
			string textureFilename;
			line_stream >> textureFilename;
			string path = mesh->directoryPath;
			path.erase(path.begin(), path.begin() + 10);
			sprites[textureNum++] = Sprite::Create(path + textureFilename);
		}
	}
	file.close();

	// デフォルトテクスチャのセット
	for (auto& sprite : sprites) { if (!sprite) { sprite = Sprite::Create("white1x1.png"); } }

	// ブレンドテクスチャがデフォルトの場合、マスク値は使わない
	if (sprites[(size_t)TexType::Blend]->tex->fileName == "white1x1.png")
	{
		sprites[(size_t)TexType::Blend]->color.r = 0;
	}

	// 定数バッファ生成
	CreateBuffer(&constBuffer, &constMap, (sizeof(ConstBufferData) + 0xff) & ~0xff);

	constMap->ambient = ambient;
	constMap->diffuse = diffuse;
	constMap->specular = specular;
	for (auto& texTrans : constMap->texTrans)
	{
		texTrans.tiling = { 1,1 };
		texTrans.uvOffset = { 0,0 };
	}
	for (auto& color : constMap->color) { color = { 1,1,1,1 }; }
	for (size_t i = 0; i < constMap->maskPow.size(); i++)
	{
		constMap->maskPow[i] = sprites[(size_t)TexType::Blend + i]->color.r;
	}
}

void Material::Update()
{
	for (auto& sprite : sprites) { sprite->Update(); }

	for (size_t i = 0; i < constMap->texTrans.size(); i++)
	{
		constMap->texTrans[i].tiling =
		{
			sprites[i]->textureSize.x / sprites[i]->size.x,
			sprites[i]->textureSize.y / sprites[i]->size.y
		};

		constMap->texTrans[i].uvOffset =
		{
			sprites[i]->textureLeftTop.x / sprites[i]->size.x,
			sprites[i]->textureLeftTop.y / sprites[i]->size.y
		};
	}

	for (size_t i = 0; i < constMap->color.size(); i++) { constMap->color[i] = sprites[i]->color; }
	for (size_t i = 0; i < constMap->maskPow.size(); i++)
	{
		constMap->maskPow[i] = sprites[(size_t)TexType::Blend + i]->color.r;
	}
	constMap->ambient = ambient;
	constMap->diffuse = diffuse;
	constMap->specular = specular;
}

void Material::Draw()
{
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
	cmdList->SetGraphicsRootConstantBufferView((UINT)RootParamNum::Material, constBuffer->GetGPUVirtualAddress());
	// シェーダリソースビューをセット
	for (UINT i = 0; i < (UINT)TexType::Num; i++)
	{
		cmdList->SetGraphicsRootDescriptorTable(i, sprites[i]->GetGPUHandle());
	}
}