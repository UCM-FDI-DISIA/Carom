#pragma once

class ScoreUI;

///Clase que contiene la puntuación a superar en una ronda y la puntuación acumulada del jugador
class ScoreContainer {
protected:
    double _currentScore;
    double _scoreToBeat;

    ScoreUI* _scoreUI;

public:
    ScoreContainer(ScoreUI* scoreUI, double scoreToBeat, double baseScore = 0);

    inline bool roundWins() {return _currentScore >= _scoreToBeat; }

    inline double getCurrentScore() { return _currentScore; }

    inline double getScoreToBeat() { return _scoreToBeat; }
    void setScoreToBeat(double newScoreToBeat);

    void addScore(double score);
    void removeScore(double score);
};