# UI Textures Directory

## Purpose
This directory contains all 2D texture assets used in the Scarlet Sands UI, including logos, backgrounds, icons, and decorative elements.

## Required Textures for Title Screen v1

**Logo:**
- `T_UI_Logo_ScarletSands` - Main game logo (recommended: 1024x512 or 2048x1024 PNG with alpha)

**Backgrounds:**
- `T_UI_Background_MainMenu` - Background overlay for main menu (optional, can use solid color)
- `T_UI_Background_Settings` - Background for settings screen (optional)
- `T_UI_Background_Credits` - Background for credits screen (optional)

**Button Elements (Optional):**
- `T_UI_Button_Normal` - Default button state
- `T_UI_Button_Hovered` - Hovered button state
- `T_UI_Button_Pressed` - Pressed button state
- `T_UI_Button_Disabled` - Disabled button state

**Icons (Optional):**
- `T_UI_Icon_Audio` - Audio settings icon
- `T_UI_Icon_Graphics` - Graphics settings icon
- `T_UI_Icon_Controls` - Controls settings icon

## Naming Convention (LOCKED - NO EXCEPTIONS)

**Pattern:** `T_UI_[Category]_[Description]`

**Categories:**
- `Logo` - Game logos and branding
- `Background` - Background images and overlays
- `Button` - Button states and decorations
- `Icon` - Small icons and symbols
- `Border` - Decorative borders and frames
- `Particle` - Texture sheets for UI particles

**Examples:**
- `T_UI_Logo_ScarletSands`
- `T_UI_Background_Gradient_Dark`
- `T_UI_Button_Normal`
- `T_UI_Icon_Settings`

## Technical Specifications

**Resolution:**
- UI logos: 1024x512 or 2048x1024 (power of 2)
- Backgrounds: Match target resolution (1920x1080 recommended)
- Icons: 64x64, 128x128, or 256x256
- Buttons: 512x128 or appropriate aspect ratio

**Format:**
- PNG with alpha channel (transparency)
- TGA for high-quality textures
- Avoid JPEG (no alpha support)

**Compression:**
- UI textures: Use TC_UserInterface2D compression
- Disable mipmaps for crisp UI rendering
- Enable alpha channel if needed

## Import Instructions

1. In Unreal Editor, navigate to this folder
2. Drag and drop PNG/TGA files into Content Browser
3. Select all imported textures
4. Right-click → Asset Actions → Bulk Edit via Property Matrix
5. Set Texture Group to "UI"
6. Set Compression Settings to "UserInterface2D (RGBA)"
7. Set MipGenSettings to "NoMipmaps"
8. Save all

## Best Practices

- Use power-of-2 dimensions when possible (512, 1024, 2048)
- Keep file sizes reasonable (< 2MB per texture)
- Use alpha channel for transparency, not color keying
- Author at 2x target size for retina/4K displays
- Test textures at 1080p and 4K resolutions

## Notes

- All textures must be optimized for UI rendering
- Avoid using world texture settings
- Consider using vector graphics (SVG) for logos when possible, then rasterize
