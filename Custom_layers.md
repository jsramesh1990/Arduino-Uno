# Custom Layers in Yocto 

# Overview

A **Custom Layer** is a user-created Yocto layer used to store:

- Custom recipes (`.bb`)
- Recipe extensions (`.bbappend`)
- Machine configurations
- BSP modifications
- Distribution configurations
- Kernel patches
- Device Tree changes
- Company-specific metadata

Custom layers are the recommended way to add project-specific functionality without modifying upstream layers.

---

# 1. What is a Layer?

A layer is a logical collection of:

```text
Recipes
Configurations
Metadata
Classes
Patches
```

used by BitBake during builds.

---

# 2. Why Custom Layers?

Suppose your project needs:

```text
Custom application
Custom kernel patch
Custom device tree
Custom image
```

Modifying:

```text
meta
meta-poky
meta-openembedded
```

directly is NOT recommended.

Instead:

```text
Create a custom layer
```

---

# 3. Benefits of Custom Layers

### Separation

```text
Project code separated
from vendor code
```

---

### Easier Updates

Vendor layers can be updated safely.

---

### Reusability

Same layer can be reused across projects.

---

### Maintainability

Cleaner project structure.

---

# 4. High-Level Architecture

```text
+----------------------+
| meta-company         |
+----------------------+
| Custom Recipes       |
| Custom BSP           |
| Custom Kernel Patch  |
| Custom Images        |
+----------------------+

          ↑

+----------------------+
| meta-vendor          |
+----------------------+

          ↑

+----------------------+
| meta-openembedded    |
+----------------------+

          ↑

+----------------------+
| meta-poky            |
+----------------------+
```

---

# 5. Typical Layer Naming

Common naming pattern:

```text
meta-<name>
```

Examples:

```text
meta-company
meta-product
meta-custom
meta-board
meta-industrial
```

---

# 6. Layer Creation

Yocto provides:

```bash
bitbake-layers create-layer meta-company
```

---

# 7. Generated Structure

```text
meta-company/
├── conf
│   └── layer.conf
├── COPYING.MIT
├── README
└── recipes-example
```

---

# 8. Layer Directory Layout

```text
meta-company/
│
├── conf/
│   └── layer.conf
│
├── recipes-apps/
│
├── recipes-core/
│
├── recipes-kernel/
│
├── recipes-bsp/
│
└── classes/
```

---

# 9. Core Layer File

```text
conf/layer.conf
```

This file registers the layer with BitBake.

---

# 10. layer.conf Example

```bitbake
BBPATH .= ":${LAYERDIR}"

BBFILES += "${LAYERDIR}/recipes-*/*/*.bb \
            ${LAYERDIR}/recipes-*/*/*.bbappend"
```

---

# 11. Layer Registration Variables

Important variables:

```bitbake
BBPATH
BBFILES
BBFILE_COLLECTIONS
BBFILE_PATTERN
BBFILE_PRIORITY
```

---

# 12. BBFILE_COLLECTIONS

Defines layer name.

```bitbake
BBFILE_COLLECTIONS += "company"
```

---

# 13. BBFILE_PATTERN

Recipe search path.

```bitbake
BBFILE_PATTERN_company := "^${LAYERDIR}/"
```

---

# 14. BBFILE_PRIORITY

Layer priority.

```bitbake
BBFILE_PRIORITY_company = "100"
```

---

# 15. Complete layer.conf Example

```bitbake
BBPATH .= ":${LAYERDIR}"

BBFILES += "${LAYERDIR}/recipes-*/*/*.bb \
            ${LAYERDIR}/recipes-*/*/*.bbappend"

BBFILE_COLLECTIONS += "company"

BBFILE_PATTERN_company := "^${LAYERDIR}/"

BBFILE_PRIORITY_company = "100"
```

---

# 16. Adding Layer to Build

Edit:

```text
conf/bblayers.conf
```

---

# 17. Example

```bitbake
BBLAYERS += "\
/home/user/meta-company \
"
```

---

# 18. Build Flow

```text
bblayers.conf
       ↓
Load Layer
       ↓
Read layer.conf
       ↓
Discover Recipes
       ↓
Build
```

---

# 19. Adding Custom Recipes

Example:

```text
meta-company/
└── recipes-apps/
    └── hello/
        └── hello_1.0.bb
```

---

# 20. Example Recipe

```bitbake
DESCRIPTION = "Hello World"

LICENSE = "MIT"

SRC_URI = "file://hello.c"
```

---

# 21. Recipe Directory Structure

```text
hello/
├── hello_1.0.bb
└── files/
    └── hello.c
```

---

# 22. Build Custom Recipe

```bash
bitbake hello
```

---

# 23. Adding bbappend Files

Custom layers commonly contain:

```text
.bbappend
```

files.

---

# 24. Example

```text
busybox_%.bbappend
```

---

# 25. Purpose

Modify upstream recipe without editing it.

---

# 26. Example Directory

```text
recipes-core/
└── busybox/
    ├── busybox_%.bbappend
    └── files/
        └── fix.patch
```

---

# 27. Patch Flow

