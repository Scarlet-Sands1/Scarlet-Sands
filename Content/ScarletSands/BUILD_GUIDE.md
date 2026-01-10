# Title Screen Build Guide - Unreal Editor

**Purpose**: Step-by-step guide to build the Title Screen experience in Unreal Editor
**Prerequisites**: C++ code compiled, Unreal Editor 5.3+ open with ScarletSands project

## Overview

This guide covers:
1. Creating SoundClass hierarchy for audio control
2. Importing/creating audio assets (UI sounds + title music)
3. Creating UMG widgets (5 widgets total)
4. Building the L_TitleBackdrop level
5. Configuring Game Mode and Player Controller
6. Testing the complete flow

**Estimated Time**: 2-4 hours for first-time setup

---

## Phase 1: Audio Foundation (30 minutes)

### Step 1.1: Create SoundClass Hierarchy

1. **Content Browser** → Navigate to `Content/ScarletSands/UI/Audio/`
   - Create folder if it doesn't exist

2. **Create SC_Master**:
   - Right-click → Sounds → Sound Class
   - Name: `SC_Master`
   - Open it
   - Properties:
     - Volume: 1.0
     - Parent: None
   - Save

3. **Create SC_Music**:
   - Right-click → Sounds → Sound Class
   - Name: `SC_Music`
   - Open it
   - Properties:
     - Volume: 0.7
     - Parent: **SC_Master** (set this!)
   - Save

4. **Create SC_SFX**:
   - Right-click → Sounds → Sound Class
   - Name: `SC_SFX`
   - Open it
   - Properties:
     - Volume: 0.8
     - Parent: **SC_Master** (set this!)
   - Save

**Verify**: Open SC_Master, check it shows SC_Music and SC_SFX as children.

### Step 1.2: Import/Create UI Sound Effects

**Quick Placeholder Option**:

For each sound (Hover, Select, Back):
1. Use Audacity or similar to generate 0.1s sine wave tones
2. Hover: 1000 Hz
3. Select: 800 Hz
4. Back: 600 Hz
5. Export as WAV files

**Import**:
1. Content Browser → Import
2. Select WAV files
3. Import to `Content/ScarletSands/UI/Audio/`
4. Name: `SFX_UI_Hover`, `SFX_UI_Select`, `SFX_UI_Back`

**Configure Each Sound**:
1. Open SoundWave asset
2. Set **Sound Class**: SC_SFX
3. Save

### Step 1.3: Create/Import Title Music

**Placeholder Option**:
- Use a 60-second ambient loop (royalty-free or placeholder)
- Or trim Unreal Starter Content music

**Import**:
1. Import WAV file → `Content/ScarletSands/UI/Audio/`
2. Name: `MUS_Title_Loop`

**Create Looping SoundCue**:
1. Right-click `MUS_Title_Loop` → Create Cue
2. Name: `MUS_Title_Loop_Cue`
3. Open it
4. Add **Looping** node
5. Connect: Wave Player → Looping → Output
6. Set **Sound Class**: SC_Music
7. Save

**Verify**: Play in editor, should loop seamlessly.

---

## Phase 2: UMG Widget Creation (60-90 minutes)

Follow specs in `/Content/ScarletSands/UI/Widgets/` folder.

### Step 2.1: Create WBP_TitleRoot

1. **Content Browser** → `Content/ScarletSands/UI/Widgets/`
2. Right-click → User Interface → Widget Blueprint
3. Name: `WBP_TitleRoot`
4. Open it

**Set Parent Class**:
1. File → Reparent Blueprint
2. Select: **MenuWidgetBase** (C++ class)
3. Confirm

**Build Hierarchy** (see WBP_TitleRoot_SPEC.md):
```
Canvas Panel
├── Background Image (full screen, dark overlay)
├── Title Logo Image (center-top)
├── "Press Any Key to Continue" Text (center-bottom, animated)
└── Version Text (bottom-right)
```

**Animation**:
1. Animations tab → + Add Animation
2. Name: `Anim_PressKeyFade`
3. Add "Press Any Key" text to track
4. Key 0.0s: Opacity 0.0
5. Key 0.5s: Opacity 1.0
6. Key 1.5s: Opacity 1.0
7. Key 2.0s: Opacity 0.0
8. Set to Loop

**Event Graph**:
```
Event Construct
├→ Play Animation (Anim_PressKeyFade, Loop)
└→ Parent: Event Construct
```

**Compile, Save**

### Step 2.2: Create WBP_MainMenu

1. Create Widget Blueprint: `WBP_MainMenu`
2. **Reparent to**: **MainMenuWidget** (C++ class)

