#pragma once

namespace BetterThanNothing
{
	class Window;
	class Device;
	class Renderer;

	class ModelPool;
	class TexturePool;

	class Scene;
	class Event;

	/**
	 * @brief The Application class is the main class of the engine's applications.
	 */
	class Application
	{
	protected:
		/**
		 * @brief A pointer to the Window
		*/
		Window* m_Window;

		/**
		 * @brief A pointer to the Device
		*/
		Device* m_Device;

		/**
		 * @brief A pointer to the Renderer
		*/
		Renderer* m_Renderer;

		/**
		 * @brief A pointer to the ModelPool
		*/
		ModelPool* m_ModelPool;

		/**
		 * @brief A pointer to the TexturePool
		*/
		TexturePool* m_TexturePool;

		/**
		 * @brief The Scenes of the Application
		*/
		std::vector<Scene*> m_Scenes;

		/**
		 * @brief The current Scene of the Application
		*/
		u32 m_CurrentSceneId;
	public:
		/**
		 * @brief Construct a new Application object
		 * @param title The title of the window
		 * @param width The width of the window
		 * @param height The height of the window
		*/
		Application(std::string_view title, u32 width, u32 height);

		/**
		 * @brief Destroy the Application object
		*/
		virtual ~Application();

		/**
		 * @brief Run the Application
		*/
		void Run();

		/**
		 * @brief Called when the Application is enabled
		*/
		virtual void OnEnable() = 0;

		/**
		 * @brief Called when the Application is disabled
		*/
		virtual void OnDisable() = 0;

		/**
		 * @brief Called when an Event is received
		 * @param event A pointer to the Event object received
		*/
		void OnEvent(Event* event);

		/**
		 * @brief Create a Scene object and register it to the Application
		 *
		 * @param name The name of the Scene
		 * @return A pointer to the created Scene object
		 */
		Scene* CreateScene(const std::string& name);

		/**
		 * @brief Get the Window object
		 * @return A pointer to the Window object
		 */
		Window* GetWindow() { return m_Window; }

		/**
		 * @brief Get the Device object
		 * @return A pointer to the Device object
		 */
		Device* GetDevice() { return m_Device; }

		/**
		 * @brief Get the Renderer object
		 * @return A pointer to the Renderer object
		 */
		Renderer* GetRenderer() { return m_Renderer; }
	};
};
