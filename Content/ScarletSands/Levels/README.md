# Game Levels

This directory contains game level maps.

## L_World_Persistent

Create this level as a placeholder for the main game world:

### Level Setup

1. **Create New Level**
   - Name: `L_World_Persistent`
   - Template: Basic or Open World

2. **Minimal Requirements**:
   - Player Start (spawn point for new game)
   - Basic terrain (flat plane or simple landscape)
   - Directional Light
   - Sky Light
   - Atmospheric effects (optional)
   - Post Process Volume

3. **Purpose**:
   - This is a **placeholder map** for New Game/Continue transitions
   - When player clicks "New Game" or "Continue", they transition to this map
   - Full gameplay systems will be implemented later
   - For now, just needs to be a valid playable map

### Testing Placeholder

For testing purposes, you can add:
- Text renderer showing "World Map - Gameplay Coming Soon"
- Simple walk-around area to verify transition works
- Exit option (press Escape to quit)

### Game Mode

- Should use a basic game mode (can be default)
- Will need proper game mode later for actual gameplay
- For now, just needs to spawn player and be functional

## Notes

- This is **scope-limited** - no gameplay systems yet
- Just proving the menu → world transition works
- Future work will expand this into the full game world
