#ifndef GENERATOR_H
#define GENERATOR_H

#include "raylib.h"
#include <vector>
#include <string>
#include <iostream>

class Generator {
public:
    Generator(Vector2 position, std::vector<std::string> framePaths, float frameTime);
    ~Generator();
    
    void Update(float deltaTime); // Update the generator's frame animation
    void Draw(); // Draw the generator on the screen
    void Interact(float deltaTime); // Fucntion to handle interaction logic

    Vector2 GetPosition(); // Get the position of the generator
    Vector2 GetScaledSize() const; // Get the scaled size of the generator
    bool isGeneratorComplete();

        // Interaction-specific variables
    bool isInteracting = false;      // Is the player interacting with the generator
    float interactionProgress = 0.0f; // Progress bar (ranges from 0 to 1)
    float skillCheckTimer = 0.0f;     // Timer for when to trigger skill checks
    bool skillCheckActive = false;    // Is a skill check active
    float skillCheckWindow = 0.0f;    // Window of the skill check
    bool skillCheckSuccess = false;   // Did the player succeed in the skill check
    
private:
    Vector2 position;
    std::vector<Texture2D> frames;  // Store the frames as a vector of textures
    int currentFrame;               // Current frame being displayed
    float frameTime;                // Time between frames
    float currentFrameTime;         // Counter to switch frames
};

#endif // GENERATOR_H
