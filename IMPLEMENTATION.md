# Title Screen v1 Implementation

This document describes the implementation of the Title Screen + Main Menu system for Scarlet Sands.

## Overview

Title Screen v1 provides a complete menu flow including:
- Title screen with "Press Any Key" prompt
- Main menu with New Game, Continue, Settings, Credits, and Quit
- Settings screen for audio, graphics, and controls
- Credits screen
- Confirmation dialogs for destructive actions
- Save game management
- Settings persistence

## Architecture

### C++ Classes

All menu functionality is implemented in C++ with UMG widgets as thin display layers:

#### Core Systems
- **ScarletSandsGameInstance**: Manages persistent game state and save slots
- **MenuManagerSubsystem**: Manages menu navigation stack and screen transitions
- **MenuWidgetBase**: Base class for all menu widgets with input handling

#### Menu Widgets
- **MainMenuWidget**: Main menu with game options
- **SettingsWidget**: Settings screen (audio, graphics, controls)
- **CreditsWidget**: Credits display
- **ConfirmDialogWidget**: Modal confirmation dialogs

#### Save System
- **ScarletSandsSaveGame**: Main save game data
- **ScarletSandsSettingsSaveGame**: User settings persistence

#### Player
- **TitleScreenPlayerController**: Controller for title screen level

### Navigation Flow

```
Title Root (Press Any Key)
    ↓
Main Menu
    ├→ New Game → [Confirm if save exists] → World Map
    ├→ Continue (enabled only if save exists) → World Map
    ├→ Settings → Audio/Graphics/Controls → Back to Main Menu
    ├→ Credits → Back to Main Menu
    └→ Quit → [Confirm] → Exit
```

### Key Features

#### Continue Button Enablement
- Checks for save file existence: `DoesSaveGameExist("SS_MainSlot")`
- Updates dynamically in `MainMenuWidget::NativeTick()`
- Disabled if no save exists

#### New Game Overwrite Protection
- Checks if save exists before starting new game
- Shows confirmation dialog if save would be overwritten
- Creates new save and transitions to world on confirmation

#### Settings Persistence
- Audio: Volume changes applied immediately to SoundClass assets
- Graphics: Applied via UGameUserSettings
- Controls: Mouse sensitivity and invert Y stored in SettingsSaveGame
- All settings persisted to save slot "SS_Settings"

#### Back Navigation
- All widgets handle Escape/B button in `NativeOnKeyDown`
- Routes to `MenuManagerSubsystem::HandleBackNavigation()`
- Maintains navigation stack for proper back flow
- Main menu shows quit confirmation on back

#### No Soft Locks
- Back always works via navigation stack
- Quit confirmation from main menu
- All dialogs closeable with cancel/back

## Content Assets

### UMG Widgets (Created in Editor)
See `Content/ScarletSands/UI/Widgets/README.md` for detailed widget requirements:
- WBP_TitleRoot
- WBP_MainMenu
- WBP_Settings
- WBP_Credits
- WBP_ConfirmDialog

### Audio (Created in Editor)
See `Content/ScarletSands/UI/Audio/README.md` for audio asset specifications:
- SFX_UI_Hover, SFX_UI_Select, SFX_UI_Back
- MUS_Title_Loop
- SC_Master, SC_Music, SC_SFX (Sound Classes)

### Levels
- **L_TitleBackdrop**: Title screen backdrop with atmospheric island scene
- **L_World_Persistent**: Placeholder world map for game transitions

## Configuration

### DefaultEngine.ini
- GameInstanceClass: `/Script/ScarletSands.ScarletSandsGameInstance`
- GameDefaultMap: L_TitleBackdrop
- EditorStartupMap: L_TitleBackdrop

### DefaultGame.ini
- MapsToCook: L_TitleBackdrop, L_World_Persistent

## Build Instructions

1. **Generate Project Files**:
   ```bash
   # Linux
   cd /path/to/Scarlet-Sands
   /path/to/UnrealEngine/Engine/Build/BatchFiles/Linux/GenerateProjectFiles.sh -project="ScarletSands.uproject"

   # Windows
   UnrealEngine\Engine\Build\BatchFiles\GenerateProjectFiles.bat -project="ScarletSands.uproject"
   ```

