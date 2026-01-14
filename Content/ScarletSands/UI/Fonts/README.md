# UI Fonts Directory

## Purpose
This directory contains all font assets used in the Scarlet Sands UI system.

## Required Fonts for Title Screen v1

**Primary UI Font:**
- A clean, readable sans-serif font for menu text
- Should support standard ASCII characters
- Recommended: Roboto, Open Sans, or similar

**Logo Font (Optional):**
- Stylized font for game logo if custom text is used
- Can be decorative/stylized

## Naming Convention

Font assets MUST follow this pattern:
- `Font_[Name]` - The font asset itself
- Example: `Font_Roboto`, `Font_LogoDisplay`

## Import Instructions

1. In Unreal Editor, navigate to this folder
2. Right-click → Import to `/Game/ScarletSands/UI/Fonts/`
3. Select your .ttf or .otf font file
4. Configure font import settings (size, anti-aliasing)
5. Name the asset following the convention above

## Font Size Guidelines

**Main Menu:**
- Button text: 24-32pt
- Title text: 48-64pt
- Body text: 18-24pt

**Settings Screen:**
- Section headers: 20pt
- Labels: 16pt
- Values: 16pt

## Notes

- Ensure fonts have appropriate licensing for game distribution
- Test readability at different resolutions (720p, 1080p, 4K)
- Consider using distance field fonts for scalability
