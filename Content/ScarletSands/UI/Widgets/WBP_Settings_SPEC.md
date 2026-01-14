# WBP_Settings Widget Specification

**Parent Class**: SettingsWidget (C++)
**Screen Type**: Settings
**Purpose**: Settings screen for audio, graphics, and controls configuration

## Widget Hierarchy

```
Canvas Panel (Root)
├── Background Overlay (Image)
├── Settings Container (Vertical Box)
│   ├── Anchor: Center
│   ├── Title Text: "Settings"
│   ├── Horizontal Divider
│   ├── Audio Section (Vertical Box)
│   │   ├── Section Header: "Audio"
│   │   ├── Master Volume Row (Horizontal Box)
│   │   │   ├── Label: "Master Volume"
│   │   │   ├── MasterVolumeSlider (Slider) ← BindWidget REQUIRED
│   │   │   │   ├── Min: 0.0, Max: 1.0
│   │   │   │   └── Default: 1.0
│   │   │   └── Value Text: "100%"
│   │   ├── Music Volume Row
│   │   │   ├── Label: "Music Volume"
│   │   │   ├── MusicVolumeSlider (Slider) ← BindWidget REQUIRED
│   │   │   │   ├── Min: 0.0, Max: 1.0
│   │   │   │   └── Default: 0.7
│   │   │   └── Value Text: "70%"
│   │   └── SFX Volume Row
│   │       ├── Label: "SFX Volume"
│   │       ├── SFXVolumeSlider (Slider) ← BindWidget REQUIRED
│   │       │   ├── Min: 0.0, Max: 1.0
│   │       │   └── Default: 0.8
│   │       └── Value Text: "80%"
│   ├── Horizontal Divider
│   ├── Graphics Section (Vertical Box)
│   │   ├── Section Header: "Graphics"
│   │   ├── Window Mode Row (Horizontal Box)
│   │   │   ├── Label: "Window Mode"
│   │   │   └── WindowModeComboBox (ComboBoxString) ← BindWidget REQUIRED
│   │   │       ├── Options: "Fullscreen", "Windowed", "Borderless Fullscreen"
│   │   │       └── Default: "Borderless Fullscreen"
│   │   ├── Resolution Row (Horizontal Box)
│   │   │   ├── Label: "Resolution"
│   │   │   └── ResolutionComboBox (ComboBoxString) ← BindWidget REQUIRED
│   │   │       ├── Options: "1280x720", "1600x900", "1920x1080", "2560x1440", "3840x2160"
│   │   │       └── Default: "1920x1080"
│   │   ├── VSync Row (Horizontal Box)
│   │   │   ├── Label: "VSync"
│   │   │   └── VSyncCheckBox (CheckBox) ← BindWidget REQUIRED
│   │   │       └── Default: Checked
│   │   └── Quality Preset Row (Horizontal Box)
│   │       ├── Label: "Quality"
│   │       └── QualityPresetComboBox (ComboBoxString) ← BindWidget REQUIRED
│   │           ├── Options: "Low", "Medium", "High", "Epic"
│   │           └── Default: "High"
│   ├── Horizontal Divider
│   ├── Controls Section (Vertical Box)
│   │   ├── Section Header: "Controls"
│   │   ├── Mouse Sensitivity Row
│   │   │   ├── Label: "Mouse Sensitivity"
│   │   │   ├── MouseSensitivitySlider (Slider) ← BindWidget REQUIRED
│   │   │   │   ├── Min: 0.1, Max: 2.0
│   │   │   │   └── Default: 1.0
│   │   │   └── Value Text: "1.0x"
│   │   └── Invert Y Axis Row
│   │       ├── Label: "Invert Y Axis"
│   │       └── InvertYCheckBox (CheckBox) ← BindWidget REQUIRED
│   │           └── Default: Unchecked
│   └── Button Row (Horizontal Box)
│       ├── ApplyButton (Button) ← BindWidget REQUIRED
│       │   ├── Text: "Apply"
│       │   └── Style: Primary button
│       └── BackButton (Button) ← BindWidget REQUIRED
│           ├── Text: "Back"
│           └── Style: Secondary button
```

## BindWidget Requirements

Variable names MUST match C++ exactly:

**Audio:**
- `MasterVolumeSlider`
- `MusicVolumeSlider`
- `SFXVolumeSlider`

**Graphics:**
- `WindowModeComboBox`
- `ResolutionComboBox`
- `VSyncCheckBox`
- `QualityPresetComboBox`

**Controls:**
- `MouseSensitivitySlider`
- `InvertYCheckBox`

**Buttons:**
- `ApplyButton`
- `BackButton`

## Blueprint Setup

### Event Graph

