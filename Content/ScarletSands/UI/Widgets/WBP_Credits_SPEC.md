# WBP_Credits Widget Specification

**Parent Class**: CreditsWidget (C++)
**Screen Type**: Credits
**Purpose**: Display game credits with scroll capability

## Widget Hierarchy

```
Canvas Panel (Root)
├── Background Overlay (Image)
├── Credits Container (Vertical Box)
│   ├── Anchor: Fill
│   ├── Title: "Credits"
│   ├── Scroll Box
│   │   ├── Size: 800x600
│   │   ├── Scroll Bar Style: Minimal
│   │   └── CreditsText (Text Block) ← BindWidget REQUIRED
│   │       ├── Text: (Set by C++ InitializeCreditsText)
│   │       ├── Font Size: 16
│   │       ├── Alignment: Center-Center
│   │       ├── Auto Wrap: true
│   │       └── Read Only: true
│   └── Back Button Container
│       └── BackButton (Button) ← BindWidget REQUIRED
│           ├── Text: "Back"
│           ├── Size: 150x40
│           └── Position: Bottom-center
```

## BindWidget Requirements

Variable names MUST match C++:
- `CreditsText` (Text Block)
- `BackButton` (Button)

## Credits Text Content (Set by C++)

The C++ CreditsWidget::InitializeCreditsText() sets this text:

```
SCARLET SANDS

A survival adventure on a mysterious island


DEVELOPMENT
Game Design & Programming
Art & Animation
Audio & Music


SPECIAL THANKS
Epic Games - Unreal Engine 5
Community Contributors


© 2024 Scarlet Sands
All Rights Reserved
```

**Do NOT set credits text in UMG** - Let C++ handle it via InitializeCreditsText().

## Blueprint Setup

### Event Graph

**Event Construct**:
- Call Parent::Event Construct
- C++ handles:
  - Binding BackButton OnClicked
  - Setting CreditsText content via InitializeCreditsText()

**NO additional Blueprint logic needed**.

## Styling

### Background
- Semi-transparent dark overlay (#000000AA)

### Title
- Font Size: 28
- Color: White (#FFFFFF)
- Font Weight: Bold
- Margin: 20px bottom

### Scroll Box
- Background: Transparent
- Scroll Bar: Thin, minimal style
- Color: #404040
- Scroll speed: Medium

### Credits Text
- Font: Roboto or game-themed font
- Font Size: 16
- Color: Light gray (#CCCCCC)
- Line Spacing: 1.5
- Alignment: Center
- Section spacing: Use newlines (C++ handles)

### Back Button
- Same style as other menu buttons
- Width: 150px, Height: 40px

## Scrolling Behavior

### Manual Scroll
- Mouse wheel scrolls up/down
- D-pad up/down scrolls (optional)

### Auto-Scroll (Optional Enhancement)
- Blueprint can add auto-scroll animation
- Speed: Slow (2-3 seconds per screen)
- Start after 2 second delay
- Stop on manual scroll

## Testing Checklist

### Visual
- [ ] Credits text displays completely
- [ ] Text is centered and readable
- [ ] Scroll box allows viewing all content
- [ ] Background overlay visible

### Functionality
- [ ] Mouse wheel scrolls credits
- [ ] Scroll bar appears if content overflows
- [ ] Back button returns to main menu
- [ ] Escape key returns to main menu
- [ ] Back sound plays on navigation

### Content
- [ ] All credit sections visible
- [ ] Text formatting is correct
- [ ] No text cutoff issues

### Integration
- [ ] BindWidget errors don't appear
- [ ] C++ CreditsWidget receives references
- [ ] InitializeCreditsText() populates content

## Common Issues

**Text Not Appearing**:
- Check CreditsText BindWidget name matches C++
- Verify C++ InitializeCreditsText() is called
- Check Text Block visibility is set to Visible

**Scroll Not Working**:
- Ensure Scroll Box is enabled
- Check content height exceeds scroll box height
- Verify Scroll Bar Visibility is set to Auto or Visible
