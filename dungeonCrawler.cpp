#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
using namespace std;

struct Wall {
    int x, y;
};

struct Loot {
    int x, y;
};

struct Enemy {
    int x, y, enemyNum;
    int health = 10;
    bool hasKey;
};

struct Player {
    int x, y;
    int health = 20;
};

struct Food {
    int x, y;
};

struct Extraction {
    int x, y;
};

vector <Food> foods;
vector<Loot> loots;
vector<Enemy> enemies;
vector<Wall> walls;
Loot loot;
Food food;
Extraction extraction;
Enemy enemy;
Wall wall;
Player player;
const int dungeonHeight = 50;
const int dungeonWidth = 50;
bool smallSword = false;
bool largeSword = false;
bool weakShield = false;
bool strongShield = false;
bool key = false;
bool isExtract = false;

void generateInventory() {
    cout << "Player Inventory:" << endl;
    if (smallSword) {
        cout << "Small Sword: +3 Attack Damage." << endl;
    } if (largeSword) {
        cout << "Large Sword: +5 Attack Damage." << endl;
    } if (weakShield) {
        cout << "Weak Shield: Chance for -1 Damage." << endl;
    } if (strongShield) {
        cout << "Strong Shield: -1 Damage." << endl;
    } if (key) {
        cout << "Key" << endl;
    }
    if (!smallSword && !largeSword && !weakShield && !strongShield && !key) {
        cout << "Empty." << endl;
    }
}

void showEnemyHealth() {
    for (auto it = enemies.begin(); it < enemies.end(); it++) {
        if (player.y == it->y && (player.x == it->x + 1 || player.x == it->x - 1) || player.x == it->x && (player.y == it->y + 1 || player.y == it->y - 1)) {
            cout << "Enemy Health: " << it->health << endl;
        }
    }
}

void showPlayerHealth() {
    cout << "Player Health: " << player.health << endl;
}

void generateDungeon() {
    for (int i = 0; i < dungeonHeight; i++) {
        for (int j = 0; j < dungeonWidth; j++) {
            bool isWall = false;
            bool isEnemy = false;
            bool isLoot = false;
            bool isFood = false;
            for (Wall wall : walls) {
                if (wall.x == j && wall.y == i) {
                    cout << "# ";
                    isWall = true;
                    break;
                }
            }
            for (Enemy enemy : enemies) {
                if (enemy.x == j && enemy.y == i) {
                    cout << "e ";
                    isEnemy = true;
                    break;
                }
            }
            for (Loot loot : loots) {
                if (loot.x == j && loot.y == i) {
                    cout << "l ";
                    isLoot = true;
                    break;
                }
            }
            for (Food food : foods) {
                if (food.x == j && food.y == i) {
                    cout << "f ";
                    isFood = true;
                    break;
                }
            }
            if (!isWall && !isEnemy && !isLoot && !isFood) {
                if (player.x == j && player.y == i) {
                    cout << "p ";
                } else  if (extraction.x == j && extraction.y == i) {
                    cout << "x ";
                } else {
                    cout << ". ";
                }
            }
        }
        cout << endl;
    }

    generateInventory();
    showPlayerHealth();
    for (Enemy enemy : enemies) {
        if (player.y == enemy.y && (player.x == enemy.x + 1 || player.x == enemy.x - 1) || player.x == enemy.x && (player.y == enemy.y + 1 || player.y == enemy.y - 1)) {
            showEnemyHealth();
        }
    }
}

void generateWalls() {
    int numWalls = rand() % 100 + 20;

    for (int i = 0; i < numWalls; i++) {
        wall.x = rand() % dungeonWidth;
        wall.y = rand() % dungeonHeight;
        walls.push_back(wall);
    }
}

void generateEnemies() {
    int numEnemies = rand() % 5 + 2;
    int spawnKey = rand() % numEnemies;
    int enemyNum = 0;

    for (int i = 0; i < numEnemies; i++) {
        enemy.x = rand() % dungeonWidth;
        enemy.y = rand() % dungeonHeight;
        enemy.enemyNum = enemyNum;
        enemyNum++;
        if (i == spawnKey) {
            enemy.hasKey = true;
        } else {
            enemy.hasKey = false;
        }
        for (Wall wall : walls) {
            if (enemy.x == wall.x && enemy.y == wall.y) {
                enemy.x++;
            }
        }
        enemies.push_back(enemy);
    }
}

void generateLoot() {
    int numLoot = rand() % 3 + 1;
    for (int i = 0; i < numLoot; i++) {
        loot.x = rand() % dungeonWidth;
        loot.y = rand() % dungeonHeight;
        for (Wall wall : walls) {
            if (loot.x == wall.x && loot.y == wall.y) {
                loot.x++;
            }
        }
        loots.push_back(loot);
    }
}

