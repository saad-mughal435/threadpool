# threadpool

A small, **header-only C++17 thread pool**. Submit any callable and get a
`std::future` for its result; exceptions thrown inside a task surface when you
call `.get()`.

[![CI](https://github.com/saad-mughal435/threadpool/actions/workflows/ci.yml/badge.svg)](https://github.com/saad-mughal435/threadpool/actions/workflows/ci.yml)

## Highlights

- **One header** (`include/tp/thread_pool.hpp`) — drop it in, link `Threads`.
- `submit(f, args...)` returns `std::future<result_of_f>` (perfect-forwarded).
- **Exception-safe**: a throwing task rethrows from `future::get()`.
- **Graceful shutdown**: the destructor *drains the queue* — every submitted
  task runs to completion before it returns.
- Classic mutex + condition-variable design; copy/assignment disabled.

## Use it

```cpp
#include <tp/thread_pool.hpp>

tp::ThreadPool pool;                       // hardware_concurrency workers
auto f  = pool.submit([](int a, int b){ return a + b; }, 2, 3);
auto g  = pool.submit([]{ return std::string("done"); });
int sum = f.get();                         // 5
```

## Build, test, run the demo

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
ctest --test-dir build --output-on-failure
./build/tp_demo
```

Requires CMake ≥ 3.16 and a C++17 compiler. Tests use
[Catch2](https://github.com/catchorg/Catch2) (fetched automatically).

The test suite covers result delivery, 1000-task throughput, a parallel range
sum, exception propagation, and the drain-on-destruct guarantee.

## License

MIT © Muhammad Saad
