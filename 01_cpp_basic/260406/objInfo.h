#pragma once
#include<iostream>
using namespace std;

typedef struct st
{
}Player, Monster;


void StartAndChoiceClass(st Obj);
void ChoiceClass(st* Obj);
void ChoiceHuntOrEnd(st* Player);
void ChoiceLevel(st* Player);
void Battle(st* Player, st* Monster);