void spawnPlayer() {
    player.x = rand() % dungeonWidth;
    player.y = rand() % dungeonHeight;
    for (Wall wall : walls) {
        if (player.x == wall.x && player.y == wall.y) {
            player.x++;
        }
    }
    for (Enemy enemy : enemies) {
        if (player.x == enemy.x && player.y == enemy.y) {
            player.x++;
        }
    }
    for (Loot loot : loots) {
        if (player.x == loot.x && player.y == loot.y) {
            player.x++;
        }
    }
    for (Food food : foods) {
        if (player.x == food.x && player.y == food.y) {
            player.x++;
        }
    }
}

bool checkWall() {
    bool isWall = false;

    for (Wall wall : walls) {
        if (player.x == wall.x && player.y == wall.y) {
            isWall = true;
            break;
        }
    }
    if (player.x < 0 || player.x >= 50 || player.y < 0 || player.y >= 50) {
        isWall = true;
    }

    return isWall;
}

bool checkLoot() {
    bool isLoot = false;

    for (auto it = loots.begin(); it < loots.end(); it++) {
        if (player.x == it->x && player.y == it->y) {
            it = loots.erase(it);
            isLoot = true;
        }
    }

    return isLoot;
}

void getLoot() {
    int randomLoot = rand() % 4 + 1;

    if (randomLoot == 1) {
        smallSword = true;
    } else if (randomLoot == 2) {
        largeSword = true;
    } else if (randomLoot == 3) {
        weakShield = true;
    } else if (randomLoot == 4) {
        strongShield = true;
    }
}

bool checkEnemy() {
    bool isEnemy = false;

    for (auto it = enemies.begin(); it < enemies.end(); it++) {
        if (player.x == it->x && player.y == it->y) {
            isEnemy = true;
        }
    }

    return isEnemy;
}

void initiateCombat() {
    int hit = rand() % 2 + 1;
    int protection = rand() % 2 + 1;

    if (hit == 1) {
        if (weakShield && !strongShield) {
            if (protection == 1) {
                player.health -= 3;
            } else if (protection == 2) {
                player.health -= 2;
            }
        } else if (strongShield) {
            player.health -= 2;
        } else {
            player.health -= 3;
        }
    } else if (hit == 2) {
        for (auto it = enemies.begin(); it < enemies.end(); it++) {
            if (it->x == player.x + 1 || it->x == player.x - 1 || it->y == player.y + 1 || it->y == player.y - 1) {            
                if (smallSword && !largeSword) {
                    it->health -= 3;
                } else if (largeSword) {
                    it->health -= 5;
                } else {
                    it->health -= 1;
                }
                if (it->health <= 0) {
                    if (it->hasKey) {
                        key = true;
                    }
                    it = enemies.erase(it);
                }
                break;
            }
        }
    }
}

bool checkFood() {
    bool isFood = false;

    for (auto it = foods.begin(); it < foods.end(); it++) {
        if (player.x == it->x && player.y == it->y) {
            isFood = true;
            it = foods.erase(it);
        }
    }

    return isFood;
}

void getFood() {
    int healthRegen = rand() % 3 + 1;

    if (healthRegen == 1) {
        player.health++;
    } else if (healthRegen == 2) {
        player.health += 2;
    } else if (healthRegen == 3) {
        player.health += 3;
    }

    if (player.health > 20) {
        player.health = 20;
    }
}

void checkExtract() {
    if (player.x == extraction.x && player.y == extraction.y) {
        if (key) {
            isExtract = true;
        }
    }
}

void movePlayer() {
    char move;
    bool isWall;
    bool isLoot = false;
    bool isEnemy = false;
    bool isFood = false;
    
    cout << "Move using (wasd): ";
    cin >> move;

    if (move == 'w') {
        player.y--;
        isWall = checkWall();
        isEnemy = checkEnemy();
        checkExtract();
        if (isWall || isEnemy) {
            player.y++;
        }
    } else if (move == 's') {
        player.y++;
        isWall = checkWall();
        isEnemy = checkEnemy();
        checkExtract();
        if (isWall || isEnemy) {
            player.y--;
        }
    } else if (move == 'a') {
        player.x--;
        isWall = checkWall();
        isEnemy = checkEnemy();
        checkExtract();
        if (isWall || isEnemy) {
            player.x++;
        }
    } else if (move == 'd') {
        player.x++;
        isWall = checkWall();
        isEnemy = checkEnemy();
        checkExtract();
        if (isWall || isEnemy) {
            player.x--;
        }
    }

    isLoot = checkLoot();
    isFood = checkFood();
    if (isLoot) {
        getLoot();
    } else if (isEnemy) {
        initiateCombat();
    } else if (isFood) {
        getFood();
    }
}

