#include "pch.h"
#include "ScoreManager.h"

ScoreManager::ScoreManager() : mScore(0)
{
}

ScoreManager::~ScoreManager()
{
}

void ScoreManager::Init()
{
}

void ScoreManager::AddKill()
{
	mScore += 1;
}

void ScoreManager::AddDeath()
{
	mScore -= 1;
}

int ScoreManager::GetScore()
{
	return mScore;
}