**Build Hierarchy** (see WBP_MainMenu_SPEC.md):
```
Canvas Panel
├── Background Overlay
└── Vertical Box (centered)
    ├── NewGameButton (Button)
    ├── ContinueButton (Button)
    ├── LoadGameButton (Button)
    ├── SettingsButton (Button)
    ├── CreditsButton (Button)
    └── QuitButton (Button)
```

**CRITICAL - Button Order**:
Must be in this EXACT order:
1. NewGameButton
2. ContinueButton
3. LoadGameButton
4. SettingsButton
5. CreditsButton
6. QuitButton

**For Each Button**:
1. Add Button to Vertical Box
2. **Variable Name** (top-right panel):
   - NewGameButton (EXACT spelling, case-sensitive)
   - ContinueButton
   - LoadGameButton
   - SettingsButton
   - CreditsButton
   - QuitButton
3. **Is Variable**: ✓ Checked
4. **Instance Editable**: Not needed
5. Size: 300x50
6. Text: Set label (e.g., "New Game")

**Styling**:
- Normal: Dark background, white text
- Hovered: Lighter background
- Focused: Bright blue border (3px)
- Disabled: Dark gray (for Continue/LoadGame)

**LoadGameButton Special**:
- In Designer, set IsEnabled: **False**
- Text: "Load Game (Coming Soon)"

**Audio Assignment**:
1. Select WBP_MainMenu (root)
2. Details → Audio section
3. Hover Sound: SFX_UI_Hover
4. Select Sound: SFX_UI_Select
5. Back Sound: SFX_UI_Back

**No Event Graph logic needed** - C++ handles everything.

**Compile, Save**

**Verify**:
- No BindWidget errors in log
- 6 buttons in correct order
- Variable names match C++ exactly

### Step 2.3: Create WBP_Settings

1. Create Widget Blueprint: `WBP_Settings`
2. **Reparent to**: **SettingsWidget** (C++ class)

**Build Hierarchy** (see WBP_Settings_SPEC.md):
```
Canvas Panel
├── Background
└── Vertical Box
    ├── Title: "Settings"
    ├── Audio Section
    │   ├── MasterVolumeSlider (Slider, range 0-1)
    │   ├── MusicVolumeSlider (Slider, range 0-1)
    │   └── SFXVolumeSlider (Slider, range 0-1)
    ├── Controls Section
    │   ├── MouseSensitivitySlider (Slider, range 0.1-2.0)
    │   └── InvertYCheckBox (CheckBox)
    └── Buttons
        ├── ApplyButton
        └── BackButton
```

**BindWidget Variables** (exact names):
- MasterVolumeSlider
- MusicVolumeSlider
- SFXVolumeSlider
- MouseSensitivitySlider
- InvertYCheckBox
- ApplyButton
- BackButton

**Audio Assignment** (on root widget):
- Hover Sound: SFX_UI_Hover
- Select Sound: SFX_UI_Select
- Back Sound: SFX_UI_Back

**Optional**: Add Blueprint logic to show slider values as percentages.

**Compile, Save**

### Step 2.4: Create WBP_Credits

1. Create Widget Blueprint: `WBP_Credits`
2. **Reparent to**: **CreditsWidget** (C++ class)

**Build Hierarchy** (see WBP_Credits_SPEC.md):
```
Canvas Panel
├── Background
└── Vertical Box
    ├── Title: "Credits"
    ├── Scroll Box
    │   └── CreditsText (Text Block)
    └── BackButton
```

**BindWidget Variables**:
- CreditsText (Text Block)
- BackButton

**CreditsText Properties**:
- Auto Wrap: True
- Justification: Center
- **Do NOT set text** - C++ sets it via InitializeCreditsText()

**Audio Assignment**:
- Hover Sound: SFX_UI_Hover
- Select Sound: SFX_UI_Select
- Back Sound: SFX_UI_Back

**Compile, Save**

### Step 2.5: Create WBP_ConfirmDialog

1. Create Widget Blueprint: `WBP_ConfirmDialog`
2. **Reparent to**: **ConfirmDialogWidget** (C++ class)

**Build Hierarchy** (see WBP_ConfirmDialog_SPEC.md):
```
Canvas Panel
├── Modal Overlay (full screen, black 80% alpha)
└── Dialog Border (centered, 500x300)
    └── Vertical Box
        ├── TitleText (Text Block)
        ├── MessageText (Text Block)
        └── Horizontal Box
            ├── ConfirmButton
            └── CancelButton
```

**BindWidget Variables**:
- TitleText (Text Block)
- MessageText (Text Block)
- ConfirmButton
- CancelButton

