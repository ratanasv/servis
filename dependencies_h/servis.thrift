namespace cpp servis

struct V3 {
    1: double x = 0.0,
    2: double y = 0.0,
    3: double z = 0.0,
}

struct Terrain {
    1: list<V3> vertices,
    2: list<i32> indices,
    3: optional list<V3> colors,
}

service VISTAS {
    Terrain getTerrain(1:string fileName)
}
