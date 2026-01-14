# Scarlet Sands - Asset Naming Conventions

**Status:** LOCKED - NO EXCEPTIONS
**Scope:** All Content Browser assets for Scarlet Sands
**Enforcement:** Mandatory for Title Screen v1 and all future work

---

## Table of Contents

1. [General Rules](#general-rules)
2. [UMG Widgets](#umg-widgets)
3. [C++ Classes](#c-classes)
4. [Textures](#textures)
5. [Materials](#materials)
6. [Audio Assets](#audio-assets)
7. [Levels](#levels)
8. [Blueprints](#blueprints)
9. [Quick Reference](#quick-reference)

---

## General Rules

### Prefix System

All assets MUST use the following prefix system:

| Asset Type | Prefix | Example |
|-----------|--------|---------|
| Widget Blueprint | `WBP_` | `WBP_MainMenu` |
| C++ Class | `U` / `A` / `F` | `UMainMenuWidget`, `APlayerController` |
| Texture | `T_` | `T_UI_Logo_ScarletSands` |
| Material | `M_` | `M_UI_Button` |
| Material Instance | `MI_` | `MI_UI_Button_Primary` |
| Sound Wave | `SFX_` / `MUS_` | `SFX_UI_Hover`, `MUS_Title_Loop` |
| Sound Class | `SC_` | `SC_Master`, `SC_Music` |
| Sound Mix | `SMX_` | `SMX_UI` |
| Level | `L_` | `L_TitleBackdrop` |
| Blueprint (Actor) | `BP_` | `BP_TitleScreenGameMode` |
| Blueprint (Object) | `BP_` | `BP_MenuSettings` |

### Naming Structure

**Pattern:** `[Prefix]_[Category]_[Description]_[Variant]`

- **Prefix:** Asset type identifier (required)
- **Category:** Broad classification (required for UI/Audio)
- **Description:** Specific name (required)
- **Variant:** Optional suffix for variations (e.g., Normal, Hovered, Disabled)

**Examples:**
- `T_UI_Background_MainMenu` - Main menu background texture
- `MI_UI_Button_Primary_Hovered` - Primary button hovered state material instance
- `SFX_UI_Select` - UI select sound effect

### Case Convention

- **Pascal Case:** All asset names use PascalCase (each word capitalized, no spaces)
- **Underscores:** Separate prefix, category, description, and variant
- **No Spaces:** Never use spaces in asset names
- **No Special Characters:** Only alphanumeric and underscores

**Good:**
- `WBP_MainMenu`
- `T_UI_Logo_ScarletSands`
- `M_UI_Button_Primary`

**Bad:**
- `main menu widget` (spaces, lowercase)
- `WBP_MainMenu-v2` (hyphen, version suffix)
- `texture_ui_logo` (lowercase, no prefix)

---

## UMG Widgets

### Prefix: `WBP_`

Widget Blueprints for all UI elements.

### Required Widgets (Title Screen v1)

| Widget Name | Purpose |
|------------|---------|
| `WBP_TitleRoot` | Root widget hosting screen stack |
| `WBP_MainMenu` | Main menu with button list |
| `WBP_Settings` | Settings screen (audio/graphics/controls) |
| `WBP_Credits` | Credits screen with scrollable text |
| `WBP_ConfirmDialog` | Reusable confirmation dialog |

### Naming Rules

- **MUST start with `WBP_`**
- Use descriptive name indicating widget purpose
- No version numbers (use source control)
- No "Widget" suffix (redundant with prefix)

**Examples:**
- `WBP_MainMenu` ✓
- `WBP_SettingsPanel` ✓
- `WBP_ButtonStyle_Primary` ✓ (reusable button style widget)

**Invalid:**
- `MainMenuWidget` ✗ (no prefix)
- `WBP_Menu` ✗ (too vague)
- `WBP_MainMenu_v2` ✗ (no version suffix)

---

## C++ Classes

### Prefix: Based on Unreal conventions

- `U` prefix for UObject-derived classes
- `A` prefix for AActor-derived classes
- `F` prefix for structs
- `E` prefix for enums
- `I` prefix for interfaces

### Required Classes (Title Screen v1)

| Class Name | Type | Purpose |
|-----------|------|---------|
| `UScarletSandsGameInstance` | UGameInstance | Manages game state and save slots |
| `UMenuManagerSubsystem` | UGameInstanceSubsystem | Navigation stack and screen management |
| `UMenuWidgetBase` | UUserWidget | Base class for all menu widgets |
| `UMainMenuWidget` | UUserWidget | Main menu implementation |
| `USettingsWidget` | UUserWidget | Settings screen implementation |
| `UCreditsWidget` | UUserWidget | Credits screen implementation |
| `UConfirmDialogWidget` | UUserWidget | Confirmation dialog implementation |
| `ATitleScreenPlayerController` | APlayerController | Title screen player controller |
| `UScarletSandsSaveGame` | USaveGame | Main save game data |
| `UScarletSandsSettingsSaveGame` | USaveGame | Settings persistence |
| `UScarletSandsGameUserSettings` | UGameUserSettings | Graphics settings subclass |
| `EMenuScreen` | Enum | Menu screen enumeration |

### Naming Rules

- **Follow Unreal C++ conventions strictly**
- Prefix with `Scarlet Sands` for game-specific classes
- Use descriptive names that indicate purpose
- Inherit naming from parent class when applicable

**Examples:**
- `UScarletSandsGameInstance` ✓ (custom GameInstance)
- `UMenuManagerSubsystem` ✓ (subsystem for menu management)
- `ATitleScreenPlayerController` ✓ (custom PlayerController)

---

## Textures

### Prefix: `T_`

All 2D image assets.

### Naming Pattern

`T_[Category]_[Description]_[Variant]`

**Categories:**
- `UI` - User interface textures
- `Env` - Environment textures (future)
- `Char` - Character textures (future)
- `VFX` - Visual effects textures (future)

### Required Textures (Title Screen v1)

| Texture Name | Purpose |
|-------------|---------|
| `T_UI_Logo_ScarletSands` | Main game logo |
| `T_UI_Background_MainMenu` | Main menu background (optional) |
| `T_UI_Background_Settings` | Settings background (optional) |
| `T_UI_Background_Credits` | Credits background (optional) |

### Optional Textures

| Texture Name | Purpose |
|-------------|---------|
| `T_UI_Button_Normal` | Button normal state |
| `T_UI_Button_Hovered` | Button hovered state |
| `T_UI_Button_Pressed` | Button pressed state |
| `T_UI_Button_Disabled` | Button disabled state |
| `T_UI_Icon_Audio` | Audio settings icon |
| `T_UI_Icon_Graphics` | Graphics settings icon |
| `T_UI_Icon_Controls` | Controls settings icon |

### Naming Rules

- **MUST start with `T_`**
- Use category to group related textures
- Use descriptive names
- Add variant suffix for state variations

**Examples:**
- `T_UI_Logo_ScarletSands` ✓
- `T_UI_Button_Hovered` ✓
- `T_UI_Icon_Settings` ✓

**Invalid:**
- `logo_texture` ✗ (no prefix, lowercase)
- `T_Logo` ✗ (no category)
- `T_UI_Button_1` ✗ (numeric suffix instead of descriptive)

---

## Materials

### Prefix: `M_` (base materials), `MI_` (material instances)

All material assets for rendering.

### Naming Pattern

**Base Materials:** `M_[Category]_[Description]`
**Material Instances:** `MI_[Category]_[Description]_[Variant]`

**Categories:**
- `UI` - User interface materials
- `Env` - Environment materials (future)
- `Char` - Character materials (future)
- `VFX` - Visual effects materials (future)

### Required Materials (Title Screen v1)

| Material Name | Type | Purpose |
|--------------|------|---------|
| `M_UI_Base` | Material | Master UI material (unlit, translucent) |
| `M_UI_Button` | Material | Button material with state parameters |
| `M_UI_Background` | Material | Background material with gradient/texture |

### Required Material Instances

| Material Instance Name | Parent | Purpose |
|-----------------------|--------|---------|
| `MI_UI_Button_Primary` | M_UI_Button | Primary button style (blue) |
| `MI_UI_Button_Secondary` | M_UI_Button | Secondary button style (gray) |
| `MI_UI_Button_Danger` | M_UI_Button | Danger button style (red) |
| `MI_UI_Background_Dark` | M_UI_Background | Dark background overlay |

### Naming Rules

- **Base materials:** `M_` prefix
- **Material instances:** `MI_` prefix
- Use category for organization
- Variant suffix for different styles

**Examples:**
- `M_UI_Base` ✓ (master material)
- `MI_UI_Button_Primary` ✓ (instance with specific colors)
- `M_UI_Background` ✓ (background material)

**Invalid:**
- `ButtonMaterial` ✗ (no prefix)
- `M_Button` ✗ (no category)
- `MI_UI_Button_1` ✗ (numeric instead of descriptive)

---

## Audio Assets

### Sound Waves

**Prefix:** `SFX_` (sound effects), `MUS_` (music)

#### Naming Pattern

**SFX:** `SFX_[Category]_[Description]`
**Music:** `MUS_[Context]_[Description]`

#### SFX Categories

- `UI` - User interface sounds
- `Footstep` - Movement sounds (future)
- `Weapon` - Combat sounds (future)
- `Impact` - Collision sounds (future)
- `Ambient` - Environmental sounds (future)

#### Music Contexts

- `Title` - Title screen
- `MainMenu` - Main menu
- `Credits` - Credits screen
- `Combat` - Combat (future)
- `Exploration` - Exploration (future)

### Required Audio (Title Screen v1)

| Asset Name | Type | Purpose |
|-----------|------|---------|
| `SFX_UI_Hover` | SFX | Button hover sound |
| `SFX_UI_Select` | SFX | Button select sound |
| `SFX_UI_Back` | SFX | Back button sound |
| `MUS_Title_Loop` | Music | Title screen background music |

### Sound Classes

**Prefix:** `SC_`

| Sound Class Name | Parent | Purpose |
|-----------------|--------|---------|
| `SC_Master` | None | Root sound class |
| `SC_Music` | SC_Master | Music submix |
| `SC_SFX` | SC_Master | Sound effects submix |

### Sound Mix

**Prefix:** `SMX_`

| Sound Mix Name | Purpose |
|---------------|---------|
| `SMX_UI` | UI audio mix (optional) |

### Naming Rules

- **SFX prefix** for sound effects
- **MUS prefix** for music
- **SC prefix** for sound classes
- **SMX prefix** for sound mixes
- Use category to group related sounds

**Examples:**
- `SFX_UI_Hover` ✓
- `MUS_Title_Loop` ✓
- `SC_Master` ✓

**Invalid:**
- `hover_sound` ✗ (no prefix, lowercase)
- `SFX_Hover` ✗ (no category)
- `Music_Title` ✗ (wrong prefix)

---

## Levels

### Prefix: `L_`

All map/level assets.

### Naming Pattern

`L_[Name]_[Variant]`

### Required Levels (Title Screen v1)

| Level Name | Purpose |
|-----------|---------|
| `L_TitleBackdrop` | Title screen background environment |
| `L_World_Persistent` | Placeholder world map (minimal) |

### Future Levels (Examples)

| Level Name | Purpose |
|-----------|---------|
| `L_World_Streaming_01` | Streaming world chunk 1 |
| `L_Combat_Arena_Tutorial` | Tutorial combat arena |
| `L_Dungeon_FireTemple` | Fire Temple dungeon |

### Naming Rules

- **MUST start with `L_`**
- Use descriptive name indicating level purpose
- Use variant suffix for different versions/areas
- No version numbers

**Examples:**
- `L_TitleBackdrop` ✓
- `L_World_Persistent` ✓
- `L_Dungeon_FireTemple_Floor1` ✓

**Invalid:**
- `TitleLevel` ✗ (no prefix)
- `L_Level1` ✗ (non-descriptive)
- `L_TitleBackdrop_v2` ✗ (version suffix)

---

## Blueprints

### Prefix: `BP_`

Blueprint assets (not UMG widgets).

### Naming Pattern

`BP_[Type]_[Description]`

**Types:**
- `GameMode` - Game mode blueprints
- `PlayerController` - Player controller blueprints
- `Character` - Character blueprints
- `Actor` - Generic actor blueprints
- `Component` - Component blueprints

### Required Blueprints (Title Screen v1)

| Blueprint Name | Type | Purpose |
|---------------|------|---------|
| `BP_TitleScreenGameMode` | GameMode | Title screen game mode |

### Future Blueprints (Examples)

| Blueprint Name | Type | Purpose |
|---------------|------|---------|
| `BP_PlayerCharacter` | Character | Main player character |
| `BP_CombatController` | PlayerController | Combat player controller |
| `BP_HealthComponent` | Component | Health system component |

### Naming Rules

- **MUST start with `BP_`**
- Include type for clarity
- Use descriptive name

**Examples:**
- `BP_TitleScreenGameMode` ✓
- `BP_PlayerCharacter` ✓
- `BP_HealthComponent` ✓

**Invalid:**
- `TitleGameMode` ✗ (no prefix)
- `BP_GM_Title` ✗ (abbreviation instead of full type)
- `BP_Character1` ✗ (non-descriptive)

---

## Quick Reference

### Title Screen v1 - All Required Asset Names

#### UMG Widgets
- `WBP_TitleRoot`
- `WBP_MainMenu`
- `WBP_Settings`
- `WBP_Credits`
- `WBP_ConfirmDialog`

#### Textures
- `T_UI_Logo_ScarletSands`

#### Materials
- `M_UI_Base`
- `M_UI_Button`
- `M_UI_Background`
- `MI_UI_Button_Primary`
- `MI_UI_Button_Secondary`
- `MI_UI_Button_Danger`

#### Audio
- `SFX_UI_Hover`
- `SFX_UI_Select`
- `SFX_UI_Back`
- `MUS_Title_Loop`
- `SC_Master`
- `SC_Music`
- `SC_SFX`

#### Levels
- `L_TitleBackdrop`
- `L_World_Persistent`

#### Blueprints
- `BP_TitleScreenGameMode`

#### C++ Classes
- `UScarletSandsGameInstance`
- `UMenuManagerSubsystem`
- `UMenuWidgetBase`
- `UMainMenuWidget`
- `USettingsWidget`
- `UCreditsWidget`
- `UConfirmDialogWidget`
- `ATitleScreenPlayerController`
- `UScarletSandsSaveGame`
- `UScarletSandsSettingsSaveGame`
- `UScarletSandsGameUserSettings`

---

## Enforcement

### Build-Time Checks

No automated enforcement for Title Screen v1. Manual review required.

### Future Automation

Consider adding:
- Pre-commit hooks to validate asset names
- Unreal asset naming validator plugin
- Build script checks

### Manual Review

Before merging:
1. Verify all assets follow naming conventions
2. Check for typos and inconsistencies
3. Ensure prefixes are correct
4. Confirm categories match folder structure

---

## Exceptions

**NO EXCEPTIONS for Title Screen v1.**

Any deviations MUST be documented and approved before implementation.

---

## Version History

- **v1.0** (2026-01-10): Initial naming conventions for Title Screen v1
- Locked for Title Screen scope - no changes without approval

---

## Notes

- This document is the SINGLE SOURCE OF TRUTH for asset naming
- All team members MUST follow these conventions
- Consistency is critical for large projects
- When in doubt, ask before creating assets
- Use examples as templates for new assets

**Last Updated:** 2026-01-10
**Status:** LOCKED - NO EXCEPTIONS
