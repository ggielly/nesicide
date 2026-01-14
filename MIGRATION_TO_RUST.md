# Migration Guide: Converting nesicide to Rust

This document outlines the process for migrating the nesicide project from C++/Qt to Rust, starting with the build system and gradually replacing components.

## Phase 1: Migrate Build System to Cargo

### Step 1: Create Cargo.toml at project root

```toml
[package]
name = "nesicide"
version = "1.0.0"
edition = "2021"

[workspace]
members = [
    "nesicide-core",
    "nes-emulator",
    "famitracker-wrapper",
]

[dependencies]
# Will add Rust dependencies here later

[build-dependencies]
cc = "1.0"
pkg-config = "0.3"
```

### Step 2: Create nesicide-core sub-project

Create `nesicide-core/Cargo.toml`:
```toml
[package]
name = "nesicide-core"
version = "0.1.0"
edition = "2021"

[lib]
crate-type = ["cdylib"]  # Creates a dynamic library

[dependencies]

[build-dependencies]
cc = "1.0"
bindgen = "0.60"
```

### Step 3: Create build script for C++ compilation

Create `nesicide-core/build.rs`:
```rust
use std::env;
use std::path::PathBuf;

fn main() {
    // Compile C++ files
    cc::Build::new()
        .cpp(true)  // Enable C++ support
        .flag("-std=c++17")
        .flag("-I./apps/ide")  // Include paths
        .flag("-I./common")
        .flag("-I./libs/nes")
        .flag("-I./deps/qscintilla2/src")
        .flag("-I./deps/qhexedit2/src")
        .flag("-I./deps/rtmidi")
        .file("./apps/ide/mainwindow.cpp")
        .file("./apps/ide/main.cpp")
        .file("./common/cqtmfc.cpp")
        .file("./common/xmlhelpers.cpp")
        // Add all C++ files you want to compile
        .compile("nesicide_core_cpp");

    // Tell Cargo where to find libraries
    println!("cargo:rustc-link-search=native=/usr/lib/x86_64-linux-gnu");
    println!("cargo:rustc-link-lib=Qt5Core");
    println!("cargo:rustc-link-lib=Qt5Gui");
    println!("cargo:rustc-link-lib=Qt5Widgets");
    println!("cargo:rustc-link-lib=SDL");
    // Add all libraries you need
}
```

### Step 4: Create Rust entry point

Create `nesicide-core/src/lib.rs`:
```rust
// Initially just an entry point for C++
// You can expose Rust functions later

#[no_mangle]
pub extern "C" fn nesicide_init() -> i32 {
    // Initialization of the project
    0  // Success
}

#[no_mangle]
pub extern "C" fn nesicide_run() -> i32 {
    // Call existing C++ code
    // For now, you can call main() from C++ via FFI
    0
}
```

### Step 5: Modify existing C++ code for FFI

In `apps/ide/main.cpp`, create an exported function:
```cpp
#ifdef __cplusplus
extern "C" {
#endif

int run_nesicide_app(int argc, char *argv[]);

#ifdef __cplusplus
}
#endif

int run_nesicide_app(int argc, char *argv[]) {
    // The existing content of your main() function
    QApplication nesicideApplication(argc, argv);
    // ... rest of your code
    return nesicideApplication.exec();
}
```

### Step 6: Create main Rust executable

Create `src/main.rs`:
```rust
use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    
    // Convert args to C format for passing to C++ function
    let c_args: Vec<std::ffi::CString> = args
        .iter()
        .map(|arg| std::ffi::CString::new(arg.as_str()).unwrap())
        .collect();
    
    let argc = c_args.len() as i32;
    let mut c_argv: Vec<*const i8> = c_args
        .iter()
        .map(|arg| arg.as_ptr())
        .collect();
    c_argv.push(std::ptr::null());
    
    // Call the existing C++ function
    unsafe {
        let result = nesicide_core::run_nesicide_app_from_rust(argc, c_argv.as_ptr());
        std::process::exit(result);
    }
}
```

## Phase 2: Install Rust and Required Tools

```bash
# Install Rust
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
source ~/.cargo/env

# Install useful tools
rustup component add rust-src
cargo install bindgen cbindgen
```

## Phase 3: Build Commands

Once configured, you can use:
```bash
cargo build      # Compile the project
cargo run        # Run the project
cargo test       # Run tests (when you have them)
cargo doc        # Generate documentation
```

## Phase 4: Gradual Component Replacement

### Start with Independent Modules:
1. **File utilities** (ROM readers/writers)
2. **Conversion algorithms** (image, audio formats)
3. **Configuration systems** (INI, JSON parsers)
4. **CPU emulation** (6502) - but be careful about performance

### Example Rust Module Structure:
```
rust-components/
├── Cargo.toml
├── src/
│   ├── lib.rs
│   ├── cpu/
│   │   └── mod.rs
│   ├── rom/
│   │   └── mod.rs
│   └── utils/
│       └── mod.rs
```

Example `rust-components/Cargo.toml`:
```toml
[package]
name = "nesicide-core"
version = "0.1.0"
edition = "2021"

[lib]
crate-type = ["staticlib", "cdylib"]

[dependencies]
serde = { version = "1.0", features = ["derive"] }
serde_json = "1.0"
```

## Phase 5: Rust-C++ Integration Example

Example of Rust calling C++:
```rust
// src/rom/mod.rs
use std::ffi::{CStr, CString};
use std::os::raw::c_char;

#[no_mangle]
pub extern "C" fn load_rom(filename: *const c_char) -> *mut u8 {
    let c_str = unsafe { CStr::from_ptr(filename) };
    let filename_str = c_str.to_str().unwrap();
    
    // Your Rust logic here
    let data = std::fs::read(filename_str).unwrap();
    let ptr = data.as_ptr();
    std::mem::forget(data); // Careful: manual memory management
    ptr as *mut u8
}
```

## Phase 6: Complete Migration Path

1. **Phase 1**: Identify and isolate critical modules
2. **Phase 2**: Replace simple utilities (parsers, converters)
3. **Phase 3**: Migrate emulation modules (CPU, PPU)
4. **Phase 4**: Rewrite GUI with Rust library (e.g., Iced, Druid)
5. **Phase 5**: Remove Qt/C++ completely and use Cargo as sole build system

## Benefits of This Approach

- **Memory Safety**: Rust guarantees absence of memory leaks
- **Performance**: Comparable or superior to C++
- **Maintainability**: Better error handling and dependency management
- **Concurrency**: Race-free concurrency model

## Important Notes

- Start with a small module to validate the approach
- Maintain existing functionality during migration
- Use FFI carefully to avoid memory management issues
- Consider using `cxx` crate for safer C++/Rust interop
- Test thoroughly after each migration step

This approach allows you to modernize the project incrementally while maintaining existing functionality. Begin with the build system migration, then gradually replace components one by one.