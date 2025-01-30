#ifndef SCOREMANAGER_H__
#define SCOREMANAGER_H__

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

#endif