



```
typedef std::shared_ptr<Resource> ResourcePtr;

ResourcePtr loadLevel = ResourceManager::get<Image>("imgs/load_level.png");

static_cast<Image>(loadLevel)->setPosition(Vect2f(10.0f, 20.0f));

window.display(loadLevel);
```