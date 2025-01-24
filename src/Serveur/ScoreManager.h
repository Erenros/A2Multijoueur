#pragma once


class ScoreManager
{
protected:

	int mScore;

public:

	ScoreManager();
	~ScoreManager();

	void Init();

	void AddKill();
	void AddDeath();
	int GetScore();
};

