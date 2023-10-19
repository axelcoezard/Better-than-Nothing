#pragma once

namespace BetterThanNothing
{
	class CRenderer;
	class CModel;
	class CCamera;

	class CScene
	{
	private:
		std::string				m_Name;

		CCamera*				m_pCamera;
		std::vector<CModel*>	m_pModels;
	public:
								CScene(std::string_view name);
								~CScene();

								CScene(const CScene&) = delete;
		CScene&					operator=(const CScene&) = delete;
								CScene(CScene&&) = delete;
		CScene&					operator=(CScene&&) = delete;

	public:
		void					InitCamera(double x, double y, double z, double pitch, double yaw, double roll);
		void					LoadModel(CRenderer* pRenderer, const std::string& modelPath, const std::string& texturePath);

		void					MoveCamera(float x, float y, float z);
		void					RotateCamera(float pitch, float yaw, float roll);

	public:
		std::string&			GetName()			{ return m_Name; }
		CCamera*				GetCamera()			{ return m_pCamera; }
		std::vector<CModel*>&	GetModels()			{ return m_pModels; }
	};
};