```text
Vendor Recipe
      ↓
bbappend
      ↓
Patch Applied
      ↓
Build
```

---

# 28. Custom Kernel Layer

Structure:

```text
recipes-kernel/
└── linux/
```

---

# 29. Kernel Patch Example

```text
linux-yocto_%.bbappend
```

---

# 30. Add Kernel Patch

```bitbake
SRC_URI += "file://my_patch.patch"
```

---

# 31. Device Tree Customization

Example:

```text
recipes-kernel/
└── linux/
```

Add:

```text
board.dts
```

---

# 32. Custom Machine Layer

Directory:

```text
conf/machine/
```

---

# 33. Machine Configuration Example

```text
conf/machine/myboard.conf
```

---

# 34. Example Machine Config

```bitbake
MACHINEOVERRIDES =. "myboard:"
```

---

# 35. BSP Layer

Contains:

```text
Bootloader
Kernel
Device Tree
Drivers
```

---

# 36. BSP Architecture

```text
meta-board
      ↓
Machine Config
      ↓
Kernel Config
      ↓
Device Tree
```

---

# 37. Custom Distribution Layer

Directory:

```text
conf/distro/
```

---

# 38. Example

```text
mydistro.conf
```

---

# 39. Distro Configuration

Controls:

```text
Package manager
Init system
Features
```

---

# 40. Custom Image Recipes

Directory:

```text
recipes-core/images/
```

---

# 41. Example

```text
my-image.bb
```

---

# 42. Image Recipe Example

```bitbake
IMAGE_INSTALL += "\
busybox \
openssh \
"
```

---

# 43. Build Custom Image

```bash
bitbake my-image
```

---

# 44. Layer Dependency

Layers may depend on other layers.

---

# 45. Example

```bitbake
LAYERDEPENDS_company = "core"
```

---

# 46. Multiple Dependencies

```bitbake
LAYERDEPENDS_company = "core openembedded-layer"
```

---

# 47. Layer Compatibility

Specify Yocto release support.

---

Example:

```bitbake
LAYERSERIES_COMPAT_company = "kirkstone mickledore nanbield"
```

---

# 48. View Layers

Command:

```bash
bitbake-layers show-layers
```

---

# 49. Example Output

```text
layer                priority

meta                    5
meta-poky               5
meta-openembedded       6
meta-company          100
```

---

# 50. Show Recipes

```bash
bitbake-layers show-recipes
```

---

# 51. Show Appends

```bash
bitbake-layers show-appends
```

---

# 52. Common Custom Layer Layout

```text
meta-company/
│
├── conf/
│   ├── layer.conf
│   ├── machine/
│   └── distro/
│
├── recipes-apps/
│
├── recipes-core/
│
├── recipes-kernel/
│
├── recipes-bsp/
│
├── classes/
│
└── files/
```

---

# 53. Real Embedded Linux Example

Company creates:

```text
meta-industrial
```

Containing:

```text
Custom App
Custom Kernel
Custom DTS
Custom Image
Custom BSP
```

---

# 54. Build Flow Example

```text
Custom Layer
      ↓
Recipes
      ↓
BitBake Parses
      ↓
Dependencies Resolved
      ↓
Build
      ↓
Image Generated
```

---

# 55. Best Practices

### Never Modify Vendor Layers

Bad:

```text
meta-ti
meta-nxp
meta-poky
```

---

### Use bbappend

Good:

```text
busybox.bbappend
```

---

### Keep Product Code Separate

Use:

```text
meta-product
```

---

### Set Proper Priority

```bitbake
BBFILE_PRIORITY_product = "100"
```

---

# 56. Common Mistakes

### Forgetting bblayers.conf

Layer not loaded.

---

### Missing layer.conf

BitBake cannot recognize layer.

---

### Wrong BBFILES Path

Recipes not discovered.

---

### Incorrect Priority

Wrong recipe selected.

---

# 57. Interview Questions

### Q1

Why create a custom layer?

Answer:

```text
To keep project-specific metadata
separate from vendor and upstream layers.
```

---

### Q2

How do you create a layer?

Answer:

```bash
bitbake-layers create-layer meta-company
```

---

### Q3

Which file defines layer configuration?

Answer:

```text
conf/layer.conf
```

---

### Q4

How is a layer added to the build?

Answer:

```text
bblayers.conf
```

---

# 58. Complete Layer Processing Flow

```text
Create Layer
      ↓
Configure layer.conf
      ↓
Add Recipes
      ↓
Add Layer to bblayers.conf
      ↓
BitBake Loads Layer
      ↓
Parses Metadata
      ↓
Builds Packages
```

---

# 59. Final Core Concept

```text
Custom Layer

=
Project-Specific Metadata Container

Used to store:

Recipes
Patches
Images
BSPs
Kernel Changes
Configurations

without modifying upstream layers.
```

---

# 60. Summary

- Custom layers isolate project-specific Yocto metadata
- Created using `bitbake-layers create-layer`
- Registered through `layer.conf`
- Added to builds via `bblayers.conf`
- Can contain recipes, patches, images, BSPs, and machine configurations
- Essential for maintainable commercial Yocto development
- Recommended way to customize Embedded Linux systems

---
