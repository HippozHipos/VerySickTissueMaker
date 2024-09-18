#pragma once

#include "ECS/ECS.h"
#include "Renderer/Mesh.h"
#include "Renderer/MeshRenderer.h"
#include "Renderer/buffers/FrameBuffer.h"

#include "UI/Imgui/BEImGuiViewport.h"

namespace be {

	struct MainPlatformWindowRenderer;
	struct Camera;
	struct Transform;
	struct Material;


	/*!
	 *  \class MeshRendererSystem
	 *  \brief System that Renders the all the meshes
	 *
	 *  This class iterates over all the MeshRenderer s in the scene and renders them. 
	 * 
	 *  MeshRenderer can be added to the scene by calling SceneContainer.Add<MeshRenderer>() 
	 *  or by calling Add on any classes that inherit from SceneContainer.
	 * 
	 *  Example
	 *  \code
	 *  class Player : public SceneObject 
	 *  {
	 * 	public:
	 *		Player()
	 *		{
	 *			MeshRenderer& meshRenderer = Add<MeshRenderer>();
	 *			ModelLoader::Load("path/to/model", meshRenderer);
	 *		}
	 *  }
	 *  \endcode
	 *
	 *	How it works: 
	 *	When rendering, it iterates through every Camera in the scene. If the camera is active, it renders 
	 *  to the Camera::target_viewport. Currently, if the Camera::target_viewport is "Main Platform Window", it
	 *  simply unbinds the frame buffers so that rendering is done to the default frame buffer. This will change 
	 *  in the future. Otherwise, it renders to the frame buffer of specified window. 
	 *  The texture of the specified frame buffer is then passed to imgui for the window that it belongs to by BEImGuiViewport::Render.
	 */
	struct MeshRendererSystem
	{
	public:
		/*!
		 *  \Constructor that stores given arguments in the class scope
		 *	\param viewportMap Reference to map of window to viewport that is stored by Renderer.
		 *  \param mainWinRenderer Reference to MainPlatformWindowRenderer that is stored by Renderer 
		    (currently unused but will eventually be used for off screen rendering).
		 */
		MeshRendererSystem(std::unordered_map<std::string, BEImGuiViewport>& viewportMap, 
			MainPlatformWindowRenderer& mainWinRenderer);

	public:
		/*!
		 *	\brief Renders all the meshes in the scene to appropriate windows.
		 */
		void Render();

	private:
		/*!
		 *	\brief Sets up appropritate lighting shaders for the rendering proccess
		 */
		void ProcessLighting(MeshRenderer& renderer);
		/*!
		 *	\brief Does the actual draw call after being appropriate vao, index buffer and shaders
		 */
		void RenderMesh(Camera& camera, MeshRenderer& renderer, Transform& transform);
	
	private:
		/*! Map of window to BEImGuiViewport. A window is identified by its name. 
		* "Main Platform Window" is the name of main window created by the application.
		* It can also be any imgui window name.
		*/
		std::unordered_map<std::string, BEImGuiViewport>& m_viewport_map;
		/*! Currently Unused
		*/
		MainPlatformWindowRenderer& m_main_window_renderer;
	};

}