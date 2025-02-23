#include "ScoreContainer.h"
// #include "ScoreUI.h"


ScoreContainer::ScoreContainer(/*ScoreUI* scoreUI,*/ double scoreToBeat, double baseScore) 
: /*_scoreUI(scoreUI), */_scoreToBeat(scoreToBeat), _currentScore(baseScore) 
{
    
}

/*NOTA: Estos métodos asumen la existencia de una clase ScoreUI que tiene un método para refrescar el display de
la puntuación (tanto actual como final)*/
void ScoreContainer::addScore(double score) {
    _currentScore += score;
    //_scoreUI->refresh(_currentScore, _scoreToBeat);
}

void ScoreContainer::removeScore(double score) {
    _currentScore -= score;
    //_scoreUI->refresh(_currentScore, _scoreToBeat);
}

void ScoreContainer::setScoreToBeat(double newScoreToBeat){
    _scoreToBeat = newScoreToBeat;
    //_scoreUI->refresh(_currentScore, _scoreToBeat);
}