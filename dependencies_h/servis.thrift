namespace cpp servis

struct V3 {
    1: double x = 0.0,
    2: double y = 0.0,
    3: double z = 0.0,
}

struct Terrain {
    1: list<V3> vertices,
    2: list<i32> indices
}

struct Texture {
	1: list<V3> texture,
	2: list<V3> texCoord
}

service VISTAS {
    Terrain getTerrain(1:string fileName)
	list<V3> getColor(1:string fileName, 2:string attribute)
	Texture getNormalMap(1:string fileName)
	Texture getTextureMap(1:string fileName, 2:string attribute)
	list<string> getAttributes(1:string fileName)
}
