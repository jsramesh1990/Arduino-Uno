# Recipes in Yocto / BitBake

# Overview

Recipes are one of the MOST IMPORTANT concepts in:
- Yocto Project
- Poky
- BitBake
- OpenEmbedded

A recipe tells BitBake:
```text
how to build a software package
```

Recipes define:
- source code location
- dependencies
- build steps
- install rules
- packaging information

Recipes are the:
```text
fundamental build units
```

of Yocto.

Without recipes:
```text
BitBake cannot build software
```

---

# 1. What is a Recipe?

A recipe is:
```text
a metadata file
```

that describes:
```text
how to build a package
```

---

# 2. Recipe File Extension

Recipes use:
```text
.bb
```

extension.

---

# 3. Example Recipe

```bitbake
DESCRIPTION = "Hello Application"

LICENSE = "MIT"

SRC_URI = "file://hello.c"
``` id="recipe1"

---

# 4. Main Purpose of Recipes

Recipes define:
- where source code comes from
- how to compile it
- how to install it
- dependencies

---

# 5. High-Level Recipe Architecture

```text
+----------------------+
| Recipe (.bb)         |
+----------------------+
           ↓
+----------------------+
| BitBake              |
+----------------------+
           ↓
+----------------------+
| Build Tasks          |
+----------------------+
           ↓
+----------------------+
| Cross Compilation    |
+----------------------+
           ↓
+----------------------+
| Package/Image        |
+----------------------+
``` id="arch1"

---

# 6. Recipe Responsibilities

Recipes define:
- source retrieval
- patching
- compilation
- installation
- packaging

---

# 7. Recipe Workflow

```text
Recipe Parsed
      ↓
Dependencies Resolved
      ↓
Tasks Generated
      ↓
Compilation
      ↓
Packaging
``` id="flow1"

---

# 8. Recipe Location

Recipes stored inside:
```text
layers
```

---

# 9. Typical Recipe Path

```text
meta-custom/recipes-apps/myapp/myapp.bb
``` id="path1"

---

# 10. Recipe Naming Convention

```text
<package-name>_<version>.bb
```

Example:
```text
bash_5.1.bb
```

---

# 11. Recipe Components

| Component | Purpose |
|-----------|---------|
| Variables | Metadata |
| Tasks | Build operations |
| Functions | Custom logic |

---

# 12. Important Recipe Variables

| Variable | Purpose |
|----------|---------|
| DESCRIPTION | Package description |
| LICENSE | License type |
| SRC_URI | Source location |
| DEPENDS | Build dependencies |
| RDEPENDS | Runtime dependencies |

---

# 13. DESCRIPTION Variable

```bitbake
DESCRIPTION = "Simple Hello Program"
``` id="desc1"

---

# 14. LICENSE Variable

```bitbake
LICENSE = "GPLv2"
``` id="lic1"

---

# 15. Why LICENSE is Important

Yocto tracks:
```text
license compliance
```

---

# 16. SRC_URI Variable

Defines:
```text
where source code comes from
```

---

# 17. Local Source Example

```bitbake
SRC_URI = "file://hello.c"
``` id="src1"

---

# 18. Git Source Example

```bitbake
SRC_URI = "git://github.com/app/project.git"
``` id="src2"

---

# 19. HTTP Download Example

```bitbake
SRC_URI = "https://example.com/app.tar.gz"
``` id="src3"

---

# 20. DEPENDS Variable

Defines:
```text
build-time dependencies
```

---

# 21. DEPENDS Example

```bitbake
DEPENDS = "openssl zlib"
``` id="dep1"

---

# 22. RDEPENDS Variable

Defines:
```text
runtime dependencies
```

---

# 23. RDEPENDS Example

```bitbake
RDEPENDS:${PN} = "bash"
``` id="dep2"

---

# 24. Package Name Variable

```bitbake
PN
```

means:
```text
package name
```

---

# 25. Package Version Variable

```bitbake
PV
```

means:
```text
package version
```

---

# 26. Recipe Tasks

Recipes generate:
```text
tasks
```

---

# 27. Common Tasks

| Task | Purpose |
|------|---------|
| do_fetch | Download source |
| do_unpack | Extract source |
| do_patch | Apply patches |
| do_configure | Configure build |
| do_compile | Compile |
| do_install | Install |
| do_package | Package files |

---

# 28. Task Execution Flow

```text
do_fetch
    ↓
do_unpack
    ↓
do_patch
    ↓
do_configure
    ↓
do_compile
    ↓
do_install
    ↓
do_package
``` id="task1"

---

# 29. do_fetch Task

Downloads:
- source archives
- git repos
- patches

---

# 30. do_unpack Task

Extracts:
```text
downloaded source code
```

---

# 31. do_patch Task

Applies:
```text
patch files
```

---

# 32. do_compile Task

Compiles source using:
```text
cross compiler
```

