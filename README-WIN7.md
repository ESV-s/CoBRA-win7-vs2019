# CoBRA на Windows 7 SP1 + Visual Studio 2019

## Что изменено относительно оригинала (trailofbits/CoBRA)

1. `std::expected` → `tl::expected` (backport C++23, single-header)
   - Файл `include/tl/expected.hpp` добавлен.
   - `include/cobra/core/Result.h` обновлён.
2. `std::unreachable()` → `__assume(false)` (C++23 → MSVC 19.29)
   - `lib/core/BitPartitioner.cpp`, `ExprUtils.cpp`, `SemilinearIR.cpp`.
3. `std::optional<Evaluator>` → `std::shared_ptr<Evaluator>` (обход бага линкера MSVC 19.29)
   - `lib/core/Orchestrator.h`, `OrchestratorPasses.h`, `ContinuationTypes.h`, `JoinState.h`, `SignatureSimplifier.h` и все `.cpp`.
4. `std::unexpected` → `tl::make_unexpected` в `Orchestrator.cpp`, `Result.h`.

## Как собрать

1. Abseil собрать с Windows SDK 8.1 (target 6.1.7601).
2. Highway 1.0.7 собрать и установить.
3. CoBRA собрать через CMake (`Visual Studio 16 2019`, x64, Release).
4. `CMAKE_PREFIX_PATH` = `<путь к Abseil install>;<путь к Highway install>`.

## Проверено

- `cobra-cli.exe --mba "(x&y)+(x|y)"` → `x + y`
- `cobra-cli.exe --mba "(x&0xFF)+(x&0xFF00)" --bitwidth 16` → `x`
- Работает на Windows 7 SP1.