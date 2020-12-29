# Minigin

This project is my assignment for the final exam of the Programming 4 course at Digital Arts and Entertainment at Howest.

## Engine features

- SceneManager
- GameObject-Component system
- Flexible Input system
- Physics system using [Box2D](https://box2d.org/)


## Engine Order of Execution

```
OnPrepare()

OnPhysicsUpdate()    <---+
OnUpdate()               |  Game Loop
OnRender()               |
OnRenderImGui()      ----+

OnCleanup()
```

---

Github Repo: https://github.com/SeppahBaws/Minigin

---
##### This project is part of my education at [Digital Arts and Entertainment](http://digitalartsandentertainment.be).
![](https://cdn.seppedekeyser.be/img-ext/DAE_Howest_logo.png)

###### https://seppedekeyser.be
