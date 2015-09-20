//
//#include "SceneLoader.hpp"
//
//#include <exeng/Vector.hpp>
//#include <exeng/scenegraph/Mesh.hpp>
//#include <exeng/graphics/Material.hpp>
//
//#include <memory>
//
//namespace raytracer {
//    using namespace exeng;
//    using namespace exeng::scenegraph;
//    using namespace exeng::graphics;
//    
//    SceneLoader::~SceneLoader() {}
//    
//    SceneLoader::SceneLoader(GraphicsDriver *driver_, MeshManager *meshManager_) 
//	{
//		this->graphicsDriver = driver_;
//		this->meshManager = meshManager_;
//    }
//    
//    // For now, just create a simple scene, boxed scene.
//    std::unique_ptr<Scene> SceneLoader::loadScene(const std::string &filename, const MaterialFormat *materialFormat) 
//	{
//		auto scene = std::make_unique<Scene>();
//
//        // empty object
//		/*
//		this->addBoxNode ( 
//			scene.get(), "boxNode1", 
//			"boxMaterial1", {1.0f, 0.3f, 0.2f, 1.0f},
//			"boxMesh1", {0.5f, 1.0f, 0.0f}, {0.75f, 0.75f, 0.75f}
//		);
//
//		this->addBoxNode ( 
//			scene.get(), "boxNode2", 
//			"boxMaterial2", {0.1f, 0.4f, 0.8f, 1.0f},
//			"boxMesh2", {-0.5f, 1.0f, 0.0f}, {0.75f, 0.75f, 0.75f}
//		);
//
//		this->addBoxNode ( 
//			scene.get(), "boxNode3", 
//			"boxMaterial3", {0.3f, 0.8f, 0.1f, 1.0f},
//			"boxMesh3", {0.0f, 0.0f, 0.0f}, {0.75f, 0.25f, 0.25f}
//		);
//		*/
//		
//		// std::string lwoFilename = "D:\\Felipe\\Desktop\\Assets\\Modelos\\Santiago3D\\Basurero\\BasureroLWO.lwo";
//		// std::string lwoFilename = "C:\\Users\\fapablaza\\Downloads\\Easel\\easel.lwo";
//		std::string lwoFilename = "easel.lwo";
//		Mesh *mesh = this->meshManager->getMesh(lwoFilename);
//
//		SceneNode *node = scene->getRootNode()->addChild("boxNode3");
//		node->setData(mesh);
//		
//        return scene;
//    }
//
//	SceneNode* SceneLoader::addBoxNode(
//		Scene *scene, const std::string &boxNodeName, 
//		const std::string &materialName, const Vector4f &materialColor, 
//		const std::string &boxMeshName, const Vector3f &boxCenter, const Vector3f &boxSize) 
//	{
//		// box material
//        Material *boxMaterial = nullptr; /*scene->createMaterial(materialName);*/
//
//		boxMaterial->setAttribute<Vector4f>("diffuse", materialColor);
//
//        // box mesh
//        // Mesh *boxMesh = this->meshManager->getMesh("/cube", this->graphicsDriver);
//		Mesh *boxMesh = this->meshManager->generateBoxMesh(boxMeshName, boxCenter, boxSize);
//        boxMesh->getSubset(0)->setMaterial(boxMaterial);
//
//        // box scenenode
//        scene->getRootNode()->addChild(boxNodeName)->setData(boxMesh);
//
//		return scene->getRootNode()->getChild(boxNodeName);
//	}
//}
