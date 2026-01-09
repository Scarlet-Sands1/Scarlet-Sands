# UI Widgets

This directory contains UMG widget blueprints for the Title Screen menu system.

## Required Widgets

Create these UMG widget blueprints in the Unreal Editor:

### WBP_TitleRoot
- **Parent Class**: MenuWidgetBase
- **Description**: Root widget for title screen, contains title logo and "Press Any Key" prompt
- **Screen Type**: TitleRoot
- **Required Elements**:
  - Title logo image
  - "Press Any Key to Continue" text that fades in/out
  - Background overlay

### WBP_MainMenu
- **Parent Class**: MainMenuWidget (C++)
- **Description**: Main menu with game options
- **Screen Type**: MainMenu
- **Required Widgets** (must use BindWidget names):
  - `NewGameButton` (Button) - Starts new game or shows overwrite confirmation
  - `ContinueButton` (Button) - Loads existing save (enabled only if save exists)
  - `SettingsButton` (Button) - Opens settings menu
  - `CreditsButton` (Button) - Opens credits screen
  - `QuitButton` (Button) - Shows quit confirmation dialog
- **Layout**: Vertical list, centered on screen

### WBP_Settings
- **Parent Class**: SettingsWidget (C++)
- **Description**: Settings screen for audio, graphics, and controls
- **Screen Type**: Settings
- **Required Widgets** (must use BindWidget names):
  - Audio Section:
    - `MasterVolumeSlider` (Slider, 0-1)
    - `MusicVolumeSlider` (Slider, 0-1)
    - `SFXVolumeSlider` (Slider, 0-1)
  - Controls Section:
    - `MouseSensitivitySlider` (Slider, 0-2)
    - `InvertYCheckBox` (CheckBox)
  - Buttons:
    - `ApplyButton` (Button) - Applies and saves settings
    - `BackButton` (Button) - Returns to previous menu
- **Layout**: Tabbed or sectioned layout with labeled sliders

### WBP_Credits
- **Parent Class**: CreditsWidget (C++)
- **Description**: Credits screen displaying game credits
- **Screen Type**: Credits
- **Required Widgets** (must use BindWidget names):
  - `CreditsText` (TextBlock) - Displays scrolling credits
  - `BackButton` (Button) - Returns to main menu
- **Layout**: Centered text with back button at bottom

### WBP_ConfirmDialog
- **Parent Class**: ConfirmDialogWidget (C++)
- **Description**: Modal confirmation dialog for Yes/No choices
- **Screen Type**: ConfirmDialog
- **Required Widgets** (must use BindWidget names):
  - `TitleText` (TextBlock) - Dialog title
  - `MessageText` (TextBlock) - Dialog message
  - `ConfirmButton` (Button) - Confirms action (labeled "Yes" or "Confirm")
  - `CancelButton` (Button) - Cancels action (labeled "No" or "Cancel")
- **Layout**: Centered modal overlay with semi-transparent background

## Notes

- All widgets should support keyboard/gamepad navigation
- Use consistent styling (fonts, colors, button styles)
- Implement hover states for buttons
- Hook up UI sound events (hover, select, back) to C++ parent class methods
