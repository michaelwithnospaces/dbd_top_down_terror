#include "raylib.h"
#include "Generator.h"
#include "Platform/Window.h"

#include <vector>
#include <string>
#include <iostream>

#define PLAYER_SIZE 40
#define TILE_SIZE 32

int main(void) {
	
	Window* window = new Window();

    const int screenWidth = 1920;
    const int screenHeight = 1080;
	window->Init("Dead by Daylight: Top-Down Terror", screenWidth, screenHeight);

    Rectangle player = { 200, 200, PLAYER_SIZE, PLAYER_SIZE };

    Camera2D camera = { 0 };
    camera.target = (Vector2){ player.x, player.y };
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };  // Center camera on screen
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Load generator frames (20 frames)
    std::vector<std::string> generatorFrames;
    for (int i = 0; i < 20; i++) {
        // Format the frame filename (e.g., "resources/generator_frame01.png")
        generatorFrames.push_back(TextFormat("resources/Generator/generator_frame%02i.png", i));
    }

    // Create the generator object with 20 frames and set the frame time (e.g., 0.05 seconds per frame)
    Generator generator((Vector2){ 400, 300 }, generatorFrames, -1.0f); // Adjust frame time as needed

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (window->IsOpen())    // Detect window close button or ESC key
    {
        // Generator hitbox
        float topOffset = 70.0f;
        Rectangle generatorPhysicalRect = {
            generator.GetPosition().x, 
            generator.GetPosition().y + topOffset, 
            generator.GetScaledSize().x, 
            generator.GetScaledSize().y - topOffset
        };
        Rectangle generatorInteractionHitbox = {
            generator.GetPosition().x - 25,  
            generator.GetPosition().y - 25 + topOffset,  
            generator.GetScaledSize().x + 50, 
            generator.GetScaledSize().y + 50 - topOffset
        };

        // DEBUG
        // std::cout << "Generator x: " << generator.GetPosition().x << "\nGenerator y: " << generator.GetPosition().y;
        // std::cout << "\n Generator size x: " << generator.GetScaledSize().x << "\n Generator size y: " << generator.GetScaledSize().y << std::endl;

        Vector2 oldPosition = {player.x, player.y};

        if (IsKeyDown(KEY_S)) player.y += 3.0f;
        else if (IsKeyDown(KEY_W)) player.y -= 3.0f;
        if (IsKeyDown(KEY_D)) player.x += 3.0f;
        else if (IsKeyDown(KEY_A)) player.x -= 3.0f;

        Rectangle playerRectangle = {player.x, player.y, PLAYER_SIZE, PLAYER_SIZE};

        // Physical hitbox
        if (CheckCollisionRecs(playerRectangle, generatorPhysicalRect)) {
            player.x = oldPosition.x;
            player.y = oldPosition.y;
        }

        // Hitbox for interaction
        if (CheckCollisionRecs(playerRectangle, generatorInteractionHitbox)) {
            if (!generator.isGeneratorComplete()) {
                DrawText("Press E to interact", 10, 10, 20, WHITE);
            } else {
                DrawText("GENERATOR COMPLETED", 10, 10, 20, GREEN);
            }
            
            if (IsKeyDown(KEY_E)) {
                generator.isInteracting = true; // Start interaction
                // Lock in place if interacting
                player.x = oldPosition.x;
                player.y = oldPosition.y;
                generator.Interact(GetFrameTime());
            } else {
                generator.isInteracting = false; // Stop interaction if released
            }
        }

        // Update camera to follow the player
        camera.target = (Vector2){ player.x, player.y };

        // Update generator animation
        generator.Update(GetFrameTime());

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground({ 34, 32, 52, 255 });
            
            BeginMode2D(camera);
                // Draw full scene with the camera following the player

                // Draw hitbox for debugging purposes
                DrawRectangleLines(
                    static_cast<int>(generatorInteractionHitbox.x), 
                    static_cast<int>(generatorInteractionHitbox.y), 
                    static_cast<int>(generatorInteractionHitbox.width), 
                    static_cast<int>(generatorInteractionHitbox.height), 
                    Fade(RED, 0.3f) 
                );

                // This is for the grid
                for (int i = 0; i < screenWidth/PLAYER_SIZE + 1; i++)
                {
                    DrawLineV((Vector2){(float)PLAYER_SIZE*i, 0}, (Vector2){ (float)PLAYER_SIZE*i, (float)screenHeight}, LIGHTGRAY);
                }

                for (int i = 0; i < screenHeight/PLAYER_SIZE + 1; i++)
                {
                    DrawLineV((Vector2){0, (float)PLAYER_SIZE*i}, (Vector2){ (float)screenWidth, (float)PLAYER_SIZE*i}, LIGHTGRAY);
                }

                DrawRectangleRec(player, RED);

                // Draw the generator
                generator.Draw();
                
            EndMode2D();

            DrawRectangle(0, 0, screenWidth, 30, Fade({ 34, 32, 52, 255 }, 0.6f));
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
