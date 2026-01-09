# UI Audio Assets

This directory contains audio assets for the menu system.

## Required Audio Assets

Create or import these audio assets in the Unreal Editor:

### Sound Effects

1. **SFX_UI_Hover**
   - Type: Sound Cue or Sound Wave
   - Description: Subtle sound when hovering over menu buttons
   - Duration: ~0.1-0.2 seconds
   - Placeholder: Use any short UI beep or click sound

2. **SFX_UI_Select**
   - Type: Sound Cue or Sound Wave
   - Description: Confirmation sound when selecting/clicking buttons
   - Duration: ~0.2-0.3 seconds
   - Placeholder: Use any UI confirmation sound

3. **SFX_UI_Back**
   - Type: Sound Cue or Sound Wave
   - Description: Sound when pressing back/cancel
   - Duration: ~0.2-0.3 seconds
   - Placeholder: Use any UI cancel or back sound

### Music

4. **MUS_Title_Loop**
   - Type: Sound Cue or Sound Wave
   - Description: Background music for title screen (looping)
   - Duration: 1-3 minutes (looping)
   - Placeholder: Use any ambient/atmospheric music track
   - Should be set to loop in the sound properties

### Sound Classes

Create these Sound Class assets to manage volume:

5. **SC_Master**
   - Type: Sound Class
   - Description: Master sound class (parent of all)
   - Properties: Default volume = 1.0

6. **SC_Music**
   - Type: Sound Class
   - Description: Music sound class
   - Parent: SC_Master
   - Properties: Default volume = 0.7

7. **SC_SFX**
   - Type: Sound Class
   - Description: Sound effects class
   - Parent: SC_Master
   - Properties: Default volume = 0.8

## Asset References

The C++ code references these assets at:
- `/Game/ScarletSands/UI/Audio/SC_Master.SC_Master`
- `/Game/ScarletSands/UI/Audio/SC_Music.SC_Music`
- `/Game/ScarletSands/UI/Audio/SC_SFX.SC_SFX`

Ensure assets are placed in this exact path structure.

## Implementation Notes

- All UI sounds should use the SC_SFX sound class
- Title music should use the SC_Music sound class
- Assign sound classes in the Sound Cue/Wave properties
- For placeholders, you can use Unreal's starter content audio or any free UI sounds
