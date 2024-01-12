#include "GameEngine.h"

#include <SDL2/SDL_mixer.h>

#include <utility>

GameEngine *GameEngine::instance = nullptr;

GameEngine::GameEngine(unsigned short fps, int screen_w, int screen_h, int level_w, int level_h) : FRAMES_PER_SECOND(fps), SCREEN_WIDTH(screen_w), SCREEN_HEIGHT(screen_h), LEVEL_WIDTH(level_w), LEVEL_HEIGHT(level_h) {}

GameEngine::~GameEngine()
{
}

/*Initializes the SDL components. Returns true if successful*/
bool GameEngine::init_SDL_libraries() { return SYSTEM.initSDLComponents(); }

/*Initializes a gamewindow, with top left corner at screens x and y. If x- or y-value is negative, the window will be centered on the screen.
Returns true if the initialization was successful.*/
bool GameEngine::init_SDL_window(std::string windowTitle, int xPosition,
                                 int yPosition)
{
    return SYSTEM.initWindowAndRenderer(windowTitle, xPosition, yPosition,
                                        SCREEN_WIDTH, SCREEN_HEIGHT);
}

/*Plays the sound from specified soundpath the specified amount of repeats. Use
-1 for infinite repeats.

The sound will be played in a "Channel". All Sprite-objects gets a specific
channel assigned to them at construction, see "assigned_channel". To make sure
the channel is free (when used outside of objects sub-classing Sprite), use
get_sound_channel() from GameEngine.

Returns the channel the sound is playing on (int), which can be used for
stopping sound later. */
int GameEngine::play_sound(const std::string &soundpath, int channel,
                           int repeats) const
{
    return Mix_PlayChannel(
        channel, AssetManager::get_instance()->get_sound(soundpath), repeats);
}

/*Stops a sound playing on specified soundchannel.
Use -1 to stop all channels.*/
void GameEngine::stop_sound(int soundchannel) const
{
    Mix_HaltChannel(soundchannel);
}

// TODO: How to force objects to use this? Or is this even needed?

/*Will return a free soundchannel that can be used solely by an object.
However, the implementer can break this system by using a channel given to them
by entering -1 as channel in play_sound....*/
int GameEngine::get_sound_channel()
{
    int available_soundchannels = Mix_AllocateChannels(-1);
    if (available_soundchannels != soundchannels_in_use.size())
    {
        soundchannels_in_use.resize(available_soundchannels);
    }

    int i = 0;
    for (i = 0; i < soundchannels_in_use.size(); ++i)
    { // Check if a channel has been given back
        if (i != soundchannels_in_use[i])
        {
            soundchannels_in_use[i] = i;
            return i;
        }
    }

    int newSize = Mix_AllocateChannels(Mix_AllocateChannels(-1) * 2); // No channel available, have to resize
    soundchannels_in_use.resize(newSize);
    soundchannels_in_use[++i] = i;
    return i;
}

void GameEngine::remove_used_channel(int channel)
{
    soundchannels_in_use[channel] = -1;
}

/* ---------------------------- RUN GAME ----------------------------*/

void GameEngine::run_game()
{
    SDL_Event event;
    paused = false;
    key_quit = false;
    running = true;
    Uint32 tick_interval = 1000 / FRAMES_PER_SECOND; // blir alltså millisekunder mellan ticks.
    while (running)
    {
        Uint32 next_tick = SDL_GetTicks() + tick_interval;

        while (SDL_PollEvent(&event))
        {
            // QUIT - Städa upp allt som har allokerats och returnera. Quit innebär att hela spelet ska stängas ned!
            if (event.type == SDL_QUIT || key_quit)
            {
                running = false;
                delete AssetManager::get_instance();
            }
            else if (event.type == SDL_KEYDOWN)
            {
                // Kolla om KEY finns i key_to_function_map, isåfall hämta den och kör funktionen
                if (key_to_function_map->count(event.key.keysym.sym) > 0)
                {
                    key_to_function_map->at(event.key.keysym.sym)();
                }

            } else if (event.type == SDL_MOUSEMOTION) {
                AssetManager::get_instance()->mouse_moved_all(event.motion.x,
                                                              event.motion.y);
            }
        }

        SDL_RenderClear(SYSTEM.renderer);

        AssetManager::get_instance()->tick_all();
        AssetManager::get_instance()->remove_marked();
        AssetManager::get_instance()->add_new_sprites_to_game();
        AssetManager::get_instance()->draw_all();

        SDL_RenderPresent(SYSTEM.renderer);

        int delay = next_tick - SDL_GetTicks(); // Hur mycket tid det är kvar till nästa tick
        if (delay > 0)
            SDL_Delay(delay);

        while (paused)
        {
            SDL_PollEvent(&event);
            if (event.type == SDL_QUIT || key_quit)
            {
                running = false;
                delete AssetManager::get_instance();
            }
            if (event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == press_to_resume)
                paused = false;
            SDL_Delay(100);
        }
    }
}

