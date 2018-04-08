# OpenGL Animator

[![OpenGL Animator](https://raw.githubusercontent.com/emargollo/Animator_OpenGL/master/docs/animator.gif)](https://github.com/emargollo/Animator_OpenGL)

Project developed to study mesh rendering and skeleton animation with OpenGL.

The meshes, skeletons and animations are loaded from a JSON file with the following structure:


```json
{
  "texture": "texName",
  "animations": [{
      "name": "animName",
      "duration": "<time_in_second>",
      "bones":[{
        "name":"boneName",
        "pos_keys":[{"x":1, "y":1, "z":1, "time":1}, "..."],
        "rot_keys":[{"w":1, "x":1, "y":1, "z":1, "time":1}, "..."],
        "scale_keys":[{"x":1, "y":1, "z":1, "time":1}, "..."]
      }, "..."]
    }, "..."],
  "meshes":[{
    "bones":[{
      "id": "<bone_id>",
      "name": "boneName",
      "pos":{"x":1, "y":1, "z":1},
      "rot":{"w":1, "x":1, "y":1, "z":1},
      "scale":{"x":1, "y":1, "z":1}
    }, "..."],
    "vertices":[{
      "id": "<vertex_id>",
      "normal": {"x":1, "y":1, "z":1},
      "pos": {"x":1, "y":1, "z":1},
      "texcoord": {"x":1, "y":1},
      "joints":[{
        "id": "<joint_id>",
        "weight": "<joint_weight>"
      }, "..."]
    }, "..."],
    "indices":["<id>", "<id>", "..."]
  }, "..."],
  "rootnode":{
    "name": "<node name>",
    "pos":{"x":1, "y":1, "z":1},
    "rot":{"w":1, "x":1, "y":1, "z":1},
    "scale":{"x":1, "y":1, "z":1},
    "children": "<vector of nodes with name, pos, rot, scale and children>"
  }
}
```

The parsing of the JSON file is done using [Nlohmann's JSON for Modern C++](https://github.com/nlohmann/json).

The class structure is inspired from [ThinMatrix's tutorial playlist](https://www.youtube.com/watch?v=f3Cr8Yx3GGA&list=PLRIWtICgwaX2tKWCxdeB7Wv_rTET9JtWW), and so is the animated model used for this project.

The rendering is performed with [OpenGL](https://www.opengl.org/) and most of the math operations are done using [glm](https://glm.g-truc.net/0.9.8/index.html).

The textures are loaded using [nothings' stb library](https://github.com/nothings/stb).
