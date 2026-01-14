# UI Materials Directory

## Purpose
This directory contains all Material assets used for UI rendering, including base materials, material instances, and parameter collections.

## Required Materials for Title Screen v1

**Base Materials:**
- `M_UI_Base` - Master material for all UI elements (unlit, translucent)
- `M_UI_Button` - Button material with hover/pressed states
- `M_UI_Background` - Background material with color tinting

**Material Instances (Optional):**
- `MI_UI_Button_Primary` - Primary button style (blue/accent color)
- `MI_UI_Button_Secondary` - Secondary button style (gray/neutral)
- `MI_UI_Button_Danger` - Danger button style (red for Quit/Confirm)
- `MI_UI_Background_Dark` - Dark background overlay

## Naming Convention (LOCKED - NO EXCEPTIONS)

**Pattern:** `M_UI_[Description]` for base materials
**Pattern:** `MI_UI_[Description]` for material instances

**Examples:**
- `M_UI_Base`
- `M_UI_Button`
- `MI_UI_Button_Primary`
- `MI_UI_Background_Gradient`

## Material Setup

### M_UI_Base (Master Material)

**Material Domain:** User Interface
**Blend Mode:** Translucent (or Masked if no transparency needed)
**Shading Model:** Unlit

**Parameters:**
- `BaseColor` (Vector3) - RGB color
- `Opacity` (Scalar) - Alpha transparency
- `Texture` (Texture2D) - Optional texture input
- `EmissiveStrength` (Scalar) - Brightness multiplier

**Usage:**
- Parent material for all UI elements
- Optimized for UI rendering (no lighting calculations)
- Supports color tinting and texture overlays

### M_UI_Button

**Parent:** M_UI_Base

**Additional Parameters:**
- `NormalColor` (Vector3) - Default state color
- `HoveredColor` (Vector3) - Hover state color
- `PressedColor` (Vector3) - Pressed state color
- `DisabledColor` (Vector3) - Disabled state color
- `BorderThickness` (Scalar) - Border width for focus indicator
- `BorderColor` (Vector3) - Border color

**Usage:**
- Used for all button widgets
- Supports state-based color changes
- Can be driven by widget parameters

### M_UI_Background

**Parent:** M_UI_Base

**Additional Parameters:**
- `GradientStart` (Vector3) - Top color for gradient
- `GradientEnd` (Vector3) - Bottom color for gradient
- `BackgroundTexture` (Texture2D) - Optional background image
- `Vignette` (Scalar) - Edge darkening strength

**Usage:**
- Background overlays for menus
- Can blend solid colors, gradients, and textures

## Material Instance Creation

1. Right-click on base material (e.g., M_UI_Button)
2. Create Material Instance
3. Name following convention: `MI_UI_[Description]`
4. Set parameter values for specific use case
5. Save

**Example - Creating Primary Button:**
1. Create instance from M_UI_Button → MI_UI_Button_Primary
2. Set NormalColor = (0.2, 0.4, 0.8) - Blue
3. Set HoveredColor = (0.3, 0.5, 0.9) - Lighter blue
4. Set PressedColor = (0.1, 0.3, 0.7) - Darker blue
5. Set DisabledColor = (0.3, 0.3, 0.3) - Gray

## Best Practices

- Keep materials simple (UI doesn't need complex shading)
- Use Material Instances for variations (don't duplicate materials)
- Parameterize colors, sizes, and textures for flexibility
- Test materials on different background colors
- Ensure readability at all supported resolutions

## Performance Notes

- UI materials are rendered in a separate pass
- Use Unlit shading model (no lighting calculations needed)
- Avoid expensive operations (avoid world position, complex math)
- Material instances are cheap - use them liberally
- Test performance with many instances visible (e.g., long settings list)

## Integration with UMG

Materials can be assigned to UMG widgets in multiple ways:

1. **Image Widget:** Set Brush → Image → Material
2. **Border Widget:** Set Brush → Material
3. **Button Widget:** Set Style → Normal/Hovered/Pressed → Material

Use Material Parameter Collections for global UI theming if needed.
