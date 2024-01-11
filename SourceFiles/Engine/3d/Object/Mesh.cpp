#include "Mesh.h"
#include "D3D12Common.h"
#include <fstream>
#include <sstream>
using namespace std;
using namespace WristerEngine;
using namespace _3D;

void LoadVector3Stream(istringstream& stream, Vector3& vec)
{
	stream >> vec.x;
	stream >> vec.y;
	stream >> vec.z;
}

void Mesh::CalculateSmoothedVertexNormals()
{
	for (auto& itr : smoothData)
	{
		// �e�ʗp�̋��ʒ��_�R���e�i
		std::vector<UINT16>& v = itr.second;
		// �S���_�̖@���𕽋ς���
		Vector3 normal;
		for (UINT16 index : v) { normal += Normalize(vertices[index].normal); }
		normal = Normalize(normal / (float)v.size());
		// ���ʖ@�����g�p����S�Ă̒��_�f�[�^�ɏ�������
		for (UINT16 index : v) { vertices[index].normal = normal; }
	}
}

void Mesh::LoadOBJ(const std::string& modelName_, bool isSmooth_)
{
	modelName = modelName_;
	isSmooth = isSmooth_;
	const string FILENAME = modelName + ".obj";
	const string DIRECTORY_PATH = "Resources/models/" + modelName + "/";

	ifstream file;
	file.open(DIRECTORY_PATH + FILENAME);
	assert(!file.fail());

	vector<Vector3> positions, normals;
	vector<Vector2> texcoords;
	int indexCountTex = 0;
	string line;

	while (getline(file, line))
	{
		istringstream line_stream(line);
		string key;
		getline(line_stream, key, ' ');

		// �}�e���A���ǂݍ���
		if (key == "mtllib")
		{
			string filename;
			line_stream >> filename;
			directoryPath = DIRECTORY_PATH;
			materialFileName = filename;
		}
		// ���_���W�ǂݍ���
		if (key == "v")
		{
			Vector3 position{};
			LoadVector3Stream(line_stream, position);
			positions.emplace_back(position);
		}
		// �e�N�X�`�����W�ǂݍ���
		if (key == "vt")
		{
			Vector2 texcoord{};
			line_stream >> texcoord.x;
			line_stream >> texcoord.y;
			texcoord.y = 1.0f - texcoord.y;
			texcoords.emplace_back(texcoord);
		}
		// �@���x�N�g���ǂݍ���
		if (key == "vn")
		{
			Vector3 normal{};
			LoadVector3Stream(line_stream, normal);
			normals.emplace_back(normal);
		}
		// �|���S���f�[�^�ǂݍ���
		if (key == "f")
		{
			string index_string;
			int faceIndexCount = 0;

			while (getline(line_stream, index_string, ' '))
			{
				istringstream index_stream(index_string);
				unsigned short indexPosition, indexNormal, indexTexcoord;
				index_stream >> indexPosition;
				index_stream.seekg(1, ios_base::cur); // �X���b�V�����΂�
				index_stream >> indexTexcoord;
				index_stream.seekg(1, ios_base::cur);
				index_stream >> indexNormal;

				// ���_�f�[�^�̒ǉ�
				Mesh::VertexData vertex;
				vertex.pos = positions[(size_t)indexPosition - 1];
				vertex.normal = normals[(size_t)indexNormal - 1];
				vertex.uv = texcoords[(size_t)indexTexcoord - 1];
				vertices.emplace_back<Mesh::VertexData&>(vertex);
				if (isSmooth) { smoothData[indexPosition].emplace_back<UINT16>((UINT16)vertices.size() - 1); }

				// �C���f�b�N�X�f�[�^�̒ǉ�
				if (faceIndexCount >= 3)
				{
					// �l�p�`�|���S����4�_�ڂȂ̂ŁA
					// �l�p�`��0,1,2,3�̓� 2,3,0�ŎO�p�`���\�z����
					indices.emplace_back<UINT16>((UINT16)indexCountTex - 1);
					indices.emplace_back<UINT16>((UINT16)indexCountTex);
					indices.emplace_back<UINT16>((UINT16)indexCountTex - 3);
				}
				else { indices.emplace_back<UINT16>((UINT16)indexCountTex); }

				indexCountTex++;
				faceIndexCount++;
			}
		}
	}
	file.close();

	if (isSmooth) { CalculateSmoothedVertexNormals(); }

	CreateBuffers();
}

void Mesh::CreateBuffers()
{
	UINT sizeVB = static_cast<UINT>(sizeof(Mesh::VertexData) * vertices.size());
	VertexData* vertMap = nullptr;	// ���_�o�b�t�@�̃}�b�v
	// ���_�o�b�t�@����
	CreateBuffer(&vertBuff, &vertMap, sizeVB);
	// �S���_�ɑ΂���
	copy(vertices.begin(), vertices.end(), vertMap); // ���W���R�s�[
	// ���_�o�b�t�@�r���[�̍쐬
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(Mesh::VertexData);
	
	UINT sizeIB = static_cast<UINT>(sizeof(UINT16) * indices.size());
	UINT16* indexMap = nullptr;
	// �C���f�b�N�X�o�b�t�@����
	CreateBuffer(&indexBuff, &indexMap, sizeIB);
	// �S�C���f�b�N�X�ɑ΂���
	copy(indices.begin(), indices.end(), indexMap);	// �C���f�b�N�X���R�s�[
	// �C���f�b�N�X�o�b�t�@�r���[�̍쐬
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;
}

void Mesh::Draw()
{
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
	// ���_�o�b�t�@�̐ݒ�
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	// �C���f�b�N�X�o�b�t�@�̐ݒ�
	cmdList->IASetIndexBuffer(&ibView);
	// �`��R�}���h
	cmdList->DrawIndexedInstanced((UINT)indices.size(), 1, 0, 0, 0);
}