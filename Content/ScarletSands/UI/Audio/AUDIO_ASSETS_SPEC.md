# UI Audio Assets Specification

**Location**: `Content/ScarletSands/UI/Audio/`
**Purpose**: UI sound effects and title music with SoundClass hierarchy

## Required Assets Overview

### SoundClass Hierarchy
```
SC_Master (root)
├── SC_Music
└── SC_SFX
```

### Sound Assets
- SFX_UI_Hover (UI hover sound effect)
- SFX_UI_Select (UI select/click sound effect)
- SFX_UI_Back (UI back/cancel sound effect)
- MUS_Title_Loop (Title screen background music)

## SoundClass Assets

### SC_Master

**Type**: SoundClass
**Purpose**: Root class for all audio, controls master volume

**Properties**:
- Volume: 1.0 (controlled by settings)
- Pitch: 1.0
- Parent: None
- Children: SC_Music, SC_SFX

**Settings Integration**:
- Controlled by MasterVolumeSlider in WBP_Settings
- C++ SettingsWidget updates `SC_Master.Properties.Volume`

**File**: `SC_Master.uasset`

---

### SC_Music

**Type**: SoundClass
**Purpose**: Background music and ambient tracks

**Properties**:
- Volume: 0.7 (default, controlled by settings)
- Pitch: 1.0
- Parent: SC_Master
- Apply ambient volumes: No

**Settings Integration**:
- Controlled by MusicVolumeSlider in WBP_Settings
- C++ SettingsWidget updates `SC_Music.Properties.Volume`

**Assigned To**:
- MUS_Title_Loop
- Future in-game music tracks

**File**: `SC_Music.uasset`

---

### SC_SFX

**Type**: SoundClass
**Purpose**: UI sound effects and game sound effects

**Properties**:
- Volume: 0.8 (default, controlled by settings)
- Pitch: 1.0
- Parent: SC_Master
- Apply ambient volumes: No

**Settings Integration**:
- Controlled by SFXVolumeSlider in WBP_Settings
- C++ SettingsWidget updates `SC_SFX.Properties.Volume`

**Assigned To**:
- SFX_UI_Hover
- SFX_UI_Select
- SFX_UI_Back
- Future game SFX

**File**: `SC_SFX.uasset`

---

## Sound Effect Assets

### SFX_UI_Hover

**Type**: SoundCue or SoundWave
**Purpose**: Button hover/focus sound

**Properties**:
- Duration: 0.05-0.1 seconds (very short)
- Volume: 0.5-0.7 (subtle)
- Pitch: Medium-high (800-1200 Hz)
- Sound Class: SC_SFX
- Attenuation: None (2D sound)
- Looping: No

**Sound Characteristics**:
- Soft, subtle
- Pleasant, non-intrusive
- Examples: Soft beep, gentle click, light whoosh

**Placeholder**:
For testing, can use:
- Simple sine wave tone (0.05s, 1000 Hz)
- Stock UI hover sound
- Temporary until proper asset created

**C++ Integration**:
```cpp
// In MenuWidgetBase.h
UPROPERTY(EditDefaultsOnly, Category = "Audio")
USoundBase* HoverSound;

// Played via:
PlayHoverSound(); // Calls UGameplayStatics::PlaySound2D
```

**File**: `SFX_UI_Hover.uasset`

---

### SFX_UI_Select

**Type**: SoundCue or SoundWave
**Purpose**: Button click/activation sound

**Properties**:
- Duration: 0.1-0.2 seconds
- Volume: 0.7-0.9 (clear, audible)
- Pitch: Medium (600-900 Hz)
- Sound Class: SC_SFX
- Attenuation: None (2D sound)
- Looping: No

**Sound Characteristics**:
- Crisp, satisfying click
- Positive confirmation
- Examples: Button click, menu select, confirmation beep

**Placeholder**:
For testing, can use:
- Simple click sound
- Stock UI select sound
- Temporary until proper asset created

**C++ Integration**:
```cpp
// In MenuWidgetBase.h
UPROPERTY(EditDefaultsOnly, Category = "Audio")
USoundBase* SelectSound;

// Played via:
PlaySelectSound();
```

**File**: `SFX_UI_Select.uasset`

---

### SFX_UI_Back

**Type**: SoundCue or SoundWave
**Purpose**: Back/cancel navigation sound

**Properties**:
- Duration: 0.1-0.15 seconds
- Volume: 0.6-0.8
- Pitch: Lower than Select (400-700 Hz)
- Sound Class: SC_SFX
- Attenuation: None (2D sound)
- Looping: No

**Sound Characteristics**:
- Slightly "negative" tone (lower pitch)
- Clear but not harsh
- Distinguishable from Select
- Examples: Soft whoosh back, gentle cancel tone

**Placeholder**:
For testing, can use:
- Reverse of select sound
- Stock UI cancel sound
- Temporary until proper asset created

**C++ Integration**:
```cpp
// In MenuWidgetBase.h
UPROPERTY(EditDefaultsOnly, Category = "Audio")
USoundBase* BackSound;

// Played via:
PlayBackSound();
```

**File**: `SFX_UI_Back.uasset`

---

## Music Asset

### MUS_Title_Loop

**Type**: SoundCue with looping SoundWave
**Purpose**: Title screen background music

**Properties**:
- Duration: 60-120 seconds (loop seamlessly)
- Sound Class: SC_Music
- Looping: Yes (seamless)
- Attenuation: None (2D sound)
- Volume: 0.7 (default, controlled by SC_Music)
- Fade In: 2 seconds
- Fade Out: 2 seconds (on level transition)

