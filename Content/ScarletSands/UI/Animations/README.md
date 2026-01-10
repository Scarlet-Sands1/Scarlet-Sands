# UI Animations Directory

## Purpose
This directory contains widget animation assets created in UMG, including fade-ins, slide transitions, and button state animations.

## Note: This folder is OPTIONAL for Title Screen v1

Widget animations are typically created **inside the UMG widget blueprints** themselves, not as separate assets. This folder exists for organizational purposes if you choose to extract animations for reuse.

## Typical Widget Animations (Created in UMG)

### WBP_TitleRoot
- `Anim_PressKeyFade` - Fade in/out animation for "Press Any Key" text
  - Duration: 2 seconds
  - Loop: Yes
  - Opacity: 0 → 1 → 1 → 0

### WBP_MainMenu (Optional)
- `Anim_FadeIn` - Fade in animation when menu appears
  - Duration: 0.5 seconds
  - Opacity: 0 → 1
- `Anim_FadeOut` - Fade out animation when menu disappears
  - Duration: 0.3 seconds
  - Opacity: 1 → 0

### WBP_Settings (Optional)
- `Anim_SlideIn` - Slide in from right when opening
  - Duration: 0.4 seconds
  - Translation X: 500 → 0
- `Anim_SlideOut` - Slide out to right when closing
  - Duration: 0.3 seconds
  - Translation X: 0 → 500

### Button Animations (Optional)
- `Anim_ButtonHover` - Subtle scale up on hover
  - Duration: 0.1 seconds
  - Scale: 1.0 → 1.05
- `Anim_ButtonPress` - Quick scale down on press
  - Duration: 0.05 seconds
  - Scale: 1.0 → 0.95

## Creating Widget Animations

Widget animations are created directly in UMG widgets:

1. Open widget blueprint (e.g., WBP_TitleRoot)
2. Go to "Animations" panel (bottom left)
3. Click "+ Animation" to create new animation
4. Name it (e.g., Anim_PressKeyFade)
5. Add tracks for widgets you want to animate
6. Add keyframes for properties (Opacity, Translation, Scale, etc.)
7. Set animation properties (duration, loop, speed)
8. Preview in animation editor

## When to Use This Folder

Use this folder ONLY if:
- You want to share animations across multiple widgets
- You're using Sequencer for complex UI cinematics
- You need to version control animation curves separately

For Title Screen v1, all animations should be created **inside the widget blueprints**.

## Animation Best Practices

**Performance:**
- Keep animations short (< 1 second for UI transitions)
- Use simple properties (opacity, translation, scale)
- Avoid animating render transforms if possible
- Don't animate too many widgets simultaneously

**Feel:**
- UI should feel snappy (fast in, slower out)
- Use easing curves for smooth motion (not linear)
- Fade-ins: 0.3-0.5 seconds
- Fade-outs: 0.2-0.3 seconds
- Button hovers: 0.1 seconds
- Button presses: 0.05 seconds

**Accessibility:**
- Provide option to disable animations (for motion sensitivity)
- Don't rely on animation alone to convey information
- Ensure animations don't interfere with input

## Common Animation Curves

**Ease In:** Slow start, fast end (good for exits)
**Ease Out:** Fast start, slow end (good for entrances)
**Ease In-Out:** Smooth both ends (good for general transitions)
**Linear:** Constant speed (rarely used, feels robotic)

## Notes

- Widget animations are lightweight and don't impact performance significantly
- Use animation events to trigger sounds or state changes
- Test animations at different frame rates (60 FPS, 120 FPS, vsync off)
- Consider reducing motion for users with motion sensitivity
