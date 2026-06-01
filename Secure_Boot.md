# Secure Boot

## Table of Contents

* Introduction
* What is Secure Boot?
* Why Secure Boot is Needed
* How Secure Boot Works
* Boot Chain of Trust
* Secure Boot in Embedded Linux
* Secure Boot in Yocto
* Components Involved
* Secure Boot Flow
* Implementation Approaches
* Advantages
* Disadvantages
* Real-World Use Cases
* Best Practices
* Interview Questions
* Conclusion

---

# Introduction

Security is one of the most important requirements in modern embedded systems. Devices deployed in automotive, industrial, medical, networking, and IoT environments must ensure that only trusted software is executed during startup.

**Secure Boot** is a security mechanism that verifies the authenticity and integrity of software before it is executed. It prevents unauthorized, modified, or malicious firmware and operating systems from running on a device.

In Yocto-based embedded Linux systems, Secure Boot is implemented using hardware-supported cryptographic verification mechanisms provided by the processor or platform.

---

# What is Secure Boot?

Secure Boot is a process that verifies each stage of the boot sequence using digital signatures.

Before executing a component, the system verifies that it was signed by a trusted key.

If verification fails:

* Boot process stops
* System enters recovery mode
* Alternative boot image may be loaded

Only trusted software is allowed to execute.

---

# Why Secure Boot is Needed

Without Secure Boot:

* Attackers can replace firmware
* Malicious kernels can be loaded
* Rootkits can be installed
* Device integrity cannot be guaranteed

Secure Boot helps protect against:

* Firmware tampering
* Unauthorized modifications
* Malware installation
* Supply chain attacks
* Physical access attacks

---

# How Secure Boot Works

Secure Boot uses cryptographic signatures.

A software image is:

1. Built
2. Signed using a private key
3. Stored in device memory

During boot:

1. Signature is verified
2. Public key is checked
3. Image integrity is validated
4. Image is executed only if verification succeeds

---

# Boot Chain of Trust

Secure Boot establishes a chain of trust.

```text
Hardware Root of Trust
          ↓
ROM Bootloader
          ↓
First Stage Bootloader
          ↓
Second Stage Bootloader
          ↓
Linux Kernel
          ↓
Device Tree
          ↓
Root Filesystem
```

Each stage verifies the next stage before execution.

If one stage fails verification, boot stops.

---

# Secure Boot in Embedded Linux

Typical verification targets include:

## Bootloader

Examples:

* U-Boot
* TF-A (Trusted Firmware-A)

## Linux Kernel

Kernel image authenticity is verified.

## Device Tree

Ensures hardware configuration has not been modified.

## Initramfs

Verifies early userspace components.

## Root Filesystem

Protects system software from tampering.

---

# Secure Boot in Yocto

Yocto itself does not provide Secure Boot hardware support.

Instead, Yocto is used to:

* Build bootloaders
* Build signed kernel images
* Build signed FIT images
* Generate certificates
* Package signed binaries

The actual verification is performed by:

* Processor ROM code
* Hardware security engines
* Trusted firmware
* Secure boot-capable bootloaders

---

# Components Involved

## Hardware Root of Trust (RoT)

The first trusted component.

Examples:

* eFuse keys
* OTP memory
* Secure Elements

---

## Boot ROM

Embedded in the processor.

Responsibilities:

* Load first-stage bootloader
* Verify digital signature

---

## U-Boot

Most common embedded Linux bootloader.

Supports:

* FIT image verification
* RSA signatures
* Verified boot

---

## Trusted Firmware-A (TF-A)

Provides secure world initialization and secure boot support.

---

## Linux Kernel

Signed and verified before execution.

---

# Secure Boot Flow

```text
Power On
    ↓
Boot ROM
    ↓
Verify Bootloader Signature
    ↓
Load Bootloader
    ↓
Verify Kernel Signature
    ↓
Load Kernel
    ↓
Verify Device Tree
    ↓
Mount Root Filesystem
    ↓
System Boot Complete
```

