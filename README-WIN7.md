# CoBRA на Windows 7 SP1 + Visual Studio 2019

Рабочая сборка CoBRA (trailofbits/CoBRA) для Windows 7 SP1 с Visual Studio 2019.
Проверено: `cobra-cli.exe` собирается и работает на Win7.

## Версии зависимостей

| Компонент | Версия | Откуда |
|-----------|--------|--------|
| **Abseil** | `20230125.0` | https://github.com/abseil/abseil-cpp/releases/tag/20230125.0 |
| **Google Highway** | `1.0.7` | https://github.com/google/highway/releases/tag/1.0.7 |
| **tl::expected** | master (single-header) | https://github.com/TartanLlama/expected |
| **Visual Studio** | 2019 (MSVC 19.29.30147.0) | — |
| **Windows SDK** | 8.1 (target 6.1.7601) | — |
| **CMake** | 3.28 | — |

## Что изменено относительно оригинала

1. `std::expected` → `tl::expected` (backport C++23, single-header)
   - Файл `include/tl/expected.hpp` добавлен.
   - `include/cobra/core/Result.h` обновлён.
2. `std::unreachable()` → `__assume(false)` (C++23 → MSVC 19.29)
   - `lib/core/BitPartitioner.cpp`, `ExprUtils.cpp`, `SemilinearIR.cpp`.
3. `std::optional<Evaluator>` → `std::shared_ptr<Evaluator>` (обход бага линкера MSVC 19.29)
   - `lib/core/Orchestrator.h`, `OrchestratorPasses.h`, `OrchestratorPasses.cpp`
   - `lib/core/ContinuationTypes.h`, `JoinState.h`
   - `include/cobra/core/SignatureSimplifier.h`
   - `lib/core/Orchestrator.cpp`, `DecompositionEngine.cpp`, `DecompositionPasses.cpp`
   - `lib/core/SemilinearPasses.cpp`, `SignaturePasses.cpp`, `LiftingPasses.cpp`
4. `std::unexpected` → `tl::make_unexpected` в `Orchestrator.cpp`, `Result.h`.

## Порядок сборки

### 1. Abseil 20230125.0

```cmd
cd D:\abseil-cpp-20230125.0
mkdir build && cd build
cmake -G "Visual Studio 16 2019" -A x64 ^
  -DCMAKE_INSTALL_PREFIX=D:\abseil-install ^
  -DCMAKE_CXX_STANDARD=17 ^
  -DABSL_PROPAGATE_CXX_STD=ON ^
  -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
cmake --install . --config Release