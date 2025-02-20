#include <iostream>
#include <string>
#include <tuple>

using namespace std;

// Ball class
class Ball {
private:
    int x, y;

public:
    Ball(int initialX = 0, int initialY = 0) : x(initialX), y(initialY) {}

    int getX() const { return x; }
    int getY() const { return y; }

    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    tuple<int, int> getPosition() const {
        return make_tuple(x, y);
    }
};

// Goal class
class Goal {
private:
    int goalX, goalY;

public:
    Goal(int x = 3, int y = 3) : goalX(x), goalY(y) {}

    bool isGoalReached(int ballX, int ballY) const {
        return ballX == goalX && ballY == goalY;
    }
};

// Robot class
class Robot {
private:
    string name;
    int hits;

public:
    Robot(string n) : name(n), hits(0) {}

    void hitBall(int ballX, int ballY, const string &direction) {
        if (direction == "up") {
            ballY++;
        } else if (direction == "down") {
            ballY--;
        } else if (direction == "left") {
            ballX--;
        } else if (direction == "right") {
            ballX++;
        }
        hits++;
        cout << name << " hit the ball towards " << direction << ". Ball position: (" << ballX << ", " << ballY << ")" << endl;
    }

    int getHits() const { return hits; }
    string getName() const { return name; }
};

// Team class
class Team {
private:
    string teamName;
    Robot* robot;

public:
    Team(string name, Robot* r) : teamName(name), robot(r) {}

    void play(Ball &ball, const Goal &goal) {
        cout << teamName << " is playing..." << endl;
        while (!goal.isGoalReached(ball.getX(), ball.getY())) {
            string direction;
            cout << "Enter direction (up, down, left, right) for " << robot->getName() << ": ";
            cin >> direction;
            robot->hitBall(ball.getX(), ball.getY(), direction);
        }
        cout << teamName << " reached the goal in " << robot->getHits() << " hits!" << endl;
    }

    int getHits() const { return robot->getHits(); }
    string getTeamName() const { return teamName; }
};

// Game class
class Game {
private:
    Team* teamOne;
    Team* teamTwo;
    Ball ball;
    Goal goal;

public:
    Game(Team* t1, Team* t2) : teamOne(t1), teamTwo(t2) {}

    void startGame() {
        cout << "Starting the game!" << endl;
        teamOne->play(ball, goal);
        ball = Ball(0, 0); // Reset ball position for the second team
        teamTwo->play(ball, goal);
        declareWinner();
    }

    void declareWinner() const {
        cout << "Game Over!" << endl;
        cout << teamOne->getTeamName() << " hits: " << teamOne->getHits() << endl;
        cout << teamTwo->getTeamName() << " hits: " << teamTwo->getHits() << endl;

        if (teamOne->getHits() < teamTwo->getHits()) {
            cout << teamOne->getTeamName() << " wins!" << endl;
        } else if (teamOne->getHits() > teamTwo->getHits()) {
            cout << teamTwo->getTeamName() << " wins!" << endl;
        } else {
            cout << "It's a tie!" << endl;
        }
    }
};

int main() {
    // Create robots
    Robot robot1("RoboKicker");
    Robot robot2("GoalMaster");

    // Create teams
    Team team1("Team A", &robot1);
    Team team2("Team B", &robot2);

    // Create and start the game
    Game game(&team1, &team2);
    game.startGame();

    return 0;
}
