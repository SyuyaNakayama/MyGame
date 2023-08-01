#pragma once
#include "ViewProjection.h"
#include "LightGroup.h"
#include "Object3d.h"

enum class RootParamNum { MatWorld = (int)TexType::Num, Material, Light, Camera };

class ModelManager
{
private:
	// ライト
	static std::unique_ptr<LightGroup> lightGroup;
	// 読み込んだモデル情報
	static std::list<std::unique_ptr<Mesh>> meshes;
	// 生成したオブジェクト
	static std::list<std::unique_ptr<Object3d>> objects;
	// ビュープロジェクションのポインタ
	static ViewProjection* viewProjection;

public:
	// 初期化
	static void Initialize();
	// 更新
	static void Update();
	// 描画処理
	static void DrawObjects();
	// モデル作成
	static Object3d* Create(const std::string& modelName, bool smoothing = false);
	static LightGroup* GetLightGroup() { return lightGroup.get(); }
	static void SetViewProjection(ViewProjection* viewProjection_) { viewProjection = viewProjection_; }
	static ViewProjection* GetViewProjection() { return viewProjection; }
};