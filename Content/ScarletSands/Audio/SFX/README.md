# SFX (Sound Effects) Directory

## Purpose
This directory contains all sound effects for Scarlet Sands, including UI sounds, gameplay sounds, and environmental audio.

## Required SFX for Title Screen v1

**UI Sounds (Priority):**
- `SFX_UI_Hover` - Button hover/focus sound
  - Duration: 0.05-0.1 seconds
  - Style: Subtle, high-pitched (800-1200 Hz)
  - Volume: Quiet (don't overpower)

- `SFX_UI_Select` - Button click/select sound
  - Duration: 0.1-0.2 seconds
  - Style: Crisp, satisfying (600-900 Hz)
  - Volume: Medium

- `SFX_UI_Back` - Back button/cancel sound
  - Duration: 0.1-0.15 seconds
  - Style: Lower pitch than Select (400-700 Hz)
  - Volume: Medium

## Naming Convention (LOCKED - NO EXCEPTIONS)

**Pattern:** `SFX_[Category]_[Description]`

**Examples:**
- `SFX_UI_Hover`
- `SFX_UI_Select`
- `SFX_UI_Back`
- `SFX_UI_Error`
- `SFX_UI_Confirm`
- `SFX_UI_SliderMove`

**Category Tags:**
- `UI` - User interface sounds
- `Footstep` - Player movement (future)
- `Weapon` - Combat sounds (future)
- `Impact` - Hit/collision sounds (future)
- `Ambient` - Background environmental sounds (future)
- `Dialogue` - Voice/speech (future)

## SoundClass Assignment

**All UI SFX MUST be assigned to:** `SC_SFX`

This ensures:
- Volume controlled by SFX Volume slider in settings
- Proper mixing with music (no clipping)
- Consistent attenuation settings

## Technical Specifications

**Format:**
- WAV (preferred for short SFX)
- 44.1 kHz sample rate
- 16-bit depth
- Mono (1 channel) for UI sounds

**Length:**
- UI sounds: 0.05-0.2 seconds (very short)
- Keep total duration minimal (no long tails)
- Use tight envelopes (quick attack, short decay)

**File Size:**
- UI SFX should be tiny (< 50KB each)
- Use WAV for quality (no compression needed for short sounds)

## Sound Design Guidelines

### SFX_UI_Hover
- **Purpose:** Provide audio feedback when hovering over interactive elements
- **Characteristics:**
  - Very short (50-100ms)
  - Subtle, non-intrusive
  - Higher frequency (bright sound)
  - Clean sine wave or soft synth
- **Example:** Soft "blip" or gentle "tick"

### SFX_UI_Select
- **Purpose:** Confirm button press or selection
- **Characteristics:**
  - Short (100-200ms)
  - Satisfying, positive feeling
  - Mid-high frequency
  - Clear attack, quick decay
- **Example:** "Click", "beep", or "pop" sound

### SFX_UI_Back
- **Purpose:** Indicate backward navigation or cancellation
- **Characteristics:**
  - Short (100-150ms)
  - Lower pitch than Select
  - Neutral feeling (not negative)
  - Clear but softer than Select
- **Example:** Lower "click" or "thunk"

## Import Instructions

1. In Unreal Editor, navigate to this folder
2. Drag and drop WAV files into Content Browser
3. Unreal will create Sound Wave assets
4. Rename following convention: `SFX_[Category]_[Description]`
5. Double-click Sound Wave asset to open
6. Set Sound Class to `/Game/ScarletSands/UI/Audio/SC_SFX`
7. Disable "Looping" checkbox (UI sounds never loop)
8. Set Volume Multiplier if needed (default 1.0)
9. Optionally create Sound Attenuation settings for 3D sounds
10. Save asset

## Sound Attenuation

For UI sounds (2D playback):
- **No attenuation needed**
- Played at consistent volume regardless of position
- Always audible when UI is visible

For future 3D sounds (gameplay):
- Create Sound Attenuation asset
- Set falloff distance
- Configure spatialization

Title Screen v1 uses **2D playback only** (no attenuation).

## Integration with C++ Widgets

UI sounds are played from C++ widget classes:

**MenuWidgetBase.h:**
```cpp
UPROPERTY(EditDefaultsOnly, Category = "Audio")
USoundBase* HoverSound;

UPROPERTY(EditDefaultsOnly, Category = "Audio")
USoundBase* SelectSound;

UPROPERTY(EditDefaultsOnly, Category = "Audio")
USoundBase* BackSound;
```

**Set in widget Blueprint:**
1. Open WBP_MainMenu (or other widget)
2. Go to Class Defaults
3. Find Audio section
4. Set HoverSound = SFX_UI_Hover
5. Set SelectSound = SFX_UI_Select
6. Set BackSound = SFX_UI_Back

**C++ automatically plays sounds on:**
- HoverSound: When button receives mouse hover
- SelectSound: When button is clicked
- BackSound: When Escape/B is pressed

## Volume Mixing

UI sounds should be mixed to avoid clipping:
- **Default SFX Volume:** 0.8 (80%)
- **Individual volumes:**
  - Hover: 0.5-0.7 (quiet, frequent)
  - Select: 0.8-1.0 (medium, occasional)
  - Back: 0.7-0.9 (medium, occasional)

Test with multiple sounds playing simultaneously (rapid button hovers).

## Best Practices

- **Keep it subtle:** UI sounds should enhance, not distract
- **Consistency:** Use similar sounds for similar actions
- **Context:** Different sounds for different contexts (confirm vs. cancel)
- **Testing:** Test with all volume settings (0%, 50%, 100%)
- **Accessibility:** Ensure sounds work with visual-only mode
- **Rapid Fire:** Test hovering rapidly across buttons (no clipping)

## Sound Design Tips

**Quick Start (No Audio Experience):**
1. Use royalty-free UI sound packs (Sonniss, freesound.org)
2. Filter for: short, click, beep, UI
3. Pick 3 sounds with different pitches
4. Import and assign

**DIY Approach:**
1. Use synthesizer (Serum, Vital, or free tools)
2. Create short sine/square wave tones
3. Apply envelope: Fast attack (0ms), short decay (50-100ms)
4. Export as WAV at 44.1kHz
5. Import to Unreal

**Professional Approach:**
1. Commission sound designer
2. Provide game theme/mood reference
3. Request variations for A/B testing
4. Iterate based on playtesting feedback

## Notes

- All UI SFX go through SC_Master → SC_SFX hierarchy
- Default SFX volume: 0.8 (80%)
- SFX volume is controlled independently from Music
- UI sounds should be short to avoid overlap
- Consider sound variations for long play sessions (avoid fatigue)
