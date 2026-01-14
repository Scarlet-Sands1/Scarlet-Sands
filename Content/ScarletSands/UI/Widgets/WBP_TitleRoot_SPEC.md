# WBP_TitleRoot Widget Specification

**Parent Class**: MenuWidgetBase (C++)
**Screen Type**: TitleRoot
**Purpose**: Root widget for the title screen with "Press Any Key" prompt

## Widget Hierarchy

```
Canvas Panel (Root)
├── Background Image (full screen)
│   └── Color: Semi-transparent black overlay
├── Title Logo (Image)
│   ├── Size: 512x256 (or appropriate for logo)
│   ├── Position: Center-top (Y: 200)
│   └── Anchor: Top-Center
├── Press Any Key Text (Text Block)
│   ├── Text: "Press Any Key to Continue"
│   ├── Font Size: 24
│   ├── Position: Center-bottom (Y: -150)
│   ├── Anchor: Bottom-Center
│   └── Animation: Fade in/out loop (0.5s fade, 1s hold)
└── Version Text (Text Block)
    ├── Text: "v1.0.0"
    ├── Font Size: 12
    ├── Position: Bottom-right corner
    └── Anchor: Bottom-Right
```

## Blueprint Setup

### Variables
- None required (inherits from MenuWidgetBase)

### Event Graph

**Event Construct**:
- Call Parent::Event Construct
- Start fade animation for "Press Any Key" text
- Set input mode to UI Only
- Show mouse cursor

**On Any Key Press** (Override NativeOnKeyDown):
- Play select sound via `PlaySelectSound()`
- Get MenuManager subsystem
- Call `MenuManager->ShowMainMenu()`
- Remove this widget from parent

### Animations

**Anim_PressKeyFade**:
- Track 1: Text opacity 0.0 → 1.0 over 0.5s
- Track 2: Text opacity 1.0 → 1.0 over 1.0s (hold)
- Track 3: Text opacity 1.0 → 0.0 over 0.5s
- Set to Loop

## Styling

### Background
- Material: Solid color or backdrop image
- Color: #000000 with 0.7 alpha
- Blur effect optional

### Title Logo
- Use project title logo asset
- White or game-themed color
- Drop shadow for depth

### Text Styling
- Font: Roboto or game-themed font
- Press Any Key: White, centered
- Version: Gray (#808080), small

## Testing Checklist

- [ ] Title logo displays correctly
- [ ] "Press Any Key" text fades in/out continuously
- [ ] Any keyboard key triggers transition to main menu
- [ ] Mouse click triggers transition
- [ ] Gamepad button triggers transition
- [ ] Select sound plays on transition
- [ ] Widget properly removes itself after transition
