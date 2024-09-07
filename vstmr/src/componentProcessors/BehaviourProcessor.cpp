#include "BehaviourProcessor.h"
#include "ECS/BehaviouralSceneObject.h"

#include <iostream>

namespace vstmr {

	struct Dummy : public BehaviouralSceneObject<Dummy> 
	{
		void Start() { std::cout << "DUMMY\n"; };
		void Update() {};
		void UI() {};
		void End() {};
	};

	BehaviourProcessor::BehaviourProcessor() : //Get behaviour manager using a dummy BehaviouralSceneObject
		m_behaviour_manager{ BehaviourManagerStore::GetBehaviourManager() }
	{
	}

	void BehaviourProcessor::CallStart()
	{
		m_behaviour_manager.CallAllStart();
	}

}
