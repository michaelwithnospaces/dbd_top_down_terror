#include "Generator.h"

// Constructor to initialize the generator
Generator::Generator(Vector2 pos, std::vector<std::string> framePaths, float frameDuration) 
{
    // Initialize member variables inside the constructor body
    position = pos;
    currentFrame = 0;
    frameTime = frameDuration;
    currentFrameTime = 0.0f;

    // Load each frame as a texture
    for (const std::string &path : framePaths) {
        frames.push_back(LoadTexture(path.c_str()));
    }
}

// Destructor to unload textures
Generator::~Generator() {
    for (Texture2D &frame : frames) {
        UnloadTexture(frame);
    }
}

// Update the generator animation
void Generator::Update(float deltaTime) {
    currentFrameTime += deltaTime;
    if (currentFrameTime >= frameTime) {
        currentFrame = (currentFrame + 1) % frames.size(); // Loop through frames
        currentFrameTime = 0.0f;
    }
}

// Draw the generator with scaling
void Generator::Draw() {
    if (!frames.empty()) {
        Vector2 scale = { 0.15f, 0.15f };  // Scale down the generator by 50%
        DrawTextureEx(frames[currentFrame], position, 0.0f, scale.x, WHITE);
    } else {
        // Draw a rectangle if no frames were loaded
        DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y), 40, 40, RED);
    }

    if (isInteracting && !(this->isGeneratorComplete())) {
        // Draw circular progress bar
        DrawCircle(static_cast<int>(position.x + 40), static_cast<int>(position.y - 50), 40, Fade(LIGHTGRAY, 0.6f));
        DrawCircleSector((Vector2){ position.x + 40, position.y - 50 }, 30, 0, 360 * interactionProgress, 32, GREEN);

        if (skillCheckActive) {
            std::cout << "SKILL CHECK ACTIVE" << std::endl; // DEBUG
            DrawCircleLines(static_cast<int>(position.x + 40), static_cast<int>(position.y - 50), 50, RED); 
        }
    } else if (this->isGeneratorComplete()) {
        DrawCircle(static_cast<int>(position.x + 25), static_cast<int>(position.y + 20), 40, Fade(YELLOW, 0.2f));
    }
}

Vector2 Generator::GetPosition() {
    return position;
}

Vector2 Generator::GetScaledSize() const {
    if (!frames.empty()) {
        Vector2 scale = { 0.15f, 0.15f };  // Use the same scale factor
        
        // Get the size of the current frame
        float originalWidth = static_cast<float>(frames[currentFrame].width);
        float originalHeight = static_cast<float>(frames[currentFrame].height);

        // Calculate the new size after scaling
        float newWidth = originalWidth * scale.x;
        float newHeight = originalHeight * scale.y;

        // Return the scaled size as a Vector2
        return { newWidth, newHeight };
    } else {
        // If there are no frames, return a default size (for example, {0, 0} or some default value)
        return { 0.0f, 0.0f };
    }
}

void Generator::Interact(float deltaTime) {
    // If the player is interacting and the progress is not complete
    if (isInteracting && interactionProgress < 1.0f) {
        interactionProgress += deltaTime * 0.1f;
        std::cout << "Interaction Progress: " << interactionProgress << std::endl; // DEBUG

        // Skill check logic
        skillCheckTimer -= deltaTime;
        if (skillCheckTimer <= 0.0f && !skillCheckActive) {
            // Trigger a skill check
            skillCheckActive = true;
            skillCheckWindow = (rand() & 3) + 1;
            skillCheckTimer = 5.0f;
        }

        // TODO: Implement Skill Check
        // Check if skill check is active and player success or fail
        if (skillCheckActive) {
            // Render skill check window
            // "IsKeyPressed(KEY_SPACE)" is a quick reaction key for skill check
            if (IsKeyPressed(KEY_SPACE)) {
                skillCheckSuccess = true;
                skillCheckActive = false;
                interactionProgress += 0.1; // Completion bonus
            } else if (skillCheckTimer <= 0.0f) {
                // If the timer runs out, player fails check
                skillCheckSuccess = false;
                skillCheckActive = false;
                interactionProgress -= 0.1; // Failure penalty
            }
        }
        // Clamp progress between 0 and 1
        if (interactionProgress > 1.0f) interactionProgress = 1.0f;
        if (interactionProgress < 0.0f) interactionProgress = 0.0f;
    }
}

bool Generator::isGeneratorComplete() {
    if (interactionProgress < 1.0f) {
        return false;
    } else {
        return true;
    }
}