#pragma once

#include "ConstantBuffer.h"
#include "LightType.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"

namespace ChefEngine::Graphics
{
	class Camera;
	class RenderObject;

	class StandardEffect
	{
	public:
		void Initialize(const std::filesystem::path& filePath);
		void Terminate();

		void Begin();
		void End();

		void Render(const RenderObject& renderObject);

		void SetCamera(const Camera& camera);
		void SetDirectionalLight(const DirectionalLight& directionalLight);

		void DebugUI();

	private:
		struct TransformData
		{
			DEMath::Matrix4 world;
			DEMath::Matrix4 wvp;
			DEMath::Vector3 viewPosition;
			float displacementWeight;
		};

		struct SettingsData
		{
			int useDisplacementMap = 1;
			int useSpecularMap = 1;
			int useDiffuseMap = 1;
			int useNormalMap = 1;
		};

		using TransformBuffer = TypedConstantBuffer<TransformData>;
		using LightBuffer = TypedConstantBuffer<DirectionalLight>;
		using SettingsBuffer = TypedConstantBuffer<SettingsData>;

		TransformBuffer mTransformBuffer;
		LightBuffer mLightBuffer;
		SettingsBuffer mSettingsBuffer;
		Sampler mSampler;

		VertexShader mVertexShader;
		PixelShader mPixelShader;

		SettingsData mSettingsData;
		float mDisplacementWeight = 1.0f;
		const Camera* mCamera = nullptr;
		const DirectionalLight* mDirectionalLight = nullptr;

	};
}