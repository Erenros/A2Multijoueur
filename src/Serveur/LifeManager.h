#ifndef LIFEMANAGER_H__
#define LIFEMANAGER_H__

class LifeManager
{
protected:

	int mHp;

public:

	LifeManager();

	void Init(int _Hp);

	virtual void TakeDamage(int _Dmg);
	virtual int GetHp();

};
#endif

