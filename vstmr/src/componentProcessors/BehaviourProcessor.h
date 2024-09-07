#pragma once

namespace vstmr {

	class BehaviourManager;
	class BehaviourProcessor
	{
	public:
		BehaviourProcessor();

	public:
		void CallStart();

	private:
		BehaviourManager& m_behaviour_manager;
	};

}