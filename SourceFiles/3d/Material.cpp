#include "Material.h"
#include <fstream>
#include <sstream>
#include "D3D12Common.h"
#include "Mesh.h"
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
			sprite = Sprite::Create(path + textureFilename);
		}
	}
	file.close();

	// �f�t�H���g�e�N�X�`���̃Z�b�g
	if(!sprite){ sprite = Sprite::Create("white1x1.png"); }

	// �萔�o�b�t�@����
	CreateBuffer(&constBuffer, &constMap, (sizeof(ConstBufferData) + 0xff) & ~0xff);

	constMap->ambient = ambient;
	constMap->diffuse = diffuse;
	constMap->specular = specular;
	constMap->tiling = { 1,1 };
	constMap->uvOffset = { 0,0 };
	constMap->color = { 1,1,1,1 };
}

void Material::Update()
{
	sprite->Update();
	constMap->tiling =
	{
		sprite->textureSize.x / sprite->size.x,
		sprite->textureSize.y / sprite->size.y
	};

	constMap->uvOffset =
	{
		sprite->textureLeftTop.x / sprite->size.x,
		sprite->textureLeftTop.y / sprite->size.y
	};

	constMap->color = sprite->color;
	constMap->ambient = ambient;
	constMap->diffuse = diffuse;
	constMap->specular = specular;
}

void Material::Draw()
{
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
	cmdList->SetGraphicsRootConstantBufferView(2, constBuffer->GetGPUVirtualAddress());
	// �V�F�[�_���\�[�X�r���[���Z�b�g
	cmdList->SetGraphicsRootDescriptorTable(0, sprite->GetGPUHandle());
}