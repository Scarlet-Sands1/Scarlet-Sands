# Title Backdrop Level

This directory contains the title screen backdrop level.

## L_TitleBackdrop

Create this level in the Unreal Editor:

### Level Setup

1. **Create New Level**
   - Name: `L_TitleBackdrop`
   - Template: Empty Level or Basic

2. **Level Components**:
   - **Camera**: Static camera positioned for title screen view
   - **Lighting**: Atmospheric lighting (Directional Light, Sky Light, Exponential Height Fog)
   - **Background**:
     - Static meshes for island scenery backdrop
     - OR Skybox with ocean/island vista
     - OR Simple gradient background
   - **Ambient Audio**: Optional ambient sound (waves, wind)

3. **Game Mode Override**:
   - World Settings → Game Mode Override: GameModeBase
   - Player Controller Class: TitleScreenPlayerController

4. **Post Process Volume**:
   - Add post-processing for cinematic look
   - Color grading for mood
   - Vignette effect optional

### Visual Style

The backdrop should convey the game's mysterious island setting:
- Distant island silhouettes
- Ocean or beach environment
- Sunset/dawn lighting for dramatic effect
- Fog/atmosphere for mystery

### Performance

- Keep backdrop simple (this is just a menu screen)
- Static lighting preferred
- Minimal dynamic elements
- Target 60+ FPS

### Audio

- Consider adding ambient loop (ocean waves, wind, birds)
- Should complement MUS_Title_Loop from UI audio

## Level Settings

Ensure these settings in World Settings:
- **Game Mode**: GameModeBase (or custom if created)
- **Default Pawn**: None (title screen doesn't need a pawn)
- **Player Controller**: TitleScreenPlayerController
- **Game Instance**: ScarletSandsGameInstance (set in Config/DefaultEngine.ini)

## Testing

1. Set as editor startup map in Project Settings
2. PIE (Play In Editor) should show title screen UI
3. Title music should play
4. Mouse cursor should be visible
5. Can navigate menus with keyboard/gamepad
