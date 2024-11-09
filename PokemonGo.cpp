#include <iostream>
#include <math.h>
using namespace std;

// https://pvpoke.com/moves/
enum types
{
    None,
    Normal,
    Fight,
    Flying,
    Poison,
    Ground,
    Rock,
    Bug,
    Ghost,
    Steel,
    Fire,
    Water,
    Grass,
    Electric,
    Psychic,
    Ice,
    Dragon,
    Dark,
    Fairy
};

// https://img.rankedboost.com/wp-content/uploads/2016/07/type-chart.jpg
double EFF[19][19] =
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0.625, 1, 0.391, 0.625, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1.6, 1, 0.625, 0.625, 1, 1.6, 0.625, 0.391, 1.6, 1, 1, 1, 1, 0.625, 1.6, 1, 1.6, 0.625},
        {1, 1, 1.6, 1, 1, 1, 0.625, 1.6, 1, 0.625, 1, 1, 1.6, 0.625, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 0.625, 0.625, 0.625, 1, 0.625, 0.391, 1, 1, 1.6, 1, 1, 1, 1, 1, 1.6},
        {1, 1, 1, 0.391, 1.6, 1, 1.6, 0.625, 1, 1.6, 1.6, 1, 0.625, 1.6, 1, 1, 1, 1, 1},
        {1, 1, 0.625, 1.6, 1, 0.625, 1, 1.6, 1, 0.625, 1.6, 1, 1, 1, 1, 1.6, 1, 1, 1},
        {1, 1, 0.625, 0.625, 0.625, 1, 1, 1, 0.625, 0.625, 0.625, 1, 1.6, 1, 1.6, 1, 1, 1.6, 0.625},
        {1, 0.391, 1, 1, 1, 1, 1, 1, 1.6, 1, 1, 1, 1, 1, 1.6, 1, 1, 0.625, 1},
        {1, 1, 1, 1, 1, 1, 1.6, 1, 1, 0.625, 0.625, 0.625, 1, 0.625, 1, 1.6, 1, 1, 1.6},
        {1, 1, 1, 1, 1, 1, 0.625, 1.6, 1, 1.6, 0.625, 0.625, 1.6, 1, 1, 1.6, 0.625, 1, 1},
        {1, 1, 1, 1, 1, 1.6, 1.6, 1, 1, 1, 1.6, 0.625, 0.625, 1, 1, 1, 0.625, 1, 1},
        {1, 1, 1, 0.625, 0.625, 1.6, 1.6, 0.625, 1, 0.625, 0.625, 1.6, 0.625, 1, 1, 1, 0.625, 1, 1},
        {1, 1, 1, 1.6, 1, 0.391, 1, 1, 1, 1, 1, 1.6, 0.625, 0.625, 1, 1, 0.625, 1, 1},
        {1, 1, 1.6, 1, 1.6, 1, 1, 1, 1, 0.625, 1, 1, 1, 1, 0.625, 1, 1, 0.391, 1},
        {1, 1, 1, 1.6, 1, 1.6, 1, 1, 1, 0.625, 0.625, 0.625, 1.6, 1, 1, 0.625, 1.6, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0.625, 1, 1, 1, 1, 1, 1, 1.6, 1, 0.391},
        {1, 1, 0.625, 1, 1, 1, 1, 1, 1.6, 1, 1, 1, 1, 1, 1.6, 1, 1, 0.625, 0.625},
        {1, 1, 1.6, 1, 0.625, 1, 1, 1, 1, 0.625, 0.625, 1, 1, 1, 1, 1, 1.6, 1.6, 1}};

