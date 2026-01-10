# WBP_ConfirmDialog Widget Specification

**Parent Class**: ConfirmDialogWidget (C++)
**Screen Type**: ConfirmDialog
**Purpose**: Reusable modal confirmation dialog for Yes/No choices

## Widget Hierarchy

```
Canvas Panel (Root)
├── Modal Overlay (Image)
│   ├── Fill entire screen
│   ├── Color: Black with 0.8 alpha
│   └── Blocks clicks to background
├── Dialog Container (Border)
│   ├── Anchor: Center
│   ├── Size: 500x300
│   ├── Background: Dark panel (#1a1a1aEE)
│   ├── Border: 2px solid #404040
│   └── Content (Vertical Box)
│       ├── Padding: 30px all sides
│       ├── TitleText (Text Block) ← BindWidget REQUIRED
│       │   ├── Font Size: 24
│       │   ├── Color: White
│       │   ├── Font Weight: Bold
│       │   ├── Alignment: Center
│       │   └── Margin: 20px bottom
│       ├── MessageText (Text Block) ← BindWidget REQUIRED
│       │   ├── Font Size: 16
│       │   ├── Color: Light Gray (#CCCCCC)
│       │   ├── Alignment: Center
│       │   ├── Auto Wrap: true
│       │   └── Margin: 30px bottom
│       └── Button Row (Horizontal Box)
│           ├── Spacing: 20px
│           ├── Alignment: Center
│           ├── ConfirmButton (Button) ← BindWidget REQUIRED
│           │   ├── Text: "Confirm" or "Yes"
│           │   ├── Size: 120x40
│           │   ├── Style: Primary/Danger button
│           │   └── Focus: Initial focus here
│           └── CancelButton (Button) ← BindWidget REQUIRED
│               ├── Text: "Cancel" or "No"
│               ├── Size: 120x40
│               └── Style: Secondary button
```

## BindWidget Requirements

Variable names MUST match C++:
- `TitleText` (Text Block)
- `MessageText` (Text Block)
- `ConfirmButton` (Button)
- `CancelButton` (Button)

## Dialog Usage

The dialog is invoked via MenuManagerSubsystem::ShowConfirmDialog():

```cpp
// Example: Quit confirmation
MenuManager->ShowConfirmDialog(
    FText::FromString(TEXT("Quit Game")),
    FText::FromString(TEXT("Are you sure you want to quit?")),
    OnConfirmDelegate,
    OnCancelDelegate
);
```

C++ ConfirmDialogWidget handles:
- Setting TitleText and MessageText
- Storing confirm/cancel delegates
- Executing appropriate delegate on button click
- Closing dialog (PopScreen)

## Dialog Types

### Quit Confirmation
- Title: "Quit Game"
- Message: "Are you sure you want to quit?"
- Confirm: Quit application
- Cancel: Return to menu

### Overwrite Save Confirmation
- Title: "Overwrite Save?"
- Message: "Starting a new game will overwrite your existing save. Continue?"
- Confirm: Start new game (delete save)
- Cancel: Return to main menu

### Load Game Placeholder (v1)
- Title: "Load Game"
- Message: "Multiple save slots coming in v1.1!"
- Confirm: No action (just close)
- Cancel: No action (just close)

## Blueprint Setup

### Event Graph

**Event Construct**:
- Call Parent::Event Construct
- C++ handles:
  - Binding button OnClicked events
  - Setting initial focus to ConfirmButton
  - Storing delegates

### C++ Methods

**SetDialogContent(Title, Message)**:
- Called by MenuManager before showing
- Sets TitleText and MessageText

**SetCallbacks(OnConfirm, OnCancel)**:
- Stores delegates for button clicks

**OnConfirmClicked()**:
- Executes confirm delegate
- Calls MenuManager->PopScreen()

**OnCancelClicked()**:
- Executes cancel delegate
- Calls MenuManager->PopScreen()

## Styling

### Modal Overlay
- Black with 80% opacity
- Fills entire screen
- Blocks background interaction

### Dialog Panel
- Background: Dark gray (#1a1a1aEE)
- Border: 2px solid medium gray (#404040)
- Shadow: Subtle drop shadow
- Size: 500x300 (adjust for content)

### Title Text
- Font Size: 24
- Color: White (#FFFFFF)
- Font Weight: Bold
- Centered

### Message Text
- Font Size: 16
- Color: Light gray (#CCCCCC)
- Centered
- Word wrap enabled
- Max width: 440px

### Buttons

**Confirm Button** (Danger style):
- Background: Dark red (#8B0000CC)
- Border: 2px solid red (#FF4444)
- Text: White
- Hover: Brighter red

**Cancel Button** (Secondary style):
- Background: Dark gray (#2a2a2aCC)
- Border: 2px solid gray (#606060)
- Text: White
- Hover: Lighter gray

## Input Handling

### Keyboard/Gamepad
- **Tab**: Switch focus between buttons
- **Enter/Space/A**: Activate focused button
- **Escape/B**: Trigger Cancel button

### Mouse
- Click Confirm: Execute confirm action
- Click Cancel: Execute cancel action
- Click outside dialog: No action (modal)

## Navigation

### Initial Focus
- ConfirmButton has initial focus
- Focus highlight clearly visible

### Focus Movement
- Tab/D-pad Right: Confirm → Cancel
- Shift+Tab/D-pad Left: Cancel → Confirm

## Testing Checklist

### Visual
- [ ] Dialog appears centered on screen
- [ ] Modal overlay blocks background
- [ ] Text is readable and properly sized
- [ ] Buttons are clearly distinguishable
- [ ] Focus highlight visible on buttons

### Functionality - Quit Dialog
- [ ] Dialog shows when clicking Quit on main menu
- [ ] Title: "Quit Game"
- [ ] Message: "Are you sure you want to quit?"
- [ ] Confirm quits application
- [ ] Cancel returns to main menu
- [ ] Escape triggers Cancel

### Functionality - Overwrite Dialog
- [ ] Dialog shows when New Game with existing save
- [ ] Title: "Overwrite Save?"
- [ ] Message describes overwrite action
- [ ] Confirm starts new game
- [ ] Cancel returns to main menu

### Functionality - Load Game Placeholder
- [ ] Dialog shows when clicking Load Game (v1)
- [ ] Title: "Load Game"
- [ ] Message: "Multiple save slots coming in v1.1!"
- [ ] Both buttons close dialog without action

### Input
- [ ] Enter/A activates Confirm
- [ ] Escape/B activates Cancel
- [ ] Tab switches focus
- [ ] Mouse clicks work on both buttons

### Integration
- [ ] BindWidget errors don't appear
- [ ] C++ ConfirmDialogWidget receives references
- [ ] Delegates execute correctly
- [ ] Dialog closes after button click
- [ ] Navigation stack handles properly

## Common Issues

**Dialog Not Appearing**:
- Check MenuManager->ShowConfirmDialog() is called
- Verify dialog added to viewport with high Z-order
- Check visibility is set to Visible

**Buttons Not Responding**:
- Verify BindWidget names match C++ exactly
- Check button IsEnabled is true
- Ensure modal overlay doesn't block button clicks

**Text Not Showing**:
- Check C++ SetDialogContent() is called
- Verify TitleText and MessageText BindWidget names
- Ensure text blocks have proper visibility

**Focus Not Working**:
- Check focus style is visually different
- Verify SetKeyboardFocus() is called on ConfirmButton
- Ensure input mode is UI Only