/*Will use the supplied map to call a gamedeveloper-implemented function when the player presses a key.

See GameEngine's use_function_on_all_sprites for further information on how to implement a function where a key pressed should make Sprite-objects react.
*/
void GameEngine::load_keys(std::unordered_map<SDL_Keycode, funcPtr> &map)
{
    key_to_function_map = &map;
}

/*GameEngine will use the supplied functionpointer argument, and use that function on all sprites once per gameloop.
The supplied function pointer needs to have signature: void function_name(Sprite* sprite_ptr)

The game developer can use dynamic cast to check if the sprite is of the right subclass of Sprite, to make sure the function is used on the right object.

Example of use:

void move_player_left(Sprite* sprite){
    if (Player* p = dynamic_cast<Player*> sprite) {
        p->move_left();
    }
}

void move_player_left_wrapper() {
    GameEngine::get_instance()->use_function_on_all_sprites(move_player_left);
}

std::unordered_map<SDL_Keycode, void (*function_pointer)()> key_mappings;

key_mappings.emplace(SDLK_LEFT, move_player_left_wrapper);

GameEngine::get_instance()->load_keys(key_mappings);

*/
void GameEngine::use_function_on_all_sprites(funcPtr2 f)
{
    AssetManager::get_instance()->handle_key_event(f);
}

void GameEngine::pause(SDL_Keycode key_press_to_resume)
{
    paused = true;
    press_to_resume = key_press_to_resume;
}

void GameEngine::quit() { key_quit = true; }

/*Loads assets from the vector*/
void GameEngine::load_assets(std::vector<std::string> assets)
{
    for (auto asset : assets)
    {
        if ((asset.find(".png") != std::string::npos) ||
            (asset.find(".jpg") != std::string::npos))
        {
            load_img(asset);
        }
        else if ((asset.find(".mp3") != std::string::npos) ||
                 (asset.find(".wav") != std::string::npos))
        {
            load_sound(asset);
        }
        else
        {
            std::cerr << "Unknown file type: " << asset << std::endl;
        }

        // TODO: add pathway?
        // TODO: Figure out what the above means, write better comments
    }
}

/*Loads an image from the path*/
bool GameEngine::load_img(std::string path)
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface == nullptr)
    {
        std::cerr << "Error loading image: " << path << std::endl;
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(SYSTEM.renderer, surface);
    if (texture == nullptr)
    {
        std::cerr << "Error creating texture from surface: " << path
                  << std::endl;
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    AssetManager::get_instance()->add_texture(path, texture);
    SDL_FreeSurface(surface);

    return true;
}

/*Loads a sound from the path, as a Chunk*/
bool GameEngine::load_sound(std::string path)
{
    Mix_Chunk *chunk = Mix_LoadWAV(path.c_str());

    if (chunk == nullptr)
    {
        std::cerr << "Error loading sound: " << path << std::endl;
        std::cerr << "SDL error: " << Mix_GetError();
        return false;
    }

    AssetManager::get_instance()->add_sound(path, chunk);
    return true;
}

void GameEngine::add_sprite(Sprite &sprite)
{
    if (running)
        AssetManager::get_instance()->add_while_running(sprite);
    else    
        AssetManager::get_instance()->add(sprite);
}

void GameEngine::set_level_background(LevelBackground &bg)
{
    AssetManager::get_instance()->set_level_background(bg);
}

int GameEngine::get_screen_width() const
{
    return SCREEN_WIDTH;
}

int GameEngine::get_screen_height() const
{
    return SCREEN_HEIGHT;
}

void GameEngine::set_screen_size(int width, int height)
{
    SDL_SetWindowSize(SYSTEM.window, width, height);
}

int GameEngine::get_level_height() const
{
    return LEVEL_HEIGHT;
}
int GameEngine::get_level_width() const
{
    return LEVEL_WIDTH;
}
void GameEngine::set_level_size(int width, int height)
{
    LEVEL_WIDTH = width;
    LEVEL_HEIGHT = height;
}

/*GameEngine is singleton. The first time this is called, a new instance will be created with given arguments and return it. All calls afterwards will return that instance.*/
GameEngine *GameEngine::get_instance(unsigned short fps, int screen_width, int screen_height, int level_width, int level_height)
{
    if (instance == nullptr)
    {
        instance = new GameEngine(fps, screen_width, screen_height, level_width, level_height);
    }
    return instance;
}
