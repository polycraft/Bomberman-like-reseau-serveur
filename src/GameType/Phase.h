#ifndef PHASE_H
#define PHASE_H

class CollisionDetector;

typedef enum EEtat
{
    E_Current=0,
    E_Next=1,
    E_Init=2,
    E_Run=3
} EEtat;

class Phase
{

public:
	Phase(CollisionDetector *collision);
	virtual ~Phase(){};
	virtual void init()=0;
	virtual void run()=0;
	void end( int next=1);
	void nextEtat();
	void setEtat(EEtat etat);

	void setCollisionDetector(CollisionDetector *collision);

    int update();
protected:
    CollisionDetector *collision;

private:
	EEtat etat;
	int next;
};



#endif // PHASE_H