// https://pogo.gamepress.gg/cp-multiplier
double CP_scalar[101] =
    {
        0.0940000000, 0.1351374318,
        0.1663978700, 0.1926509190,
        0.2157324700, 0.2365726613,
        0.2557200500, 0.2735303812,
        0.2902498800, 0.3060573775,
        0.3210876000, 0.3354450362,
        0.3492126800, 0.3624577511,
        0.3752356000, 0.3875924160,
        0.3995672800, 0.4111935514,
        0.4225000000, 0.4329264091,
        0.4431075500, 0.4530599591,
        0.4627984000, 0.4723360930,
        0.4816849500, 0.4908558003,
        0.4998584400, 0.5087017650,
        0.5173939500, 0.5259425113,
        0.5343543000, 0.5426357375,
        0.5507927000, 0.5588305862,
        0.5667545000, 0.5745691333,
        0.5822789000, 0.5898879072,
        0.5974000000, 0.6048236651,
        0.6121573000, 0.6194041216,
        0.6265671000, 0.6336491432,
        0.6406529500, 0.6475809666,
        0.6544356300, 0.6612192524,
        0.6679340000, 0.6745818959,
        0.6811649000, 0.6876849038,
        0.6941436500, 0.7005428700,
        0.7068842000, 0.7131691091,
        0.7193991000, 0.7255756136,
        0.7317000000, 0.7347410093,
        0.7377695000, 0.7407855938,
        0.7437894300, 0.7467812109,
        0.7497610400, 0.7527290867,
        0.7556855000, 0.7586303683,
        0.7615638400, 0.7644860647,
        0.7673971700, 0.7702972656,
        0.7731865000, 0.7760649616,
        0.7789327500, 0.7817900548,
        0.7846370000, 0.7874736075,
        0.7903000000, 0.7928039680,
        0.7953000100, 0.7978000150,
        0.8003000000, 0.8027999950,
        0.8053000000, 0.8078000000,
        0.8102999900, 0.8127999850,
        0.8152999900, 0.8177999900,
        0.8202999900, 0.8227999900,
        0.8252999900, 0.8277999900,
        0.8302999900, 0.8327999900,
        0.8352999900, 0.8377999900,
        0.8402999900, 0.84279999
    };
class Move
{
    public:
    string name;
    types movetype;
    int damage;
};
class ThunderShock : public Move
{
    public:
    ThunderShock()
    {
        name = "Thunder Shock";
        movetype = Electric;
        damage = 3;
    }
};
class FireSpin : public Move{
    public:
    FireSpin()
    {
        name = "Fire Spin";
        movetype = Fire;
        damage = 11;
    }
};

class Pokemon
{
    protected:
        string name;
        types type1, type2;
        int base_attack, base_defense, base_stamina;
        int iv_attack, iv_defense, iv_stamina;
        float level;
        Move *fastMove;

    public:
    string getName()
    {
        return name;
    }
    float getLevel()
    {
        return level;
    }
    float setLevel(float level)
    {
            if(level >= 0)
            {
                this->level = level;
            }
    }
    double getAttack()
    {
        return (base_attack + iv_attack) * CP_scalar[int((level - 1) * 2)];
    }
    double getDefense()
    {
        return (base_defense + iv_defense) * CP_scalar[int((level - 1) * 2)];
    }
    double getStamina()
    {
        return (base_stamina + iv_stamina) * CP_scalar[int((level - 1) * 2)];
    }
    double getCP()
    {
        return max((int)floor(getAttack() * sqrt(getDefense() * getStamina()) / 10), 10);
    }
    double getHP()
    {
        return floor(getStamina());
    }
    double moveDamage(Pokemon& P)
    {
        double stab = 1;
        if(P.type1 == fastMove->movetype || type2 == fastMove->movetype)
        {
              stab = 1.2;
        }
        double move_eff = EFF[fastMove->movetype][P.type1] * EFF[fastMove->movetype][P.type2];
        return floor(0.65 * fastMove->damage * getAttack() / P.getDefense() * stab * move_eff) + 1;
    }
};

class Pikachu: public Pokemon
{
    public:
        Pikachu()
        {
            name="Pikachu";
            type1 = Electric;
            type2 = None;
            base_attack = 112;
            base_defense = 96;
            base_stamina = 111;
            iv_attack = 15;
            iv_defense = 15;
            iv_stamina = 15;
            level = 30;
            fastMove = new ThunderShock();
        }
};

class Charzard: public Pokemon
{
    public:
        Charzard()
        {
            name="Charzard";
            type1= Fire;
            type2 = Flying;
            base_attack = 223;
            base_defense = 173;
            base_stamina = 186;
            iv_attack = 15;
            iv_defense = 15;
            iv_stamina = 15;
            level = 30;
            fastMove = new FireSpin();
        }
};

int main()
{
    Pokemon **pokedex = new Pokemon*[2];
    pokedex[0] = new Pikachu(); 
    pokedex[1] = new Charzard();

    for(int i = 0; i < 2; i++)
    {
        cout << pokedex[i] ->getName() << " ";
        cout << pokedex[i] ->getLevel() << " ";
        cout << pokedex[i] ->getAttack() << " ";
        cout << pokedex[i] ->getDefense() << " ";
        cout << pokedex[i] ->getStamina() << " ";
        cout << pokedex[i] ->getCP() << " ";
        cout << pokedex[i] ->getHP() << endl;
    } 

    cout << pokedex[0]->moveDamage(*pokedex[1]) << " ";
    cout << pokedex[1]->moveDamage(*pokedex[0]) << " ";
}
