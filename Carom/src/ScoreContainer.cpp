#include "ScoreContainer.h"
// #include "ScoreUI.h"

ScoreContainer::ScoreContainer(ScoreUI* scoreUI, double scoreToBeat, double baseScore) 
    : _scoreUI(scoreUI), _scoreToBeat(scoreToBeat), _currentScore(baseScore) 
{

}

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