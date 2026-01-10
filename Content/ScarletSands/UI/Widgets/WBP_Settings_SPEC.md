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
│   │   └── Note: "(Use UGameUserSettings for quality, resolution, etc.)"
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
- `MasterVolumeSlider`
- `MusicVolumeSlider`
- `SFXVolumeSlider`
- `MouseSensitivitySlider`
- `InvertYCheckBox`
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

### Mouse Sensitivity
- Stored in SettingsSaveGame
- Applied to player controller on load

### Invert Y Axis
- Stored in SettingsSaveGame
- Applied to player controller on load

### Apply Button
- Saves all settings to SS_Settings save slot
- Shows confirmation (optional)
- Does NOT close settings screen

### Back Button
- Returns to main menu
- Does NOT save changes (only Apply saves)
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

### Buttons
- [ ] Apply button saves settings
- [ ] Apply doesn't close screen
- [ ] Back button returns to main menu
- [ ] Back doesn't save unsaved changes
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
