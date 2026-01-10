# L_TitleBackdrop Level Specification

**Level Name**: L_TitleBackdrop
**Purpose**: Title screen backdrop level with atmospheric scene
**Player Controller**: TitleScreenPlayerController
**Game Mode**: BP_TitleScreenGameMode (custom)
**Approach**: Animated camera pan of simple environment
**Justification**: AAA feeling while cheap; doesn't require full world

## Level Overview

A visually appealing backdrop for the title screen featuring:
- **Locked Approach:** Slow camera pan over a small cinematic environment
- Minimalist scene (small island, rock formation, or scenic vista)
- Atmospheric lighting (golden hour / dusk)
- Ambient audio (ocean, wind, subtle ambiance)
- Optional particle effects (mist, dust motes)
- **NO** gameplay elements, AI, or world streaming
- **Goal:** Create AAA cinematic feel with minimal asset cost

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

## Build Process (Beginner-Friendly Walkthrough)

This section provides **step-by-step Unreal Editor instructions** for building L_TitleBackdrop from scratch. Estimated time: **2-4 hours** (including experimentation).

---

### Step 1: Create Base Level (15 minutes)

1. **Open Unreal Editor** for the Scarlet Sands project
2. **File → New Level**
3. Select **Empty Level** (NOT Default or Open World)
4. Click **Create**
5. **Save the level**:
   - Ctrl+S (or File → Save Current Level As...)
   - Navigate to: `Content/ScarletSands/Levels/TitleBackdrop/`
   - Name: `L_TitleBackdrop`
   - Click **Save**

**Result:** You now have a blank black level with no actors.

---

### Step 2: Add Essential Lighting (20 minutes)

#### 2.1 Add Directional Light (Sun)