---

# Implementation Approaches

## U-Boot Verified Boot

U-Boot verifies:

* Kernel
* Device Tree
* Initramfs

before booting Linux.

Commonly used in Yocto projects.

---

## FIT Image Signing

FIT (Flattened Image Tree) bundles:

* Kernel
* Device Tree
* Initramfs

into a single signed image.

Example:

```text
fitImage
```

Advantages:

* Single image verification
* Easier deployment
* Strong integrity protection

---

## Trusted Firmware-A Secure Boot

TF-A validates images before passing control to U-Boot.

Common in:

* NXP
* STM32MP
* Rockchip
* ARM platforms

---

# Yocto Integration Example

Enable signed FIT image generation:

```conf
KERNEL_CLASSES += " kernel-fitimage "
```

Enable signing:

```conf
UBOOT_SIGN_ENABLE = "1"
```

Specify key:

```conf
UBOOT_SIGN_KEYDIR = "/keys"
```

Specify key name:

```conf
UBOOT_SIGN_KEYNAME = "dev"
```

Generate signed image:

```bash
bitbake core-image-minimal
```

Result:

```text
fitImage
```

contains signed kernel components.

---

# Advantages

## Improved Security

Prevents unauthorized software execution.

## Firmware Integrity

Detects modified images.

## Protection Against Malware

Stops malicious boot components.

## Chain of Trust

Maintains trust throughout boot sequence.

## Compliance Requirements

Required in many regulated industries.

## Device Protection

Prevents installation of unofficial firmware.

---

# Disadvantages

## Increased Complexity

Additional signing and verification steps.

## Key Management Challenges

Private keys must be protected securely.

## Recovery Complexity

Failed signatures can prevent booting.

## Development Overhead

Testing and maintenance become more complex.

## Hardware Dependency

Requires processor support for secure boot features.

---

# Real-World Use Cases

## Automotive Systems

* ECU security
* Vehicle gateways
* ADAS platforms

## Industrial Automation

* PLC controllers
* Factory gateways

## Medical Devices

* Patient monitoring systems
* Diagnostic equipment

## Consumer Electronics

* Smart TVs
* Set-top boxes

## IoT Devices

* Smart meters
* Home automation gateways

## Networking Equipment

* Routers
* Firewalls
* Switches

---

# Best Practices

* Protect private signing keys
* Use hardware root of trust
* Sign all boot components
* Enable FIT image verification
* Use secure key storage
* Rotate signing keys when required
* Verify secure boot status during production testing
* Implement recovery mechanisms

---

# Interview Questions

### What is Secure Boot?

Secure Boot is a mechanism that verifies software signatures before execution, ensuring that only trusted software runs on a device.

---

### What is the Chain of Trust?

A security model where each boot stage verifies the next stage before execution.

---

### What is the Root of Trust?

The first trusted component in the boot process, usually implemented in hardware.

---

### What is FIT Image Signing?

A mechanism in U-Boot that digitally signs kernel, device tree, and initramfs images for verification during boot.

---

### Does Yocto provide Secure Boot?

Yocto does not implement Secure Boot itself. It provides tools and recipes to build and sign images, while hardware and bootloaders perform verification.

---

### What is Verified Boot?

A boot process where every component is cryptographically verified before execution.

---

# Conclusion

Secure Boot is a critical security feature in embedded Linux systems that ensures only trusted software is executed during startup. In Yocto projects, Secure Boot is commonly implemented using hardware root of trust, signed bootloaders, U-Boot verified boot, FIT image signing, and Trusted Firmware-A. By establishing a chain of trust from hardware to the operating system, Secure Boot protects devices against firmware tampering, malware, and unauthorized modifications.

### Short Interview Answer

**Secure Boot** is a security mechanism that ensures only authenticated and digitally signed software is executed during the boot process. In Yocto-based systems, Secure Boot is typically implemented using hardware root of trust, signed bootloaders, U-Boot verified boot, and FIT image signing to establish a chain of trust from power-on to Linux startup.