---

# 33. do_install Task

Installs files into:
```text
temporary root filesystem
```

---

# 34. Example do_compile

```bitbake
do_compile() {
    make
}
``` id="compile1"

---

# 35. Example do_install

```bitbake
do_install() {
    install -d ${D}/usr/bin
    install -m 0755 hello ${D}/usr/bin
}
``` id="install1"

---

# 36. Cross Compilation

Recipes automatically use:
```text
target cross compiler
```

---

# 37. Cross Compilation Flow

```text
Host PC
    ↓
ARM Cross Compiler
    ↓
ARM Binary
``` id="cross1"

---

# 38. Recipe Classes

Recipes may inherit:
```text
.bbclass files
```

---

# 39. inherit Keyword

```bitbake
inherit cmake
``` id="class1"

---

# 40. Common Classes

| Class | Purpose |
|-------|----------|
| autotools | GNU autotools |
| cmake | CMake |
| kernel | Kernel build |

---

# 41. Recipe Parsing

BitBake parses recipes during:
```text
build startup
```

---

# 42. Recipe Dependency Graph

BitBake creates:
```text
Directed Acyclic Graph (DAG)
```

from recipes.

---

# 43. DAG Example

```text
Application
     ↓
Library
     ↓
Compiler
``` id="dag1"

---

# 44. Recipe Build Directory

Temporary build area:

```text
WORKDIR
```

---

# 45. WORKDIR Example

```bitbake
${WORKDIR}
``` id="work1"

---

# 46. Install Directory Variable

```bitbake
${D}
```

means:
```text
destination install directory
```

---

# 47. Recipe Overrides

Overrides customize:
- architecture
- machine
- distro

---

# 48. Override Example

```bitbake
SRC_URI:append = " file://fix.patch"
``` id="ovr1"

---

# 49. bbappend Files

Used to:
```text
modify existing recipes
```

---

# 50. bbappend Example

```text
busybox.bbappend
```

---

# 51. Why bbappend is Important

Allows:
- customization
- patches
- additional dependencies

without editing original recipe.

---

# 52. Recipe Output

Recipes generate:
- binaries
- libraries
- packages

---

# 53. Package Formats

Supported:
- rpm
- deb
- ipk

---

# 54. Image Recipes

Images themselves are:
```text
recipes
```

---

# 55. Image Recipe Example

```bitbake
IMAGE_INSTALL += "bash"
``` id="img1"

---

# 56. Recipe and Layers Relationship

```text
Layer
   ↓
Contains Recipes
   ↓
BitBake Parses Recipes
``` id="rel1"

---

# 57. Recipe Debugging

---

## Verbose Build

```bash
bitbake -v myapp
``` id="dbg1"

---

## View Environment

```bash
bitbake -e myapp
``` id="dbg2"

---

## Clean Recipe

```bash
bitbake -c clean myapp
``` id="dbg3"

---

# 58. Common Recipe Problems

| Problem | Description |
|---------|-------------|
| Missing dependency | Build fails |
| Wrong SRC_URI | Source download fails |
| Incorrect install path | Missing files |
| Syntax errors | Parse failure |

---

# 59. Recipe Build Flow

```text
Recipe Parsed
       ↓
Dependencies Resolved
       ↓
Sources Downloaded
       ↓
Cross Compilation
       ↓
Files Installed
       ↓
Packages Generated
``` id="flow2"

---

# 60. Real Embedded Linux Example

```text
busybox.bb
      ↓
BitBake Parses Recipe
      ↓
BusyBox Downloaded
      ↓
Cross Compiled
      ↓
Installed into RootFS
``` id="real1"

---

# 61. Recipe Advantages

| Advantage | Description |
|-----------|-------------|
| Modular | Yes |
| Reusable | Yes |
| Automated builds | Yes |
| Dependency handling | Yes |

---

# 62. Recipes vs Makefiles

| Recipe | Makefile |
|--------|-----------|
| High-level metadata | Build commands |
| Dependency aware | Local build only |
| Cross compilation integrated | Manual |

---

# 63. Recipes vs Layers

| Recipes | Layers |
|---------|---------|
| Individual build instructions | Collections of metadata |

---

# 64. Complete Recipe Workflow

```text
Developer Writes Recipe
         ↓
Recipe Added to Layer
         ↓
BitBake Parses Recipe
         ↓
Dependencies Calculated
         ↓
Tasks Executed
         ↓
Cross Compilation
         ↓
Package Generated
         ↓
Image Created
``` id="final1"

---

# 65. Final Core Concept

```text
Recipe =
Build Instruction File
for BitBake
```

---

# 66. Summary

- Recipes describe how software is built in Yocto
- Stored as .bb files
- Define source locations and dependencies
- Generate tasks for BitBake
- Support cross-compilation
- Organized inside layers
- Fundamental unit of Yocto builds

---


````
