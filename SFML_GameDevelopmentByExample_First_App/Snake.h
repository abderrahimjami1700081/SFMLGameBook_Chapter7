#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
struct SnakeSegment
{
	SnakeSegment(int x, int y) :
		position(x, y) {}
	sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction 
{
	None, 
	Up,
	Down,
	Left,
	Right
};
class Snake
{
public:
	Snake(int l_blockSize);
	~Snake();

	//Helper methods
	void SetDirection(Direction l_dir) { m_dir = l_dir; }
	Direction GetDirection() { return m_dir; }
	int GetSpeed() { return m_speed; }
	sf::Vector2i GetPosition() {
		return (!m_snakeBody.empty() ?
			m_snakeBody.front().position : sf::Vector2i(1, 1));
	}
	int GetLives() { return m_lives; }
	int GetScore() { return m_score; }
	void IncreaseScore() { m_score += 10; }
	bool HasLost() { return m_lost; }

	void Lose() { m_lost = true; }		//Handle losing here
	void ToggleLost() { m_lost = !m_lost; }


	void Extend();		//Grow the snake
	void Reset();		//Reset to starting position

	void Move();		//Movement method
	void Tick();		//Update method
	void Cut(int l_segments);			//Method for cutting snake
	void Render(sf::RenderWindow& l_window);
	
	Direction GetPhysicalDirection();
private:
	void CheckCollision();		//Checking for collisions

	SnakeContainer m_snakeBody;
	int m_size;						//Size of the graphics
	Direction m_dir;				//Current direction
	int m_speed;					//Speed of the snake
	int m_lives;					//Lives
	int m_score;					//Score
	bool m_lost;					//Losing state
	sf::RectangleShape m_bodyRect;	//Shape used in rendering.
};

