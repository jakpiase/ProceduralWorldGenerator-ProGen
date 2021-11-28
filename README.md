# ProGen
## Implementation of procedural world content generator.
### How to build
```
git clone https://github.com/jakpiase/ProceduralWorldGenerator-ProGen.git
cd ProceduralWorldGenerator-ProGen
mkdir build && cd build
cmake .. && make -j
```
**Note:** you may also need to install [ZLIB](https://zlib.net/) if your system does not have it yet

### How to run
./ProGen_run room_content=**<content_type>** room_content_path=**<room_content_path>**

**<content_type>** determines what kind of room content will be used, it can be one of:
- none (default)
- static
- generate

**Note:** to use "room_content=generate" you must have tensorflow 2.5.0 installed

**<room_content_path>** determines the filepath to pregenerated rooms, default = "valid_images.npy" it is used only if **<content_type>**=static

