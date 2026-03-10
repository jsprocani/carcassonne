#ifndef CARCASSONNE_STRUCTURES
#define CARCASSONNE_STRUCTURES
#include <raylib.h>

typedef enum landscape land;
enum landscape{nothing, city, pre, road, blazon, abbey, village};

typedef enum cardinal cardinal;
enum cardinal{N, E, S, W, X};


typedef enum class class;
enum class{none, thief, knight, monk, peasant};

typedef struct coordinates coord;
struct coordinates{
    int x, y;
};

typedef struct rectangle rect;
struct rectangle{
    int x, y;
    unsigned int w, h;
};

typedef struct icon icon;
struct icon{
    Image image;
    Texture2D texture;
};

typedef struct meeple meeple;
struct meeple{
    _Bool posed, dominant;
    cardinal position;
    class role;
    Color color;
};

typedef struct player player;
struct player{
    int id, count, score;
    Color color;
    meeple meeples[7];
};

typedef struct tile tile;
struct tile{
    int id;
    coord position;
    land sides[4], center;
    Image image;
    meeple *meeple;
    Texture2D texture;
};

typedef struct grid grid;
struct grid{
    tile **tiles;
    unsigned int top, right, bottom, left, center;
};

typedef struct deck deck;
struct deck{
    tile *tiles;
    unsigned int current, size;
};

typedef struct perimeter perim;
struct perimeter{
    coord *outline;
    int size;
};

#endif // CARCASSONNE_STRUCTURES
