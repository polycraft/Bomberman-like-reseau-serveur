#ifndef COMPAREBOMBERMAN_H
#define COMPAREBOMBERMAN_H

class Bomberman;

//Trie les bomberman par ordre d'id
class CompareBomberman
{
    public:
    bool operator()(const Bomberman* a,const Bomberman *b);
};

#endif // COMPAREBOMBERMAN_H