bool checkSpace() {
    bool isOpen = false;
    bool isPlayer = false;
    bool isWall = false;
    bool isExit = false;
    bool isEnemy = false;

    for (Enemy enemy : enemies) {
        if (player.x == enemy.x && player.y == enemy.y) {
            isPlayer = true;
        } else if (enemy.x == extraction.x && enemy.y == extraction.y) {
            isExit = true;
        }
        for (Wall wall : walls) {
            if (enemy.x == wall.x && enemy.y == wall.y) {
                isWall = true;
                break;
            }
        }
        if (enemy.x < 0 || enemy.x >= 50 || enemy.y < 0 || enemy.y >= 50) {
            isWall = true;
        }
        for (Enemy otherEnemy : enemies) {
            if (enemy.enemyNum != otherEnemy.enemyNum) {
                if (enemy.x == otherEnemy.x && enemy.y == otherEnemy.y) {
                    isEnemy = true;
                }
            }
        }
    }

    if (!isPlayer && !isWall && !isExit && !isEnemy) {
        isOpen = true;
    }

    return isOpen;
}

void moveEnemy() {
    int enemyMovement = rand() % 2 + 1;
    int enemyDirection = rand() % 2 + 1;
    bool isOpen;

    for (auto it = enemies.begin(); it < enemies.end(); it++) {
        if ((abs(player.x - it->x) <= 5) && (abs(player.y - it->y) <= 5)) {
            if (it->y == player.y) {
                if (it->x < player.x) {
                    it->x++;
                    isOpen = checkSpace();
                    if (!isOpen) {
                        it->x--;
                    }
                } else if (it->x > player.x) {
                    it->x--;
                    isOpen = checkSpace();
                    if (!isOpen) {
                        it->x++;
                    }
                }
            } else if (it->x == player.x) {
                if (it->y < player.y) {
                    it->y++;
                    isOpen = checkSpace();
                    if (!isOpen) {
                        it->y--;
                    }
                } else if (it->y > player.y) {
                    it->y--;
                    isOpen = checkSpace();
                    if (!isOpen) {
                        it->y++;
                    }
                }
            } else {
                if (enemyMovement == 1) {
                    if (it->x < player.x) {
                        it->x++;
                        isOpen = checkSpace();
                        if (!isOpen) {
                            it->x--;
                        }
                    } else if (it->x > player.x) {
                        it->x--;
                        isOpen = checkSpace();
                        if (!isOpen) {
                            it->x++;
                        }
                    }
                } else if (enemyMovement == 2) {
                    if (it->y < player.y) {
                        it->y++;
                        isOpen = checkSpace();
                        if (!isOpen) {
                            it->y--;
                        }
                    } else if (it->y > player.y) {
                        it->y--;
                        isOpen = checkSpace();
                        if (!isOpen) {
                            it->y++;
                        }
                    }
                }
            }
        } else {
            if (enemyMovement == 1) {
                if (enemyDirection == 1) {
                    it->y--;
                    isOpen = checkSpace();
                    if (!isOpen) {
                        it->y++;
                    }
                } else if (enemyDirection == 2) {
                    it->y++;
                    isOpen = checkSpace();
                    if (!isOpen) {
                        it->y--;
                    }
                }
            } else if (enemyMovement == 2) {
                if (enemyDirection == 1) {
                    it->x--;
                    isOpen = checkSpace();
                    if (!isOpen) {
                        it->x++;
                    }
                } else if (enemyDirection == 2) {
                    it->x++;
                    isOpen = checkSpace();
                    if (!isOpen) {
                        it->x--;
                    }
                }
            }
        }
    }
}

void generateFood() {
    int numFood = rand() % 5 + 2;

    for (int i = 0; i < numFood; i++) {
        food.x = rand() % dungeonWidth;
        food.y = rand() % dungeonHeight;
        for (Wall wall : walls) {
            if (food.x == wall.x && food.y == wall.y) {
                food.x++;
            }
        }
        foods.push_back(food);
    }
}

void generateExit() {
    extraction.x = rand() % dungeonWidth;
    extraction.y = rand() % dungeonHeight;
    if (extraction.x == player.x && extraction.y == player.y) {
        extraction.x++;
    }
    for (Wall wall : walls) {
        if (extraction.x == wall.x && extraction.y == wall.y) {
            extraction.x++;
        }
    }
    for (Loot loot : loots) {
        if (extraction.x == loot.x && extraction.y == loot.y) {
            extraction.x++;
        }
    }
    for (Food food : foods) {
        if (extraction.x == food.x && extraction.y == food.y) {
            extraction.x++;
        }
    }
}

int main() {
    srand(time(0));


    generateWalls();
    generateLoot();
    generateEnemies();
    generateFood();
    spawnPlayer();
    generateExit();
    while (player.health > 0 && !isExtract) {
        system("clear");
        generateDungeon();
        movePlayer();
        moveEnemy();
    }

    if (isExtract) {
        cout << "You have made it to the extraction point!" << endl;
    } else if (player.health <= 0) {
        cout << "GAME OVER!! YOU HAVE DIED!" << endl;
    }

    return 0;
}