**Musical Characteristics**:
- Atmospheric, ambient
- Not too energetic (title screen mood)
- Island/adventure theme (matches game)
- Seamless loop point
- No harsh transitions

**Genre/Style**:
- Ambient orchestral
- Atmospheric synth
- Cinematic underscore
- Light ethnic/world music elements

**Placeholder**:
For testing, can use:
- Unreal Engine starter content music (trimmed)
- Royalty-free ambient track
- Simple ambient loop
- Temporary until proper composition

**Technical Requirements**:
- Format: WAV or OGG
- Sample Rate: 44.1 kHz or 48 kHz
- Bit Depth: 16-bit or 24-bit
- Compression: Vorbis (OGG) for size optimization
- Loop Points: Set in audio editor for seamless loop

**SoundCue Setup**:
1. Import SoundWave (WAV file)
2. Create SoundCue
3. Add Looping node
4. Set Sound Class to SC_Music
5. Add Enveloper node for fade in/out
6. Save as MUS_Title_Loop

**Level Integration**:
Place in L_TitleBackdrop level:
- As ambient sound actor, OR
- Triggered by TitleScreenPlayerController BeginPlay

**File**: `MUS_Title_Loop.uasset`

---

## Asset Creation Guide

### Creating SoundClass Assets

**In Unreal Editor**:

1. Content Browser → Right Click
2. Sounds → Sound Class
3. Name: SC_Master
4. Open asset
5. Set properties (volume, pitch)
6. Save

Repeat for SC_Music and SC_SFX, setting SC_Master as parent.

### Creating Sound Effects

**Option 1: Import WAV Files**

1. Prepare WAV files (mono or stereo)
2. Content Browser → Import
3. Select WAV files
4. Import to `Content/ScarletSands/UI/Audio/`
5. Create SoundCue for each (optional)
6. Set Sound Class to SC_SFX

**Option 2: Use SoundCue for Variation**

1. Import base WAV
2. Create SoundCue
3. Add Random node for pitch/volume variation
4. Adds variety to repeated sounds
5. Set Sound Class to SC_SFX

### Creating Title Music

1. Import music WAV file
2. In SoundWave properties:
   - Set Looping: True
   - Or use SoundCue with Looping node
3. Set Sound Class: SC_Music
4. Test loop point seamlessly cycles
5. Add fade in/out enveloper if needed

## Widget Integration

### In UMG Widgets

**WBP_MainMenu, WBP_Settings, WBP_Credits, WBP_ConfirmDialog**:

All inherit from MenuWidgetBase which has:
```cpp
UPROPERTY(EditDefaultsOnly, Category = "Audio")
USoundBase* HoverSound;

UPROPERTY(EditDefaultsOnly, Category = "Audio")
USoundBase* SelectSound;

UPROPERTY(EditDefaultsOnly, Category = "Audio")
USoundBase* BackSound;
```

**In UMG Designer**:
1. Select widget (e.g., WBP_MainMenu)
2. Details Panel → Audio section
3. Hover Sound: Select SFX_UI_Hover
4. Select Sound: Select SFX_UI_Select
5. Back Sound: Select SFX_UI_Back

**C++ calls these automatically**:
- OnHovered events → PlayHoverSound()
- OnClicked events → PlaySelectSound()
- OnBackPressed → PlayBackSound()

## Testing Checklist

### SoundClass Hierarchy
- [ ] SC_Master exists
- [ ] SC_Music parent is SC_Master
- [ ] SC_SFX parent is SC_Master
- [ ] All classes have correct volume defaults

### Sound Assets
- [ ] SFX_UI_Hover imports correctly
- [ ] SFX_UI_Select imports correctly
- [ ] SFX_UI_Back imports correctly
- [ ] MUS_Title_Loop imports and loops

### Sound Class Assignment
- [ ] All UI SFX assigned to SC_SFX
- [ ] Title music assigned to SC_Music
- [ ] No assets using default sound class

### Integration - Widgets
- [ ] MenuWidgetBase has audio properties
- [ ] All menu widgets inherit from MenuWidgetBase
- [ ] Audio assets assigned in UMG
- [ ] Sounds play on hover
- [ ] Sounds play on click
- [ ] Sounds play on back/escape

### Integration - Level
- [ ] Title music plays in L_TitleBackdrop
- [ ] Music loops seamlessly
- [ ] Music fades in on level load
- [ ] Music respects volume settings

### Settings Integration
- [ ] Master volume slider affects all audio
- [ ] Music volume slider only affects music
- [ ] SFX volume slider only affects UI sounds
- [ ] Volume changes are immediate
- [ ] Settings persist after restart

## Placeholder Asset Sources

For rapid prototyping before final audio:

**Free Sound Libraries**:
- freesound.org (CC0/CC-BY licensed)
- incompetech.com (royalty-free music)
- zapsplat.com (UI sounds)
- sonniss.com (GDC bundles)

**Unreal Engine**:
- Starter Content audio
- Marketplace free packs

**Temporary Synthesis**:
- Use Audacity to generate simple tones
- Create placeholder beeps/clicks
- Trim Starter Content music for loops

## Common Issues

**Sounds Not Playing**:
- Check SoundBase* pointers assigned in UMG
- Verify C++ PlayXXXSound() calls execute
- Check audio device output settings

**Volume Not Changing**:
- Verify SoundClass assignment
- Check C++ SettingsWidget loads SoundClass refs
- Ensure Properties.Volume is being set

**Music Not Looping**:
- Check SoundWave Looping property
- Or use SoundCue with Looping node
- Verify loop points are seamless

**Settings Don't Persist**:
- Check SettingsSaveGame serialization
- Verify Apply button calls SaveSettings()
- Check save file exists: Saved/SaveGames/SS_Settings.sav
