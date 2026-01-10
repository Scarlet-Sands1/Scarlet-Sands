# Music Directory

## Purpose
This directory contains all music tracks for Scarlet Sands, separated from UI/SFX for organizational clarity.

## Required Music for Title Screen v1

**Title Music:**
- `MUS_Title_Loop` - Background music for title screen
  - Duration: 60-120 seconds
  - Format: Seamless loop (no pops/clicks at loop point)
  - Style: Ambient, atmospheric, sets the mood for the game
  - Recommended: Orchestral, electronic ambient, or hybrid

## Naming Convention (LOCKED - NO EXCEPTIONS)

**Pattern:** `MUS_[Context]_[Description]`

**Examples:**
- `MUS_Title_Loop` - Title screen background music
- `MUS_MainMenu_Ambient` - Main menu ambient loop
- `MUS_Credits_Cue` - Credits roll music

**Context Tags:**
- `Title` - Title screen/splash
- `MainMenu` - Main menu background
- `Credits` - Credits screen
- `Combat` - Combat music (future)
- `Exploration` - Exploration music (future)
- `Boss` - Boss battle music (future)

## SoundClass Assignment

**All music tracks MUST be assigned to:** `SC_Music`

This ensures:
- Volume controlled by Music Volume slider in settings
- Proper mixing with SFX (UI sounds don't clash)
- Consistent attenuation settings

## Technical Specifications

**Format:**
- WAV or OGG Vorbis
- 44.1 kHz or 48 kHz sample rate
- 16-bit (minimum) or 24-bit (recommended)
- Stereo (2 channels)

**Length:**
- Title music: 60-120 seconds minimum
- Must loop seamlessly (fade in/out at loop point)
- Avoid abrupt endings or jarring transitions

**File Size:**
- Keep under 10MB per track (use OGG compression if needed)
- Balance quality vs. size (OGG at 192 kbps is usually sufficient)

## Import Instructions

1. In Unreal Editor, navigate to this folder
2. Drag and drop WAV/OGG files into Content Browser
3. Unreal will create Sound Wave assets
4. Rename following convention: `MUS_[Context]_[Description]`
5. Double-click Sound Wave asset to open
6. Set Sound Class to `/Game/ScarletSands/UI/Audio/SC_Music`
7. Enable "Looping" checkbox (for loop tracks)
8. Set Volume Multiplier if needed (default 1.0)
9. Save asset

## Loop Configuration

For seamless looping:
1. Author music with exact loop points
2. In Sound Wave editor:
   - Enable "Looping"
   - Set Loop Start/End if not using full duration
   - Preview to ensure no pops/clicks
3. Alternatively, use Sound Cue for advanced loop control

## Sound Cue vs Sound Wave

**Use Sound Wave when:**
- Simple looping music
- No variations needed
- Direct playback from C++ or Blueprint

**Use Sound Cue when:**
- Layering multiple tracks
- Random variations
- Crossfade loops
- Complex mixing logic

For Title Screen v1, **Sound Wave is sufficient** for `MUS_Title_Loop`.

## Integration with Title Screen

Music playback is handled in the TitleBackdrop level:
1. Place Ambient Sound actor in L_TitleBackdrop
2. Set Sound to `MUS_Title_Loop`
3. Enable Auto Activate
4. Set Sound Class to SC_Music (if not already set in Sound Wave)
5. Volume: Controlled by settings (SC_Music.Volume)

## Best Practices

- Keep music subtle for menus (don't overpower UI sounds)
- Use fade-in at start (0.5-1 second)
- Ensure seamless loop (no audio artifacts)
- Test with volume sliders (Master, Music)
- Consider dynamic music layers for future (menu vs. gameplay)

## Notes

- Music volume is controlled independently from SFX
- Default music volume: 0.7 (70%)
- All music goes through SC_Master → SC_Music hierarchy
- Consider licensing if using third-party music
