#pragma once
#include "PointAudio.h"
#include <list>
#include <memory>
#include <string>
#include <map>

namespace WristerEngine
{
	// �I�[�f�B�I�Ǘ�
	class AudioManager
	{
	private:
		static std::map<bool, std::list<std::unique_ptr<Audio>>> audios;
		static std::map<bool, std::list<std::unique_ptr<PointAudio>>> pointAudios;

	public:
		// ������
		static void Initialize();
		// �I��
		static void Finalize();

		/// <summary>
		/// �I�[�f�B�I����
		/// </summary>
		/// <param name="fileName">�t�@�C����</param>
		/// <param name="isLoop">���[�v�Đ��t���O</param>
		/// <returns>�I�[�f�B�I�C���X�^���X�̃|�C���^</returns>
		static Audio* Create(const std::string& fileName, bool isLoop = false);

		/// <summary>
		/// �_��������
		/// </summary>
		/// <param name="fileName">�t�@�C����</param>
		/// <param name="isLoop">���[�v�Đ��t���O</param>
		/// <param name="audioPos">�����̃��[���h���W</param>
		/// <param name="useCamera">true�ɂ���ƃJ�����̈ʒu���}�C�N���W�ɂȂ�</param>
		/// <param name="usePan">true�ɂ���Ɖ��������E�ړ�����</param>
		/// <returns>�_�����C���X�^���X�̃|�C���^</returns>
		static PointAudio* CreatePointAudio(const std::string& fileName,
			bool isLoop = false, const Vector3& audioPos = {}, bool useCamera = true, bool usePan = true);

		// �S�I�[�f�B�I�C���X�^���X�̍X�V
		static void Update();
	};
}