**Modal Overlay**:
- Anchors: Fill entire screen
- Color: Black with 0.8 alpha
- Blocks background clicks

**Dialog Styling**:
- ConfirmButton: Red/danger style
- CancelButton: Secondary/gray style

**Audio Assignment**:
- Hover Sound: SFX_UI_Hover
- Select Sound: SFX_UI_Select
- Back Sound: SFX_UI_Back

**Compile, Save**

---

## Phase 3: Level Creation (45-60 minutes)

### Step 3.1: Create TitleBackdrop Level

1. **File** → New Level → Empty Level
2. **Save As**: `L_TitleBackdrop`
3. Location: `Content/ScarletSands/Levels/TitleBackdrop/`

### Step 3.2: Add Essential Actors

**Player Start**:
1. Place Modes → Basic → Player Start
2. Position: (0, 0, 100)

**Lighting**:
1. Directional Light
   - Intensity: 3.0
   - Rotation: Low angle (sunrise)
2. Sky Light
   - Intensity: 0.5
   - Mobility: Static
3. Atmospheric Fog (optional)
   - Density: 0.02

**Post Process Volume**:
1. Place in scene
2. Settings → Unbound: ✓ Checked
3. Auto Exposure: Disabled
4. Bloom: 0.5
5. Vignette: Slight

**Sky Sphere**:
1. Place Modes → Visual Effects → Sky Sphere
2. Adjust sun brightness

### Step 3.3: Build Environment

**Option 1 - Simple**:
- Add Plane (10m x 10m)
- Apply ground texture
- Position: (0, 0, 0)

**Option 2 - Detailed**:
- Add Landscape (1km x 1km)
- Sculpt terrain with hills
- Paint textures
- Add rocks, vegetation

**Camera Positioning**:
- Position camera at scenic viewpoint
- This is the view players see
- No camera movement needed (static)

### Step 3.4: Add Audio

**Ambient Sound**:
1. Place → Sounds → Ambient Sound
2. Sound: (ocean waves ambient - optional)
3. Position: Near player start or set as 2D

**Title Music**:
1. Place → Sounds → Ambient Sound
2. Sound: **MUS_Title_Loop_Cue**
3. Settings:
   - Is UISound: True (or 2D)
   - Auto Activate: True
4. Or trigger from controller BeginPlay

### Step 3.5: Configure Game Mode

**Create Game Mode Blueprint**:
1. Content Browser → Blueprint Class
2. Parent: GameModeBase
3. Name: `BP_TitleScreenGameMode`
4. Open it
5. Details:
   - Player Controller Class: **TitleScreenPlayerController**
   - Default Pawn Class: **None**
6. Save

**Set in Level**:
1. World Settings (Window → World Settings)
2. Game Mode → Game Mode Override: **BP_TitleScreenGameMode**
3. Save level

### Step 3.6: Build Lighting

1. Build → Build Lighting Only
2. Wait for build to complete
3. Check for errors

---

## Phase 4: Widget Wiring (15-30 minutes)

### Step 4.1: Configure MenuManagerSubsystem Widget Classes

**Option 1 - In C++ Header** (if not done):
Add to MenuManagerSubsystem.h:
```cpp
UPROPERTY(EditDefaultsOnly, Category = "Menu Manager")
TMap<EMenuScreen, TSubclassOf<UUserWidget>> WidgetClasses;
```

**Option 2 - In Blueprint** (Create BP_MenuManager):
1. Create Blueprint inheriting from GameInstance
2. Override MenuManagerSubsystem
3. Set widget class mappings

**Option 3 - Programmatic** (simplest for v1):
Widgets are instantiated directly by controllers/level blueprints.

### Step 4.2: Test TitleScreenPlayerController

**Verify Controller Spawns**:
1. PIE in L_TitleBackdrop
2. Check Output Log - should see controller spawn
3. Check mouse cursor visible
4. Check input mode is UI

**If Widget Not Showing**:

Create minimal level blueprint test:
1. Level Blueprint → Event BeginPlay
2. Get Player Controller
3. Create Widget: WBP_TitleRoot
4. Add to Viewport
5. Test

Or ensure TitleScreenPlayerController creates widget in BeginPlay.

---

## Phase 5: Integration Testing (30 minutes)

### Test Flow

**Start Game**:
1. Editor → Play (PIE)
2. Should load L_TitleBackdrop
3. WBP_TitleRoot appears
4. "Press Any Key" fades in/out
5. Title music plays

**Press Any Key**:
6. WBP_TitleRoot closes
7. WBP_MainMenu appears
8. Focus on Continue or New Game (depending on save)

**Main Menu Navigation**:
9. Hover buttons - hear hover sound
10. D-pad/arrows navigate - focus changes
11. Click New Game - select sound plays
12. (Since no save) Immediately loads world

