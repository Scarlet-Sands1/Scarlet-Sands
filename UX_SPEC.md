# Title Screen UX Specification

This document describes the user experience requirements for the Title Screen and Main Menu system.

## 1. Screen Map (Navigation Graph)

```
Boot → Title Screen (Backdrop + UI Root)
    ↓ (Any Key)
Main Menu Screen
    ├→ New Game
    ├→ Continue (disabled if no save)
    ├→ Load Game (v1: optional; hidden/disabled if no slots)
    ├→ Settings
    │   ├→ Audio tab (required)
    │   ├→ Graphics tab (required)
    │   ├→ Controls tab (required)
    │   └→ Buttons: Apply, Back
    ├→ Credits
    │   └→ Scrollable credits + Back
    └→ Quit → Confirm Quit dialog

Confirm Dialog (Reusable Modal)
    ├→ Quit confirmation (required)
    └→ Overwrite save confirmation for New Game if save exists (required)
```

## 2. Button Order (Main Menu)

The main menu buttons must appear in this exact order from top to bottom:

1. **New Game**
2. **Continue** (disabled if no save)
3. **Load Game** (v1.1 optional; hide or disable in v1)
4. **Settings**
5. **Credits**
6. **Quit**

**Rationale**: Standard AAA pattern with New Game first, Continue second (enabled when save exists).

## 3. Navigation & Focus Rules (Controller + KB/M)

### Focus Rules

**On screen open**: Focus lands on the highest-priority enabled button:
- If save exists → **Continue**
- Else → **New Game**

### Input Methods

**D-pad / Left stick / Up/Down arrows**: Moves focus through buttons
- Navigation wraps (bottom → top, top → bottom)
- Skips disabled buttons automatically
- Plays hover sound on focus change

**Mouse hover**: Updates focus highlight
- Controller/keyboard focus doesn't get "lost"
- Synchronizes CurrentFocusIndex with hovered button
- Plays hover sound

**Confirm**: Enter / Space / Gamepad A
**Back**: Escape / Gamepad B

### Focus Visibility

- Focus highlight is always visible and high-contrast
- Clear visual indication of which button has focus
- Works consistently across all input methods (mouse, keyboard, gamepad)

## 4. No Soft-Locks

Escape/B always works to go back:

**Main Menu**: Opens Quit confirm dialog (recommended) or does nothing
**Settings/Credits**: Returns to Main Menu
**Confirm dialog**: Cancels dialog and returns to prior screen

Navigation stack guarantees back always has a valid destination.

## 5. Continue / Load Enablement Rules

### Single-slot save (v1)

- **Save slot name**: `SS_MainSlot`
- **Continue enabled if**: `DoesSaveGameExist(SS_MainSlot)` returns true
- **Continue action**: Loads from that slot
- **Dynamic checking**: Enabled state updates in real-time via `NativeTick()`

### New Game Flow

**If no save exists**:
- Clicking New Game immediately creates new game and transitions to world

**If save exists**:
- Clicking New Game shows **Overwrite Confirmation** dialog
- Dialog message: "Starting a new game will overwrite your existing save. Continue?"
- If **confirmed** → delete/overwrite slot → start new session
- If **canceled** → return to main menu

### Load Game (v1.1 optional)

**If not implementing slots yet** (v1):
- **Option A**: Hide the button entirely (`SetVisibility(Collapsed)`)
- **Option B**: Show disabled with label "(Coming Soon)" (safe placeholder)
- C++ implementation shows placeholder dialog: "Multiple save slots coming in v1.1!"

**If implementing slots later** (v1.1+):
- Load screen lists slots + metadata (timestamp, playtime)
- Player can select which slot to load
- Out of scope for v1

## 6. Settings Behavior

### Apply Button
- Applies all changes immediately
- Saves to persistent storage (`SS_Settings` slot)
- Does not close settings screen
- Shows confirmation or feedback (optional)

### Back Button
- Returns to Main Menu
- Does not save changes (changes persist from Apply only)
- Can warn user about unsaved changes (optional enhancement)

## 7. Audio Feedback

All UI interactions should have audio feedback:

**Hover**: `SFX_UI_Hover` plays when focus changes (mouse hover or D-pad navigation)
**Select**: `SFX_UI_Select` plays when button is clicked/activated
**Back**: `SFX_UI_Back` plays when back navigation occurs

Audio is managed through C++ and triggered by widget base class methods:
- `PlayHoverSound()`
- `PlaySelectSound()`
- `PlayBackSound()`

## 8. Implementation Notes

### C++ First Architecture

- All logic in C++ (MainMenuWidget, MenuManagerSubsystem)
- UMG widgets are display only + forward events
- Focus management handled in C++ via navigation arrays
- Input routing through `NativeOnKeyDown`

### Navigation Order Array

```cpp
// Built in NativeConstruct, maintains button order
NavigationOrder.Add(NewGameButton);       // Index 0
NavigationOrder.Add(ContinueButton);      // Index 1
NavigationOrder.Add(LoadGameButton);      // Index 2
NavigationOrder.Add(SettingsButton);      // Index 3
NavigationOrder.Add(CreditsButton);       // Index 4
NavigationOrder.Add(QuitButton);          // Index 5
```

### Focus Management

- `CurrentFocusIndex` tracks which button has focus
- `SetInitialFocus()` sets focus on screen open per priority rules
- Arrow/D-pad navigation increments/decrements index, skipping disabled
- Mouse hover updates `CurrentFocusIndex` to keep keyboard/gamepad in sync

### Save Checking

```cpp
bool UMainMenuWidget::DoesSaveExist() const
{
    UScarletSandsGameInstance* GameInstance = Cast<UScarletSandsGameInstance>(GetGameInstance());
    if (GameInstance)
    {
        return GameInstance->DoesSaveGameExist(TEXT("SS_MainSlot"));
    }
    return false;
}
```

Called in `NativeTick()` to dynamically enable/disable Continue button.

## 9. Accessibility Considerations

- High contrast focus indicators
- Clear button labels
- Supports multiple input methods simultaneously
- No timed interactions required
- All interactive elements are keyboard/gamepad accessible
- Text is readable at standard UI scales

## 10. Testing Checklist

- [ ] Continue disabled when no save exists
- [ ] Continue enabled when save exists
- [ ] Focus lands on Continue when enabled and save exists
- [ ] Focus lands on New Game when no save
- [ ] D-pad Down navigates to next enabled button
- [ ] D-pad Up navigates to previous enabled button
- [ ] Navigation wraps from bottom to top and vice versa
- [ ] Disabled buttons are skipped during navigation
- [ ] Mouse hover updates focus indicator
- [ ] Mouse hover synchronizes with keyboard focus
- [ ] Enter/Space/A activates focused button
- [ ] Escape/B opens quit confirm from main menu
- [ ] Escape/B returns to main menu from Settings
- [ ] Escape/B returns to main menu from Credits
- [ ] Escape/B cancels confirm dialogs
- [ ] New Game without save → immediate transition
- [ ] New Game with save → shows overwrite confirmation
- [ ] Overwrite cancel → returns to main menu
- [ ] Overwrite confirm → starts new game
- [ ] Hover sound plays on focus change
- [ ] Select sound plays on button click
- [ ] Back sound plays on back navigation
- [ ] Load Game button is disabled/hidden in v1
- [ ] No soft locks anywhere in navigation

## 11. Version History

**v1** (Current):
- Single-slot save system (`SS_MainSlot`)
- New Game/Continue/Settings/Credits/Quit
- Load Game button disabled or hidden
- Overwrite confirmation for New Game
- Quit confirmation
- Full keyboard/mouse/gamepad navigation
- Focus management with priority rules

**v1.1** (Planned):
- Multiple save slots
- Load Game screen functional
- Slot metadata display (timestamp, playtime)
- Delete save confirmation

## 12. References

- Implementation: `Source/ScarletSands/Menu/MainMenuWidget.h/cpp`
- Subsystem: `Source/ScarletSands/Menu/MenuManagerSubsystem.h/cpp`
- Save System: `Source/ScarletSands/Save/ScarletSandsSaveGame.h/cpp`
- Widget Docs: `Content/ScarletSands/UI/Widgets/README.md`