2. **Build C++ Code**:
   - Open solution in Visual Studio / Rider / VS Code
   - Build configuration: Development Editor
   - Build target: ScarletSandsEditor
   - Or use Unreal Build Tool directly

3. **Open in Editor**:
   - Launch Unreal Editor 5.3+
   - Open ScarletSands.uproject
   - Project should compile modules automatically

4. **Create Content Assets**:
   - Follow READMEs in Content directories
   - Create UMG widgets with proper parent classes
   - Import/create audio assets
   - Build levels L_TitleBackdrop and L_World_Persistent

## Testing

### Test Checklist

- [ ] Build compiles with no errors (Development Editor)
- [ ] PIE launches title screen level
- [ ] Title screen displays with UI
- [ ] Can navigate to main menu
- [ ] **Continue button is disabled** when no save exists
- [ ] New Game starts game without confirmation when no save
- [ ] Can navigate to Settings
- [ ] Audio sliders work and persist
- [ ] Mouse sensitivity and invert Y work and persist
- [ ] Can navigate to Credits
- [ ] Back button works from all screens
- [ ] Settings apply and persist after editor restart
- [ ] After creating save: **Continue button enables**
- [ ] New Game shows overwrite confirmation when save exists
- [ ] Confirming overwrite starts new game
- [ ] Canceling overwrite returns to main menu
- [ ] Quit from main menu shows confirmation
- [ ] Confirming quit exits game
- [ ] Escape/B navigates back properly
- [ ] Keyboard/gamepad navigation works
- [ ] UI sounds play on hover/select/back

### Test Steps

1. **First Launch (No Save)**:
   - PIE → Title screen appears
   - Press any key → Main menu appears
   - Continue button should be **DISABLED**
   - Click New Game → Loads world (no confirmation)

2. **Settings Test**:
   - Main Menu → Settings
   - Change audio volumes → Should hear immediate effect
   - Change mouse sensitivity
   - Toggle invert Y
   - Click Apply → Settings saved
   - Click Back → Returns to main menu
   - Exit PIE, restart → Settings should persist

3. **Continue Test (After Save Exists)**:
   - Create a save (New Game)
   - Return to title screen
   - Main Menu → Continue button should be **ENABLED**
   - Click Continue → Loads world with save data

4. **Overwrite Protection**:
   - With save existing, Main Menu → New Game
   - Confirmation dialog appears: "Overwrite Save?"
   - Click Cancel → Returns to main menu
   - Click New Game → Confirm → Starts new game (save overwritten)

5. **Quit Confirmation**:
   - Main Menu → Quit
   - Confirmation dialog appears: "Quit Game?"
   - Click Cancel → Returns to main menu
   - Click Quit → Confirm → Game exits

6. **Navigation**:
   - Test Escape/B from every screen
   - Verify back navigation stack works correctly
   - Verify no soft locks

## Known Limitations

- Content assets (UMG, audio, levels) must be created manually in editor
- Binary assets cannot be version controlled without Git LFS
- Graphics settings require UGameUserSettings implementation
- Controller remapping not implemented (future enhancement)

## Future Enhancements (Out of Scope v1)

- Advanced graphics settings (resolution, quality presets, VSync)
- Rebindable controls/key mapping
- Multiple save slots with UI
- Load game menu
- Options for difficulty, accessibility
- Localization support
- Cloud save integration

## C++ Module Structure

```
Source/ScarletSands/
├── ScarletSands.h/cpp           # Module definition
├── ScarletSandsGameInstance.h/cpp
├── Menu/
│   ├── MenuManagerSubsystem.h/cpp
│   ├── MenuWidgetBase.h/cpp
│   ├── MainMenuWidget.h/cpp
│   ├── SettingsWidget.h/cpp
│   ├── CreditsWidget.h/cpp
│   └── ConfirmDialogWidget.h/cpp
├── Save/
│   ├── ScarletSandsSaveGame.h/cpp
│   └── ScarletSandsSettingsSaveGame.h/cpp
└── Player/
    └── TitleScreenPlayerController.h/cpp
```

## Notes

- All C++ first: widgets only display + forward events
- MenuManagerSubsystem owns all state and navigation
- No Blueprint business logic (animations only)
- Save/Load uses UE's built-in save game system
- Settings use SoundClass volumes + UGameUserSettings
- Input handled in NativeOnKeyDown for back navigation
