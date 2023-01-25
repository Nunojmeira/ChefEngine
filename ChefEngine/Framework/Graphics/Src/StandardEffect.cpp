#include "Precompiled.h"
#include "StandardEffect.h"
#include "Camera.h"
#include "RenderObject.h"
#include "VertexTypes.h"

using namespace ChefEngine;
using namespace ChefEngine::Graphics;

void StandardEffect::Initialize(const std::filesystem::path& filePath)
{
	mTransformBuffer.Initialize();
	mLightBuffer.Initialize();
	mSettingsBuffer.Initialize();

	mVertexShader.Initialize<Vertex>(filePath);
	mPixelShader.Initialize(filePath);
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void StandardEffect::Terminate()
{
	mSampler.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mLightBuffer.Terminate();
	mTransformBuffer.Terminate();
	mSettingsBuffer.Terminate();
}

void StandardEffect::Begin()
{
	ASSERT(mCamera != nullptr, "StandardEffect - no camera set!");
	ASSERT(mDirectionalLight != nullptr, "StandardEffect - no light set!");
	mVertexShader.Bind();
	mPixelShader.Bind();

	mTransformBuffer.BindVS(0);

	mLightBuffer.BindVS(1);
	mLightBuffer.BindPS(1);

	mSettingsBuffer.BindVS(2);
	mSettingsBuffer.BindPS(2);

	mSampler.BindVS(0);
	mSampler.BindPS(0);
}

void StandardEffect::End()
{
	// If cleanup is needed afterwards
}

void StandardEffect::Render(const RenderObject& renderObject)
{
	const auto& matWorld = renderObject.transform.GetMatrix4();
	const auto& matView = mCamera->GetViewMatrix();
	const auto& matProj = mCamera->GetProjectionMatrix();

	TransformData transformData;
	transformData.world = Transpose(matWorld);
	transformData.wvp = Transpose(matWorld * matView * matProj);
	transformData.viewPosition = mCamera->GetPosition();
	transformData.displacementWeight = mDisplacementWeight;

	SettingsData settingsData;
	settingsData.useDiffuseMap = mSettingsData.useDiffuseMap > 0 && renderObject.diffuseMapId > 0;
	settingsData.useSpecularMap = mSettingsData.useSpecularMap > 0 && renderObject.specularMapId > 0;
	settingsData.useDisplacementMap = mSettingsData.useDisplacementMap > 0 && renderObject.displacementMapId > 0;
	settingsData.useNormalMap = mSettingsData.useNormalMap > 0 && renderObject.normalMapId > 0;

	mTransformBuffer.Update(transformData);
	mLightBuffer.Update(*mDirectionalLight);
	mSettingsBuffer.Update(settingsData);

	// Send data to shader and display
	auto tm = TextureManager::Get();
	tm->BindPS(renderObject.diffuseMapId, 0);
	tm->BindPS(renderObject.normalMapId, 1);
	tm->BindVS(renderObject.displacementMapId, 2);
	tm->BindPS(renderObject.specularMapId, 3);
	renderObject.meshBuffer.Render();
}

void StandardEffect::SetCamera(const Camera& camera)
{
	mCamera =& camera;
}
void StandardEffect::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	mDirectionalLight = &directionalLight;
}

void StandardEffect::DebugUI()
{
	if (ImGui::CollapsingHeader("Standard Effect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Displacement Weight", &mDisplacementWeight, 0.1f);

		bool useDiffuseMap = mSettingsData.useDiffuseMap > 0;
		ImGui::Checkbox("Use Diffuse Map", &useDiffuseMap);
		mSettingsData.useDiffuseMap = (useDiffuseMap) ? 1 : 0;

		bool useSpecularMap = mSettingsData.useSpecularMap > 0;
		ImGui::Checkbox("Use Specular Map", &useSpecularMap);
		mSettingsData.useSpecularMap = (useSpecularMap) ? 1 : 0;

		bool useDisplacementMap = mSettingsData.useDisplacementMap > 0;
		ImGui::Checkbox("Use Displacement Map", &useDisplacementMap);
		mSettingsData.useDisplacementMap = (useDisplacementMap) ? 1 : 0;

		bool useNormalMap = mSettingsData.useNormalMap > 0;
		ImGui::Checkbox("Use Normal Map", &useNormalMap);
		mSettingsData.useNormalMap = (useNormalMap) ? 1 : 0;

	}
}