1. In the **Place Actors** panel (left side), search for "Directional Light"
2. Drag **Directional Light** into the viewport
3. Select the Directional Light in the **Outliner** (right side)
4. In **Details** panel (right side), set:
   - **Transform → Location:** (0, 0, 500) - Doesn't matter much for static lights
   - **Transform → Rotation:** (-30, -45, 0) - Low angle for golden hour
   - **Light → Intensity:** 3.0 lux
   - **Light → Light Color:** Warm yellow (#FFE4B5)
     - Click the color box → Adjust to warm tone
   - **Light → Source Angle:** 0.5 (soft shadows)
   - **Mobility:** Static (for baked lighting)
5. Press **F** to focus viewport on the light

**Result:** Warm directional sunlight (will be baked later).

#### 2.2 Add Sky Light

1. Search for "Sky Light" in **Place Actors**
2. Drag **Sky Light** into viewport
3. In **Details**:
   - **Light → Intensity:** 0.5 lux
   - **Light → Source Type:** SLS Captured Scene
   - **Mobility:** Static
4. Click **Recapture Scene** button (will be blue/gray)

**Result:** Soft ambient fill lighting.

#### 2.3 Add Atmospheric Fog (Optional)

1. Search for "Atmospheric Fog" in **Place Actors**
2. Drag into viewport
3. In **Details**:
   - **Fog Density:** 0.02
   - **Fog Height Falloff:** 0.2
   - **Fog Max Opacity:** 0.6

**Result:** Adds atmospheric depth to the scene.

#### 2.4 Add Post Process Volume

1. Search for "Post Process Volume"
2. Drag into viewport
3. Select it, in **Details**:
   - **Post Process Volume Settings → Infinite Extent (Unbound):** Check this box ✓
   - Expand **Lens → Bloom**:
     - **Method:** Standard
     - **Intensity:** 0.5
     - **Threshold:** 1.0
   - Expand **Lens → Vignette**:
     - **Intensity:** 0.4 (slight edge darkening)
   - Expand **Color Grading → Global**:
     - **Saturation:** (1.0, 0.9, 0.9) - Slight desaturation for mood

**Result:** Cinematic color grading and bloom.

#### 2.5 Add Sky Sphere

1. In **Content Browser**, navigate to: Content → Engine → EngineSky
2. Find **BP_Sky_Sphere** blueprint
3. Drag into viewport
4. In **Details**:
   - **Default → Refresh Material:** Click button
   - **Sun Brightness:** 50
   - **Cloud Speed:** 0.1 (slow)

**Result:** Sky gradient with clouds.

---

### Step 3: Add Ground Plane (15 minutes)

#### Option A: Simple Plane (Fastest)

1. In **Place Actors**, search for "Plane"
2. Drag **Plane** static mesh into viewport
3. Select it, in **Details**:
   - **Transform → Location:** (0, 0, 0)
   - **Transform → Scale:** (50, 50, 1) - Large ground plane
4. Create a basic material:
   - Right-click in **Content Browser** → Material → Material
   - Name: `M_GroundPlane`
   - Open it, add a **Constant3Vector** node (color)
   - Set color to sandy beige or grass green
   - Connect to **Base Color**
   - Save
5. Assign material to plane

**Result:** Simple colored ground.

#### Option B: Landscape (More Realistic)

1. **Landscape Mode** button (top toolbar, mountain icon)
2. **New Landscape** tab
3. Settings:
   - **Section Size:** 7x7 quads
   - **Sections Per Component:** 1x1
   - **Number of Components:** 8x8 (small landscape)
   - **Material:** None for now (use default)
4. Click **Create**
5. Exit Landscape Mode (same button)

**Result:** Editable terrain (can sculpt later).

---

### Step 4: Add Camera with Slow Pan (30 minutes)

This is the **key feature** for the title screen backdrop.

#### 4.1 Place Cinematic Camera

1. Search for "Cine Camera Actor" in **Place Actors**
2. Drag into viewport
3. Position camera at scenic viewpoint:
   - Select camera in Outliner
   - Use **Viewport Camera Controls**:
     - Right-click + WASD to fly around
     - Find a good angle showing your ground/environment
   - Press **Ctrl+Shift+P** to pilot the camera actor
   - Move to desired position
   - Press **Eject** (or **Ctrl+Shift+P** again) to stop piloting
4. In **Details**:
   - **Transform → Location:** Note these coords (e.g., (500, 0, 200))
   - **Transform → Rotation:** (0, -15, 0) - Slight tilt down
   - **Filmback → Sensor Width:** 36mm (cinematic look)
   - **Current Focal Length:** 35mm (wide angle, more environment visible)
   - **Depth of Field:** Disable for now (too complex for v1)

#### 4.2 Create Slow Pan Blueprint

1. Right-click in **Content Browser** → Blueprint Class
2. Parent Class: **Actor**
3. Name: `BP_TitleCamera`
4. Open the blueprint
5. **Add Component**:
   - Click **Add Component** button
   - Search for "Cine Camera"
   - Add **Cine Camera Component**
6. **Set camera as root**:
   - In Components panel, drag Cine Camera Component to top (make it root)
7. **Event Graph**:
   - Delete "Event BeginPlay" node (we don't need it)
   - Right-click → Search "Event Tick"
   - Add **Event Tick** node
8. **Add rotation logic**:
   - Drag from **Event Tick** execution pin
   - Search "Add Actor Local Rotation"
   - Connect
9. **Configure rotation**:
   - On **Add Actor Local Rotation** node:
   - **Delta Rotation** input:
     - Right-click → Split Struct Pin
     - **Yaw:** Connect a multiply node:
       - Get **Delta Seconds** output from Event Tick
       - Multiply by **5.0** (5 degrees per second rotation)
       - Connect result to Yaw input
     - **Pitch:** Leave at 0
     - **Roll:** Leave at 0
10. **Compile and Save** blueprint

#### 4.3 Place BP_TitleCamera in Level

1. Find **BP_TitleCamera** in Content Browser
2. Drag into viewport
3. Position where you placed the Cine Camera Actor earlier
4. **Delete the original Cine Camera Actor** (we're using the blueprint now)
5. Test:
   - Press **Play (PIE)**
   - Camera should slowly rotate
   - Adjust rotation speed in blueprint if needed (change the 5.0 multiplier)

**Result:** Slow rotating camera that creates cinematic feel.

---

### Step 5: Add Audio (15 minutes)

#### 5.1 Create Placeholder Music (Temporary)

*Note: You'll import real MUS_Title_Loop later. For now, use placeholder.*

1. Place **Ambient Sound** actor:
   - Search "Ambient Sound" in Place Actors
   - Drag into viewport near Player Start
2. In **Details**:
   - **Sound → Sound:** (Leave empty for now, or use free music asset)
   - **Sound → Volume Multiplier:** 1.0
   - **Sound → Auto Activate:** True ✓
   - **Attenuation Settings → Override Attenuation:** True
   - **Attenuation → Spatialize:** False (2D sound)
   - **Sound Class:** `/Game/ScarletSands/UI/Audio/SC_Music` (if created)

#### 5.2 Add Ambient Sounds (Optional)

1. Place another **Ambient Sound**
2. Set to ocean waves or wind ambiance
3. Configure similar to music

**Result:** Audio will play when level loads.

---

### Step 6: Add Player Start (5 minutes)

1. Search "Player Start" in **Place Actors**
2. Drag into viewport
3. Position anywhere (not used for title screen, but required)
4. **Details → Location:** (0, 0, 100)

**Result:** Mandatory actor for level (even though not used).

---

### Step 7: Configure Game Mode (20 minutes)

#### 7.1 Create BP_TitleScreenGameMode

1. Right-click in Content Browser → Blueprint Class
2. Parent Class: **Game Mode Base**
3. Name: `BP_TitleScreenGameMode`
4. Open it
5. In **Class Defaults** (right panel):
   - **Player Controller Class:** Select **TitleScreenPlayerController** (C++ class)
   - **Default Pawn Class:** None (leave empty, UI-only)
   - **HUD Class:** None
6. **Compile and Save**

#### 7.2 Set Game Mode Override in Level

1. In viewport, click **Settings** (gear icon) → **World Settings**
2. **World Settings** panel appears (right side)
3. Under **Game Mode**:
   - **Game Mode Override:** Select **BP_TitleScreenGameMode**
4. Close World Settings

**Result:** Level will use custom game mode when loaded.

---

### Step 8: Configure Project Settings (10 minutes)

#### 8.1 Set Default Map

1. **Edit → Project Settings**
2. **Maps & Modes** section
3. **Default Maps**:
   - **Game Default Map:** `/Game/ScarletSands/Levels/TitleBackdrop/L_TitleBackdrop`
   - **Editor Startup Map:** `/Game/ScarletSands/Levels/TitleBackdrop/L_TitleBackdrop`
4. **Close** Project Settings

**Result:** Game always starts with this level.

#### 8.2 Verify DefaultEngine.ini

1. Close Unreal Editor
2. Open `Config/DefaultEngine.ini` in text editor
3. Verify these lines exist under `[/Script/EngineSettings.GameMapsSettings]`:
   ```ini
   GameDefaultMap=/Game/ScarletSands/Levels/TitleBackdrop/L_TitleBackdrop
   EditorStartupMap=/Game/ScarletSands/Levels/TitleBackdrop/L_TitleBackdrop
   ```
4. Save and close
5. Reopen Unreal Editor

**Result:** Permanent configuration.

---

### Step 9: Build Lighting (15 minutes)

1. In viewport, click **Build** button (top toolbar)
2. Select **Build Lighting Only** (for faster iteration)
3. **Quality:** Medium (for testing)
4. Click **Build**
5. Wait for lightmaps to bake (progress bar)
6. When done, lighting should look much better (no more unbuilt warnings)

**Result:** Baked static lighting (better performance).

---

### Step 10: Test Integration (10 minutes)

1. Press **Play (PIE)** button
2. **Expected behavior**:
   - Level loads
   - Camera slowly rotates
   - WBP_TitleRoot widget appears (if C++ is set up)
   - Mouse cursor visible
   - "Press Any Key" prompt
3. Press any key:
   - Should transition to WBP_MainMenu
4. Test navigation, audio, etc.

**Troubleshooting:**
- If UI doesn't appear: Check TitleScreenPlayerController setup
- If camera doesn't rotate: Check BP_TitleCamera Event Tick logic
- If audio doesn't play: Check Sound Class assignments

---

### Step 11: Polish and Optimize (30-60 minutes)

#### Visual Polish
- Add subtle Niagara particle effects (dust motes, mist)
- Adjust color grading for mood
- Fine-tune camera angle and rotation speed
- Add props (rocks, foliage) for visual interest

#### Audio Polish
- Import final MUS_Title_Loop
- Adjust volume levels
- Add ambient sounds (wind, waves)

#### Performance Optimization
- **Build Lighting** on **Production Quality**
- Check frame rate (should be 60+ FPS easily)
- Disable expensive features if needed
- Test on target hardware

**Result:** Polished, performant title screen backdrop.

---

## Summary of Beginner Workflow

1. **Create empty level** → Save as L_TitleBackdrop
2. **Add lighting** → Directional Light, Sky Light, Atmospheric Fog, Post Process
3. **Add ground** → Plane or Landscape
4. **Add camera** → BP_TitleCamera with slow pan rotation
5. **Add audio** → Ambient Sound with MUS_Title_Loop
6. **Add Player Start** (required but unused)
7. **Create Game Mode** → BP_TitleScreenGameMode with TitleScreenPlayerController
8. **Set as default map** in Project Settings
9. **Build lighting** for baked shadows
10. **Test and polish**

**Time Estimate:** 2-4 hours total (including learning/experimentation)

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