**Event Construct**:
- Call Parent::Event Construct
- C++ handles:
  - Loading saved settings
  - Binding slider/checkbox events
  - Setting initial values
  - Applying audio changes to SoundClass assets

### Slider Value Display (Optional Blueprint Logic)

You can add Blueprint logic to update value text labels:

**On MasterVolumeSlider Value Changed**:
- Get slider value
- Format as percentage: `Value * 100 + "%"`
- Set to Value Text

Repeat for Music, SFX, and MouseSensitivity sliders.

## Behavior (C++ Controlled)

### Audio Sliders
- Changes applied immediately (real-time preview)
- Updates SoundClass volume properties:
  - MasterVolumeSlider → SC_Master.Volume
  - MusicVolumeSlider → SC_Music.Volume
  - SFXVolumeSlider → SC_SFX.Volume

### Graphics Settings
- Window Mode: Fullscreen (0), Windowed (1), Borderless Fullscreen (2)
- Resolution: Standard 16:9 resolutions
- VSync: Enable/disable vertical sync
- Quality Preset: Maps to Unreal's scalability levels (0=Low, 1=Medium, 2=High, 3=Epic)
- Stored in GameUserSettings.ini
- Applied when Apply button is pressed

### Mouse Sensitivity
- Stored in SettingsSaveGame
- Applied to player controller on load

### Invert Y Axis
- Stored in SettingsSaveGame
- Applied to player controller on load

### Apply Button
- Saves all settings:
  - Audio/Controls → SS_Settings save slot
  - Graphics → GameUserSettings.ini
- Updates "saved values" for dirty checking
- Does NOT close settings screen

### Back Button
- Checks for unsaved changes using dirty tracking
- If changes exist:
  - Shows "Discard Changes?" confirmation dialog
  - Confirm: Discards changes and returns to main menu
  - Cancel: Stays in settings screen
- If no changes: Returns to main menu immediately
- Plays back sound

## Styling

### Section Headers
- Font Size: 20
- Color: White (#FFFFFF)
- Font Weight: Bold
- Margin: 20px top, 10px bottom

### Labels
- Font Size: 16
- Color: Light gray (#CCCCCC)
- Alignment: Left

### Sliders
- Track color: Dark gray (#404040)
- Fill color: Blue (#4080FF)
- Thumb: White circle with shadow
- Width: 200px

### Value Text
- Font Size: 16
- Color: White (#FFFFFF)
- Alignment: Right
- Width: 60px

### Buttons
- Width: 150px
- Height: 40px
- Same styling as main menu buttons

## Testing Checklist

### Visual
- [ ] All sections clearly labeled
- [ ] Sliders are properly sized and aligned
- [ ] Value displays update in real-time
- [ ] Buttons are accessible and visible

### Audio Settings
- [ ] Master volume changes affect all sounds
- [ ] Music volume only affects background music
- [ ] SFX volume only affects UI sounds
- [ ] Volume changes are audible immediately
- [ ] Settings persist after Apply + restart

### Control Settings
- [ ] Mouse sensitivity slider works
- [ ] Invert Y checkbox toggles state
- [ ] Settings persist after Apply + restart

### Graphics Settings
- [ ] Window mode dropdown has 3 options
- [ ] Resolution dropdown shows common 16:9 resolutions
- [ ] VSync checkbox toggles state
- [ ] Quality preset dropdown has 4 levels
- [ ] Graphics changes visible after Apply
- [ ] Settings persist after Apply + restart

### Buttons
- [ ] Apply button saves all settings
- [ ] Apply updates "saved values" for dirty checking
- [ ] Apply doesn't close screen
- [ ] Back button checks for unsaved changes
- [ ] Back shows "Discard Changes?" dialog if dirty
- [ ] Back returns to main menu if no changes
- [ ] Escape key triggers Back

### Integration
- [ ] BindWidget errors don't appear
- [ ] C++ SettingsWidget receives all references
- [ ] SoundClass assets load correctly
- [ ] Settings save/load works

## Sound Classes Required

Create these SoundClass assets at:
`Content/ScarletSands/UI/Audio/`

**SC_Master.uasset**:
- Parent: None (root class)
- Default Volume: 1.0

**SC_Music.uasset**:
- Parent: SC_Master
- Default Volume: 0.7

**SC_SFX.uasset**:
- Parent: SC_Master
- Default Volume: 0.8

Assign SoundClass to audio assets:
- Title music → SC_Music
- UI sounds (hover, select, back) → SC_SFX

## Common Issues

**Volume Changes Not Heard**:
- Check that SoundClass assets exist
- Verify audio assets are assigned correct SoundClass
- Check C++ loads SoundClass references correctly

**Settings Don't Persist**:
- Verify Apply button calls SaveSettings()
- Check save file created at `Saved/SaveGames/SS_Settings.sav`
- Ensure SettingsSaveGame serialization works
