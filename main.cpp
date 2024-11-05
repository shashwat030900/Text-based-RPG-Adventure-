#include <iostream>
#include <ctime>

class Player {
    
private:
    int health;
    int maxHealth;
    int baseDamage;
    int extraDamage;
    int healAmount;
    
public:
    Player(int maxHealth, int baseDamage, int minExtraDamage, int maxExtraDamage, int minHeal, int maxHeal)
        : health(maxHealth), maxHealth(maxHealth), baseDamage(baseDamage) {
        
        srand(time(0));

       
        extraDamage = minExtraDamage + rand() % (maxExtraDamage - minExtraDamage + 1);
        healAmount = minHeal + rand() % (maxHeal - minHeal + 1);
    }

    virtual void takeDamage(int damage) {
        health = (health - damage < 0) ? 0 : health - damage;
        std::cout << "Player takes " << damage << " damage. Remaining health: " << health << std::endl;
    }

    virtual int giveAdditionalDamage() {
        return extraDamage; 
    }

    virtual void heal() {
        if (health == maxHealth) {
            std::cout << "Health is already full. Healing cannot take place." << std::endl;
            return; 
        }
        
        health = (health + healAmount > maxHealth) ? maxHealth : health + healAmount;
        std::cout << "Player heals " << healAmount << " health. Current health: " << health << std::endl;
    }

    int getHealth() const {
        return health;
    }

    int getBaseDamage() const {
        return baseDamage;
    }


};

class SkillfulPlayer : public Player {
public:
    SkillfulPlayer() : Player(100, 5, 1, 3, 2, 5) {}
};

class BalancedPlayer : public Player {
public:
    BalancedPlayer() : Player(75, 10, 2, 5, 3, 7) {}
};

class RagedPlayer : public Player {
public:
    RagedPlayer() : Player(50, 15, 3, 7, 5, 10) {}
};

Player* createPlayer(char type) {
    switch (type) {
        case 'A': return new SkillfulPlayer();
        case 'B': return new BalancedPlayer();
        case 'C': return new RagedPlayer();
        default: return nullptr;
    }
}

void gameTurn(Player& attacker, Player& defender, const std::string& playerName) {
    std::cout << "It's " << playerName << "'s turn:" << std::endl;
    std::cout << "1. Heal\n2. Attack\n";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        attacker.heal();
    } else if (choice == 2) {
        int totalDamage = attacker.getBaseDamage() + attacker.giveAdditionalDamage();
        defender.takeDamage(totalDamage);
    } else {
        std::cout << "Invalid choice. Turn skipped." << std::endl;
    }
}

int main() {
    std::cout << "Player 1, choose your type (A for Skillful, B for Balanced, C for Raged): ";
    char player1Type;
    std::cin >> player1Type;
    
    std::cout << "Player 2, choose your type (A for Skillful, B for Balanced, C for Raged): ";
    char player2Type;
    std::cin >> player2Type;

    Player* player1 = createPlayer(player1Type);
    Player* player2 = createPlayer(player2Type);

    if (!player1 || !player2) {
        std::cout << "Invalid player type." << std::endl;
        return 1;
    }

    while (player1->getHealth() > 0 && player2->getHealth() > 0) {
        gameTurn(*player1, *player2, "Player 1");
        if (player2->getHealth() > 0) { 
            gameTurn(*player2, *player1, "Player 2");
        }
    }

    std::cout << (player1->getHealth() > 0 ? "Player 1 wins!" : "Player 2 wins!") << std::endl;

    delete player1;
    delete player2;

    return 0;
}
