#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "j1Module.h"
#include "Player.h"

// TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
// ----------------------------------------------------
struct Image
{

	p2SString source;
	int width;
	int height;

};

struct TerrainType
{

	p2SString name;
	int tile;

};

struct Tile
{

	int id;
	p2SString terrain[4];

};

/*struct TileSet
{
	p2SString name;
	int firstgid;
	int margin;
	int spacing;
	int tile_width;
	int tile_height;
	Image image;
	TerrainType terraintype;
	p2List<Tile*> tiles;
	bool LoadTile(pugi::xml_node&, Tile*);

};*/


struct Properties
{
	struct Property
	{
		p2SString name;
		int value;
		float valuefloat;
	};

	~Properties()
	{
		//p2List_item<Property*>* item;
		p2List_item<Property*>* item = properties.start;

		while (item != properties.end)
		{
			RELEASE(item->data);
			item = item->next;
		}

		properties.clear();
	}

	int GetInt(const char* name, int default_value = 0) const;
	float GetFloat(const char* name, float default_value = 0) const;

	p2List<Property*> properties;
};

struct ParticleObject
{
	std::string name;
	int			width;
	int			height;
	int			pos_x;
	int			pos_y;
	Properties	properties;
};

struct TileSet
{
	~TileSet()
	{
		App->tex->UnLoad(texture);
	}

	SDL_Rect GetTileRect(int id) const;

	p2SString name;
	int					firstgid;
	int					margin;
	int					spacing;
	int					tile_width;
	int					tile_height;
	SDL_Texture*		texture;
	int					tex_width;
	int					tex_height;
	int					num_tiles_width;
	int					num_tiles_height;
	int					offset_x;
	int					offset_y;
};

struct MapLayer
{
	std::string name;
	int			width;
	int			height;
	uint*		data;
	Properties	properties;

	MapLayer() : data(NULL)
	{}

	~MapLayer()
	{
		RELEASE(data);
	}

	inline uint Get(int x, int y) const
	{
		return data[(y*width) + x];
	}
};


// TODO 1: Create a struct needed to hold the information to Map node
enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};

enum RenderOrder
{
	RIGHT_DOWN = 0,
	RIGHT_UP,
	LEFT_DOWN,
	LEFT_UP
};

struct MapData
{

	int width;
	int height;
	int tile_width;
	int tile_height;
	MapTypes			type;

	p2List<TileSet*> tilesets;
	p2List<MapLayer*> layers;
	p2List<ParticleObject*> particleobj;
};


// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw(int time);

	TileSet * GetTilesetFromTileId(int id) const;

	iPoint MapToWorld(int x, int y) const;

	iPoint WorldToMap(int x, int y) const;

	// Called before quitting
	bool CleanUp();

	iPoint GetPositionStart();

	bool NextLvl(int x, int y, int width, int height) const;

	bool CheckDead(int x, int y, int width, int height) const;

	bool MovementCost(int x, int y, int width, int height, Direction dir) const;

	// Load new map
	bool Load(const char* path);

private:
	
	//Load map function are private alone map can acces
	bool LoadMap();
	bool loadTileSet(pugi::xml_node&, TileSet*);

	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);

	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);

	bool LoadParticleObject(pugi::xml_node& node, ParticleObject* layer);

	bool LoadProperties(pugi::xml_node& node, Properties& properties);

	void SetParticles();

public:

	// TODO 1: Add your struct for map info as public for now
	MapData mapdata;
	//TileSet tileset;
private:
	fPoint posBackground;
	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__