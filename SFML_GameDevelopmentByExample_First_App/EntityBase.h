#pragma once
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


enum class EntityType
{
	Base, 
	Enemy,
	Player
};


enum class EntityState
{
	Idle,
	Walking,
	Jumping,
	Attacking,
	Hurt, 
	Dying
};

struct CollisionElement
{
	CollisionElement(float l_area, TileInfo* l_info, const sf::FloatRect& l_bounds) : 
		m_area(l_area), m_title(l_info), m_tileBounds(l_bounds) {}
	float m_area;
	TileInfo* m_title;
	sf::FloatRect m_tileBounds;
};

using Collisions = std::vector<CollisionElement>;

bool SortCollisions(const CollisionElement& l_1, 
	const CollisionElement& l_2);

//Class Forward declaration
class EntityManager;
class EntityBase
{
	friend class EntityManager;
public:

	EntityBase(EntityManager* l_entityMgr);
	virtual ~EntityBase();

	//Getters and Setters 
	void SetPosition(const sf::Vector2f& l_pos);
	void SetPosition(const float& l_x, const float& l_y);
	void SetSize(const float& l_x, const float& l_y);
	void SetState(const EntityState& l_state);

	std::string& GetName() { return m_name; }
	unsigned int GetId() { return m_id; }
	EntityType& GetType() { return m_type; }
	EntityState& GetState() { return m_state; }
	sf::Vector2f& GetPosition() { return m_position; }


	void Move(float l_x, float l_y);
	void AddVelocity(float l_x, float l_y);
	void Accelerate(float l_x, float l_y);
	void SetAcceleration(float l_x, float l_y);
	void ApplyFriction(float l_x, float l_y);
	virtual void Update(float l_dT);
	virtual void Draw(sf::RenderWindow* l_wind) = 0;

protected:
	//Methods
	void UpdateAABB();
	void CheckCollisions();
	void ResolveCollisions();
	//Method for what THIS entity does TO the l_collider entity.
	virtual void OnEntityCollision(EntityBase* l_collider, bool l_attack);




	//Data Members
	std::string m_name;
	EntityType m_type;
	unsigned int m_id; //Entity Id in the entity  manager
	sf::Vector2f m_position; // Position before entity moved.
	sf::Vector2f m_positionOld; // Position before entity Moved
	sf::Vector2f m_velocity; //Current Velocity;
	sf::Vector2f m_maxVelocity; //Maximum velocity;
	sf::Vector2f m_speed; //Value of acceleration
	sf::Vector2f m_acceleration; //Current Acceleration
	sf::Vector2f m_friction; //Default friction value
	TileInfo* m_referenceTile; //Tile underneath entity
	sf::Vector2f m_size; // Size of the collision box
	sf::FloatRect m_AABB; //The bounding box for collisions
	EntityState m_state; //Current entity state
	//Flags for remembering axis collisions
	bool m_collidingOnX;
	bool m_collidingOnY;

	Collisions m_collisions;
	EntityManager* m_entityManager;

};

