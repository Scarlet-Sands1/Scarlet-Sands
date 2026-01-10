# WBP_MainMenu Widget Specification

**Parent Class**: MainMenuWidget (C++)
**Screen Type**: MainMenu
**Purpose**: Main menu with game options and navigation

## CRITICAL: Button Order (NON-NEGOTIABLE)

Per UX spec, buttons MUST appear in this exact order from top to bottom:
1. **NewGameButton**
2. **ContinueButton**
3. **LoadGameButton**
4. **SettingsButton**
5. **CreditsButton**
6. **QuitButton**

## Widget Hierarchy

```
Canvas Panel (Root)
├── Background Overlay (Image)
│   └── Color: Semi-transparent dark overlay
├── Menu Container (Vertical Box)
│   ├── Anchor: Center
│   ├── Alignment: Center-Center
│   └── Padding: 20px between buttons
│   ├── NewGameButton (Button) ← BindWidget REQUIRED
│   │   ├── Style: Primary button style
│   │   ├── Size: 300x50
│   │   ├── Text: "New Game"
│   │   └── Focus Style: Highlighted border/glow
│   ├── ContinueButton (Button) ← BindWidget REQUIRED
│   │   ├── Style: Primary button style
│   │   ├── Size: 300x50
│   │   ├── Text: "Continue"
│   │   ├── Enabled: Controlled by C++ (dynamic)
│   │   └── Disabled Style: Grayed out
│   ├── LoadGameButton (Button) ← BindWidget REQUIRED
│   │   ├── Style: Primary button style
│   │   ├── Size: 300x50
│   │   ├── Text: "Load Game (Coming Soon)"
│   │   ├── Enabled: false (v1 disabled)
│   │   └── Disabled Style: Grayed out
│   ├── SettingsButton (Button) ← BindWidget REQUIRED
│   │   ├── Style: Primary button style
│   │   ├── Size: 300x50
│   │   └── Text: "Settings"
│   ├── CreditsButton (Button) ← BindWidget REQUIRED
│   │   ├── Style: Primary button style
│   │   ├── Size: 300x50
│   │   └── Text: "Credits"
│   └── QuitButton (Button) ← BindWidget REQUIRED
│       ├── Style: Secondary/Danger button style
│       ├── Size: 300x50
│       └── Text: "Quit"
```

## BindWidget Requirements

**ALL buttons must have BindWidget meta tag in C++** (already implemented).

In UMG Designer, ensure variable names EXACTLY match:
- `NewGameButton`
- `ContinueButton`
- `LoadGameButton`
- `SettingsButton`
- `CreditsButton`
- `QuitButton`

**CASE SENSITIVE** - Must match C++ exactly or binding will fail at runtime.

## Blueprint Setup

### Variables
- None required (C++ handles all navigation logic)

### Event Graph

**Event Construct**:
- Call Parent::Event Construct
- C++ will handle:
  - Button event binding (OnClicked, OnHovered)
  - Continue button state (enable/disable based on save)
  - LoadGame button state (disabled in v1)
  - Initial focus setup
  - Navigation order array

**NO Blueprint logic needed** - All handled in C++ MainMenuWidget class.

## Button Styling

### Normal State
- Background: Dark semi-transparent (#1a1a1aCC)
- Border: 2px solid #404040
- Text: White (#FFFFFF)
- Font Size: 18

### Hovered State
- Background: Lighter (#2a2a2aCC)
- Border: 2px solid #606060
- Text: White (#FFFFFF)
- Play hover sound (handled by C++)

### Focused State (Keyboard/Gamepad)
- Background: #2a2a2aCC
- Border: 3px solid #00AAFF (bright blue)
- Glow effect optional
- Text: White (#FFFFFF)

### Pressed State
- Background: Darker (#0a0a0aCC)
- Border: 2px solid #808080
- Text: Slightly gray (#E0E0E0)
- Play select sound (handled by C++)

### Disabled State (Continue/LoadGame)
- Background: Very dark (#0f0f0fCC)
- Border: 1px solid #303030
- Text: Dark gray (#505050)
- No hover/click response

## Navigation Behavior (C++ Controlled)

The C++ MainMenuWidget handles:

### Focus Priority
- If save exists → ContinueButton gets focus
- If no save → NewGameButton gets focus

### D-pad/Arrow Navigation
- Down: Move to next enabled button (wrap to top)
- Up: Move to previous enabled button (wrap to bottom)
- Skips disabled buttons automatically

### Mouse Integration
- Hover updates CurrentFocusIndex
- Keeps keyboard/gamepad navigation in sync

### Input Handling
- Enter/Space/Gamepad A: Activate focused button
- Escape/Gamepad B: Show quit confirmation

## Audio Integration

C++ MainMenuWidget handles all audio via MenuWidgetBase:
- `PlayHoverSound()` on button hover/focus change
- `PlaySelectSound()` on button click
- `PlayBackSound()` on escape/back

Assign sound assets in C++ or UMG:
- HoverSound: SFX_UI_Hover
- SelectSound: SFX_UI_Select
- BackSound: SFX_UI_Back

## Testing Checklist

### Visual
- [ ] All 6 buttons appear in correct order
- [ ] Button sizes are uniform (300x50)
- [ ] Spacing between buttons is consistent (20px)
- [ ] Text is centered and readable
- [ ] Focus highlight is clearly visible

### Functionality (No Save)
- [ ] Continue button is disabled/grayed
- [ ] LoadGame button is disabled with "(Coming Soon)" text
- [ ] New Game has initial focus
- [ ] New Game starts game immediately (no confirmation)

### Functionality (With Save)
- [ ] Continue button is enabled
- [ ] Continue has initial focus (not New Game)
- [ ] Continue loads existing save
- [ ] New Game shows overwrite confirmation

### Navigation
- [ ] D-pad Down moves focus to next enabled button
- [ ] D-pad Up moves focus to previous enabled button
- [ ] Navigation wraps (bottom → top, top → bottom)
- [ ] Disabled buttons are skipped
- [ ] Mouse hover updates focus visual
- [ ] Keyboard/gamepad focus stays visible

### Audio
- [ ] Hover sound plays on mouse hover
- [ ] Hover sound plays on D-pad navigation
- [ ] Select sound plays on button click
- [ ] Back sound plays on Escape key
- [ ] Quit confirmation shows on Escape

### Integration
- [ ] BindWidget errors don't appear in log
- [ ] C++ MainMenuWidget receives button references
- [ ] All button callbacks fire correctly
- [ ] MenuManager navigation works

## Common Issues

**BindWidget Failure**:
- Error: "Could not find widget named 'NewGameButton'"
- Fix: Ensure variable name in UMG matches C++ exactly (case sensitive)

**Buttons Not Clickable**:
- Check if button Visibility is set to Visible (not Collapsed/Hidden)
- Check if parent Canvas Panel has proper Hit Test Visibility

**Focus Not Visible**:
- Ensure Focus Style is different from Normal State
- Add bright border or glow to focused buttons

**Navigation Not Working**:
- Verify NativeOnKeyDown is not blocked by Blueprint
- Check that IsEnabled is true for navigable buttons