**With Save (Test Later)**:
1. Create save by playing game
2. Return to title
3. Continue button enabled
4. Continue has focus
5. New Game shows overwrite dialog

**Settings**:
1. Main Menu → Settings
2. Change volume sliders - hear immediate effect
3. Click Apply - settings saved
4. Back to main menu
5. Restart game - settings persist

**Credits**:
1. Main Menu → Credits
2. Credits text displays (set by C++)
3. Can scroll if long
4. Back returns to main menu

**Quit**:
1. Main Menu → Quit
2. Confirmation dialog appears
3. Cancel returns to menu
4. Confirm quits game

### Test Checklist

**Audio**:
- [ ] Title music plays and loops
- [ ] UI sounds play (hover, select, back)
- [ ] Volume sliders affect audio
- [ ] Settings persist

**Navigation**:
- [ ] D-pad/arrows navigate buttons
- [ ] Mouse hover works
- [ ] Focus is visible
- [ ] No soft locks

**Widgets**:
- [ ] All 5 widgets display correctly
- [ ] No BindWidget errors
- [ ] Buttons work
- [ ] Text is readable

**Flow**:
- [ ] Title → Main Menu works
- [ ] Main Menu → Settings → Back works
- [ ] Main Menu → Credits → Back works
- [ ] Quit confirmation works
- [ ] New Game loads world

---

## Phase 6: Project Configuration (10 minutes)

### DefaultEngine.ini

Ensure these settings:
```ini
[/Script/EngineSettings.GameMapsSettings]
GameDefaultMap=/Game/ScarletSands/Levels/TitleBackdrop/L_TitleBackdrop
EditorStartupMap=/Game/ScarletSands/Levels/TitleBackdrop/L_TitleBackdrop
GameInstanceClass=/Script/ScarletSands.ScarletSandsGameInstance

[/Script/Engine.Engine]
GameViewportClientClassName=/Script/Engine.GameViewportClient
```

### DefaultGame.ini

Add maps to cook:
```ini
[/Script/UnrealEd.ProjectPackagingSettings]
+MapsToCook=(FilePath="/Game/ScarletSands/Levels/TitleBackdrop/L_TitleBackdrop")
+MapsToCook=(FilePath="/Game/ScarletSands/Levels/L_World_Persistent")
```

---

## Common Issues & Fixes

### BindWidget Errors

**Error**: "Could not find widget named 'NewGameButton'"

**Fix**:
1. Open WBP_MainMenu
2. Select button
3. Details → Variable Name: **NewGameButton** (exact, case-sensitive)
4. Is Variable: ✓ Checked
5. Compile, save

### Widgets Not Appearing

**Issue**: TitleRoot doesn't show on level load

**Fix**:
1. Check TitleScreenPlayerController is set in Game Mode
2. Verify controller BeginPlay creates widget
3. Check widget added to viewport with Z-order 0
4. Verify input mode set to UI Only

### Audio Not Playing

**Issue**: No sound when hovering buttons

**Fix**:
1. Check audio assets assigned in widget Details → Audio
2. Verify SoundClass assignments (SC_SFX)
3. Check C++ PlayHoverSound() is called
4. Test audio device output

### Continue Button Always Disabled

**Issue**: Even with save, Continue disabled

**Fix**:
1. Check save file exists: `Saved/SaveGames/SS_MainSlot.sav`
2. Verify C++ DoesSaveGameExist() works
3. Check UpdateContinueButtonState() is called in NativeTick
4. Ensure button IsEnabled is not forced to false in UMG

### Focus Not Visible

**Issue**: Can't see which button has focus

**Fix**:
1. Button style → Focused State
2. Set bright border (3px, blue)
3. Different background color
4. Add glow/highlight effect

### Performance Issues

**Issue**: Low FPS in title screen

**Fix**:
1. Build lighting (bake lightmaps)
2. Disable real-time shadows
3. Reduce post-process effects
4. Simplify terrain/meshes
5. Check for infinite loops in blueprints

---

## Build Complete!

Once all tests pass, you have a fully functional Title Screen v1:

✓ Title screen with backdrop level
✓ Main menu with navigation
✓ Settings with persistence
✓ Credits screen
✓ Confirmation dialogs
✓ Full audio integration
✓ Keyboard/mouse/gamepad support

**Next Steps** (outside v1 scope):
- Replace placeholder audio with final assets
- Polish visuals (better backdrop, button styles)
- Add animations (menu transitions)
- Implement multiple save slots (v1.1)
- Add graphics quality presets to settings

**Ready for PR merge and build testing!**
