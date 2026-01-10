# L_TitleBackdrop Level Specification

**Level Name**: L_TitleBackdrop
**Purpose**: Title screen backdrop level with atmospheric scene
**Player Controller**: TitleScreenPlayerController
**Game Mode**: Custom title screen game mode

## Level Overview

A visually appealing backdrop for the title screen featuring:
- Atmospheric island environment
- Cinematic camera positioning
- Ambient lighting
- Optional particle effects (mist, birds, etc.)
- Background ambient audio

## Required Actors

### 1. Player Start
- **Position**: (0, 0, 100)
- **Rotation**: Facing interesting view angle
- **Purpose**: Spawn point (not actually used, controller UI-only)

### 2. Directional Light (Sun)
- **Intensity**: 3.0
- **Color**: Warm (#FFE4B5 or similar)
- **Angle**: Low angle for dramatic lighting (sunrise/sunset)
- **Cast Shadows**: Yes
- **Mobility**: Static

### 3. Sky Light
- **Intensity**: 0.5
- **Source**: SLS Captured Scene
- **Mobility**: Static
- **Purpose**: Fill lighting for ambient

### 4. Atmospheric Fog (Optional)
- **Fog Density**: 0.02
- **Fog Height Falloff**: 0.2
- **Fog Max Opacity**: 0.6
- **Adds depth to scene**

### 5. Post Process Volume
- **Is Unbound**: True
- **Settings**:
  - Auto Exposure: Disabled or set to fixed
  - Bloom: Enabled, Intensity 0.5
  - Vignette: Slight darkening at edges
  - Color Grading: Slight desaturation for moody feel

### 6. Sky Sphere
- **Blueprint**: BP_Sky_Sphere (Unreal default)
- **Or**: Custom skybox with clouds
- **Sun Brightness**: 50
- **Clouds Speed**: Slow (0.1)

### 7. Cinematic Camera (Optional)
- **Position**: Positioned for best view
- **Focal Length**: 35-50mm
- **Depth of Field**: Slight bokeh for cinematic feel
- **Purpose**: If using camera for title view

## Environment Elements

### Terrain
- **Option 1**: Simple landscape with island features
  - Size: 1km x 1km (small, focused area)
  - Materials: Beach sand, grass, rocks
  - Height variation for visual interest

- **Option 2**: Flat plane with textured ground
  - Size: 500m x 500m
  - Material: Beach or grass texture
  - Less performance intensive

### Optional Props
- Rocks and boulders for interest
- Simple vegetation (grass, trees)
- Beach elements (if island theme)
- Distant mountains (static mesh or skybox)

### Particle Systems (Optional)
- Mist/fog particles near ground
- Ambient dust particles
- Birds flying in distance (if performance allows)
- Falling leaves or petals

## Audio

### Ambient Sound
- **Asset**: Amb_TitleScreen_Loop (to be created)
- **Content**: Ocean waves, wind, ambient nature
- **Volume**: 0.3-0.5
- **Looping**: Yes
- **Attenuation**: None (2D sound)

### Music
- **Asset**: MUS_Title_Loop
- **Sound Class**: SC_Music
- **Looping**: Yes
- **Fade In**: 2 seconds
- **Volume**: Set by SC_Music volume

Place Audio components at Player Start or set as 2D sounds.

## Lighting Setup

### Time of Day
- **Recommended**: Late afternoon/Golden hour
- **Reason**: Warm, inviting colors

### Color Palette
- Sky: Blue-orange gradient
- Highlights: Warm yellows/oranges
- Shadows: Cool blues
- Overall: High contrast for visual interest

### Performance
- Use static lighting (bake lightmaps)
- Avoid real-time shadows if possible
- Optimize post-process settings

## Level Settings

### World Settings

**Game Mode Override**:
- Create `BP_TitleScreenGameMode`
- Player Controller Class: TitleScreenPlayerController
- Default Pawn: None (UI-only, no character needed)

**World Composition**: Disabled (single level)

### Project Settings References

**DefaultEngine.ini**:
```ini
[/Script/EngineSettings.GameMapsSettings]
GameDefaultMap=/Game/ScarletSands/Levels/TitleBackdrop/L_TitleBackdrop
EditorStartupMap=/Game/ScarletSands/Levels/TitleBackdrop/L_TitleBackdrop
```

## Camera Setup

### Option 1: Fixed Camera View
- Position camera at scenic viewpoint
- Set as default view in level
- Player controller uses this view
- No camera movement

### Option 2: Slow Pan Camera
- Blueprint: BP_TitleCamera
- Rotates slowly on yaw axis
- Speed: 1-2 degrees per second
- Creates subtle movement

### Option 3: Matinee/Sequencer Camera
- Create camera sequence
- Play on level load
- Loop sequence
- Shows different angles over time

## UI Integration

### TitleScreenPlayerController Setup

**BeginPlay Behavior**:
1. Set input mode to UI Only
2. Show mouse cursor
3. Create WBP_TitleRoot widget
4. Add to viewport
5. Widget handles "Press Any Key" → Main Menu transition

**Controller Settings**:
- Enable Click Events: True
- Enable Mouse Over Events: True
- Show Mouse Cursor: True

### Widget Stack
1. WBP_TitleRoot (shown on level load)
2. Player presses key
3. WBP_TitleRoot removed
4. WBP_MainMenu shown via MenuManager

## Performance Targets

### Frame Rate
- Target: 60 FPS minimum
- This is a static scene, should be easy to optimize

### Optimization
- Use static meshes with LODs
- Bake lighting
- Minimal dynamic elements
- Low poly terrain if using landscape

## Testing Checklist

### Visual
- [ ] Scene is visually appealing
- [ ] Lighting creates good atmosphere
- [ ] No visual glitches or artifacts
- [ ] Camera angle shows best view

### Audio
- [ ] Ambient sound plays correctly
- [ ] Title music plays and loops
- [ ] Audio volumes are balanced
- [ ] No audio pops or clicks

### Performance
- [ ] Consistent 60 FPS
- [ ] No hitches or stutters
- [ ] Quick level load time (<3 seconds)

### Integration
- [ ] Level loads as default map
- [ ] TitleScreenPlayerController spawns
- [ ] WBP_TitleRoot appears on screen
- [ ] Mouse cursor is visible
- [ ] Input mode set to UI
- [ ] Press any key transitions to main menu

### Functionality
- [ ] Can navigate to main menu
- [ ] All UI interactions work
- [ ] Audio settings affect title music
- [ ] No errors in output log

## Build Process

### Step 1: Create Base Level
1. File → New Level → Empty Level
2. Save as `L_TitleBackdrop`
3. Location: `Content/ScarletSands/Levels/TitleBackdrop/`

### Step 2: Add Essential Actors
1. Add Player Start
2. Add Directional Light
3. Add Sky Light
4. Add Atmospheric Fog
5. Add Post Process Volume

### Step 3: Build Environment
1. Add terrain or ground plane
2. Add props and decorations
3. Position camera view
4. Test lighting

### Step 4: Add Audio
1. Place ambient sound actors
2. Place title music
3. Test audio levels

### Step 5: Configure Game Mode
1. Create BP_TitleScreenGameMode
2. Set Player Controller Class
3. Set Default Pawn Class to None
4. Override in World Settings

### Step 6: Test & Iterate
1. PIE to test
2. Verify UI appears
3. Check audio playback
4. Optimize performance
5. Polish visuals

## Common Issues

**UI Not Appearing**:
- Check TitleScreenPlayerController is set in Game Mode
- Verify controller's BeginPlay creates widget
- Check widget is added to viewport

**No Audio**:
- Verify Audio actors placed in level
- Check Sound Class assignments
- Ensure audio assets are set to loop

**Performance Issues**:
- Disable real-time shadows
- Reduce post-process effects
- Simplify geometry
- Use static lighting

**Wrong Level Loads**:
- Check DefaultEngine.ini GameDefaultMap setting
- Verify level path is correct
- Check packaged build includes level in cook
