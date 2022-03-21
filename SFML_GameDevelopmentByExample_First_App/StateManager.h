#pragma once


//Including std containers
#include <vector>
#include <unordered_map>

#include "SharedContext.h"

//GameStates
#include "State_Intro.h"
#include "State_MainMenu.h"
#include "State_Game.h"
#include "State_Paused.h"
#include "State_GameOver.h"
enum class StateType
{
	Intro = 1,
	MainMenu,
	Game,
	Paused,
	GameOver,
	Credits
};


//Container used to hold states, is made up of pair objects (a statype and an instance
// of type BaseState)
using StateContainer = std::vector<
	std::pair<StateType, BaseState*>>;

//Typecontainer is a container of state types, keep looking at the rest 
//of the code to learn more
using TypeContainer = std::vector<StateType>;

//The follwing is a type of variable used to store functions that will create 
//Different types of BaseState objects depending on the statetype 
using StateFactory = std::unordered_map<StateType,
	std::function<BaseState*(void)>>;


class StateManager
{
public:
	StateManager(SharedContext* l_shared);
	~StateManager();

	void Update(const sf::Time& l_time);
	void Draw();

	void ProcessRequests();

	SharedContext* GetContext();
	bool HasState(const StateType& l_type);

	void SwitchTo(const StateType& l_type);
	void Remove(const StateType& l_type);

private:

	//Methods
	void CreateState(const StateType& l_type);
	void RemoveState(const StateType& l_type);

	template<class T>
	//The following function is defined in the header because it is a templated function
	void RegisterState(const StateType& l_type)
	{
		//The first part of the following initialization is like saying
		//The element in the unorderedmap statefactory with key "l_type"... the element being the
		//std::function... is equal to the lambda expression

		//OHHHH I get it now.. the " -> BaseState*" part of the lambda expression is the return type
		//Normally it is implicitly defined by the compiler but in this case it is set explicitely 
		m_stateFactory[l_type] = [this]() -> BaseState*
		{
			// ??? Why do you need to pass the pointer to the statemanager
			//When creating a new gamestate?
			return new T(this);
		};
	}
	//Members
	SharedContext* m_shared;
	StateContainer m_states;
	TypeContainer m_toRemove;
	StateFactory m_stateFactory;

	// StateType
	StateType m_currentState;






};

